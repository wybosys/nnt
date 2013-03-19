#!/usr/bin/env python

from ctypes import *

dl = None

def ut_add(mod, suit):
    # create case.
    mod.restype = c_void_p
    case = mod()
    # add case to suit.
    func_add = dl.UTSuiteAddCase;
    func_add.argtypes = [ c_void_p, c_void_p ]
    func_add(case, suit)
    # drop case.
    func_drop = dl.Drop
    func_drop.argtypes = [ c_void_p ]
    func_drop(case)

def ut_store(suit):
    ut_add(dl.UTBdb, suit)
    ut_add(dl.UTMssql, suit)

def ut_main(path):
    global dl
    dl = CDLL(path)
    # create suit.
    func_suit = dl.UTSuiteDefault
    func_suit.restype = c_void_p
    suit = func_suit()
    # add suit
    ut_store(suit)
    # run suit.
    func_run = dl.UTSuiteRun
    func_run.argtypes = [ c_void_p ]
    func_run(suit)
    # free suit.
    func_free = dl.UTSuiteFree
    func_free.argtypes = [ c_void_p ]
    func_free(suit)

target = raw_input("name: ")
ut_main(target)
