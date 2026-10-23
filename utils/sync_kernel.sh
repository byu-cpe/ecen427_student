#!/bin/bash

# Copy your kernel/ directory up to the PYNQ board, so you can edit code on
# your computer and build it on the board.
#
# By default this script KEEPS RUNNING and re-copies your files every time you
# save.  Leave it open in its own terminal while you work, and press Ctrl+C
# when you're done.
#
#   ./utils/sync_kernel.sh          Keep syncing until you press Ctrl+C.
#   ./utils/sync_kernel.sh once     Copy one time, then exit.
#   ./utils/sync_kernel.sh test     Show what WOULD be copied/deleted, but
#                                   don't actually change anything.


##############################################################################
# STUDENTS: Edit these two settings to match your setup.
##############################################################################

# The hostname or IP address of your PYNQ board.
BOARD_HOSTNAME=""

# The full path to the kernel directory ON THE BOARD, for example
# /home/byu/ecen427/kernel.  This is where your files will be copied to.  It
# must end in /kernel: anything on the board in this directory that isn't on
# your computer gets deleted.
BOARD_KERNEL_DIR=""

##############################################################################
# You shouldn't need to change anything below this line.
##############################################################################


# Every PYNQ board uses the "byu" account, so this never needs to change.
BOARD_USER="byu"

# The kernel directory on YOUR computer.  This script lives in utils/, so the
# kernel directory is one level up.
MY_KERNEL_DIR="$(dirname "$0")/../kernel"

# How often to check for changes, in seconds.
CHECK_EVERY=2

# Read the command line argument ("once", "test", or nothing at all).
MODE="$1"

# Files we do NOT want to copy.  These are all files created by the compiler
# when you build.  Skipping them means we never overwrite (or delete) the
# files the board just built.
SKIP="--exclude=*.o --exclude=*.ko --exclude=*.mod --exclude=*.mod.c
      --exclude=*.d --exclude=*.cmd --exclude=*.symvers
      --exclude=modules.order --exclude=modules.builtin*
      --exclude=.tmp_versions --exclude=*.swp --exclude=.git"

# Because we reconnect over and over, we tell ssh to keep one connection open
# and reuse it.  Without this, every check would need a brand new login, which
# takes about a second.
REUSE="ssh -o ControlMaster=auto -o ControlPath=/tmp/sync_kernel_%h -o ControlPersist=60"


# Copy the files up to the board.
#
# The rsync options mean:
#   -a           copy the whole directory, keeping timestamps and permissions
#   -z           compress the data while sending it (faster over the network)
#   --delete     if you delete a file on your computer, delete it on the board
#   --out-format print each file we actually copy (and stay silent otherwise)
copy_files() {
    rsync -az --delete --out-format="  updated %n" $EXTRA $SKIP -e "$REUSE" \
        "$MY_KERNEL_DIR/" "$BOARD_USER@$BOARD_HOSTNAME:$BOARD_KERNEL_DIR/"
}

# Runs when you press Ctrl+C.  Closes the shared ssh connection on the way out.
stop_syncing() {
    echo ""
    echo "Stopped syncing.  Your files on the board are up to date."
    ssh -o ControlPath=/tmp/sync_kernel_%h -O exit \
        "$BOARD_USER@$BOARD_HOSTNAME" 2> /dev/null
    exit 0
}


# Catch the most common mistake: forgetting to fill in the settings above.
if [ -z "$BOARD_HOSTNAME" ] || [ -z "$BOARD_KERNEL_DIR" ]; then
    echo "Please edit $0 and set BOARD_HOSTNAME and BOARD_KERNEL_DIR."
    exit 1
fi

# Because of --delete, pointing this at the wrong directory (say, your whole
# repo) would wipe everything in it except kernel/.  Only sync to a kernel
# directory.
BOARD_KERNEL_DIR="${BOARD_KERNEL_DIR%/}"
if [ "$(basename "$BOARD_KERNEL_DIR")" != "kernel" ]; then
    echo "BOARD_KERNEL_DIR must end in /kernel (it is $BOARD_KERNEL_DIR)."
    exit 1
fi

# In "test" mode, add rsync's --dry-run option so nothing actually changes.
EXTRA=""
if [ "$MODE" = "test" ]; then
    EXTRA="--dry-run"
    echo "TEST MODE: nothing will actually be copied."
fi

echo "Copying kernel files to $BOARD_USER@$BOARD_HOSTNAME:$BOARD_KERNEL_DIR"

copy_files
if [ $? -ne 0 ]; then
    echo "Copy failed.  Can you connect with 'ssh $BOARD_USER@$BOARD_HOSTNAME'?"
    exit 1
fi

# For "once" and "test", we're finished.
if [ "$MODE" = "once" ] || [ "$MODE" = "test" ]; then
    echo "Done."
    exit 0
fi


##############################################################################
# Keep running, copying every time a file changes, until Ctrl+C.
##############################################################################

# From here on, Ctrl+C runs stop_syncing() instead of killing us abruptly.
trap stop_syncing INT

echo ""
echo "----------------------------------------------------------------"
echo " Watching for changes.  Edit your files and they'll be copied"
echo " to the board automatically."
echo ""
echo " Leave this window open.  Press Ctrl+C when you are done."
echo "----------------------------------------------------------------"

if command -v inotifywait > /dev/null; then
    # inotifywait waits (using no CPU) until a file changes.  It keeps running
    # (-m) and prints a line per change, so a save made while a copy is in
    # progress is still noticed.
    inotifywait -m -q -r -e modify,create,delete,move --format x "$MY_KERNEL_DIR" |
    while read -r _; do
        # One save can cause several changes; let them settle, then copy once.
        while read -r -t 0.2 _; do :; done
        copy_files
    done
else
    # inotifywait isn't installed, so just check every couple of seconds.
    echo "(Tip: 'sudo apt install inotify-tools' makes changes copy instantly.)"
    while true; do
        sleep $CHECK_EVERY
        copy_files
    done
fi
