# csc6522
Repo for final project of CSC6522 Operating Systems course at Mississippi College.

The goal of this repo is to write a device driver for a 32GB USB stick that 
enables transfer of data between the computer and the stick.

Currently, this is a working character device.

## Process
- Compile by running `make`
- Insert the module with `sudo insmod clementDriver.ko`
- Give read/write perms to everyone: `sudo chmod ugo+rw /dev/mynull`
- Write to it (leaving off the newline char): `echo -n "test" > /dev/mynull` 
- Read from it: `cat /dev/mynull` (should see the final 't' from our message)
- Unload the module by running `sudo rmmod clementDriver.ko`
