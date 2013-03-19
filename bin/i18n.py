#!/usr/bin/env python

import os
import re
import codecs

##find wsi's home directory by find .WSI_IDENTIFY file.
def find_wsi (tgtdir):
    wsi_path = ""
    if (os.path.exists(tgtdir + "/.WSI_IDENTIFY")):
        wsi_path = tgtdir + "/wsi"
    else:
        # find in parent dir.
        sup_dir = os.path.dirname(tgtdir)
        wsi_path = find_wsi(sup_dir)
        # find in sub dir.
        if (wsi_path == ""):
            for each in os.listdir(tgtdir):
                full_each = tgtdir + "/" + each
                if (os.path.isdir(full_each)):
                    wsi_path = find_wsi(full_each)
                    if (wsi_path != ""):
                        break
    return wsi_path

##select language.
def sel_language ():
    sel = ""
    langs = []
    # list all language.
    for each in os.listdir(os.path.curdir):
        full = "./" + each
        if (os.path.isdir(full) == False):
            continue
        data = os.path.splitext(each)
        if (data[1] == ".lproj"):
            langs = langs + [data[0]]
    idx = 0
    for each in langs:
        print idx, ": " + each
        idx += 1
    selidx = raw_input("select: ")
    if (selidx == ''):
        return sel
    selidx = int(selidx)
    sel = langs[selidx]
    return sel

def read_langfile (langfile):
    ret = {}
    if (os.path.exists(langfile) == False):
        print "error: file not found, " + langfile
        return ret
    fd = codecs.open(langfile, 'r', 'utf-8')
    pat = re.compile(r'"(.*)"\s*=\s*"(.*)";')
    for line in fd.readlines():
        res = pat.findall(line)
        if (len(res) == 1):
            ret[res[0][0]] = res[0][1]
    fd.close()
    return ret

pat_source = re.compile(r'(\.m|\.mm|\.cpp)$')
pat_w = re.compile(r'_W\(@"((?:[^=\(\)]|[.])*)"\)')
pat_tr = re.compile(r'tr\(@"((?:[^=\(\)]|[.])*)"\)')

## filter all source.
def readstore (tgtdir, store):
    for each in os.listdir(tgtdir):
        full_each = tgtdir + "/" + each
        if (os.path.isdir(full_each)):
            store = readstore(full_each, store)
        else:
            if (pat_source.search(each) == None):
                continue
            fd = open(full_each, 'r')
            for line in fd.readlines():
                res = pat_w.findall(line)
                for key in res:
                    if (store.has_key(key)):
                        continue;
                    else:
                        store[key] = ""
                res = pat_tr.findall(line)
                for key in res:
                    if (store.has_key(key)):
                        continue;
                    else:
                        store[key] = ""
            fd.close()
    return store

##translate
def translate (wsi, lang):
    file_path = "./" + lang + ".lproj/Localizable.strings"
    store = read_langfile(file_path)
    wsi_class = wsi + "/Classes"
    self_class = os.path.dirname(os.path.abspath(os.path.curdir))
    tgtstore = readstore(wsi_class, {})
    tgtstore = readstore(self_class, tgtstore)
    for key in tgtstore.keys():
        if store.has_key(key):
            continue;
        store[key] = ""
    for key,val in store.items():
        if (val == ''):
            str_input = raw_input(key + " = ")
            if str_input == '':
                #store[key] = key
                store[key] = None
            else:
                store[key] = unicode(str_input, 'utf-8')
    ##save
    fd = codecs.open(file_path, 'w', 'utf-8')
    for key, val in store.items():
        if (val == None):
            continue            
        try:
            line = '"' + key + '" = "' + val + '";\n'
            fd.write(line)
        except UnicodeDecodeError:
            print "skip one key."
    fd.close()
    pass

##main
def main():
    # find wsi.
    wsi_path = find_wsi(os.path.abspath(os.path.curdir))
    if (wsi_path == ""):
        print "error: can not find wsi"
        return
    else:
        print "wsi: " + wsi_path
    # select language.
    lang_id = sel_language()
    if (lang_id == ""):
        print "error: no language selected"
        return
    else:
        print "lang: " + lang_id
    # translate.
    translate(wsi_path, lang_id)
    pass

main()

raw_input("press enter to exit")
