#!/usr/bin/env python
import os,sys,time
import json
import optparse
import commands
import LaunchOnCondor
import LIP.TauAnalysis.storeTools_cff as storeTools


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
   if(validCertificate and (not os.path.isfile(os.path.expanduser('~/x509_user_proxy/x509_proxy')))):
       validCertificate = False
       print "False step 1"
   if(validCertificate and (time.time() - os.path.getmtime(os.path.expanduser('~/x509_user_proxy/x509_proxy'))) > 600): 
       validCertificate = False
       print "False step 2"
   if(validCertificate and int(commands.getstatusoutput('(export X509_USER_PROXY=~/x509_user_proxy/x509_proxy;voms-proxy-init --noregen;voms-proxy-info -all) | grep timeleft | tail -n 1')[1].split(':')[2]) < 8 ):
       validCertificate = False
       print "False step 3"

   if(not validCertificate):
      print "You are going to run on a sample over grid using either CRAB or the AAA protocol, it is therefore needed to initialize your grid certificate"
      os.system('mkdir -p ~/x509_user_proxy; voms-proxy-init --voms cms -valid 192:00 --out ~/x509_user_proxy/x509_proxy')#all must be done in the same command to avoid environement problems.  Note that the first sourcing is only needed in Louvain
   initialCommand = 'export X509_USER_PROXY=~/x509_user_proxy/x509_proxy;voms-proxy-init --noregen; '


def getFileList(procData):
   FileList = [];
   miniAODSamples = getByLabel(procData, 'miniAOD', '')
   isMINIAODDataset = ("/MINIAOD" in getByLabel(procData, 'dset', '')) or  ("amagitte" in getByLabel(procData,'dset',''))
   print "Is miniAODDataset %s" % isMINIAODDataset
   split = getByLabel(procData, 'split', 1)

   if(isMINIAODDataset or len(getByLabel(procData, 'miniAOD', '')) > 0):
      instance = ""
      if(len(getByLabel(procData, 'dbsURL', '')) > 0): instance =  "instance=prod/" + getByLabel(procData, 'dbsURL', '')
      print "Going to get sites"
      listSites = commands.getstatusoutput('das_client.py --query="site dataset=' + getByLabel(procData, 'dset', '') + ' ' + instance + ' | grep site.name,site.dataset_fraction " --limit=0')[1]
      print "Sites got"
      IsOnLocalTier = False
      for site in listSites.split('\n'):
         if(localTier != "" and localTier in site and '100.00%' in site):
            IsOnLocalTier =True
            print ("Sample is found to be on the local grid tier (%s): %s") %(localTier, site)
            break
      list = []
      if(IsOnLocalTier or isMINIAODDataset):
         list = []
         if(DatasetFileDB == "DAS"):
             list = commands.getstatusoutput('das_client.py --query="file dataset=' + getByLabel(procData, 'dset', '') + ' ' + instance + '" --limit=0')[1].split()
                          
         elif(DatasetFileDB == "DBS"):
            curlCommand = "curl -ks --key $X509_USER_PROXY --cert $X509_USER_PROXY -X GET "
            dbsPath     = "https://cmsweb.cern.ch/dbs/prod/global/DBSReader"
            sedTheList  = ' | sed \"s#logical_file_name#\\nlogical_file_name#g\" | sed \"s#logical_file_name\': \'##g\" | sed \"s#\'}, {u\'##g\" | sed \"s#\'}]##g\" | grep store '
            list        = commands.getstatusoutput(initialCommand + curlCommand + '"' + dbsPath + '/files?dataset=' + getByLabel(procData, 'dset', '') + '"' + sedTheList)[1].split()

         list = [x for x in list if ".root" in x] #make sure that we only consider root files
         for i in range(0, len(list)):  
            if IsOnLocalTier:
               list[i] = "root://eoscms//eos/cms" + list[i]
            else:
               list[i] = "root://cms-xrd-global.cern.ch/" + list[i] #works worldwide
              #list[i] = "root://xrootd-cms.infn.it/"+list[i]    #optimal for EU side
              #list[i] = "root://cmsxrootd.fnal.gov/"+list[i]    #optimal for US side

      elif(len(getByLabel(procData, 'miniAOD', '')) > 0):
         print "Processing private local sample: " + getByLabel(procData, 'miniAOD', '')
         list = storeTools.fillFromStore(getByLabel(procData, 'miniAOD', ''), 0, -1, True);                  
      else:
         print "Processing an unknown type of sample (assuming it's a private local sample): " + getByLabel(procData, 'miniAOD', '')
         list = storeTools.fillFromStore(getByLabel(procData, 'miniAOD', ''), 0, -1, True);

      list = storeTools.keepOnlyFilesFromGoodRun(list, getByLabel(procData, 'lumiMask', ''))    
      
      ngroup = len(list)/split
      if (ngroup * split != len(list) ):
          ngroup = ngroup + 1
      groupList = ''
      i = 0;
      while(i < len(list) ):
         groupList += '"' + list[i] + '",\\n';
         if(i > 0 and i % ngroup == 0):
            FileList.append(groupList)
            groupList = ''
         i = i + 1;               
      if groupList != '':
          FileList.append(groupList)
   else:
      for segment in range(0, split) :
         print "Processing a non EDM/miniAOD sample in : " + opt.indir + '/' + origdtag + '_' + str(segment) + '.root'
         eventsFile = opt.indir + '/' + origdtag + '_' + str(segment) + '.root'
         if(eventsFile.find('/store/') == 0)  : eventsFile = commands.getstatusoutput('cmsPfn ' + eventsFile)[1]
         FileList.append('"' + eventsFile + '"')
   return FileList

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
if (opt.run_option == 'hadd') :
    opt.indir += '/output_files/event_analysis'
print "opt.debug %s" % opt.debug
(opt, args) = parser.parse_args()
scriptFile=os.path.expandvars('${CMSSW_BASE}/bin/${SCRAM_ARCH}/wrapLocalAnalysisRun.sh')

FarmDirectory                      = opt.outdir + "/FARM"
JobName                            = opt.theExecutable
LaunchOnCondor.Jobs_RunHere        = 1
LaunchOnCondor.Jobs_Queue          = opt.queue
LaunchOnCondor.Jobs_LSFRequirement = '"' + opt.requirementtoBatch + '"'
#LaunchOnCondor.Jobs_EmailReport    = opt.report
LaunchOnCondor.Jobs_InitCmds       = ['ulimit -c 0;']  #disable production of core dump in case of job crash
LaunchOnCondor.Jobs_InitCmds      += [initialCommand]

#define local site
localTier = ""
hostname = commands.getstatusoutput("hostname -f")[1]
if(hostname.find("ucl.ac.be") != -1): localTier = "T2_BE_UCL"
if(hostname.find("cern.ch") != -1)  : localTier = "T2_CH_CERN"

initProxy()

#open the file which describes the sample
jsonFile = open(opt.samplesDB, 'r')
procList = json.load(jsonFile, encoding = 'utf-8').items()
#run over sample
for procData in procList :
    #run over processes
    for desc in procData[1] :
        #run over items in process
        isdata      = getByLabel(desc, 'isdata', False)
        mctruthmode = getByLabel(desc, 'mctruthmode', 0)
        data        = desc['data']
        for procData in data :
            origdtag = getByLabel(procData, 'dtag',  '')
            if(origdtag == '') : continue
            dtag = origdtag
            xsec     = getByLabel(procData, 'xsec',  -1)
            br       = getByLabel(procData, 'br',    [])
            init     = getByLabel(procData, 'init',   1)
            split    = getByLabel(procData, 'split',  1)
                   
            if (xsec > 0 and not isdata) :
                for ibr in br :  xsec = xsec*ibr
            split_store = split
            if (opt.debug) :
                split = 1
            if (opt.queue == '') :
                split = 1  
            if (opt.run_option == 'hadd') :
                split = 1
            FileList = ['"' + getByLabel(procData, 'dset', 'UnknownDataset') + '"']
            if(LaunchOnCondor.subTool != 'crab'):
                if (not opt.debug):
                    FileList = getFileList(procData)
                else:
                    FileList = ["\"/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_7_4_2/src/LIP/TauAnalysis/test/B09C2BE7-0509-E511-B6C7-20CF305B051B.root\",\\n"]
            print "FileList obtained"

            LaunchOnCondor.SendCluster_Create(FarmDirectory, JobName + '_' + dtag)

            for segment in range(0, len(FileList)) :

                if (not opt.run_option == "hadd") :
                    eventsFile = FileList[segment]
                    eventsFile = eventsFile.replace('?svcClass=default', '')
                else:
                        eventsFile = '\'' + opt.indir + '/' + origdtag + '\''
                   
                #create the cfg file

                sedcmd = 'sed \''
                sedcmd += 's%"@dtag"%"'      + dtag                                 + '"%;'
            	sedcmd += 's%"@input"%'      + eventsFile                           + '%;'
                sedcmd += 's%@outdir%'       + opt.outdir                           + '%;'
                sedcmd += 's%@isData%'       + str(isdata)                          + '%;'
                sedcmd += 's%@init%'         + str(init)                            + '%;'
                sedcmd += 's%@xsec%'         + str(xsec)                            + '%;'
                sedcmd += 's%@debug%'        + str(opt.debug)                       + '%;'
                sedcmd += 's%@mctruthmode%'  + str(mctruthmode)                     + '%;'
                sedcmd += 's%@file_split%'   + str(split_store)                     + '%;'
                sedcmd += 's%@segment%'      + str(segment)                         + '%;'
                sedcmd += 's%@lumiMask%"'    + getByLabel(procData, 'lumiMask', '') + '"%;'
                sedcmd += '\''
               
                if (opt.run_option == 'process') :
                    cfgfile = opt.outdir +'/configuration_files/event_analysis/' + origdtag + '_' + str(segment) + '_cfg.py'
                if (opt.run_option == 'hadd') :
                    cfgfile = opt.outdir + '/configuration_files/hadd/' + origdtag + '_' + str(segment) + '_cfg.py'

                os.system('cat ' + opt.cfg_file + ' | ' + sedcmd + ' > ' + cfgfile)

                #run the job
                if opt.queue == "0" :
                    print "launching"
                    os.system(opt.theExecutable + ' ' + cfgfile + ' ' + str(opt.run_option))
                else:
                    if(LaunchOnCondor.subTool == 'crab'):
                       LaunchOnCondor.Jobs_CRABDataset  = FileList[0]
                       LaunchOnCondor.Jobs_CRABcfgFile  = cfgfile
                       LaunchOnCondor.Jobs_CRABexe      = opt.theExecutable
                       if(commands.getstatusoutput("whoami")[1] == 'viesturs'):
                           LaunchOnCondor.Jobs_CRABStorageSite = 'T2_PT_NCG_Lisbon'
                       else:
                           LaunchOnCondor.Jobs_CRABStorageSite = 'T2_BE_UCL'
                       LaunchOnCondor.Jobs_CRABname     = dtag
                       LaunchOnCondor.Jobs_CRABInDBS    = getByLabel(procData, 'dbsURL', 'global')
                       LaunchOnCondor.Jobs_CRABUnitPerJob = 100 / split 
                       LaunchOnCondor.SendCluster_Push(["BASH", str(opt.theExecutable + ' ' + cfgfile)])
                if opt.debug:
                    break
            LaunchOnCondor.SendCluster_Submit()





