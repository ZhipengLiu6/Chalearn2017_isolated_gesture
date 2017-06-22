#coding:utf-8
"""
function:The program is a simple tutorial which teach how to get subfile name
input:an absolute path
output:sorted subfile list
author:zhipengliu
data:2016-7-18
"""
import os, sys
def GetSubfileName(path):
    dirs = os.listdir(path)
    dirs.sort()
    return dirs
