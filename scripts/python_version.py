#!/usr/bin/env python
import sys
import commands
print (sys.version)
PROXYDIR="/lustre/ncg.ingrid.pt/cmslocal/viesturs/RunII/FARM/inputs"
print "1st \n %s" % commands.getoutput('(export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy;voms-proxy-init --noregen 2> /dev/null;voms-proxy-info --all)')
print "2nd \n %s" % commands.getoutput('(export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy;voms-proxy-init --noregen 2> /dev/null;voms-proxy-info --all 2> /dev/null) | grep timeleft')
print "3rd \n %s" % commands.getoutput('(export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy;voms-proxy-init --noregen 2> /dev/null;voms-proxy-info --all 2> /dev/null) | grep timeleft | tail -n 1').replace("timeleft  : ", "")
a = int(commands.getoutput('(export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy;voms-proxy-init --noregen 2> /dev/null;voms-proxy-info --all 2> /dev/null) | grep timeleft | tail -n 1').replace("timeleft  : ", "").split(':')[1]) 
print "a = %u" % a

b = int(commands.getstatusoutput('(export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy;voms-proxy-init --noregen 2> /dev/null;voms-proxy-info --all 2> /dev/null) | grep timeleft | tail -n 1')[1].split(':')[1]) 
print "b = %u" % b
