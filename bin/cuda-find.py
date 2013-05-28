#!/usr/bin/env python

import os, re

def find_macos(base):
    if (os.path.exists(base) == False):
        return None
    pat = re.compile("CUDA-(.+)")
    allver = []
    for dir in os.listdir(base):
        full = base + dir
        if (os.path.isdir(full) == False):
            continue
        vers = pat.findall(dir)
        if (len(vers) == 0):
            continue
        ver = vers[0]
        allver.append(ver)
    allver = sorted(allver)
    return base + "CUDA-" + allver[-1]

def main():
    dir = find_macos("/Developer/NVIDIA/")
    if (dir != None):
        return dir
    return ""

print(main())
