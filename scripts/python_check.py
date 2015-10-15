#! /usr/bin/env python
import subprocess
import commands

isdir = commands.getoutput("if [ -d \"/afs/cern.ch/work/v/vveckaln/private/CMSSW_7_4_2/src/LIP/TauAnalysis\" ]; \nthen\necho \"true\"\nfi")
print isdir
