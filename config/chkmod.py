#!/usr/bin/python

import os
import sys

ksyms = ["mcount", "printk", "strlen"]

mod = sys.argv[1]
nms = os.popen("nm -u " + mod).read().split('\n')

usyms = []
for each in nms:
    if (len(each) == 0):
        continue
    sym = each[each.find("U ") + 2:]
    if (sym not in ksyms):
        usyms.append(sym)

for each in usyms:
    print(each)
