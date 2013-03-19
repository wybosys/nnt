#!/usr/bin/env python

import sys

dpi = 160

def func():
    if (len(sys.argv) != 2):
        return "please inpute value"
    return dpi * float(sys.argv[1]) / 72

print func()
