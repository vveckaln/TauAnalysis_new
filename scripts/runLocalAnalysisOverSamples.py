#!/usr/bin/env python
import os,sys
import json
import optparse
import commands
import LaunchOnCondor
"""
Gets the value of a given item
(if not available a default value is returned)
"""
def getByLabel(desc,key,defaultVal=None) :
    try :
        return desc[key]
    except KeyError:
        return defaultVal


#configure
usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-e', '--exe'        ,    dest = 'theExecutable'      , help = 'excecutable'                           , default = '')
parser.add_option('-j', '--json'       ,    dest = 'samplesDB'          , help = 'samples json file'                     , default = '')
parser.add_option('-d', '--dir'        ,    dest = 'indir'              , help = 'input directory or tag in json file'   , default = 'aoddir')
parser.add_option('-o', '--out'        ,    dest = 'outdir'             , help = 'output directory'                      , default = '')
parser.add_option('-c', '--cfg'        ,    dest = 'cfg_file'           , help = 'base configuration file template'      , default = '')
parser.add_option('-s', '--sub'        ,    dest = 'queue'              , help = 'batch queue'                           , default = '')
parser.add_option('-t', '--test'       ,    dest = 'debug'              , help = 'small runs for test and debugging'     , default = False)
parser.add_option('-r', '--run'        ,    dest = 'run_option'         , help = 'run option'                            , default = 'process')

(opt, args) = parser.parse_args()
if (opt.run_option == 'hadd') :
    opt.indir += '/output_files/event_analysis'
FarmDirectory = opt.outdir+"/FARM"
JobName = opt.theExecutable
LaunchOnCondor.Jobs_RunHere = 1
LaunchOnCondor.Jobs_Queue = opt.queue
LaunchOnCondor.Jobs_LSFRequirement = '"' + 'pool>30000' + '"'
LaunchOnCondor.Jobs_EmailReport = False
LaunchOnCondor.SendCluster_Create(FarmDirectory, JobName)

split=1
segment=0
                                        
#open the file which describes the sample
jsonFile = open(opt.samplesDB, 'r')
procList = json.load(jsonFile, encoding = 'utf-8').items()

#run over sample
for proc in procList :
    #run over processes
    for desc in proc[1] :

        #run over items in process
        isdata      = getByLabel(desc, 'isdata', False)
        mctruthmode = getByLabel(desc, 'mctruthmode', 0)
        data        = desc['data']
        for d in data :
            origdtag = getByLabel(d,'dtag','')
            xsec     = getByLabel(d,'xsec',-1)
            br       = getByLabel(d,'br',[])
            split    = getByLabel(d,'split',1)
                          
            if (xsec > 0 and not isdata) :
                for ibr in br :  xsec = xsec*ibr
            split_store = split
            if (opt.debug) :
                split = 1
            if (opt.queue == '') :
                split = 1  
            if (opt.run_option == 'hadd') :
                split = 1
            for segment in range(0, split) :
                
                if (not opt.run_option == "hadd") :
                    if (split_store == 1) :
                        eventsFile = '\'' + opt.indir + '/' + origdtag + '.root\''
                    else :
                        eventsFile = '\'' + opt.indir + '/' + origdtag + '_' + str(segment) + '.root\''
                else:
                        eventsFile = '\'' + opt.indir + '/' + origdtag + '\''
                   
                #create the cfg file
                sedcmd = 'sed \"'

                sedcmd += 's%@input%'        + eventsFile       + '%;'
                sedcmd += 's%@outdir%'       + opt.outdir       + '%;'
                sedcmd += 's%@isData%'       + str(isdata)      + '%;'
                sedcmd += 's%@xsec%'         + str(xsec)        + '%;'
                sedcmd += 's%@debug%'        + str(opt.debug)   + '%;'
                sedcmd += 's%@mctruthmode%'  + str(mctruthmode) + '%;'
                sedcmd += 's%@file_split%'   + str(split_store) + '%;'
                sedcmd += 's%@segment%'      + str(segment)     + '%;'

                sedcmd += '\"'
                if (opt.run_option == 'process') :
                    cfgfile = opt.outdir +'/configuration_files/event_analysis/' + origdtag + '_' + str(segment) + '_cfg.py'
                if (opt.run_option == 'hadd') :
                    cfgfile = opt.outdir +'/configuration_files/hadd/' + origdtag + '_' + str(segment) + '_cfg.py'

                os.system('cat ' + opt.cfg_file + ' | ' + sedcmd + ' > ' + cfgfile)

            #run the job

                if len(opt.queue) == 0 :
                    os.system(opt.theExecutable + 
                              ' ' + cfgfile + 
                              ' ' + str(opt.run_option)
                              )
                else :
                    LaunchOnCondor.SendCluster_Push(["BASH", str(opt.theExecutable + 
                                                                 ' ' + cfgfile + 
                                                                 ' ' + str(opt.run_option)
                                                                 )
                                                                ])
                #raw_input('press Enter')
LaunchOnCondor.SendCluster_Submit()                
