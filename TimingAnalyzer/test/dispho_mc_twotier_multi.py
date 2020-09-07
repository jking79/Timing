import os, re
import FWCore.ParameterSet.Config as cms
  
### CMSSW command line parameter parser
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('python')

## LHC Info
options.register('lhcInfoValid',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get lhc info');
options.register('rawCollectionsValid',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get digi/uncalRechit');
options.register('kuRechitValid',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get kuRechit');
options.register('mcValid',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get pcalo in mc');

#options.register('rlelist','events2018.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'Events to Process');
## blinding
options.register('blindSF',1000,VarParsing.multiplicity.singleton,VarParsing.varType.int,'pick every nth SF event');
options.register('applyBlindSF',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply event SF blinding');
options.register('blindMET',100.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'blind events greater than MET cut');
options.register('applyBlindMET',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply event MET blinding');

## object prep cuts
options.register('jetpTmin',15.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'jet pT minimum cut');
options.register('jetEtamax',3.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'jet eta maximum cut');
options.register('jetIDmin',1,VarParsing.multiplicity.singleton,VarParsing.varType.int,'jet ID minimum cut');
options.register('rhEmin',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'recHit energy minimum cut');
options.register('phpTmin',20.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'photon pT minimum cut');
options.register('phIDmin','none',VarParsing.multiplicity.singleton,VarParsing.varType.string,'photon ID minimum cut');

## object extra pruning cuts
options.register('seedTimemin',-25.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'photon seed time minimum cut');
options.register('nPhosmax',2,VarParsing.multiplicity.singleton,VarParsing.varType.int,'number of photons to clean jets');

## photon storing options
options.register('splitPho',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store leading top two photons, OOT and GED');
options.register('onlyGED',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store only leading GED photons, at most four');
options.register('onlyOOT',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store only leading OOT photons, at most four');

## lepton prep cuts
options.register('ellowpTmin',20.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'electron low pT minimum cut');
options.register('elhighpTmin',50.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'electron high pT minimum cut');
options.register('mulowpTmin',20.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'muon low pT minimum cut');
options.register('muhighpTmin',50.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'muon high pT minimum cut');

## rechit storing options
options.register('storeRecHits',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'store all rechits above rhEmin');

## pre-selection cuts
options.register('applyTrigger',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply trigger pre-selection');
options.register('minHT',400.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'jet HT minimum cut');
options.register('applyHT',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to apply HT pre-selection');
options.register('phgoodpTmin',70.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'good photon pT minimum cut');
options.register('phgoodIDmin','loose',VarParsing.multiplicity.singleton,VarParsing.varType.string,'good photon ID minimum cut');
options.register('applyPhGood',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to require at least one good photon in pre-selection');

## matching cuts
options.register('dRmin',0.3,VarParsing.multiplicity.singleton,VarParsing.varType.float,'dR minimum cut');
options.register('pTres',100.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'pT resolution cut');
options.register('gendRmin',0.1,VarParsing.multiplicity.singleton,VarParsing.varType.float,'gen dR minimum cut');
options.register('genpTres',0.5,VarParsing.multiplicity.singleton,VarParsing.varType.float,'gen pT resolution cut');
options.register('trackdRmin',0.2,VarParsing.multiplicity.singleton,VarParsing.varType.float,'track dR minimum cut');
options.register('trackpTmin',5.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'track pT minimum cut');
options.register('genjetdRmin',0.2,VarParsing.multiplicity.singleton,VarParsing.varType.float,'genjet dR minimum cut for smearing');
options.register('genjetpTfactor',3.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'genjet pT resolution factor for smearing');
options.register('leptondRmin',0.3,VarParsing.multiplicity.singleton,VarParsing.varType.float,'lepton dR minimum cut for veto');

## Extra JER info
options.register('smearjetEmin',0.01,VarParsing.multiplicity.singleton,VarParsing.varType.float,'min jet E for smearing');

## trigger input
options.register('inputPaths','/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/HLTpathsWExtras.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal paths');
options.register('inputFilters','/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/HLTfilters.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal filters');

## met filter input
options.register('inputFlags','/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/METflags.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input MET filter flags');

## data or MC options
options.register('isMC',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate data or MC');
options.register('isGMSB',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate GMSB');
options.register('isHVDS',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate HVDS');
options.register('isBkgd',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate Background MC');
options.register('isToy',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate Toy MC');
options.register('isADD',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to indicate ADD Monophoton');
options.register('xsec',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'cross section in pb');
options.register('filterEff',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'filter efficiency of MC');
options.register('BR',1.0,VarParsing.multiplicity.singleton,VarParsing.varType.float,'branching ratio of MC');

## GT to be used
options.register('globalTag','102X_upgrade2018_realistic_v20',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');

## do a demo run over only 1k events
options.register('demoMode',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to run over only 1k events');

## processName
options.register('processName','TREE',VarParsing.multiplicity.singleton,VarParsing.varType.string,'process name to be considered');

## outputFile Name
options.register('outputFileName','ku_mc_test_tt_dispho_v2.root',VarParsing.multiplicity.singleton,VarParsing.varType.string,'output file name created by cmsRun');

## etra bits
options.register('nThreads',8,VarParsing.multiplicity.singleton,VarParsing.varType.int,'number of threads per job');
options.register('deleteEarly',True,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'delete temp products early if not needed');
options.register('runUnscheduled',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'run unscheduled for products');

## parsing command line arguments
options.parseArguments()

if options.isGMSB or options.isHVDS or options.isBkgd or options.isToy or options.isADD: options.isMC = True

print "     ##### Settings ######"
#print "       -- Blinding --"
#print "blindSF        : ",options.blindSF
#print "applyBlindSF   : ",options.applyBlindSF
#print "blindMET       : ",options.blindMET
#print "applyBlindMET  : ",options.applyBlindMET
print "      -- Object Prep --"
print "jetpTmin       : ",options.jetpTmin
print "jetEtamax      : ",options.jetEtamax
print "jetIDmin       : ",options.jetIDmin
print "rhEmin         : ",options.rhEmin
print "phpTmin        : ",options.phpTmin
print "phIDmin        : ",options.phIDmin
print "     -- Extra Pruning --"
print "seedTimemin    : ",options.seedTimemin
print "nPhosmax       : ",options.nPhosmax
print "     -- Photon Storing --"
#print "splitPho       : ",options.splitPho
print "onlyGED        : ",options.onlyGED
#print "onlyOOT        : ",options.onlyOOT
print "      -- Lepton Prep --"
print "ellowpTmin     : ",options.ellowpTmin
print "elhighpTmin    : ",options.elhighpTmin
print "mulowpTmin     : ",options.mulowpTmin
print "muhighpTmin    : ",options.muhighpTmin
print "     -- RecHit Storing --"
print "storeRecHits   : ",options.storeRecHits
print "   -- Event Pre-Selection --"
print "applyTrigger   : ",options.applyTrigger
print "minHT          : ",options.minHT
print "applyHT        : ",options.applyHT
print "phgoodpTmin    : ",options.phgoodpTmin	
print "phgoodIDmin    : ",options.phgoodIDmin
print "applyPhGood    : ",options.applyPhGood	
print "        -- Matching --"
print "dRmin          : ",options.dRmin
print "pTres          : ",options.pTres
print "gendRmin       : ",options.gendRmin
print "genpTres       : ",options.genpTres
print "trackdRmin     : ",options.trackdRmin
print "trackpTmin     : ",options.trackpTmin
print "genjetdRmin    : ",options.genjetdRmin
print "genjetpTfactor : ",options.genjetpTfactor
print "leptondRmin    : ",options.leptondRmin
print "       -- Extra JER --"
print "smearjetEmin   : ",options.smearjetEmin
print "        -- Trigger --"
print "inputPaths     : ",options.inputPaths
print "inputFilters   : ",options.inputFilters
print "       -- MET Filters --"
print "inputFlags     : ",options.inputFlags
#print "        -- MC Info --"
#print "isMC           : ",options.isMC
if options.isMC:
	print "isGMSB         : ",options.isGMSB
	print "isHVDS         : ",options.isHVDS
	print "isBkgd         : ",options.isBkgd
	print "isToy          : ",options.isToy
	print "isADD          : ",options.isADD
	print "xsec           : ",options.xsec
	print "filterEff      : ",options.filterEff
	print "BR             : ",options.BR
print "           -- GT --"
print "globalTag      : ",options.globalTag	
print "         -- Output --"
#print "demoMode       : ",options.demoMode
print "processName    : ",options.processName	
print "outputFileName : ",options.outputFileName	
#print "        -- Extra bits --"
#print "nThreads       : ",options.nThreads
#print "runUnscheduled : ",options.runUnscheduled
#print "deleteEarly    : ",options.deleteEarly
print " "
print "LHC Info       : ",options.lhcInfoValid
print "rawCollections : ",options.rawCollectionsValid
print "kuRechit       : ",options.kuRechitValid
print "mcValid        : ",options.mcValid
print "     #####################"

## Define the CMSSW process
from Configuration.StandardSequences.Eras import eras
process = cms.Process(options.processName,eras.Run2_2018)

## Load the standard set of configuration modules
process.load('Configuration.StandardSequences.Services_cff')
#process.load("Configuration.Geometry.GeometryRecoDB_cff")
#process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')

process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Timing.TimingAnalyzer.jwk_ku_ecalLocalRecoSequence_cff')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration.StandardSequences.EndOfProcess_cff')

## Message Logger settings
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# LHC Info
#process.LHCInfoReader = cms.ESSource("PoolDBESSource",
#				     DBParameters = cms.PSet(
#		messageLevel = cms.untracked.int32(0),
#		authenticationPath = cms.untracked.string('')),
#				     toGet = cms.VPSet( 
#		cms.PSet(
#			record = cms.string("LHCInfoRcd"),
#			tag = cms.string("LHCInfoStartFill_prompt_v0")
#                        #tag = cms.string("LHCInfoEndFill_prompt_v0") 
#                        #tag = cms.string("LHCInfoEndFill_prompt_v1")
#                        #tag = cms.string("LHCInfoEndFill_prompt_v2")
#			)
#		),
#				     connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
#				     )
#
#process.lhcinfo_prefer = cms.ESPrefer("PoolDBESSource","LHCInfoReader")


## Define the input source
#eventList = open(options.rlelist,'r')
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'file:jwk_reco_data_DIGI2RAW.root'),
#       '/store/mc/RunIIAutumn18MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/80000/A6B73E60-65C7-3D4E-86C4-8DA0AB4FD93A.root',
       '/store/mc/RunIIAutumn18MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00000/0546D29B-D9C3-3742-A752-20A5B992AC21.root',
#       '/store/mc/RunIIAutumn18MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00000/0468DEDA-67F0-2544-94D3-E1E56509C17A.root'
        ),
    secondaryFileNames = cms.untracked.vstring(
       #'/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/80001/34717EB2-1778-8645-8EE6-7725783DD606.root',
       #'/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/80000/E7F9BAA0-3D86-C647-AAF8-3C30D5735E07.root',
       #'/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/80000/BDE610F9-C5A8-0149-8BC4-0A405EFFA91B.root',
       #'/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/80000/6B276C42-DD03-1E4E-840B-E014709B98C5.root',
       #'/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/80001/CC1918D4-D7BA-6849-8195-AE0C00CB10BE.root',
#####
       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7541F0FD-62C3-B841-8548-E35E4E25667C.root',
       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FCFD5A0A-7EC6-5348-AE2C-6A0B1E723456.root',
       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89BC981D-77E8-CB46-8E91-437237433867.root',
######
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FF94A334-599E-A144-9EE4-99DED1AAEF7A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FF88423D-08CF-1342-BDC1-CA7222A9D83F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FF6CD111-5866-7240-96EB-4047AE3AA8D5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FF41BF3D-4F66-D940-9E32-448EC5D49474.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FF3ABB6B-CE92-1840-9251-DFCA8379A269.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FEF124D8-4473-BE4E-8415-EFD5F5C8CF47.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FEBFB87C-1B21-A34A-991B-8F7F571D4F6C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FEBF171F-BBD9-5741-A332-B6B9B84F9247.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FEA02D37-911C-7145-9634-4D3B74A8CAC1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FE76A838-45AD-214B-B557-0513083A0E25.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FE74FAAF-1D2D-B34C-869E-428BD7CC4EF1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FE556645-DC1A-E843-973F-60E6CDE4EC49.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FE432F4A-0E2A-F443-A592-074133D878AB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FE19A295-BCF9-4C45-8D01-F869883CA693.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FD55B6DD-A5A4-7E40-A1B4-A07977C44CFA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FD1373B6-DAD8-7145-9270-02D5E74EB93D.root',
##       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FCFD5A0A-7EC6-5348-AE2C-6A0B1E723456.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FCCB2466-3A9A-5840-96A8-E9CCFB44DCA8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FC854E41-1F9D-9148-BA21-31DF74E2E21B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FC03E3AA-58BA-2A41-B9C2-5BDAB60337AB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FBE415DF-6A15-F64F-A7BB-2E0E3760795B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FBC95C82-771D-C644-9D82-440A204441D9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FBBB38F4-889F-C342-86D7-2B9464DEA350.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FB9E2182-1E54-9E4E-8C7E-64CF76F7BF35.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FB67B697-6E15-F648-BFFA-C9080448FCA3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FB50744D-648D-A44D-8E1E-688E3934E9FB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FB062DF5-7E9A-924C-8B75-1CFD452E0A48.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FAE1D4BC-7B46-8741-9091-98770E7CC505.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FAD90909-0558-A446-B1FF-A9F910C2CC12.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FAC610DA-75DF-944B-9E15-BC09A44CE3CD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FABFBA75-0788-4949-B1C0-4967C355D00E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FA9451C1-7C3B-3A4A-A626-0BB02F188D25.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FA683DFE-4E05-1042-A31E-C01C46DAFC8A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/FA4107C4-C46E-3B4F-9B10-7F2C6BC3A0D2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F99A62C1-F6CE-E748-80B7-F2C16C3F153D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F96B1F5E-BBFC-5947-B634-E40B72D58CE5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F9604EDE-D5EE-8349-960F-5921E90630EB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F91D2065-C43D-5947-B4C5-B98F259EED37.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F8C908AB-11E4-A942-81B2-42E4238CA1E5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F8B9A911-69DB-BA49-A52E-8C1E486FAB9E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F8B97316-33E2-964B-9CA4-760F7FAB51AD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F8961E9A-E86D-DE43-BE0B-908A1559E483.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F88F1D7B-4D9C-5A4E-9E33-DB0A62193AB8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F7D9476B-D80D-2B4F-B477-D532FC3FF5DA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F72701EF-F077-CC48-BFD5-429E5E923C25.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F69B6865-C628-A441-B6EE-63211E4BFC61.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F688A2C4-C8F3-3449-A5FF-F0AFCEDB0C5C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F625A820-2B4C-1048-96C0-101169729C6E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F6116771-5C24-DF49-8253-F8BDDF9A1751.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F5CDBE28-4B40-B548-B181-2A2FBAC30678.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F553F254-9ED8-3244-BEF5-7BBD1AE20296.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F53E4CF3-10DA-7648-A064-C6A7F066394A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F5201F09-88C3-CB47-B655-54CB71EAB98D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F512232B-B482-3140-9A10-4CCFE920FD25.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F43A1349-B816-F242-BBA5-C37EC17CAC3C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F3D84DC7-4EE4-0847-92DE-E31268F778A8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F342D5DF-C303-5141-AC17-510A2130AACF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F30E081A-2858-9041-84C9-DCE7005051DD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F2D7CD9F-0579-AB40-A812-2EC3EFBEA964.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F29FA361-FE64-4944-8D92-94A612E6BE30.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F280BE14-BDE3-634D-8F35-3B84D223582D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F280979B-08C9-3D47-9264-1E8DABB9B1AB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F274F765-E766-0A4B-8B70-FEE12ABCD4D1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F2321899-3D95-E044-8674-695C1177D136.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F2082D96-7ADD-EF4E-871F-CDE34D5959C7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F1E12E5F-30AD-9543-A0A8-FB59AA483F7E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F186DFA7-C24D-3C4B-8AF0-9B798352261E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F1794D69-C773-3445-82BA-2DD1146C61F2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F17854FB-52B6-CA4F-82CE-A7520A9A9827.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F174F79D-DE86-1249-BB50-970878B47E1C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F0F83787-A1D5-5841-9B42-0AD8E1AAD4D0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F0C5224A-8781-A24E-89D4-648BF5F363BC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/F0A3F93B-5F84-A34A-A1CF-32C5B847681E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EFF38AB9-6AE0-FA44-8249-9F2DEC08CDAD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EF8ECB71-32B4-744C-A385-A32789299125.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EF1AB16D-C032-9F4C-8D48-9D84139D89FA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EE9AD3DA-3D93-6048-8909-EC0F1DD20636.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EE6D0136-6B76-2340-9C3F-7E85FA0B7F35.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EE6B0F3B-FC70-8E4C-8ED0-C3D5E6385BE6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EE42879C-61ED-334A-AF5A-0EEEF08C4570.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EE2AD8FB-6BBA-F44C-B086-046CFBCA7FA7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EDCFA8FC-67E4-B54D-9979-5DF568CFDBA7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/ED333ADE-3A7A-9248-B2CF-F928915235DF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/ED0B16AD-6AD1-AD45-B399-25B450C9CFEE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/ECCD8A9F-EF4C-E84F-B78F-0B5D9B38DB2C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/ECB94CCD-06A2-DF4D-AB81-8F01919152D8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EC9356FD-A269-1247-BBBC-B4FC5618C2BD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EC8E8BFD-15EB-8842-BCFF-356591943B26.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EC76CEF1-E6B7-2C4A-AF06-D9D5BBE0895A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EC442229-665A-8942-86D5-9D51C9561C22.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EC1E3AA9-7B3F-4542-BE19-84725C94EABF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EBFAE567-A922-FB46-8CC5-234F06B798F3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EB6A3EA4-A70E-3E46-904C-68C43D0F5B2E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EB31E8DC-05AB-5F41-A5DE-1BF411671468.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EB22CBC1-057D-9C4D-B886-7E738F168A56.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EAFC799F-D4D2-E347-9107-0C148CBF5285.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EAF6A552-8FD8-7D4D-8F5D-53B990B8D69E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EAEAE18B-E669-3E43-8C37-682A7C700004.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EA5C0240-D019-5B4A-9B38-7378B05176D6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EA486037-4A20-4841-8AA2-B2C91394C33E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EA22FE7A-AC28-8245-AF29-182F74907C14.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/EA0975AB-4ADA-834D-A21E-5B165EE1F113.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E9A5A618-0840-214D-B327-5708A9127017.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E9838D71-4BD9-6B46-97C6-CD7F1844EE6F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E92DEABC-791E-C34F-9B49-C5F78F5B9D66.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E85C5B5D-2E54-BC48-86C4-C2B8165007B8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E7EA2DD4-A452-9940-ABC8-F9ED6CD8D6B4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E7457A27-42E0-B64E-820B-32D606531CF5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E71C7883-A04C-B042-BDEF-2FF1D17D81C6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E6A3C12A-D436-1541-8413-7B59588A4DE2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E69AE9B5-7059-5442-BC75-53DEE8D5E673.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E65C99E7-9BCF-B943-A08F-3ABA8DDE0DA6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E65A638C-8079-274B-8964-FCF207361611.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E6565A0C-E39D-A742-9473-31827BE21043.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E62C1B84-104C-AC49-AA73-7C8327639407.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E6100781-358E-1E49-9E02-342D861ACE3A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E6016E72-AC4C-F44B-8BE9-C28D0C878FA2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E5FFE923-12AD-CC4D-BDE5-E6D9FF31A0F5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E5CC28CD-89FF-0346-AFD0-6C73A8FE6646.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E551A440-12A4-F244-9270-9F6EE459C2DF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E4EB1F4A-87DB-5646-9FCF-CC9173E2A080.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E4E397E9-192A-4B41-90CC-E61DB2D183BF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E489DDB4-6328-754D-9019-7A919094DA1F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E47DFCAA-E5DF-8042-B8FF-FB1A136B8A16.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E4754574-31F7-F74A-9895-20770BB593CD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E445E501-005A-7045-AC26-A5E0669A42BF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E410507D-57E6-2945-A19D-7A6DF4C87879.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E332810E-F838-7342-8F67-D007941BFD7B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E2EDAEFE-8097-0E4F-8A19-0F1D44880FC3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E2B83C31-8F71-3B4F-B203-20280B45AD46.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E259237A-8899-354E-B3BE-09C271380AEB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E24C47FA-8AE1-0742-A382-D46C807FD9A5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E22104E0-2AD9-1E4D-A8ED-D9D933C40BA6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E20EB73B-627B-1D48-A08A-431FD7C66044.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E1A7C6C3-DFB6-AB42-9E1C-7C88628422B8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E19E4375-3DF8-5843-82EC-8184355B62E7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E161AE1E-B92D-0D4C-9D2F-35DADA981A0A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E144A743-0D37-C74F-8853-CAD817D49212.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E0D84F16-07A1-234B-8DD5-447F5B923D71.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E0D16356-66D0-7948-AF17-B386F105F82F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E0BFF273-DA1D-C247-9782-C01A3EA5B511.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/E01C5E52-22B3-1E45-99A7-356902D94F68.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DF61FB6C-C519-FA40-A776-3B4671730091.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DF5FBE82-2AED-FD48-8A9C-D96FAB8D6CD6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DF4E4CCB-871C-ED4D-A2CD-9680A6B8B715.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DEDD154C-6069-E741-A274-65B4B24B60C3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DED3DA5A-4361-1E4A-94F6-3BDCAF79D72C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DE9E0552-6266-4B45-9FA9-4F81973B9F05.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DE94A67E-AB1D-A943-BA28-A70C9AE1DEA4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DE826D53-B648-2942-9FF9-911C08A02632.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DE734506-9367-344C-8A1D-418CAA98A3C1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DE39A8C7-9C4E-F441-8F2A-A21627BD3104.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DE3250C0-01B6-7943-BAB0-1FAFE7B5EBB8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DDA88ACA-9BE7-CC46-93A4-B4CFE2F3793F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DD617F31-F458-784C-BF4A-2D70986852A8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DD5976E3-9D37-DE43-A4FB-CF630D1BDA29.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DCA59D2B-1478-EE40-BB37-BE041BB07362.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DC52FD61-8511-8F41-810F-3DEBD925B014.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DC451AB3-7B3A-6D40-947B-791A5D43F98F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DC1D26D2-43D9-0040-8EF2-E1405A9ADCB9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DC0D2CA3-2CD5-EA4C-AFFF-AA74C20D5C44.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DBE9AD2A-5F35-0249-983C-1B01CC3BD8AF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DBD24032-346B-6740-80BB-A2C7B9796C1C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DBA6A0BA-B909-9147-88DA-BB10E66043B6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DB227D9D-E6D6-654A-8AD1-1022E97E3EB8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DAEA499D-0E50-D14A-BCB6-95AB7584144B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/DA1AE08D-0DE2-3D4B-97BF-38040463211B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D9D7AA69-ECF6-7F44-8E32-380604701CD3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D96D57A6-AB60-3443-A63E-A0DB587AF02A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D9433CC8-7C02-5D4D-8C42-1AB4B55BF4BE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D9203F22-65AD-154D-8878-37270F06C1DD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D8DAEE33-A3E8-A34E-BA6C-DA26DCAD25D4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D8A4D42C-C5E4-4848-B92C-506FF4ECE311.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D8443D8C-44D6-7644-A178-6C41C0CDE00D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D83ADEBB-2235-F04E-A849-FEAC7199566B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D7F87097-67ED-4642-ADF0-164C3836094E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D7DC0AA1-9319-6140-812F-57489B92A263.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D7CC4C19-36A9-0D4B-9CB4-08DC593494F3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D7979ECB-E0A4-D047-8CCF-6D4C1FC1EA7D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D784F7FF-FA5C-2246-9CA5-015083EDC6A5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D736B068-E73C-1D49-801E-1CAC34037F4B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D71D41D0-62E7-C846-AD25-094AEF955A2C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D633FBBD-16DD-514E-9225-62F70AF2B13D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D6332682-9BBF-1B40-8C67-422DDFEB0892.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D6318D03-E762-5549-B3CA-0E268D22B5D9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D626FA4B-C1F2-B94D-AAEA-C59C09012ADD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D5F1E32F-B814-D248-AB07-2FC78EFBE5F3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D547A17B-FF08-7048-BC3F-2B8791FA2A52.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D4D9140D-F46C-D842-9ED3-360F3F8FB7EF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D4705658-C206-1F48-9275-A5F395B695BB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D33E8421-0E3F-7C4C-A5C9-C1B0F0343EE5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D2ECB4BC-C5A0-814B-A2C6-A9820C79B917.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D29EACBB-B4E7-9544-BC3E-DD5F00A93D45.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D271D730-C8D6-7B4E-91F2-A97EC7FAE292.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D2715E5E-9E3D-B745-82C2-0D3CDD0B5DFE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D2580232-20D0-EC42-89B5-F61646A1BB13.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D1E924B0-2CDC-1F4E-944F-DC54A8A9E038.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D10F62F8-07CD-734A-9452-B87441B14CAD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D10AA2EA-BA70-D940-8036-2BE27F89887D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D108ACC5-F5FD-4145-931B-7FA91A59F30D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D0F8838B-7E05-1C48-AE16-84F569A06E41.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D0DA07E1-3390-4745-83B3-F72358D89024.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D0D02A46-5E37-B144-A511-3A480DBA1BF0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D0A390DF-4FE2-B44B-85CC-33491DF70012.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D02C042B-A083-064D-9C11-3171DB32E686.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D024E899-3626-474F-823E-AA784D5BAA13.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D024DEB5-C65A-2941-A758-58B05EABBEDC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/D0195608-A756-1D47-B4E0-23B40D5ED40C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CFF03893-C0A5-5042-898C-3A6D211E63B8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CFC1F5B6-2643-9544-8357-A1F3AA3A941C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CF3124D8-3BE6-5B4E-95E2-A667A1131125.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CE7F0C90-0C24-034C-926F-4CCBDBCBDF9C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CE78B011-1D17-DC4D-83E7-A86461B1C775.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CE3D457C-C43B-ED41-BE9E-D4502D491A29.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CE38106B-2157-464F-946F-3ACE217238E3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CE0B2149-AEA7-A445-82B9-F7336CA50459.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CD8D2FB4-41D8-C047-BE6B-8E9C25A7A9BC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CD210600-4ACF-7147-8E68-5B1DF41A8B17.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CCF5356D-A63A-CF4F-9904-FFD6ACAFAD03.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CC1BE799-6223-4A4F-AF16-7688A18417DF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CB72F8C3-3232-A541-BE97-1CD71280E654.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CB660BC8-C6D8-D747-A4DB-D8729433F93A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CAD277AC-54FB-8843-B9F6-708DD04C63A8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CACC920B-BF47-C041-83D3-9E0A25BD4A62.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CAC29B1E-D133-534A-AC28-64FC6D7F5D50.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CA97F119-566C-6646-A48C-6D5F63DA7AD8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CA878BCA-340F-B543-BA49-207D82F6C4BC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CA4C480A-1C6A-D245-B4BB-B5555265F980.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CA3EE557-2B36-F64F-883F-2F09602A3003.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CA1D69B9-110B-8546-AFE9-CEB270C1F71A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/CA059415-2E55-F944-AF31-545A6E2005DB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C9D0D8B7-ABBE-0445-8D50-A3DF327A4612.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C97BAF62-72A7-E44C-86CE-7041500C9DA2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C8E32DEE-9901-614E-90E3-5F8F3AE4025D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C88A62E9-0D90-0049-B1F2-97F8B7A597C7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C8812989-5168-2D4D-9CD7-98C4A5E7BB60.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C86EA74D-E7A7-DF47-8508-664B794B6B57.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C85622C9-218F-124A-BD2A-E09249BF5EE0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C84C0E94-B17C-A048-83EB-9CB5EB244B92.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C7DD5D25-0422-ED47-B33A-E23BACCF3902.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C73390EB-64CC-C645-BC68-C4E3C00BE1DE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C72341CA-40B6-124D-8889-001CA238BC99.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C71CC250-A705-8C47-A391-678108AFEB28.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C6C395EB-2DDE-0A48-BAC3-81B63F7BBB64.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C581E1CD-5FDE-944B-B6E3-8853BAA4B911.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C572A32F-B7C9-8244-81DD-4D79853BEE93.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C55339C0-6E40-A241-B16E-E92FD8F5EA5D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C4F20500-BC39-A84C-8913-04777808DCAD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C4A0FD06-568B-8142-BCC8-4770154CCB31.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C49D278E-F859-6D45-A04A-EF147D6324C2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C4952BE4-2CC4-2F4B-A20F-420C7B899171.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C42ECC11-A5B9-5648-A2EA-FAB76BD63E24.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C3B2E6CB-AC16-7E48-946D-C332B97E1376.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C37B1E56-F640-094D-BBCD-2E8CB9A528B5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C3708040-21DF-7D49-AB21-5353F13C26FC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C33516F0-515F-284C-8633-FE52BF6C0FA2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C328010E-43CB-B841-B095-ED6E855A3200.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C2CBBE22-BD1F-4A46-BEF4-0193078D30D5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C25DADF9-712C-694E-82EF-4B25EA4930B7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C25789CA-FCE8-4E4A-8026-AB53183CAE43.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C2122ADF-2908-D244-BD96-CCB6FECCBCD0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C2018FF3-5898-8746-82D7-5AD446D0F6D9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C124B21E-7340-0846-9094-270947F2896B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C11CFFB8-97F7-7C49-96B4-D32CD76A3F5F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C03735B6-D0B9-4446-91B8-E384DC6E52EF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/C0351BAC-2C90-2147-A454-F7A66BBF4907.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BFACACEC-6115-694C-9C8A-537C69B57E94.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BF8AFFE8-107B-C84A-A76B-284DCF6F450C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BF34808F-61DA-FA44-9FDA-ED1375EC92E3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BF1268E8-AD6F-F145-96C5-0A7A136BAA3D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BE65F228-01C8-7C40-8689-324CBC1C24DD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BDC8ED51-3919-1E45-8DCF-94AB64F485DA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BDB6E9E6-B423-404A-8EC0-1B133526F67C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BC9F1C15-2749-3E40-B9FB-E17964C95F16.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BC03AC46-4D8A-424A-9DD8-C0BFFEA696D3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BB683393-8BCF-4747-AC3B-D828B8B73931.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BB5D76A1-BCD9-7242-975D-7E5C07D753D5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BB241B32-EC3F-A946-B203-D942737A3D16.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BAFE0FA3-F77E-454F-9015-D40F919E409E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BACA6390-8C07-B142-8E82-3675E43897AD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BAC43FF1-C113-C246-8274-73FA6552B595.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BAC282A5-6EDC-E149-BDB8-4FF9F83FFCF6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BA5FA2E5-C21C-AC4E-B213-F3DBA9145FA9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/BA17F092-8917-8045-8B51-7DDA3969A905.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B9A25E29-643A-E94F-8146-E1CE53713A3C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B85BF137-0D82-7B46-AB8D-18D2884B98D6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B81C11AA-1A15-4C4C-AFA6-EDC9E1059ECE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B580C0A3-A734-6B44-AE3A-6C8C5BB78E55.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B57FB64F-4B2D-9348-AE75-C82F5FB8313D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B4E03214-0D29-0B4B-88B4-B512C133142D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B49648C5-9448-1F44-B417-EA136FE9489B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B400DC75-B366-2E42-9AD4-BC8F2198376E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B3E08CA3-F6ED-394D-B9EC-28A87AAAE17C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B339422A-453B-A248-9780-26ED9A5C0B9D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B335BC94-DAEB-214C-964B-4013A68CBE95.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B334012C-1D4E-6344-88EF-B3BBE0B19AF9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B32CB361-415F-4D47-A138-0A99E806BB84.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B31E0656-57BE-9D4E-AEC8-9F9DE476BDD9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B2847E62-7F42-3544-98C7-00382832B9EA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B21993D8-8938-B143-B572-B7E5B2A99213.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B1FC5FC7-E24E-9047-AD78-02A0B57D33CE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B18FB5BA-B0E5-9A42-B959-12ADE9621AFE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B15FF06D-F8CD-6D48-B55F-0BAA647BEAE8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B148EE88-1E8E-6643-8601-3BCF13640E86.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B0ECF79E-74CE-F442-8EA5-05D883BAF36A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B0E0ED49-772B-8640-83F2-ABD183EAD4CC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B0C1DCE1-1499-C747-9881-50578B4069F9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B09D1B3C-8E2F-B843-BF4F-E8F91859832C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B083DA28-8A7B-344A-B5E0-C5A8DE6392F7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B0155959-D99A-E242-BADF-B339D5043230.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/B006A9B8-D269-2B43-B86C-2FF62070A0D7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AFFB0C0D-5097-FA45-9EDA-49C3DCE1F5CE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AFD35702-77F6-CD4A-900B-F659954603F8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AF951C44-5EB2-8146-92F4-F8AC35F4E7C6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AEA49803-0389-2141-BF11-4365C4DC6A94.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AEA48B9E-129A-3443-9065-73861E164854.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AE41DAF8-1F45-294D-B789-9D79E59FB6DA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AE28E343-1BA8-6241-B1B5-D176E14CA249.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AB819E5B-6E79-B244-B684-C0144E68B9EC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AB6DA6AD-BBB1-EC45-8537-902C9CF66DE0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/AB428BA9-124B-8540-88D3-3F67D5018F91.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A9C58E2E-0F55-0A4C-BF68-75F8368E799A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A7A331C6-494D-4A49-A7B9-6A38862ACFDE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A79B02EE-F92B-B94D-BFDB-3AA0250FB3F9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A72728BD-BD68-5B4E-A7D7-264F2B254E64.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A6D056A8-DC91-C448-9454-A4B24AC43B29.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A6AC47A4-CD3E-7345-AB39-424AC51193D1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A6228BA2-E59B-F945-B201-5261D5287A5E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A604C795-52BA-6340-BD82-AB0B1BEAE391.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A5C06C7F-7317-3041-AA4E-1E43598DDF4F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A56B86D7-B8B9-B242-B253-20A7350864F4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A52845B2-D5BB-224D-8CF2-A0CBCFEB9613.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A44D1796-0AE0-7248-91B4-39EDF0CEF7F7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A3B666DB-F7C3-3944-B01D-2FA3A7CBC70C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A37025D5-851C-964F-8166-8E7C597BDB14.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A326D354-E639-C94A-8F38-56B79A9DC552.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A313FD6F-AB7A-C249-A076-431A90298A54.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A309E58B-70C8-3542-9636-D2308F09CCC0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A2CC52DD-60FD-8E47-9168-894008344AD8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A2B2C4CB-B1FC-6043-A9CD-91D627603FD2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A270A135-C97D-2A40-9C4D-6A5D6C77D848.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A21135D2-02CD-7046-92A5-64FAB780DAE8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A1EB64A7-BC13-3142-A370-C2A4C9BEB58F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A1B360B9-BC56-824E-B79F-19FDE084C99E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A1920DE8-4750-D844-8458-B3E4C0C87013.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A15EB16B-1623-6542-8E23-0B4DDDCEB498.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A1091CA2-9381-A34D-829C-B2E748489D05.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A0C7BE7E-CA7C-EB42-B79D-E3EB8D4EF92B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A0AF06D4-88EE-3A48-8AF7-C3F5E1FCC77E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A07C4E9C-312B-594F-A62E-382F77DC4754.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A06890C0-2555-5342-B20C-D856407FD819.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/A05BDAE7-C355-CF4B-9FA1-C94D287E6343.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9FF517C8-DA66-EF40-B051-4FD275D4170C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9F92FAE6-A7C5-2845-9B2B-2DA635C9EFE7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9F222833-3189-EB43-808D-BE6763FF2B5B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9F1F2B50-CCFE-E240-803A-9953F49FECBF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9E1DDF6E-D58E-684A-B50B-FAF61CC519B7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9DF90AFC-1CC9-FE45-BF7F-8BAE98D5F4CE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9D9EECBE-A928-8244-A944-3E495CCF4C45.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9D7C58A0-B6DE-5645-A2D9-9C18BF410FA7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9D7718D0-6328-5645-B3E8-2FE5A509B56F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9CEA7E4D-16DF-2743-9B1A-777729F78A1A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9C639AD9-658B-8C44-A693-FE29A7B65AF5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9C52B881-C0DF-8240-B7E2-6298BF2BB304.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9BF701B3-666D-1E45-84BE-55476376D45C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9B8B6B33-254C-3240-938E-30622D9CAC21.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9AD817AB-C862-7A43-86BA-2ECA2437E4A7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9AD2090A-937B-9147-BD8B-36E9AB9156E7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9A68E241-D741-904D-AE2D-BAD13E3FC4FC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9A55BA64-F089-5048-A992-FC2571E16249.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9A315CA4-524D-514F-B4F9-1FCC5B33F340.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9A269F07-769C-0445-BF55-FC47BFD1C26E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/99F06402-C865-B449-BB91-9F6256F7A774.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/999E1242-580E-944D-8A7C-37C3B8ED4D3E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/996B706F-7A56-9F4A-B4EA-C7D62C6068BF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/995AD78C-99DC-5042-A7DC-BEBE05A7B069.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/98DE4ED7-DA78-ED4C-91F2-5C6FF5C7D90B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/98CD34DC-7CEE-DA44-A4F5-4F8206D720E0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/986DFF9D-C1E4-B14E-8B2A-9837A9FDF4D4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/986C8086-E9BC-514D-BEB1-095E16839581.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9855B8D6-08AB-AA48-A129-06D81FE35643.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/97FF14A8-9999-044E-8BF7-FFEE5D468958.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/97DB9F0B-80B3-FE43-AD0E-77EB5C1D0338.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/97D5CBD7-F4E9-7E4C-8C1C-DF021206DE5C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/97C4B7AF-7BE9-464F-9DA7-7ED4AE09C2FD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/979120B9-5422-F046-A048-EE97960C0BCC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9761B732-8FAC-FB44-9370-D743293666D2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/974884B1-5966-EE4E-9A19-0F93F8E3BE1E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/96C203F9-FC95-1E41-B9E3-E8F7DB96BC06.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/964D73FA-6653-664E-9C2C-C612701CB114.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9630E153-4E84-5B4F-80B8-8296C5E97B5E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9626E8E7-B45B-D44A-B92B-8AD53E1497AC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/95DEE615-4979-014B-B795-1FADB8F4B45A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/95AA6B87-53FA-2240-9D51-404545C0732A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/95A93254-D94B-8847-AA1B-6DDDABA3B9EA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/948EF4C8-139E-6648-A654-576A22D273E1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/948E52F4-44D1-A145-947D-42B35A79D24B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/945D5241-550D-E44B-B55D-AE54005DAA1F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/940D766E-5241-BA43-AC16-656FBB3295F3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/93ED652F-3D06-AF44-95B8-4B09541DD7BB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/93630F15-220F-CD46-A7F0-3876D81A2AC5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/93479479-6BC7-254B-9270-5A6EF75FD47E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9331B6A5-F76A-2341-B3FD-5C767CD02AEA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/92BA9F6B-D75F-524A-97AD-D39C8BA2CE25.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/92B753B1-B3C4-E445-8EC0-8C3336D22BCF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/92599960-4C6B-A243-A6AE-77CF2595BD72.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/924E7464-7138-1F4D-8A11-2A2904804F29.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/91F3F483-936A-A34C-9766-8E4C381BD81C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/91EB54FC-B999-4E42-A703-21DDD02F54F1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/91BD68DC-9079-EE47-A98E-22AE0875A137.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9175B989-268A-5647-9EC7-42326AEEBF4D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/90D4770C-06BB-E145-88E3-AE5A450B8909.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9089A146-179B-F944-847B-4172166E5C37.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9056A139-D32D-2B4D-9D9A-DEC0AEB1838B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/9034AC69-3F69-1246-A41B-1D131717218E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8FCC1B99-8159-3945-A21D-FA249B27B84D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8FC0A41E-A3BB-7645-ADBF-088843F68E49.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8FAD82A8-9926-9D43-8FC6-33D37B98F647.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8F831A01-8DCF-8E48-A808-433FCB6CF31F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8F3199BD-9976-CC41-9F4B-F9AF5F9F833D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8EF686E8-7C4C-834A-A056-D48B9C2B64AC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8E9437F1-D59F-4346-930B-CD0C689CEA34.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8E8C49CD-D0E9-A743-961E-8D47C1442013.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8E3C95B1-728E-CA44-ACD0-32B55972D452.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8E39D327-5F55-A940-B73D-EA5BBC2CCBF8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8E233A46-1D3D-544C-A1ED-A8AD6FA96D0A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8D9D5D89-78E8-1543-AA04-3D05976C45AE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8D6F5E4F-A758-2E4E-A304-2415B380EB40.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8D42B72C-4EF1-4D47-AE9C-C115A621363D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8CCC2BC3-C4D2-2E44-BB24-50A3B977908B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8CBABB00-F431-0C47-8BC5-2303B5EB5F1C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8C7CA482-E917-604C-BA2F-31B7A3A0B9EB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8BE8EB5D-7DEB-F946-A666-19259EAA2D49.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8B802422-79EA-684E-99E4-97314FA6260F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8B04328D-76F6-E94A-BF9A-9B296E5D4462.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8AFBB408-0FFB-A448-A062-7C47F396D028.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8AE67FA5-F5A5-BA40-B071-07E21D986DAB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8AAA84A8-429C-4B42-A6E7-A85EE8779BF6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8A78E480-D19E-B94D-BF85-CE1A02C2A2AB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8A4C72ED-CB08-9449-BC37-4B626DFA7C35.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8A218ACB-C5F7-364B-A886-106792C2E2E9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8A1F2A12-3DCA-FA4C-9681-903ECC338C2E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89F995A0-1434-2C4A-A879-5364CB1FA417.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89D03D48-E5D9-3E4F-95F8-C9BA7B839179.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89CD6864-6FD0-404B-9287-4CA32CA446E4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89C45BB5-987C-104B-BA5E-A8CB7CE6A614.root',
##       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89BC981D-77E8-CB46-8E91-437237433867.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89B58E74-6B80-F749-B973-0EA9C89B6187.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89A3AB9E-3084-154E-B1B3-C1BBF40874CA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/895566CD-FCDB-1A40-898C-9D5FC2D367A3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/89010BE0-7238-5647-BF2E-8861241F3A71.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/88FC3DFF-DB9A-A740-9C9B-3B8AA765866B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/88685FF0-8FB2-9140-9E3F-12EDD3135DEC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/87B2BCE9-CFCD-8348-8C7C-6DEE90FAF4F3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/879D23C2-9E42-0D40-AA26-D50761BE9468.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/87642509-EFA5-8D48-8FE6-3B09343DC242.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/86FFA287-7EE9-0A4B-8B76-D3849744553A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/86DF9DDB-44B3-EF47-AC09-FDB5714D38AB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/866EE35B-B63A-AB4B-8FCD-F5DE9A687FA6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/864D35A9-95CB-4744-B77D-F729683188F8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8640DCFD-3854-E64F-A09B-BF9598E326C2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/85FAF9ED-63D1-5941-AA95-403251C8218E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/84DECD61-2136-E045-925E-5B0E4547EF81.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/84D1EF45-B75D-B14E-BA53-16954F82FAED.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/84C164AE-AFC0-104A-88C2-9C00FA0A4A4F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8489BECA-4022-4E4F-A41E-B44C577800A6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/846FD5E2-DCA9-744D-AC13-D4AC77EC9611.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/83C5EC4F-08CA-7C4F-B6AA-EB6CBFB0E1B9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/83AEFC6F-99F7-6F40-90F6-D1A0AD627291.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/82E8D2FF-1F79-864E-A13F-34B0D648A194.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/828D2AE0-39DC-6445-BAFD-1D00A708BC9D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/82775060-1F32-D04F-9EE7-67517690BAEA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8231CFDE-38FF-774D-B19B-120F2E142049.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/81BAC9C3-C1E3-8C4F-B22A-5086AF2F15DE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/81A06DC6-E331-094D-8742-F2EBDB258CA5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/813FB95E-F67F-4A48-ACE3-CA5E60E4E10F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/80C64303-1130-9242-AD97-8D1517BF759D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/8018DD74-DCF9-3642-A1F1-39F85CCCF9D4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7FB2911D-1B36-0E40-A3D0-F71C905169C7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7F3E299E-8703-2243-8906-E8BCF6DC4011.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7F27CDDF-3176-E845-A3D4-FA21756430C6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7F06ABE7-34D2-DE4A-AC91-DCB2F6561DF9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7EF5F05B-B295-8B47-B653-70A1D21372F8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7EC66DA0-71E4-BA4A-A000-9EDEA2882371.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7E86B2A2-41E8-164F-BB4B-7D4FE9C6FF1F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7E6EEF7C-4ADE-E74D-9191-EE96C18E043E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7DE6CBE1-9DDB-5040-9895-62F7BEE242A9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7DC832EF-897C-D64D-9429-51D420FA11A0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7D63B442-CF2B-9F4D-93E6-41701F6523AB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7D2775C4-A695-CF4E-8393-2B2C46F04CD0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7CEB5A4A-F0A0-DE45-9C0E-343891EFF28F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7C678474-034F-3D41-8481-6BEFFE1BE9D2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7C2DBEBC-D08F-2A48-AB70-100D1A2442F1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7BD42A07-ABCE-7F40-9397-FB3CDFB1EB93.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7AACD79D-3FC7-F54B-9546-95BBC2394CD9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/79B8FDF8-4F34-AB4F-8AD9-48443B48C6B5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7986583C-5C63-1F43-ACA4-A474BE9FAC65.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7975F597-D764-AD4C-860C-26E68AD7F9A6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/796AFB80-283D-D54D-912F-0120C0A51F71.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/794C5956-C27A-6045-B2F7-FE4D5DD8F29A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/78A33D2E-BA20-D840-9747-9A6DB216C91C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/789C63C0-33B0-1D4E-9ED6-32C69C5B84C2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/786C4480-9B80-F44A-8267-28BA7EE7E81D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/781C38B8-4219-3943-B249-D1CA207361E6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/77ED0344-63DC-F04B-B96D-A768C31232B8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/779BFB12-BE0A-BE4C-85CC-287D62133DEA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/770F84B9-6505-EA4E-98AD-B338A3FF663C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/765BF767-77DE-6F43-9403-200B84E2DC39.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7615321D-63C4-0D47-89D0-947D154D17C5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/75C47A1C-8311-1C4E-8F95-1BD365391C3E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/75BD4B1E-DA80-A447-A107-EEF4E40D1A46.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7598978A-E3E6-8F49-98D8-CC0FF885E4A1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/756ACCFD-4533-144C-93B4-E8936F07690E.root',
##       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7541F0FD-62C3-B841-8548-E35E4E25667C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/749840F2-4193-234B-BD84-5C4A63087FD4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/745D1034-8C17-AB40-8928-133B224FE002.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7456F4ED-57D9-974B-8A3A-7FD75B81E530.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/73BC0C6F-2051-F742-8C10-8A37CD2BD8B5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/737A19FC-DF4F-C749-A971-915E0E033E9F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/733AAD6E-03BD-4D44-8313-56F82A98B1F5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/72AAFC0D-7346-934C-857C-D36422D474C1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/729ABCB5-7ADF-294C-840B-04D60A69D7A8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/7244419C-04B4-CC4E-BCDB-EFE6BBCCE008.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/72261F13-0ECB-D443-B981-86DA6B174D10.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/71F8D5F8-DEC2-A94A-9B48-719ED0D1802D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/71AC3D9D-C2D9-6243-8ED1-1A8A6F1D26EA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/719418F7-E84C-4F45-8D40-7282B144F365.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/71919C89-D9B2-1A4D-8320-DD9B3B3CF6C1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/70F89651-EEEB-E741-B64B-25DAD604E8C6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/70DC11ED-E03E-0448-BF1A-E65239207391.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/708AD292-7EBA-9945-9F66-011B47CAABAA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6FEAC1AC-2A25-9C49-AD8B-2FB1453E1E03.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6FC2FF85-6838-ED4F-B1CE-9348332A7155.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6FAFC645-0BAB-C342-94E8-976930BB70B1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6F3F2226-30F0-F54C-8DCF-2DE608A92723.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6EDFD213-0418-8847-B2C9-23F99D01094B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6E6C165A-7174-0540-8331-188C4A6B5104.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6E37C43F-7971-4344-A5AF-13E91B37C47C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6E306DF7-179A-D146-AA88-B5878DEC934A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6E11B7D4-9FC5-0346-8FF7-5CA147264E7C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6DF1C708-069C-F348-B478-0C8319F860C6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6DC721E1-13C9-B34F-BEE8-61BD0C7D5E68.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6DB7B08B-360D-884D-9947-57DC05E4C824.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6D50B9AC-C2A9-3349-8C0D-362C025AD26A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6CD64B21-BE2D-EE43-B323-D26C4AF079E0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6CD50490-8BD6-8546-9391-FD5C5C5D64A2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6C91C379-9EAA-2047-A29E-322EC560DC7F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6C9119D0-6E82-F44F-8F29-E3F985E6F245.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6C7DAE21-2803-4F42-B075-0B38E54E7AA0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6C2B5844-D341-B949-AFDD-302C87236A5E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6BFBBD54-1357-C242-800E-7659438B86BF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6BE1C644-9BE8-B34A-9F7F-D4D677CEE48C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6B4CE4F2-B1CA-004A-AFAF-28BBEF2D812D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6B09166E-2F90-244B-AE89-9031B43C9A79.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6A9505AF-51DE-2142-9094-E46072FF3398.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6A89CE9D-27C7-4B49-A752-FBD8596E2EDB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6A7AE49C-6EC0-1741-8362-8BE837D4267F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6A572993-5A94-894E-B7DB-2AA1253E2A2B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6A1DEF55-8A57-F448-A6EA-86D6E682DCB2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/69FD028F-3D93-8741-82FA-7FAE251D6FBD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/69953DD4-D266-3047-91FE-E3BCAD2AC0C0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/694DDACC-B73C-8C4C-B80E-AC9042F83B86.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/68B18A76-1842-6D4C-A9D3-002B67E4FEE2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/68992225-CF0E-EA4F-8D02-B5692C864813.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/687BB334-CA8C-A64D-A55F-675DCCCBDE67.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/687AEA7B-9F31-9D44-BDF4-C908ADE7EEB2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6845F1B1-FAED-2343-9D4E-7C55CEB333D3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/67BDE8B2-29CA-0341-B416-6CA022C34289.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/66343DBC-A72C-C340-9A9B-56F77A13ABDD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/66228EA0-F541-1A4B-A8CE-F231D49FA7A7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/661CA29D-D578-5F4E-AE97-E534B5C7173E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/65701C62-5C06-EE46-80D2-EEB656381546.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/65270F70-C414-A04D-A428-6B35064464BD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/651314C2-D18E-A740-9D5A-FBA3E1AFA5CF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/64C4A5A5-D04A-254D-B46D-4EDCDFEDE5C9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/64529A55-E57B-D84E-9876-F472D0182FC8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6440C4BD-5663-394D-A21B-FC31686D830B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6439EC82-4100-4244-BE8D-985F1A87415E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/637528CE-C5AA-5A42-8D5E-65E4AB46C01C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6373B9AB-B626-994F-9A51-AB8F23A1AF87.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/63629EFE-AC1A-5547-A678-EA5025FAFB79.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/629D8963-7695-4745-8456-5942E0D4D78F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6277E341-BAEA-A24F-9283-F1BF0E126360.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6275756E-0B2E-AC41-B5AF-500007FD8F57.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/626A6F58-E80E-5947-BA5C-8EA0421EBB9B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/62691E40-BF2B-0247-8012-59BDC821D506.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/61D3B027-4DB0-3640-AFBC-2F7D8FFE97D1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/61C7329B-B768-5A40-BB84-3FCC8AB13255.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/61ADCF67-5787-1B40-B368-29612E00127C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6180B079-06A3-7A4C-937D-83FDF8BD72FF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/610BA23C-B430-1B4D-ADDF-B6975CFAAEF9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/60F9BBF3-DB54-644E-9E5B-764323AB504F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/601F9B24-31C2-944C-A7C6-B875644E84C2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/6002BC83-DE60-A24D-9C47-826674411107.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5FCA1CAA-71A8-EB43-BB18-457633DCB28C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5F23FF82-31E5-CF4F-9CA1-CB84E60A0A31.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5EFB0842-93E3-F949-B47E-9E48CDE527C2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5ED5CDDB-6BDC-4F4F-947E-CD29C1DF21DF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5E8AF42B-9D29-8B4C-96C1-BF87573AC73F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5E5BF446-F969-3D43-841C-045DE9DD71F0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5E22E808-4238-C941-90CE-5D05925E60A7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5DD8B838-DDB8-3B40-976F-9BEE75E6D0B7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5DC961DA-7992-754B-A7B5-238EB98089AB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5DB9DC9B-3D24-4949-BE05-E54017243113.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5D9F10A1-0C4E-FC41-A292-E11386FA72CC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5D4B9B7A-17E9-8D40-9D37-851D7786F80D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5BF048DB-3E01-E946-A19F-0AD2767086F4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5B3F741D-7EA2-E84A-818F-5676D9936943.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5B187594-F89F-5C4D-8BFF-0381F08DED8D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5A5D0268-E68A-A140-BF29-038D3DD0E6D9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/59E12C0E-D369-A14D-AF50-AF40FA0BC8A6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/598F2C0C-7233-D849-8A2F-1D8534D126F4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/597F269E-CEC9-E24C-AD23-63A1B9A938E1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5964034E-B658-2C47-8F91-59B9C7ED3BF8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/59415C73-16EC-1546-90E1-0CEB993362D7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5933A08D-4411-0646-9EB1-6DE698424D1F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/590577B4-A7DE-8D48-8327-A6D1C2868954.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5889E383-0191-3649-8942-9C919EC0DE49.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5877F0C2-E64E-734B-90A7-98D3AF68816F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/584A7DCD-672D-F44E-AC38-FA529957A470.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/57FA57BA-9A68-5B4C-9C4B-FEE87D43CD57.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/577E3709-AD96-904F-80B6-EEB2948833B5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/56CAFF52-29FA-AE4F-B9CB-7475961EA6D1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/56C5CDD9-4B9A-2C42-B5F5-005DD5E13962.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/56BA8402-6276-5248-A17D-A5FCB9FB678A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/56B49BB7-0E6A-DF48-BBE1-5B440588592A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5652226B-6805-6748-9789-2DCB789A59B4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5649D4A8-31EE-D54B-B576-8782FBCD3756.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5641C3E1-0648-DC40-83DE-9029B677E18B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/561D9CD5-4AD6-E74F-A44C-0FC7E2DD84D5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/55FFCD93-41F8-3445-9EFC-4585811043D5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/55F0B961-C948-BB4A-88E6-A3F284143D87.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/55D12B3A-ED17-4946-981D-9DD31A55D4B0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/55AF472F-9A5F-BC47-94AA-3DB049096D08.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/557F5E7A-5207-6A44-BEBF-B8DAF7DB2272.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5578605F-08D0-C34E-943A-BB7A17FA78C6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5551C64A-BA54-4D4B-816F-2CD60E2FC32B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/552C6881-44C1-C84C-BB09-C5D40FCB17C9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/551EB226-97DA-494D-8087-6B12A36A5B6D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5505D103-2F11-B34F-9BA8-93C891FA80C4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/54CAE308-F670-404D-B569-2BFEA94846AF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5464EC01-67D8-1E4A-B1DC-E916954304E9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/546149F6-52E3-1149-870E-C5587B7EBF31.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/53AD099E-6A45-A34B-8080-345C0088BD3F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/53A8A156-26D3-7D45-A6B0-6CD22D0E1D2B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/53A14EBC-FE30-0A4D-8CE9-016ECE460E7D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/537571CF-86D9-5149-9CD8-36621255127F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/533D29CA-D450-7640-AFA4-FE9ADE637F11.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/52D977A3-5626-1A44-AE0A-DF7194AC60F9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/52D8F461-1C93-F248-B856-D58BAFCE7AAB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/52CAFF28-BF15-F44F-8177-5084302FD2FF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5289F021-721B-DE42-BAA0-3AD792041F22.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/525FE074-002B-844C-8594-6D350E39B544.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/52289D8C-13A4-2C42-B9EC-15DDC7DEEC7B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/516EC003-A4A2-5745-8EE1-14F524F25280.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5162ADFC-AC12-894B-B4E6-B3538DD76E09.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5161FEA4-2C47-F84E-A032-AE7C14CEF186.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/5154733B-46A3-3849-9373-B9754D9E4A8B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/514691D8-F1D6-F843-9EBF-920B0B1C2EB5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/513326A9-8242-2B48-8AF8-E4CB15463BED.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/50FDBB5B-23C1-E449-9907-6DA99D4B656B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/50F8FACB-13C7-1F40-9CD5-B5EE88FBE5F9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/50F5E47A-DEA9-264A-8B70-74871FC7E888.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/50DBD211-2F2D-F144-860B-2DD102F48CEF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/50CEDD14-F1B1-2045-8BCA-212EC1DC1298.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/507AECF4-5EAF-2B42-94F4-4168C83FFC5D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/506B50F8-7B42-3E4B-BB1D-6BFCC88AAA1B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4FB492F0-B6CD-F040-B6A1-316F4DA1F9F7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4FB136AF-AD47-0D49-88B9-B6729A58AAAA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4F916471-CD95-8D40-8BD7-61B7FAC7AB4A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4F68A271-B42D-E448-80BA-81FCD9CB55F4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4F57AB12-2347-7D42-A585-C56A0A54B41B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4F4464FE-4A77-A545-B9AD-ACA5A407B744.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4F12B277-7870-964F-83D1-9FCF130E126B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4EFE8FBE-3501-0C41-87C1-B99C82D9B5FF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4EEBDC20-5CF9-3E49-8F5A-BB8F75684E6E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4EE6679A-EDFF-D54A-BC14-DAE87CFD05E3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4EAF3C3A-2E43-2248-AA5A-42627619F448.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4E9BE342-C41E-ED4D-A03D-C6AD608A8229.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4E665C22-9D5E-EB43-B513-A10B98ABB736.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4E421248-8235-5E4D-8099-B88196306200.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4DFDD904-692C-5146-9F42-59BB6E5E84A4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4DEFD9DF-2D9B-4048-9FF9-4505467DBE68.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4DBD678A-DF8D-1344-8600-14D8CBF1C35D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4D9EAE80-4AC8-9B40-B684-0B8ED8836A1B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4D3E8EED-5580-5A46-842A-49AE442C3DAC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4CFABFF9-C1A7-314F-AD5F-222051E7F592.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4C9DDA21-D3C6-3048-A4DD-2758E0C2EF88.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4C8C114F-68B4-0047-9656-1949EEBDD4B2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4C5BEDFE-86BE-164D-98C7-2DCEAAEED036.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4C20E2C8-CDFF-B740-B681-68CE39818423.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4B6BD38F-6ECA-104E-837D-D6361BE3FC6F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4B4B3E60-2FAE-FF43-9EE2-6EBFCD593FD2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4A527A95-2262-F740-932A-3DC9DF93F91C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4A12D350-DCE5-9B43-ACDD-1A07DA8D6FC3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4A04F065-2BBB-164D-90B3-0532EEB5B63C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/49E112C1-EEC3-D04C-B473-A50894CDDC96.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/498A383A-1F0D-8E46-94D7-227BF51B7C78.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4981D929-38F0-DC4B-8C84-DA28EA317E58.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4979D8A1-61A4-3046-A98C-20318725438C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4914E760-75A7-0B45-93F7-F990D07E1E1E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4908F69F-1F27-C344-9D8E-9439362ACF98.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/489AF757-91AA-B044-95A4-1F5C8D0AF9F3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4888E05D-8D88-2B46-8097-72F966143825.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/48863C43-36B4-1843-9A33-9627B2CD123B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4839393A-3377-9B42-AD4E-D16BD2320B89.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4803961B-D8CE-D84A-808E-8CBF55740B39.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/47EDCDD3-04D9-D844-9520-4085C1A110B6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/474A3623-3FB1-624D-AE47-7B9F165BB2FB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/46CAFD57-E979-AF42-9D82-8E4CB96E1047.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/46BADE48-C8B3-6643-A5C2-F4E3A5B95372.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/46804C8C-4768-AF45-9C9F-C5C77E29B699.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4614C62E-DEDA-1B4A-8E61-BC6A2B1CF21D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/45DCAAD6-0E36-8F4C-A0C6-6ECAF6C454A6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/45C055FC-1362-DA46-9D71-25A0E2CB4E4A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/45370E3D-239E-5C40-937A-0E269D26ECAD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/451E60C1-1BC3-2A41-981E-11E7F5B02BCF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4505792E-DF10-9142-B33A-91B651DCD856.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/44D01391-6FA0-8248-B59E-7AB40AE8A08B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/442CFC79-F7E9-1F46-9D5D-DF0079324904.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/44085C05-A65E-D340-B3DC-BFD549A83512.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/43BDAE90-1EB3-2249-B453-7105C31D3626.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/438CAA57-BBFA-0D41-9090-2BFAA1634433.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/435015FF-7709-914B-9F3F-20930149038C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/42FFF039-018F-B343-B6D8-25DBFD15FC0C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/42844930-F39E-9348-B24A-DE2F01FE1C8D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/426BC30A-F1C8-6645-AE27-D5A289DFFAD8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/425BA5F7-DCEF-6741-A8C7-1DB5B849F197.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/421E26F2-62AD-7A44-941A-B361472C959B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/42157163-5259-B24D-B6A2-920EEA7D8A5A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/41DAD56F-16A1-ED42-A5F0-B0CE4B5E769E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/418F6474-8400-FF47-A4A7-BC74C5B875BE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/414C9A18-8C72-D346-8320-1CA1F5C13D5C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/41345F75-CDC8-A346-8481-DE7ABCEBC6EB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/40B05B4D-163E-4D47-BEB9-80DAE9338BE5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/4098BCBA-1803-1D43-AEC1-26DA7B8B4C83.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/40718627-1AB7-334C-834C-524866B42B10.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/406BA15C-F6B7-084C-BB49-AF83C13FEB47.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/405A04D9-9281-BE4B-99F9-C3BED2260FE6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/40031576-0CE9-8147-ACF4-CAB1B4497EFD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3FA25736-86DE-2642-B4BC-DB4E57AFD6BE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3F8C0D32-B302-2B40-A2E6-E12D5854BC72.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3F439B5D-433B-BC43-8607-E0963B73F0C8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3F18393E-3020-3847-ADF5-079602451744.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3F0BFAF3-C410-C74F-A206-CA1C482F8037.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3EF169AF-18C8-434B-A617-3C23A875333C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3EBEB251-9604-A940-B394-EC9EEE95E36A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3E5FCB73-190A-6C41-8894-F863EA3A14DF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3E267D7B-4EAC-6641-B097-973863F4C810.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3D31A7DD-01E4-6741-AA9E-864D902B5A34.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3D01EDE3-B00C-3E47-8D48-870B58CFA185.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3CFCECFD-BEE0-B240-89FF-8946242EEB71.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3CA3648A-6CF7-8D49-9FAC-182573579C37.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3C70E823-3AE9-9640-A70F-DFE0F42A0CBD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3BF02594-92C5-434B-8238-06ABEBB927DF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3BE31751-F1F0-FC49-AAD6-DAEF9343593E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3BE2FEB3-1A7B-6248-9AFC-ED5BFAF99D6D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3B99C0F8-46E7-5F4E-BD6E-5FCBB527C1B7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3B571958-819E-9949-A17B-82BA53F36802.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3B406B15-5B32-9F46-B6B1-78E6A59DABC4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3A353FE5-1337-704B-A2F9-7E1C6AD723FB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/39D0B007-18A8-AD4E-A851-766BEDADF78D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/39827562-FA10-1040-AAD7-351D7780EA51.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/393CB560-1D79-B74C-AFA2-9CEFAA0F91D1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/39183015-9B11-9749-9610-181B02D5C6B3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/38FC81A7-964B-D649-8539-10D8A98D03F8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/38547F8B-34D5-FE4D-820A-6B1FDEC04C7E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/38098DC2-2320-1D40-AE2D-0E573913E940.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3803A0E3-2E65-FC4D-8374-9E2B032E9ED3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/37CA6D8D-7255-D24C-A145-621D9E65D171.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/377AF195-4194-F346-B911-0B9B7AF7E793.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3765D8D6-FADD-2045-B2E1-64B2975DCA52.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/374A0360-B680-794D-8FE6-C9C04D412463.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3740A43A-952E-E745-95CE-D92E569A14F5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/37368646-477A-B84E-AFBB-BF48B374602E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3721DAFD-3858-044C-A666-4D3386773502.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/37140526-3D4D-8E43-BBE8-39BEA0C73060.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/35D878BC-AE06-BF44-A42D-FDA35F3311DF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/353ED36D-F86C-734F-AAB1-C94CC94BADFB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/35130043-9792-814B-A268-DC354A481FE2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/34972205-9F86-FC4C-B58F-4FB0C85C745A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/33DF8A8D-882A-1F4B-BEB7-D3682382DF9D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/33BE7BC1-D8DB-E34E-A245-7EC0984C3B68.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3399D5C2-60FE-8340-A902-4B8CDF81D2D6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/32A1E228-33BB-3F4D-9E81-A7BDEF649317.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/32596DD6-EC89-094D-9B13-E837202E48B9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/323D91E9-D070-804B-8D76-2903B0857204.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/32197DAF-C6E0-B34B-ACE8-A90D99D3055E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/320F5ADE-4B5B-E044-BDD9-5E1497BB6011.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/320649E9-A147-A94E-B30F-CC3E2AEE6DA2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3202E184-62F2-1743-BA2B-7D9CB78DF5B9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/31915C17-A6FE-D74D-B1DD-5C2A8DA4D897.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3163049D-6326-7243-BB7C-481C30CC87E3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/31325A78-86D3-9B4B-A7D5-640D2835AD5E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/30F50583-FB0D-4540-B98D-11277F975549.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/30D8D375-BA9F-A442-94C1-2CB0BCF29D43.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3081EFC4-9A34-7148-94B8-F6D0FF4C150D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/30550F15-9F0E-574A-997D-A4321B07D97F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/303A1106-2D48-0746-9EC6-BB8143EDADF6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/3029320D-7F96-3943-801F-864681CDBEFB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/301CCE34-C961-7347-8AE5-9AC4F3557DF7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2FF62E37-6992-AB45-81D1-0C73CB6574DA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2FF52587-7484-DD4C-8018-B06C9CAF8C4F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2F105110-6374-274F-9E30-3A244E4189D9.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2EC42098-114C-D54A-BEE6-59436BC0988A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2E7BA13E-429C-B443-9B17-4F29C4443953.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2E751CC8-A834-994A-B003-42D3FC7EBC49.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2E2D8AA8-09CE-804D-98AC-DADD5231EE29.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2E0F9D63-04C3-3B41-8508-DEFB419C1DFB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2CC26F91-38FC-EA4D-A8B8-802B563DB7F1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C8A4447-07FE-964C-8BC5-F348C67D3B37.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C7FEC34-489B-D64B-BA3A-89C0E9590A69.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C6AD1EF-23A8-9C4C-9D8C-7DBC11AB5D38.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C56E5CC-5220-B74F-A3BD-2A6DBC94D26D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C38B583-974A-E54A-AA10-B0F586626E89.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C2D1FEF-E296-434D-A385-AFEB7D867FA0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C275DBC-9374-3642-971E-17A213FAEB52.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2C22A062-9235-8A4D-ADD8-C44E728DACA5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2BE78CCE-AABB-BA48-B874-335248686D78.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2BC77154-E8F6-7D4B-9A7D-24C0181F24F7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2BA4712F-AA87-F44A-B62E-395B98EF23AC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2B4CD702-FC03-3441-99DE-EAA0C14203B8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2B296B80-15DA-2947-B6EF-E983CFCAFB1B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2B13B11F-8F3F-B948-9D3E-E485E436CF73.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2AB39BB1-D45E-3A42-8E6D-E84A88F8E800.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2A24A9A8-3055-DE49-9F49-BA2BE0A4F8C6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/29CF9031-567D-C24C-9C9E-D69BA0C5174E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2938E120-85F3-684E-A324-52BFE9597153.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/29127741-C041-C448-BC56-618A469C2137.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/28ADA949-24F2-FF47-92F4-834DAD13A70D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/28946171-3DAC-4D47-82CF-BB9062360215.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/286DDD00-FB00-8947-958B-09FDD132489A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/286C37DE-04FF-A141-B64A-ACC829377E1C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/285FD5BF-FF2D-F545-802F-212D5B48CA19.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/282D5D38-8E82-2F4A-84B7-D209364A722A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/28043B2F-913D-3749-A5A9-BFA94F34177A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/27C3F5D9-DF4F-7A43-BB11-CE76BBCD3DB8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/27B78951-F759-F34F-9FB1-BD47096AFB6A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/27B583ED-B3A2-964C-A03C-7E132B79E0E4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2708BEB0-001C-B343-8033-32B178E45DB0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/26DC5596-A7BA-524A-AB29-EAAEFAC89D69.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/26A239BF-6050-BC40-8A55-7D4F2E80C7A8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/259DFF9A-6CC1-6C43-965A-572741142FC2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2566DE5A-CFD9-7E43-BF90-EF68F340E998.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/24C1F5CF-9AB5-204F-ABE5-B2E3889C641E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/247628A2-E2B2-A248-B1D4-F7031C7974ED.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/24331541-E912-EC4B-9D59-19619F987945.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/242CDBE3-9B10-BF44-9F8F-71CABE101362.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/23E4A4C9-98D3-4B4E-9303-DF83E5593AF5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/23DF1965-F78F-F24E-AC93-7B0DD53A671D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/23BD7EBA-F18C-0F4D-9FB9-586866C03356.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/22EED583-7451-8A40-8C6C-BBE7A1C6CC74.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/22C1AFE1-27CC-5240-993A-BDC190BEE4E8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/22920119-E1FB-7646-9961-C985DE38322B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/220FC0C6-8A82-C748-AEF6-C8358890EA6E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2198C896-2647-1C4C-BE7A-6331BE119954.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/2194CCD4-F88F-2048-B023-CF68B1A9336A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/213BB529-0A9C-BB4D-A8D5-1319E0D262A6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/21343038-1CBC-4540-A9C5-9EB2951CC413.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/213221BF-2A3C-4944-BD34-D57D40C05377.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/21202D47-6219-394E-B088-35AD9D0744AF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/20C4AA3A-7D60-A64F-B22A-AF2E9AF04A87.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/201CEC2E-70C4-7644-8E63-1461F2465831.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1FFA58B3-BC20-5149-A48B-4E05C97A58F6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1FBC832E-C75E-9E48-A66A-D58B0E6D2CFA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1F9A5F97-85FA-DD45-B0A4-0740FBB6156A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1F79CAA4-6F13-164F-8868-D7D573D28C89.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1F36893F-1A75-C846-8C66-1BBF8E5516A1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1F34FB9E-CDA3-E14A-93CC-AFE722ADBC56.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1EC6B09F-9934-5640-9694-869F0D52A1E4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1E80F395-9D68-9746-9B89-99AAC4D8A878.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1E74776F-18A8-BA44-BBA0-B334527402FD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1DF4231B-A473-A94A-A54A-73063FBDBB05.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1DE26755-016D-B345-8E0D-415076563C35.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1D895221-FBC6-B346-A6E2-DEE6EC5738FD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1D3E6FFF-449B-164D-BE6A-44475E7C722B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1D1377E2-34C6-D040-BE05-52B89A3A86C7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1CEE337E-4DA4-7F43-8AB1-B8EBF32DF703.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1CBE70DB-3DCD-8B48-8BFE-C091E6F14ADE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1CA37EC2-13C8-674C-AE25-F29A0403CCE3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1C522457-975E-184A-B3AB-B71A2CB0D201.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1C0433B0-6EBD-164B-B4D2-20BCE18B7691.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1BAB220C-433D-304E-BF76-E336B051869D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1B6CF8A4-46B2-1B49-8EB5-693F1C1C20DB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1B37D07C-2FC5-BD4D-AC2B-09DED2B9EEAB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1B0C1282-6E5E-3B4B-9B69-99A046790B82.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1AD664BA-2A8D-5D46-915D-8A8EE1EB068D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1AAFA575-96B0-994D-898D-A3DA7945FB2C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1A945F04-1D56-BF41-A18F-F075CCC0D078.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/19B642E7-1347-4D44-B87A-EB33D053AEC4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/19B0F384-7B00-374A-A079-EFF75DE31024.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/197CCDA3-DC6F-B844-A8E1-68B3C8098CCD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/18F43B0A-A322-344A-9FF2-7D2EDE58CD01.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/18912A27-5BE1-3141-808B-6B1AE5D1A429.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/185B9CFD-7369-B744-B24E-8370E8DCA2D0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/184CD529-71A7-524D-A297-C45A819DBC0D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/184021C8-52C3-D345-A988-3E0BE107E40E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/17DC6FFE-0691-D246-89E9-6A925D5396A8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/176AEB14-91F2-B447-B7A9-2FC079342047.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/172D0CA3-142D-0644-9E44-7FBD37300997.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1639753E-C379-0442-95E8-9002F9C42C48.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/16348134-F2AD-CE44-81CC-BBEC5ED0DABB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/15E1B32F-05DB-9E4D-AC5E-E894A75EB430.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/155AE633-1F08-F742-99AF-8B2E29562F50.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1554E9F3-EAC8-2646-A087-751D61DE5CD2.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1539EE84-420B-7547-9C0F-826DCD72EB54.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/150A8560-D6F0-C845-9F2A-2F133FACE014.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/15035433-AB0D-C442-93CC-CCC3441A1F47.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/14E539C0-2530-7B43-8E5C-F605D8A98864.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/14C29ECD-EFF2-7A47-8D93-F73726799AF8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/148C5536-9D5E-2149-97E3-401DDEB0AA5D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1464D0E2-DE64-BF4A-915C-73649614EF1D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1436145A-93BF-D843-A23C-37F7BBC5D964.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1418E907-EC26-5F40-A712-1DE5BFA47745.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/13E13698-3395-F04D-BEA5-3432E004853E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1375F34B-9FFB-F94B-BBFB-C3F1E627C132.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/134B8DC8-8992-424A-9443-E28D6DC2098D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/12BFD246-1A7F-B444-8556-046C4D496C46.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/121A8BF7-8C91-ED45-9291-7520062AEDD4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/11B09389-B869-9344-BE06-95992CB1E885.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/1154F604-6FD8-314D-B577-84E34CA0DCBA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/10F17012-4CDD-234D-A325-58F19A80DA29.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/10EB7F5D-56FE-2D4E-8629-77A35389A881.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/10BC2F4D-25B7-FD40-9A6B-650FC426E46D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/10856BCD-A674-BE4B-9060-960F72D940E1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/107CFC68-AADD-DA4D-AC07-BD25257E580D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/106704C1-6291-DA40-BC33-FEAD65A53665.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/103E47C3-76FF-7E4C-9557-7A7815882B57.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/101CD8C4-1E3D-9A48-99E7-70B517BAB8FD.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0FDBF087-A30D-6149-812A-249BF68BF01B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0F954E51-5D0D-2845-88C1-23768433B70D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0F72ACBC-F3A5-5E47-9DA0-F4127B456A97.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0F4C1DDC-1904-B343-BBB1-D7766134CA6E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0EE636C2-A33C-7140-B25B-23731B47A837.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0EB32AE6-A643-DD45-8010-5C9D0506F1D3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0E689574-070F-344C-8837-3722C0B9BEC1.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0E570D07-1AFE-5B42-B211-C62CC7F56648.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0E2F82B9-5934-2740-9413-4ED86D410562.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0DAC2B46-61DA-7145-B931-75817A99BB63.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0D944AE5-0829-8F40-8ABD-D2488FB092CB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0D839FD8-C00E-AE48-A35B-07787DE168C8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0D0182EE-1180-DC42-8274-89F0121A0CE7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0CB89FFA-E34F-EC41-8A5F-69103F0BB422.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0CB73C7E-503B-1344-8719-7AC3FE42E77D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0CA6D3F4-5F17-0E42-85BF-B8480D1FB1CF.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0C9637E6-356F-8A4A-99D1-AAEA579350DE.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0C567832-7410-F84C-A1AA-6BC1C0726483.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0BF6EA26-99B1-5D44-BAA5-DA1AC028D55F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0BD36899-D446-E142-AC94-D8F418D9F391.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0BA4E288-201B-714E-A985-046EAC9D9BFC.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0B69C9BC-0121-AA43-908E-DD4D33EBF188.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0B366A6C-B4BF-2F4E-9041-F3FF1E3028D0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0B238FEF-9C2F-404A-91A9-366A5E96D7CB.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0ABA8784-8DAA-3742-B93B-0027BB5C6E68.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0A7364F5-3A54-8943-AE10-EEE8D80EB0E4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0A5F8424-555B-5647-8E99-5F40D7C8C66D.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0A25314D-4238-8148-B4CA-AB568E8823A4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0A0EF64D-AC12-9048-86FB-085B8EB8FC6E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/09564F1C-97D0-214A-88B4-6E00E1F3A9AA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/092C6A8F-7784-A446-8867-585B3FA6A8C8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/092A6D52-1085-BD4C-9331-B04BB33C2724.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/08534C57-EBE5-AA4E-B1CE-0CD8F2493A47.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/07E72CD0-3697-324E-9C41-CF6EE2CF6105.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/07CA66F4-95FC-8D45-A6CA-26D7D4083A49.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/07C52A0F-8247-DC4B-BAE3-7C9AA86A736C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/07B4E078-5041-CF4F-9A23-461A96684056.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/075600CE-B7DF-6B49-8C33-121CC489E5C8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/06EF9457-3DF8-A14E-96A1-0B0276FAC1EA.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/06BEAD96-6DF7-A941-86BB-824E0425C0B7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/06BAE019-5D28-0040-BCB2-89B252F1ED95.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/06A84173-7359-E649-939E-6905D4D5D641.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0662491F-1E41-B64F-9915-36DE2C208352.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0618C2D4-D4A7-AF48-BA6D-F8F99934884F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/05F96B01-F942-7A47-8D66-D5659F2FF0B3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/05CB23C1-442D-C643-A8BC-668B6ABAE4A3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/05A002B0-AD0D-1B42-8967-4D2061C2507F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0575357E-2120-FF44-8825-FD8727CB0EB0.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/056961D1-7FB3-8B4D-9299-00D2A1C7A18F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0564742F-EE98-4343-9793-439C2D6E5240.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/04D51EC1-1C1C-BE4B-A495-6D52D67D8831.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/04B7D2F0-521B-D44C-9450-4FDE07659603.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/04AA14C9-068F-434D-8136-FE7398A9C05C.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/048AD428-6A29-CA43-9E61-D79D5C1E962B.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/04524804-B652-034F-B5B1-86F2045665D6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0427D517-E316-D54D-9B9B-B5F1EAD6DE35.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0418705A-0A6E-A247-9EBE-FF0153EB5F93.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/03ECD3E7-56E9-A04E-B49C-357984E6FE5E.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/03EB2F9E-2CC3-A44A-9FFA-FD64294C68E3.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/03B8DE5C-9860-944B-AFDA-B3F4593551A7.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/03A1617E-B3BA-8E41-9786-740B0D285EB6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/039F7B49-B45F-3C4C-A18D-EDEC36CE9F44.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/035FB8B3-DFC5-904E-AE44-882F3F5473C4.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/031D4F38-31B5-C143-A027-41CF119F41A5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/02D6AA36-395E-304B-A165-4BEFF691B88F.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/02931CDF-04A1-F442-9522-475FD5856DD5.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/02930928-DAC2-8B47-BA91-AA273F5AB420.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/01D8D81D-1E1F-A348-9082-34AE5215EFE8.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/006E5724-DF4F-4A43-9A3C-0F401D452FB6.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/003128DA-2744-434C-9579-7FA9476C768A.root',
#       '/store/mc/RunIIAutumn18DR/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/GEN-SIM-RAW/FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/00001/0030D111-687D-D546-A2EA-4B510D1A5AAE.root',

	),
    #eventsToProcess = cms.untracked.VEventRange(eventList)
)


## How many events to process
#if   options.demoMode : process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
#else                  : process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5970))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100000))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag depending on the sample type
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag.globaltag = options.globalTag  

## Create output file
## Setup the service to make a ROOT TTree
process.TFileService = cms.Service("TFileService", 
		                   fileName = cms.string(options.outputFileName))
				   
## Decide which label to use for MET Flags
#if   options.isMC : triggerFlagsProcess = "PAT"
#else              : triggerFlagsProcess = "RECO"
triggerFlagsProcess = "RECO"

## generate track collection at miniAOD
from PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi import unpackedTracksAndVertices
process.unpackedTracksAndVertices = unpackedTracksAndVertices.clone()

# Make the tree 
#process.tree = cms.EDAnalyzer("DisPho",
process.tree = cms.EDAnalyzer("DisPhoMulti",
   ## additional collections
   kuRechitValid = cms.bool(options.kuRechitValid),
   rawCollectionsValid = cms.bool(options.rawCollectionsValid),
   mcValid = cms.bool(options.mcValid),
   ## LHC Info
   lhcInfoValid = cms.bool(options.lhcInfoValid),
   ## blinding 
   blindSF = cms.int32(options.blindSF),
   applyBlindSF = cms.bool(options.applyBlindSF),
   blindMET = cms.double(options.blindMET),
   applyBlindMET = cms.bool(options.applyBlindMET),
   ## object prep cuts
   jetpTmin  = cms.double(options.jetpTmin),
   jetEtamax = cms.double(options.jetEtamax),
   jetIDmin  = cms.int32(options.jetIDmin),
   rhEmin    = cms.double(options.rhEmin),
   phpTmin   = cms.double(options.phpTmin),
   phIDmin   = cms.string(options.phIDmin),
   ## extra object pruning
   seedTimemin = cms.double(options.seedTimemin),
   nPhosmax    = cms.int32(options.nPhosmax),
   ## photon storing options
   splitPho = cms.bool(options.splitPho),
   onlyGED  = cms.bool(options.onlyGED),
   onlyOOT  = cms.bool(options.onlyOOT),
   ## lepton prep cuts 
   ellowpTmin  = cms.double(options.ellowpTmin),
   elhighpTmin = cms.double(options.elhighpTmin),
   mulowpTmin  = cms.double(options.mulowpTmin),
   muhighpTmin = cms.double(options.muhighpTmin),
   ## recHit storing options
   storeRecHits = cms.bool(options.storeRecHits),
   ## pre-selection
   applyTrigger = cms.bool(options.applyTrigger),
   minHT        = cms.double(options.minHT),
   applyHT      = cms.bool(options.applyHT),
   phgoodpTmin  = cms.double(options.phgoodpTmin),
   phgoodIDmin  = cms.string(options.phgoodIDmin),
   applyPhGood  = cms.bool(options.applyPhGood),
   ## matched criteria
   dRmin = cms.double(options.dRmin),
   pTres = cms.double(options.pTres),
   gendRmin = cms.double(options.gendRmin),
   genpTres = cms.double(options.genpTres),
   trackdRmin = cms.double(options.trackdRmin),
   trackpTmin = cms.double(options.trackpTmin),
   genjetdRmin = cms.double(options.genjetdRmin),
   genjetpTfactor = cms.double(options.genjetpTfactor),
   leptondRmin = cms.double(options.leptondRmin),
   ## extra JER info
   smearjetEmin = cms.double(options.smearjetEmin),
   ## triggers
   inputPaths     = cms.string(options.inputPaths),
   inputFilters   = cms.string(options.inputFilters),
   triggerResults = cms.InputTag("TriggerResults", "", "HLT"),
   triggerObjects = cms.InputTag("slimmedPatTrigger"),
   ## met filters
   inputFlags       = cms.string(options.inputFlags),
   triggerFlags     = cms.InputTag("TriggerResults", "", triggerFlagsProcess),
   ecalBadCalibFlag = cms.InputTag("ecalBadCalibReducedMINIAODFilter"),			      
   ## tracks
   tracks = cms.InputTag("unpackedTracksAndVertices"),
   ## vertices
   vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
   ## rho
   rho = cms.InputTag("fixedGridRhoFastjetAll"), #fixedGridRhoAll
   ## METs
   #mets = cms.InputTag("slimmedMETsModifiedMET"),
   mets = cms.InputTag("slimmedMETs"),
   ## jets
   #jets = cms.InputTag("updatedPatJetsUpdatedJEC"),
   jets = cms.InputTag("slimmedJets"),
   ## electrons
   electrons = cms.InputTag("slimmedElectrons"),
   ## muons
   muons = cms.InputTag("slimmedMuons"),
   ## photons
   gedPhotons = cms.InputTag("slimmedPhotons"),
   ootPhotons = cms.InputTag("slimmedOOTPhotons"),
   ## ecal recHits
   recHitsEB = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
   recHitsEE = cms.InputTag("reducedEgamma", "reducedEERecHits"),

   ## ecal kuRecHits
   #kuRecHitsEB = cms.InputTag("kuEcalRecHit", "kuRecHitsEB"),
   #kuRecHitsEE = cms.InputTag("kuEcalRecHit", "kuRecHitsEE"),

   #kuStcRecHitsEB = cms.InputTag("kuStcEcalRecHit", "kuStcRecHitsEB"),
   #kuStcRecHitsEE = cms.InputTag("kuStcEcalRecHit", "kuStcRecHitsEE"),

   #kuNotRecHitsEB = cms.InputTag("kuNotEcalRecHit", "kuNotRecHitsEB"),
   #kuNotRecHitsEE = cms.InputTag("kuNotEcalRecHit", "kuNotRecHitsEE"),

   kuNotStcRecHitsEB = cms.InputTag("kuNotStcEcalRecHit", "kuNotStcRecHitsEB"),
   kuNotStcRecHitsEE = cms.InputTag("kuNotStcEcalRecHit", "kuNotStcRecHitsEE"),

   ## ecal Multi rechits

   ##kuWtRecHitsEB = cms.InputTag("kuWtEcalRecHit", "kuWtRecHitsEB"),
   ##kuWtRecHitsEE = cms.InputTag("kuWtEcalRecHit", "kuWtRecHitsEE"),

   kuWtStcRecHitsEB = cms.InputTag("kuWtStcEcalRecHit", "kuWtStcRecHitsEB"),
   kuWtStcRecHitsEE = cms.InputTag("kuWtStcEcalRecHit", "kuWtStcRecHitsEE"),

   ##kuWootRecHitsEB = cms.InputTag("kuWootEcalRecHit", "kuWootRecHitsEB"),
   ##kuWootRecHitsEE = cms.InputTag("kuWootEcalRecHit", "kuWootRecHitsEE"),

   kuWootStcRecHitsEB = cms.InputTag("kuWootStcEcalRecHit", "kuWootStcRecHitsEB"),
   kuWootStcRecHitsEE = cms.InputTag("kuWootStcEcalRecHit", "kuWootStcRecHitsEE"),

   kuMfootStcRecHitsEB = cms.InputTag("kuMfootStcEcalRecHit", "kuMfootStcRecHitsEB"),
   kuMfootStcRecHitsEE = cms.InputTag("kuMfootStcEcalRecHit", "kuMfootStcRecHitsEE"),

   kuMfootCCStcRecHitsEB = cms.InputTag("kuMfootCCStcEcalRecHit", "kuMfootCCStcRecHitsEB"),
   kuMfootCCStcRecHitsEE = cms.InputTag("kuMfootCCStcEcalRecHit", "kuMfootCCStcRecHitsEE"),

   ## ecal uncalib recHits
   ku_uncalibratedRecHitsEB = cms.InputTag("kuMfootEcalMultiFitUncalibRecHit","kuMfootEcalUncalibRecHitsEB"),
   ku_uncalibratedRecHitsEE = cms.InputTag("kuMfootEcalMultiFitUncalibRecHit","kuMfootEcalUncalibRecHitsEE"),
   uncalibratedRecHitsEB = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"),
   uncalibratedRecHitsEE = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"),

   #ku_uncalibratedRecHitsEB = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEB"),
   #ku_uncalibratedRecHitsEE = cms.InputTag("kuEcalMultiFitUncalibRecHit","kuEcalUncalibRecHitsEE"),

   #kuNot_uncalibratedRecHitsEB = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEB"),
   #kuNot_uncalibratedRecHitsEE = cms.InputTag("kuNotEcalMultiFitUncalibRecHit","kuNotEcalUncalibRecHitsEE"),




   ## digis
   EBdigiCollection = cms.InputTag("ecalDigis","ebDigis"),
   EEdigiCollection = cms.InputTag("ecalDigis","eeDigis"),

   ## gen info
   isGMSB       = cms.bool(options.isGMSB),
   isHVDS       = cms.bool(options.isHVDS),
   isBkgd       = cms.bool(options.isBkgd),
   isToy        = cms.bool(options.isToy),
   isADD        = cms.bool(options.isADD),
   xsec         = cms.double(options.xsec),
   filterEff    = cms.double(options.filterEff),
   BR           = cms.double(options.BR),
   genEvt       = cms.InputTag("generator"),
   gent0        = cms.InputTag("genParticles", "t0"),
   genxyz0      = cms.InputTag("genParticles", "xyz0"),
   pileups      = cms.InputTag("slimmedAddPileupInfo"),
   genParticles = cms.InputTag("prunedGenParticles"),
   genJets      = cms.InputTag("slimmedGenJets"),
)


# Set up the path
#process.treePath = cms.Path(
process.tree_step = cms.EndPath(
	process.unpackedTracksAndVertices +
	process.tree
)

process.jwk_digisunpacker = cms.Sequence(
				process.L1TRawToDigi+
				#siPixelDigis+
				#siStripDigis+
        		process.ecalDigis+
        		process.ecalPreshowerDigis#+
	                        #hcalDigis+
	                        #muonCSCDigis+
	                        #muonDTDigis+
	                        #muonRPCDigis+
	                      	#castorDigis+
	                      	#scalersRawToDigi+
	                      	#tcdsDigis+
	                      	#onlineMetaDataDigis
        			)

process.jwk_calolocalreco = cms.Sequence(
					#process.ku_min_ecalLocalRecoSequence
               #process.ku_multi_ecalLocalRecoSequence
               process.ku_reduced_multi_ecalLocalRecoSequence
               #process.ku_ecalLocalRecoSequence
               #process.ecalLocalRecoSequence
					#process.hcalLocalRecoSequence
				)

process.jwk_localreco = cms.Sequence(
				process.bunchSpacingProducer+
				#process.trackerlocalreco+
				#process.muonlocalreco+
				process.jwk_calolocalreco
				#process.castorreco
				)

process.jwk_highlevelreco = cms.Sequence(
			                     #process.egammaHighLevelRecoPrePF*
                              #process.particleFlowReco*
                              #process.egammaHighLevelRecoPostPF*
                              #process.muoncosmichighlevelreco*
                              #process.muonshighlevelreco *
                              #process.particleFlowLinks*
                              #process.jetHighLevelReco*
                              #process.metrecoPlusHCALNoise*
                              #process.btagging*
                              #process.recoPFMET*
                              #process.PFTau*
                              #process.reducedRecHits #*
                              #process.cosmicDCTracksSeq
                             )

process.jwk_reconstruction = cms.Sequence(
				#process.localreco*
            process.jwk_localreco*
				#process.globalreco*
				#process.jwk_highlevelreco*
				process.logErrorHarvester
)

process.content = cms.EDAnalyzer("EventContentAnalyzer")
process.content_step = cms.Path(process.content)

#process.raw2digi_step = cms.Path(process.RawToDigi)
process.ecalraw2digi_step = cms.Path(process.jwk_digisunpacker)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.jwk_reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)

process.schedule = cms.Schedule(
		#process.raw2digi_step,
		process.ecalraw2digi_step,
      process.L1Reco_step,
		process.reconstruction_step,
		#process.content_step,
		process.endjob_step,
		process.tree_step
)

### Extra bits from other configs
#process.options = cms.untracked.PSet(
#	numberOfThreads=cms.untracked.uint32(options.nThreads),
#	numberOfStreams=cms.untracked.uint32(options.nThreads/2)
#)
process.options = cms.untracked.PSet()

from FWCore.ParameterSet.Utilities import convertToUnscheduled
if options.runUnscheduled : 
	process = convertToUnscheduled(process)

from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
if options.deleteEarly :
	process = customiseEarlyDelete(process)

