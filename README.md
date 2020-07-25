# csc6522
Repo for final project of CSC6522 Operating Systems course at Mississippi College.

The goal of this repo is to write a device driver for a 32GB USB stick that 
enables transfer of data between the computer and the stick.

Currently, there are two drivers. The first is a working character
device that prints out the last character fed into it. The other is
a driver for the Samsung USB flash drive.

Both of these were taken from examples on https://sysplay.in.

## Character Driver (clementDriver)
- Compile by running `make`
- Insert the module with `sudo insmod clementDriver.ko`
- Give read/write perms to everyone: `sudo chmod ugo+rw /dev/mynull`
- Write to it (leaving off the newline char): `echo -n "test" > /dev/mynull` 
- Read from it: `cat /dev/mynull` (should see the final 't' from our message)
- Unload the module by running `sudo rmmod clementDriver.ko`

## Flash Drive Driver (pen_driver) 
- `sudo rmmod usb-storage` to remove the main USB storage module so it won't
intercept the Samsung drive when inserted (may need to reboot the computer
with the USB drive disconnected if it's not working).
- `sudo insmod pen_driver.ko`
- plug in the flash drive
- run `dmesg` to check that it reacted to the drive plugging in
- Write to flash drive: `echo -n "test" > /dev/pen<MINOR NUMBER>`
- Read (doesn't work yet): `cat /dev/pen<MINOR NUMBER>`
- `sudo rmmod pen_register.ko` to remove module.
