#!/usr/bin/env python
import subprocess
import os
PROXYDIR="/lustre/ncg.ingrid.pt/cmslocal/viesturs/RunII/FARM/inputs"
cmd='mkdir -p ' + PROXYDIR + '; voms-proxy-init --voms cms             -valid 720:00 --out ' + PROXYDIR + '/x509_proxy'
print cmd
#cr = subprocess.check_output(cmd)
#os.system(cmd)
out=subprocess.check_output(cmd, shell=True)
#out,err = cr.communicate()
print "output\n", out
if out.find("Hello") > -1:
    print "hey"
