# CSC6522 Final Project

Final project for CSC6522 Topics in Operating Systems course at
Mississippi College by Michael Clement.

The project consists of a character driver linux kernel module that,
when fed characters by a userspace program, returns the ROT13 character
value.

This kernel module was written and tested in Ubuntu 18.04. Use of the userspace
interface application requires Python3.

# Usage
## Standalone Character Driver
- Ensure that the proper kernel header files are installed by running
`sudo apt install linux-headers-$(uname -r)` 
- Clone this repository and `cd` into the `driver` directory 
- Using the included Makefile, run `make`. This will build the
  driver, insert it into the kernel, and give read/write priveleges
  to all users.
- At this point, sending a single char to the device will return the ROT13
  value of that character, i.e. `echo -n "a" > /dev/cdnull | cat /dev/cdnull` 
  (result will be 'n')
- When finished, run `make clean` to unload the module and remove the compiled
  files.

## Using Python userApp.py for more user-friendly interaction 
- in the `driver` directory, run `python userApp.py` to start up the python
  script. This will run the makefile and insert the module into the kernel.
  Once the module is inserted, the user will be prompted to send a string to
  the kernel.
- Sending a string of characters will return the ROT13 version, as processed
  by the kernel module.
- Press `ctrl+c` to quit. The python script will automatically run `make
clean`.

## Resources
Tutorial/documentation resources gleaned from:
- https://linux-kernel-labs.github.io/
- https://sysplay.in
- https://www.tecmint.com/install-kernel-headers-in-ubuntu-and-debian/
