#!/usr/bin/env python

import sys

with open(sys.argv[1], 'rb') as f:
    byte = f.read(1)
    output = ""
    while byte != "":
        output += '0x%x,' % ord(byte)
        byte = f.read(1)
    print output
