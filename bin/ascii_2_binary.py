#!/usr/bin/env python

i = 0;

while (i < 256):
    if i <= ord('f') and i >= ord('a'):
        print '0x' + chr(i) + ','
    elif i <= ord('F') and i >= ord('A'):
        print '0x' + chr(i) + ','
    elif i <= ord('9') and i >= ord('0'):
        print '0x' + chr(i) + ','
    else:
        print '0,'
    i += 1
