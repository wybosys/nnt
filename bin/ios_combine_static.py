#!/usr/bin/env python

import sys
product = ""

if (len(sys.argv) == 1):
    product = raw_input("please input product name: ")
else:
    product = sys.argv[1]

import getpass
cuser = getpass.getuser()

dir = "/Users/" + cuser + "/Library/Developer/Xcode/DerivedData/"

# find product.
import os
for each in os.listdir(dir):
    if (product in each):
        dir += each
        break

dir += "/Build/Products/"

dev_debug = dir + "/Debug-iphoneos/lib" + product + ".a"
dev_release = dir + "/Release-iphoneos/lib" + product + ".a"
sim_debug = dir + "/Debug-iphonesimulator/lib" + product + ".a"
sim_release = dir + "/Release-iphonesimulator/lib" + product + ".a"

import commands

cmds_debug = "lipo -create " + dev_debug + " " + sim_debug + " -output " + dir + product + "-d.a"
cmds_release = "lipo -create " + dev_release + " " + sim_release + " -output " + dir + product + "-r.a"

ret = commands.getstatusoutput(cmds_debug)
if (ret[0] != 0):
    print ret[1]

ret = commands.getstatusoutput(cmds_release)
if (ret[0] != 0):
    print ret[1]

cmds_fix = "lipo -remove i386 " + dir + product + "-r.a -output " + dir + product + "-r.a"
ret = commands.getstatusoutput(cmds_fix)
if (ret[0] != 0):
    print ret[1]

cmds_fix = "lipo -remove armv7 " + dir + product + "-d.a -output " + dir + product + "-d.a"
ret = commands.getstatusoutput(cmds_fix)
if (ret[0] != 0):
    print ret[1]

#cmds_fix = "lipo -remove armv7s " + dir + product + "-d.a -output " + dir + product + "-d.a"
#ret = commands.getstatusoutput(cmds_fix)
#if (ret[0] != 0):
#    print ret[1]

cmds_fix = "lipo -create " + dir + product + "-d.a " + dir + product + "-r.a" + " -output " + dir + "lib" + product + ".a" 
ret = commands.getstatusoutput(cmds_fix)
if (ret[0] != 0):
    print ret[1]

cmds_fix = "open " + dir
commands.getstatusoutput(cmds_fix)

