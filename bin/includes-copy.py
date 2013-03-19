#!/usr/bin/env python

import os
import re
import shutil

print("generator all include files for WSI library")

ignores = re.compile(r'.DS_Store|.svn|.git|_.+|^.+\.c$|^.+\.cpp$|^.+\.cxx$|^.+\.m$|^.+\.mm$|^.+\.png$|^.+\.jpg$|^.+\.jpeg$|^.+\.gif$|^.+\.css$|^.+\.prv.h$|^.+\.prv.hpp$|^.+\.res$')

workdir = os.getcwd()
if (re.compile(r'[\w/]+/bin$').match(workdir)):
    workdir = workdir[:-4]

classdir = workdir + '/Classes'
incdir = workdir + '/nnt'

def isabs(string):
    '''
    @return true if string is an absolute path or protocoladdress
    for addresses beginning in http:// or ftp:// or ldap:// -
    they are considered &quot;absolute&quot; paths.
    '''
    if protocolPattern.match(string): return 1
    return os.path.isabs(string)

def rel2abs(path, base = os.curdir):
    ''' converts a relative path to an absolute path.
    @param path the path to convert - if already absolute, is returned
    without conversion.
    @param base - optional. Defaults to the current directory.
    The base is intelligently concatenated to the given relative path.
    @return the relative path of path from base
    '''
    if isabs(path): return path
    retval = os.path.join(base,path)
    return os.path.abspath(retval)


def pathsplit(p, rest=[]):
    (h,t) = os.path.split(p)
    if len(h) < 1: return [t]+rest
    if len(t) < 1: return [h]+rest
    return pathsplit(h,[t]+rest)

def commonpath(l1, l2, common=[]):
    if len(l1) < 1: return (common, l1, l2)
    if len(l2) < 1: return (common, l1, l2)
    if l1[0] != l2[0]: return (common, l1, l2)
    return commonpath(l1[1:], l2[1:], common+[l1[0]])


def relpath(p1, p2):
    (common,l1,l2) = commonpath(pathsplit(p1), pathsplit(p2))
    p = []
    if len(l1) > 0:
        p = [ "../" * len(l1) ]
    p = p + l2
    if len(p) is 0:
        return '.'
    return os.path.join( *p )


def abs2rel(path, base = os.curdir):
    ''' @return a relative path from base to path.

    base can be absolute, or relative to curdir, or defaults
    to curdir.
    '''
    if protocolPattern.match(path): return path
    base = rel2abs(base)
    path = rel2abs(path) # redundant - should already be absolute
    return relpath(base, path)

# copy h file from class to inc
##mode = raw_input('select mode (0 link 1 copy): ')
mode = "1"
if (mode != '1'):
    mode = '0'

def process_mode (des, src, mode):
    for each in os.listdir(src):        
        if (ignores.match(each)):
            continue
        tmp_src = src + '/' + each;
        tmp_des = des + '/' + each;
        if (os.path.isdir(tmp_src)):
            if (not os.path.exists(tmp_des)):
                os.mkdir(tmp_des)
            process_mode(tmp_des, tmp_src, mode)
        else:
            if (mode == '0'): #link mode
                dir_des = os.path.dirname(tmp_des)
                dir_src = os.path.dirname(tmp_src)
                file_name = os.path.basename(tmp_src)
                tmp_dir = relpath(dir_des, dir_src) 
                str_inc = '# include "' + tmp_dir + '/' + file_name + '"'
                fd = open(tmp_des, 'w')
                fd.write(str_inc)
                fd.close()
            elif (mode == '1'): #copy mode
                shutil.copy(tmp_src, tmp_des)

process_mode(incdir, classdir, mode)

##raw_input('press any key to exit')
