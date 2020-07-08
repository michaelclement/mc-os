# csc6522
Repo for final project of CSC6522 Operating Systems course at Mississippi College.

The goal of this repo is to write a device driver for a 32GB USB stick that 
enables transfer of data between the computer and the stick.

## Process
- Compile by running `make`
- load the module by running `sudo insmod clementDriver.ko`
- verify it loaded by running `lsmod`
- unload the module by running `sudo rmmod clementDriver.ko`
