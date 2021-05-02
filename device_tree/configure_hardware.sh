#!/bin/bash

# This script should be placed in /usr/local/sbin

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

# Create /configfs
if [ ! -d /configfs ]; then
    echo "Creating /configfs"
    mkdir /configfs
fi

# Mount
if ! mountpoint -q /configfs; then
    echo "Mounting /configfs"
    mount -t configfs configfs /configfs
fi

cd /configfs/device-tree/overlays/

# Remove existing hardware if it exists
if [ -d  "./full" ]; then
    echo "Removing existing hardware"
    rmdir ./full
fi

# Add new hardare
mkdir full

echo "Configuring hardware"
echo -n "ecen427.dtbo" > full/path
echo "Done"