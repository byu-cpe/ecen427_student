#!/usr/bin/bash

if [ $# -ne 2 ]; 
    then echo "Usage: run_remote.sh remote-machine-name binary"
    exit 2
fi

if [ ! -f "$2" ]; then
    echo "$2 binary file does not exist."
    exit 2
fi

echo -n "Enter your sudo password on your PYNQ:"
read -s password
echo ""

filename="$(basename $2)"

echo "Copying $2 to byu@$1:~/temp/$filename"
ssh byu@$1 "mkdir -p ~/temp"
scp $2 byu@$1:~/temp/

echo "Running sudo ~/temp/$filename"
ssh -t byu@$1 "echo '$password$newline' | sudo -S ~/temp/$filename"