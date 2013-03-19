#!/usr/bin/env python

tgt = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']

for i in tgt:
    tmp = ""
    for j in tgt:
        if i == '0':
            tmp += "'" + j + "', "
        else:
            tmp += "'" + i + j + "', "
    print tmp
