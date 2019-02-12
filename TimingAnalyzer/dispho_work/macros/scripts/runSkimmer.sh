#!/bin/bash

## config
indir=${1}
outdir=${2}
filename=${3}
skimconfig=${4}

## run macro
#root -b -q -l runSkimmer.C\(\"${indir}\",\"${outdir}\",\"${filename}\",\"${skimconfig}\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/skimmed\",\"dispho_2017C.root\",\"skim_config/standard_nominal.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/skimmed\",\"dispho_2017D.root\",\"skim_config/standard_nominal.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/skimmed\",\"dispho_2017E.root\",\"skim_config/standard_nominal.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/skimmed\",\"dispho_2017F.root\",\"skim_config/standard_nominal.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/skimmed\",\"dispho_2017B.root\",\"skim_config/standard_nominal.txt\"\)
## Final message
echo "Finished Skimming for file:" #${filename}
