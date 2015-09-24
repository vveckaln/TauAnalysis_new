#!/usr/bin/env python
import os,sys,time
import json
import optparse
import commands
import LaunchOnCondor
import LIP.TauAnalysis.storeTools_cff as storeTools

PROXYDIR = "~/x509_user_proxy"
DatasetFileDB = "DAS"  #DEFAULT: will use das_client.py command line interface
#DatasetFileDB = "DBS" #OPTION:  will use curl to parse https GET request on DBSserver



"""
Gets the value of a given item
(if not available a default value is returned)
"""
def getByLabel(proc, key, defaultVal = None) :
    try :
        return proc[key]
    except KeyError:
        return defaultVal

initialCommand = '';
def initProxy():
   global initialCommand
   validCertificate = True
   if(validCertificate and (not os.path.isfile(os.path.expanduser(PROXYDIR + '/x509_proxy')))):
       validCertificate = False
       print "False step 1"
   if(validCertificate and (time.time() - os.path.getmtime(os.path.expanduser(PROXYDIR + '/x509_proxy'))) > 600): 
       validCertificate = False
       print "False step 2"
   if(validCertificate and int(commands.getstatusoutput('(export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy;voms-proxy-init --noregen;voms-proxy-info --all) | grep timeleft | tail -n 1')[1].split(':')[2]) < 8 ):
       validCertificate = False
       print "False step 3"
   if(validCertificate):
       print "Certicate valid"

   if(not validCertificate):
      print "You are going to run on a sample over grid using either CRAB or the AAA protocol, it is therefore needed to initialize your grid certificate"
#      os.system('mkdir -p ~/x509_user_proxy; voms-proxy-init --voms cms -valid 192:00 --out ~/x509_user_proxy/x509_proxy')#all must be done in the same command to avoid environement problems.  Note that the first sourcing is only needed in Louvain
#      os.system('voms-proxy-init --voms cms -valid 192:00')
      os.system('mkdir -p '+PROXYDIR+'; voms-proxy-init --voms cms             -valid 720:00 --out '+PROXYDIR+'/x509_proxy')
   initialCommand = 'export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy; voms-proxy-init --voms cms --noregen; '

#   initialCommand = 'export X509_USER_PROXY=' + PROXYDIR + '/x509_proxy;voms-proxy-init --voms cms --noregen; '

#configure
usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-e', '--exe'        ,    dest = 'theExecutable'      , help = 'excecutable'                           , default = '')
parser.add_option('-j', '--json'       ,    dest = 'samplesDB'          , help = 'samples json file'                     , default = '')
parser.add_option('-d', '--dir'        ,    dest = 'indir'              , help = 'input directory or tag in json file'   , default = 'aoddir')
parser.add_option('-o', '--out'        ,    dest = 'outdir'             , help = 'output directory'                      , default = '')
parser.add_option('-c', '--cfg'        ,    dest = 'cfg_file'           , help = 'base configuration file template'      , default = '')
parser.add_option('-s', '--sub'        ,    dest = 'queue'              , help = 'batch queue OR "crab" to use crab3'    , default = '8nh')
parser.add_option('-t', '--test'       ,    dest = 'debug'              , help = 'small runs for test and debugging'     , default = False)
parser.add_option('-r', '--run'        ,    dest = 'run_option'         , help = 'run option'                            , default = 'process')
parser.add_option('-R', '--R'          ,    dest='requirementtoBatch'   , help = 'requirement for batch queue'           , default = 'pool>30000')
(opt, args) = parser.parse_args()
(opt, args) = parser.parse_args()
scriptFile=os.path.expandvars('${CMSSW_BASE}/bin/${SCRAM_ARCH}/wrapLocalAnalysisRun.sh')
FarmDirectory                      = opt.outdir + "/FARM"
PROXYDIR                           = FarmDirectory + "/inputs" 
initProxy()
JobName                            = opt.theExecutable
LaunchOnCondor.Jobs_RunHere        = 1
LaunchOnCondor.Jobs_Queue          = opt.queue
LaunchOnCondor.Jobs_LSFRequirement = '"' + opt.requirementtoBatch + '"'
#LaunchOnCondor.Jobs_EmailReport    = opt.report
LaunchOnCondor.Jobs_InitCmds       = ['ulimit -c 0;']  #disable production of core dump in case of job crash
LaunchOnCondor.Jobs_InitCmds      += [initialCommand]
LaunchOnCondor.SendCluster_Create(FarmDirectory, JobName + '_test')
if(LaunchOnCondor.subTool == 'crab'):
    LaunchOnCondor.Jobs_CRABDataset  = FileList[0]
    LaunchOnCondor.Jobs_CRABcfgFile  = cfgfile
    LaunchOnCondor.Jobs_CRABexe      = opt.theExecutable
    if(commands.getstatusoutput("whoami")[1] == 'viesturs'):
        LaunchOnCondor.Jobs_CRABStorageSite = 'T2_PT_NCG_Lisbon'
    else:
        LaunchOnCondor.Jobs_CRABStorageSite = 'T2_CH_CERN'
        LaunchOnCondor.Jobs_CRABname     = dtag
        LaunchOnCondor.Jobs_CRABInDBS    = getByLabel(procData, 'dbsURL', 'global')
        LaunchOnCondor.Jobs_CRABUnitPerJob = 100 / split 
LaunchOnCondor.SendCluster_Push(["BASH", opt.theExecutable])
LaunchOnCondor.SendCluster_Submit()





