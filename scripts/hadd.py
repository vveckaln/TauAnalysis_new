#!/usr/bin/env python
import os,sys
import json
import optparse
import commands

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
(opt, args) = parser.parse_args()

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

        data = desc['data']
        for d in data :
            origdtag = getByLabel(d,'dtag','')
            print('dtag = %s'% origdtag)
            xsec = getByLabel(d,'xsec',-1)
            br = getByLabel(d,'br',[])
                          
            if(xsec>0 and not isdata) :
                for ibr in br :  xsec = xsec*ibr
            split=getByLabel(d,'split',1)
            resultsFiles = ''
	    for segment in range(0, split) :
                
                resultsFiles +='\'' + opt.outdir + '/output_files/output_event_analysis/' + origdtag + '_' + str(segment) + '_out.root\''
                if segment < split -1:
                    resultsFiles += ', '
                
                #create the cfg file
            sedcmd = 'sed \"'
            sedcmd += 's%@input%'       + resultsFiles     + '%;'
            sedcmd += 's%@outdir%'      + opt.outdir       + '%;'
            sedcmd += 's%@isData%'      + str(isdata)      + '%;'
            sedcmd += 's%@xsec%'        + str(xsec)        + '%;'
            sedcmd += 's%@debug%'       + 'False'          + '%;'
            sedcmd += 's%@mctruthmode%' + str(mctruthmode) + '%;'
            
            sedcmd += '\"'
		
            cfgfile=opt.outdir +'/configuration_files/config_hadd/'+ origdtag + '_cfg.py'
            os.system('cat ' + opt.cfg_file + ' | ' + sedcmd + ' > ' + cfgfile)

            #run the job
                
            os.system(opt.theExecutable + ' ' + cfgfile + ' hadd')

# hadd.py -e Analysis -j $CMSSW_BASE/src/LIP/TauAnalysis/data/top_samples.json -d /lustre/ncg.ingrid.pt/cmst3/store/user/cbeiraod/14_08_06_2l2nu_EDMtuples_merged -o /lustre/ncg.ingrid.pt/cmslocal/viesturs/llvv_analysis_output -c data/runAnalysis_cfg.py.templ               
