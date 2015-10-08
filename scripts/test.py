#!/usr/bin/env python
import subprocess
import os
import sys
PROXYDIR="/lustre/ncg.ingrid.pt/cmslocal/viesturs/RunII/FARM/inputs"
cmd='mkdir -p ' + PROXYDIR + '; voms-proxy-init --voms cms             -valid 720:00 --out ' + PROXYDIR + '/x509_proxy'
print cmd
#cr = subprocess.check_output(cmd)
#os.system(cmd)
while True:
    p=subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
#out,err=proc.communicate()
    totalout=''
    
    while True:
        out = p.stdout.readline()
        if out == '' and p.poll() != None:
            break
        if out:
            self.logger.info(out.strip())
            #sys.stdout.write(out)
        #    print "from here"
            #sys.stdout.flush()
            
    """
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
       
#print "output\n", out
#if out.find("Hello") > -1:
#    print "hey"
"""
