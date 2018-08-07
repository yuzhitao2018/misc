#!/usr/bin/env python
#coding: utf8

import sys
sys.path.append("/export/jenkins/scripts")

import os, time, stat
import utils as UT

def file_st(file_name, st):
    return os.stat(file_name)[st]

time_now = int(time.time())
print "time_now=%d" % time_now

DAY_SEC=86400
GARBAGE=3*DAY_SEC

def CleanDir(dir_path):
    ls_list = UT.check_output("ls -lt %s" % dir_path, debug=0, out=0).splitlines()
    for line in ls_list:
        unit_list = line.split()
        if len(unit_list) < 9:
            continue

        file_name = os.path.join(dir_path, unit_list[8])
        file_mode = file_st(file_name, stat.ST_MODE)
        if stat.S_ISDIR(file_mode):
            continue

        c_time = file_st(file_name, stat.ST_CTIME)
        if time_now - c_time > GARBAGE:
            print "file:%s c_time=%d, time_now=%d" % (file_name, c_time, time_now)
              

DIR_PATH_LIST=["/export/jenkins/server_package_backup"]
DIR_PATH_LIST.append("/export/jenkins/workspace/sync_server_to_external/open_beta")
DIR_PATH_LIST.append("/export/jenkins/workspace/sync_server_to_external/hk_obn")


for DIR_PATH in DIR_PATH_LIST:
    CleanDir(DIR_PATH)



