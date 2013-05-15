#!/usr/bin/python

import os
import sys

ksyms = ["mcount", "printk", "strlen", "__kmalloc", "kfree", "memcmp", "memcpy", "memset", "alloc_chrdev_region", "register_chrdev_region", "cdev_add", "cdev_init", "kmalloc_caches", "kmem_cache_alloc_trace", "__class_create", "device_create", "class_destroy", "device_destroy", "unregister_chrdev_region", "copy_from_user", "copy_to_user", "_cond_resched"]

mod = sys.argv[1]
nms = os.popen("nm -u " + mod).read().split('\n')

usyms = []
for each in nms:
    if (len(each) == 0):
        continue
    sym = each[each.find("U ") + 2:]
    if (sym not in ksyms):
        usyms.append(sym)

print('\n'.join(usyms))
