#!/usr/bin/env python
#coding: utf8

import os
import time
import stat
import sys
import select
import subprocess

def file_st(file_name, st):
    return os.stat(file_name)[st]

def log(s):
    print s
    sys.stdout.flush()

def check_output(command, out=1, debug=0, tab=0, **kw):
    """本地执行
    """
    if debug:
        log("\t" if tab else "" + "Executing: %s" % command)

    p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, **kw)
    output = ""

    rlist = [p.stdout, p.stderr]
    while rlist:
        readable, _, _ = select.select(rlist, [], [])
        for r in readable:
            try:
                line = r.readline()
            except UnicodeDecodeError as e:
                log("SSH.check_output 有一行无法解析")
                continue
            if not line:
                rlist.remove(r)
                continue
            if out or r == p.stderr:
                log("\t" if tab else "" + line.strip("\n"))
            if r == p.stdout:
                output += line 
    p.wait() 
    if p.returncode != 0: 
        raise Exception(p.returncode) 
    return output

time_now = int(time.time())
print "time_now=%d" % time_now

DATE_SEC=86400

DIR_PATH="/export/yuzhitao/test/test_dir"

ls_list = check_output("ls -lt %s" % DIR_PATH, debug=0, out=0).splitlines()
for line in ls_list:
    unit_list = line.split()
    if len(unit_list) < 9:
        continue

    file_name = os.path.join(DIR_PATH, unit_list[8])
    file_mode = file_st(file_name, stat.ST_MODE)
    if stat.S_ISDIR(file_mode):
        continue

    c_time = fo.file_st(file_name, stat.ST_CTIME)
    #if time_now - c_time > DATE_SEC:
    if time_now - c_time > 10:
        print "file:%s c_time=%d, time_now=%d" % (file_name, c_time, time_now)
        #print check_output("rm %s" % file_name, debug=0, out=0)


