"""
Author: Michael Clement

This program is an interactive prompt for sending
characters to the character driver kernel module.

The kernel module takes the characters and performs
a simple ROT13 on them, returning the new value which
is then displayed to the user.

This is just meant to make it easy to interact with
it and demonstrate that the kernel module actually
loads and works.
"""

import os

def make():
    """
    Calls the make function to build
    and insert the device driver module.
    """
    os.system('make')
    print("Made.")


def invoke_kernel_module(string):
    """
    This function takes a user string
    and invokes the kernel module char
    driver to get the ROT13 value and
    return it.
    """

    # This will hold the output of the kernel ROT
    rot_string = ""
    
    print(f"Sending {string} to kernel for rotation.")
    for char in str.lower(string):
        cmd = f'echo -n "{char}" > /dev/cdnull | cat /dev/cdnull'
        stream = os.popen(cmd)
        rot_string += stream.read()

    return rot_string
        

def send_chars():
    """
    This is the main loop that the user
    interacts with to send chars to the
    character device driver.
    """
    loop = True
    while loop:
        try:
            print("\n---- Press CTRL-C to quit ----")
            print("  Enter a string to convert:  ")
            user_string = input()
            rot = invoke_kernel_module(user_string)
            # Show the result
            print("Rotated string: ", rot, "\n")
        except KeyboardInterrupt:
            print("\nExiting...")
            # Exit loop if they press ctrl-c
            loop = False


if __name__=="__main__":
    make()
    # start the main loop
    send_chars()
