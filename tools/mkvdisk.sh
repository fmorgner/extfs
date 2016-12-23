#!/bin/bash

# This script creates a 16Mb disk in a file

echo -n "Creating disk image..."
if dd if=/dev/zero of=vdisk.img bs=1M count=16 &>/dev/null; then
  echo " done"
  echo -n "Creating ext2 file system..."
  if mkfs.ext2 -L vdisk vdisk.img &>/dev/null; then
    echo " done"
  else
    echo " failed"
    exit 2
  fi
else
  echo " failed"
  exit 1
fi
