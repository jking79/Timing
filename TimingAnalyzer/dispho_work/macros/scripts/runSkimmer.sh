#!/bin/bash

## config
indir=${1}
outdir=${2}
filename=${3}
skimconfig=${4}

## run macro

##DiXtal

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2017B.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2017C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2017D.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2017E.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2017F.root\",\"skim_config/DiXtal_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017B.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017D.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017E.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2017F.root\",\"skim_config/DiXtal_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018D_17Sep2018_0000.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018D_17Sep2018_0001.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018D_17Sep2018_0002.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018D_17Sep2018_0003.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018A_17Sep2018_0000.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018A_17Sep2018_0001.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018B_17Sep2018.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2018C_17Sep2018.root\",\"skim_config/DiXtal_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2016C.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2016D.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2016E.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2016F.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2016G.root\",\"skim_config/DiXtal_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_2016H.root\",\"skim_config/DiXtal_Skim.txt\"\)

root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016C.root\",\"skim_config/DiXtal_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016D.root\",\"skim_config/DiXtal_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016E.root\",\"skim_config/DiXtal_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016F.root\",\"skim_config/DiXtal_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016G.root\",\"skim_config/DiXtal_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"dispho_deg2016H.root\",\"skim_config/DiXtal_Skim.txt\"\)


##ZEE 

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2017B.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2017C.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2017D.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2017E.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2017F.root\",\"skim_config/Zee_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017B.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017C.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017D.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017E.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2017F.root\",\"skim_config/Zee_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018D_0000.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018D_0001.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018D_0002.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018D_0003.root\",\"skim_config/Zee_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018A_0000.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018A_0001.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018B.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2018C.root\",\"skim_config/Zee_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2016C.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2016D.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2016E.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2016F.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2016G.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_2016H.root\",\"skim_config/Zee_Skim.txt\"\)

root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016C.root\",\"skim_config/Zee_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016D.root\",\"skim_config/Zee_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016E.root\",\"skim_config/Zee_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016F.root\",\"skim_config/Zee_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016G.root\",\"skim_config/Zee_Skim.txt\"\)
root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"dispho_deg2016H.root\",\"skim_config/Zee_Skim.txt\"\)

##RAW tests

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_lhc_skims\",\"dispho_2018Dp_RAW.root\",\"skim_config/DiXtal_lhc_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_lhc_skims\",\"dispho_2018Dp_RAW.root\",\"skim_config/Zee_lhc_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"test_dispho.root\",\"skim_config/DiXtal_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/dixtal_skims\",\"raw_output_62.root\",\"skim_config/DiXtal_Skim.txt\"\)

#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"trial_run18A_dispho.root\",\"skim_config/Zee_Skim.txt\"\)
#root -b -q -l runSkimmer.C\(\"/home/t3-ku/jaking/trees/ecal\",\"/home/t3-ku/jaking/trees/ecal/zee_skims\",\"test_dispho.root\",\"skim_config/Zee_Skim.txt\"\)



## Final message
echo "Finished Skimming for file:" #${filename}
