#!/usr/bin/python

# Why Python, you ask? Because I'm assuming most people have Python installed
# these days, and if they're on Windows, they may not have Make installed.
# So, yeah.

import sys
import os

# Parameters
elf = "out.elf"
hex = "out.hex"
sep = os.path.sep

# Print usage
def printUsage():
    print("Usage: python ", sys.argv[0], " <path/to/avr-code.c>")

# Arg check
if len(sys.argv) - 1 != 1:
    print("ERROR: Incorrect number of arguments")
    printUsage()
    exit()
    
# Provide help
if (sys.argv[1] == '-h') or (sys.argv[1] == '--help'):
    printUsage()
    exit()
    
# Parse arguments
full_path = sys.argv[1]
path_file = os.path.split(full_path)
path = path_file[0]
file = path_file[1]
    
# Compile
cmd = "avr-gcc -Os -mmcu=attiny84 -o " + path + sep + elf + " " + full_path
print(cmd)
ret = os.system(cmd)
if ret != 0:
    exit()

# Create hex file
cmd = "avr-objcopy -j .text -j .data -O ihex " + path + sep + elf + " " + \
        path + sep + hex
print(cmd)
ret = os.system(cmd)
if ret != 0:
    exit()

# Upload to ATtiny84
cmd = "avrdude -c usbtiny -p t84 -U flash:w:" + path + sep + hex
print(cmd)
ret = os.system(cmd)
if ret != 0:
    exit()

