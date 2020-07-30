# csc6522
Repo for final project of CSC6522 Operating Systems course at Mississippi College.

Linux kernel module character driver that performs ROT13 (from in the kernel).

## Character Driver (with ROT13 functionality)
- Using the included Makefile, run `make`. This will build the
  driver, insert it into the kernel, and give read/write priveleges
  to all users.
- At this point, sending a single char to the device will return the ROT13
  value of that character, i.e. `echo -n "a" > /dev/cdnull | cat /dev/cdnull` 
  (result will be 'n')
- When finished, run `make clean` to unload the module and remove the compiled
  files.

## Resources
Tutorial/documentation resources gleaned from:
- https://linux-kernel-labs.github.io/
- https://sysplay.in
