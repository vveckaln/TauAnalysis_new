#!/usr/bin/env python
import subprocess
import os
import sys
import contextlib
PROXYDIR="/afs/cern.ch/work/v/vveckaln/private/RunII/FARM/inputs"
cmd='mkdir -p ' + PROXYDIR + '; voms-proxy-init --voms cms             -valid 720:00 --out ' + PROXYDIR + '/x509_proxy'

# Unix, Windows and old Macintosh end-of-line
while True:
    p=subprocess.Popen(cmd, shell=True, stderr=subprocess.PIPE)

#out,err=proc.communicate()
    totalerr=''
    while True:
    
        err = p.stderr.read(1)
        totalerr += err
        if err == '' and p.poll() != None:
            break
        if err != '':
            sys.stderr.write(err)
            #     print "from here"
            sys.stderr.flush()
    if totalerr.find("No credentials found!") == -1:
        break
       
