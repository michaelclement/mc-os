# csc6522
Repo for final project of CSC6522 Operating Systems course at Mississippi College.

Linux kernel module character driver.


## Character Driver (clementDriver)
- Compile by running `make`
- Insert the module with `sudo insmod clementDriver.ko`
- Give read/write perms to everyone: `sudo chmod ugo+rw /dev/mynull`
- Write to it (leaving off the newline char): `echo -n "test" > /dev/mynull` 
- Read from it: `cat /dev/mynull` (should see the final 't' from our message)
- Unload the module by running `sudo rmmod clementDriver.ko`


Based on examples from tutorials on https://sysplay.in.
