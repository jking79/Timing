import os, re
import FWCore.ParameterSet.Config as cms
  
### CMSSW command line parameter parser
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('python')

## LHC Info
#options.register('lhcInfoValid',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get lhc info');
options.register('rawCollectionsValid',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get digi/uncalRechit');
options.register('kuRechitValid',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to get kuRechit');

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
options.register('inputPaths','/home/t3-ku/jaking/ecaltiming/CMSSW_10_6_20/src/Timing/TimingAnalyzer/test/input/HLTpathsWExtras.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal paths');
options.register('inputFilters','/home/t3-ku/jaking/ecaltiming/CMSSW_10_6_20/src/Timing/TimingAnalyzer/test/input/HLTfilters.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input signal filters');

## met filter input
options.register('inputFlags','/home/t3-ku/jaking/ecaltiming/CMSSW_10_6_20/src/Timing/TimingAnalyzer/test/input/METflags.txt',VarParsing.multiplicity.singleton,VarParsing.varType.string,'text file list of input MET filter flags');

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
#options.register('globalTag','101X_dataRun2_Prompt_v11',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');
options.register('globalTag','106X_dataRun2_v28',VarParsing.multiplicity.singleton,VarParsing.varType.string,'gloabl tag to be used');

## do a demo run over only 1k events
options.register('demoMode',False,VarParsing.multiplicity.singleton,VarParsing.varType.bool,'flag to run over only 1k events');

## processName
options.register('processName','TREE',VarParsing.multiplicity.singleton,VarParsing.varType.string,'process name to be considered');

## outputFile Name
options.register('outputFileName','ku_test_UL8D_dispho.root',VarParsing.multiplicity.singleton,VarParsing.varType.string,'output file name created by cmsRun');

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
#print "LHC Info       : ",options.lhcInfoValid
print "rawCollections : ",options.rawCollectionsValid
print "kuRechit       : ",options.kuRechitValid
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
#process.load('Timing.TimingAnalyzer.jwk_ku_ecalLocalRecoSequence_cff')

#process.load('PhysicsTools.PatAlgos.slimming.metFilterPaths_cff')
process.load('Configuration.StandardSequences.PAT_cff')
#process.load('Timing.TimingAnalyzer.jwk_PAT_cff')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration.StandardSequences.EndOfProcess_cff')

## Message Logger settings
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
#process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger.cerr.FwkReport.reportEvery = 100000

# LHC Info
#process.LHCInfoReader = cms.ESSource("PoolDBESSource",
#				     DBParameters = cms.PSet(
#		messageLevel = cms.untracked.int32(0),
#		authenticationPath = cms.untracked.string('')),
#				     toGet = cms.VPSet( 
#		cms.PSet(
#			record = cms.string("LHCInfoRcd"),
#			tag = cms.string("LHCInfoStartFillTest_v2")
#			)
#		),
#				     connect = cms.string('frontier://FrontierPrep/CMS_CONDITIONS')
#				     )
#
#process.lhcinfo_prefer = cms.ESPrefer("PoolDBESSource","LHCInfoReader")


## Define the input source
#eventList = open(options.rlelist,'r')
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'file:jwk_reco_data_DIGI2RAW.root'),
   #'/store/data/Run2017B/SingleElectron/MINIAOD/09Aug2019_UL2017-v1/130000/000698DC-325D-BA42-8BAB-FE708FC18AE5.root'
    '/store/data/Run2018D/EGamma/MINIAOD/12Nov2019_UL2018-v4/260000/B492981C-E2C5-014A-993E-0C85FF79A330.root'
	#'/store/data/Run2017D/DoubleEG/MINIAOD/31Mar2018-v1/00000/A20F8F1B-4137-E811-A406-B083FED12B5C.root'
	#'/store/data/Run2016B/DoubleEG/MINIAOD/17Jul2018_ver2-v1/00000/FA955B82-4C8D-E811-B99F-008CFA165F44.root'
	#'file:rootSourceFiles/run2017D/miniaod/A20F8F1B-4137-E811-A406-B083FED12B5C.root'
        ),
)


## How many events to process
#if   options.demoMode : process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
#else                  : process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag depending on the sample type
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag.globaltag = options.globalTag  
from CondCore.CondDB.CondDB_cfi import *
process.GlobalTag = cms.ESSource("PoolDBESSource",
                                 CondDB.clone(connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')),
                                 globaltag = cms.string('106X_dataRun2_v28'),
                                 #Get time calibration (corrections) tag
                                 toGet = cms.VPSet(
                                   cms.PSet(record = cms.string("EcalTimeCalibConstantsRcd"),
                                     tag = cms.string("EcalTimeCalibConstants_2018_RunD_UL_Corr_v2"),
                                     connect = cms.string("sqlite_file:EcalTimeCalibConstants_2018_RunD_UL_Corr_v2.db"),
                                          )
                                 )
)


## Create output file
## Setup the service to make a ROOT TTree
process.TFileService = cms.Service("TFileService", 
		                   fileName = cms.string(options.outputFileName))
				   
## Decide which label to use for MET Flags
#if   options.isMC : triggerFlagsProcess = "PAT"
#else              : triggerFlagsProcess = "RECO"
triggerFlagsProcess = "RECO"


process.load("RecoLocalCalo.EcalRecProducers.ecalRecalibRecHit_cfi")
process.ecalRecalibRecHit.EBRecHitCollection = cms.InputTag("reducedEgamma", "reducedEBRecHits")
process.ecalRecalibRecHit.EERecHitCollection = cms.InputTag("reducedEgamma", "reducedEERecHits")
process.ecalRecalibRecHit.EBRecalibRecHitCollection = cms.string('recalibEcalRecHitsEB')
process.ecalRecalibRecHit.EERecalibRecHitCollection = cms.string('recalibEcalRecHitsEE')
process.ecalRecalibRecHit.doTimeCalib = True
process.recalib_sequence = cms.Sequence(process.ecalRecalibRecHit)
process.recalpath = cms.Path(process.recalib_sequence)

## generate track collection at miniAOD
from PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi import unpackedTracksAndVertices
process.unpackedTracksAndVertices = unpackedTracksAndVertices.clone()

## Rerun one MET filter: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#How_to_run_ecal_BadCalibReducedM
baddetEcallist = cms.vuint32(
    [872439604,872422825,872420274,872423218,
     872423215,872416066,872435036,872439336,
     872420273,872436907,872420147,872439731,
     872436657,872420397,872439732,872439339,
     872439603,872422436,872439861,872437051,
     872437052,872420649,872422436,872421950,
     872437185,872422564,872421566,872421695,
     872421955,872421567,872437184,872421951,
     872421694,872437056,872437057,872437313])

process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter("EcalBadCalibFilter",
    EcalRecHitSource = cms.InputTag("reducedEgamma:reducedEERecHits"),
    ecalMinEt        = cms.double(50.),
    baddetEcal       = baddetEcallist,
    taggingMode      = cms.bool(True),
    debug            = cms.bool(False)
)

# Make the tree 
process.tree = cms.EDAnalyzer("DisPhoMulti",
   ## additional collections
   kuRechitValid = cms.bool(options.kuRechitValid),
   rawCollectionsValid = cms.bool(options.rawCollectionsValid),
   ## LHC Info
   #lhcInfoValid = cms.bool(options.lhcInfoValid),
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
   #recHitsEB = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
   recHitsEB = cms.InputTag("ecalRecalibRecHit", "recalibEcalRecHitsEB"),
   #recHitsEE = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
   recHitsEE = cms.InputTag("ecalRecalibRecHit", "recalibEcalRecHitsEE"),

   ## ecal kuRecHits
   kuRecHitsEB = cms.InputTag("kuEcalRecHit", "kuRecHitsEB"),
   kuRecHitsEE = cms.InputTag("kuEcalRecHit", "kuRecHitsEE"),

   kuStcRecHitsEB = cms.InputTag("kuStcEcalRecHit", "kuStcRecHitsEB"),
   kuStcRecHitsEE = cms.InputTag("kuStcEcalRecHit", "kuStcRecHitsEE"),

   kuNotRecHitsEB = cms.InputTag("kuNotEcalRecHit", "kuNotRecHitsEB"),
   kuNotRecHitsEE = cms.InputTag("kuNotEcalRecHit", "kuNotRecHitsEE"),

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
#   process.unpackedTracksAndVertices +
#   #process.ecalBadCalibReducedMINIAODFilter +
#   process.tree
#)

process.tree_step = cms.EndPath(
	process.unpackedTracksAndVertices +
   #process.ecalBadCalibReducedMINIAODFilter +
	process.tree
)

#process.jwk_digisunpacker = cms.Sequence(
#				process.L1TRawToDigi+
#				#siPixelDigis+
#				#siStripDigis+
#        			process.ecalDigis+
#        			process.ecalPreshowerDigis#+
#	                        #hcalDigis+
#	                        #muonCSCDigis+
#	                        #muonDTDigis+
#	                        #muonRPCDigis+
#	                      	#castorDigis+
#	                      	#scalersRawToDigi+
#	                      	#tcdsDigis+
#	                      	#onlineMetaDataDigis
#        			)
#
#process.jwk_calolocalreco = cms.Sequence(
#				#process.ku_min_ecalLocalRecoSequence
#                                process.ku_multi_ecalLocalRecoSequence
#                                #process.ku_ecalLocalRecoSequence
#                                #process.ecalLocalRecoSequence
#				#process.hcalLocalRecoSequence
#				)
#
#process.jwk_localreco = cms.Sequence(
#				process.bunchSpacingProducer+
#				#process.trackerlocalreco+
#				#process.muonlocalreco+
#				process.jwk_calolocalreco
#				#process.castorreco
#				)
#
#process.jwk_highlevelreco = cms.Sequence(
#			      #process.egammaHighLevelRecoPrePF*
#                              #process.particleFlowReco*
#                              #process.egammaHighLevelRecoPostPF*
#                              #process.muoncosmichighlevelreco*
#                              #process.muonshighlevelreco *
#                              #process.particleFlowLinks*
#                              #process.jetHighLevelReco*
#                              #process.metrecoPlusHCALNoise*
#                              #process.btagging*
#                              #process.recoPFMET*
#                              #process.PFTau*
#                              #process.reducedRecHits #*
#                              #process.cosmicDCTracksSeq
#                             )
#
#process.jwk_reconstruction = cms.Sequence(
#				#process.localreco*
#            process.jwk_localreco*
#				#process.globalreco*
#				#process.jwk_highlevelreco*
#				process.logErrorHarvester
#)

#process.content = cms.EDAnalyzer("EventContentAnalyzer")
#process.content_step = cms.Path(process.content)

#process.raw2digi_step = cms.Path(process.RawToDigi)
#process.ecalraw2digi_step = cms.Path(process.jwk_digisunpacker)
#process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.jwk_reconstruction)
#process.endjob_step = cms.EndPath(process.endOfProcess)

process.schedule = cms.Schedule(
		#process.raw2digi_step,
		#process.ecalraw2digi_step,
      #process.L1Reco_step,
		#process.reconstruction_step,
		#process.content_step,
      #process.treePath,
		#process.endjob_step,
      process.recalpath,
		process.tree_step
)

### Extra bits from other configs
#process.options = cms.untracked.PSet(
#	numberOfThreads=cms.untracked.uint32(options.nThreads),
#	numberOfStreams=cms.untracked.uint32(options.nThreads/2)
#)
process.options = cms.untracked.PSet()

#process.schedule.associate(process.patTask)
#from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
#associatePatAlgosToolsTask(process)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.PatAlgos.slimming.miniAOD_tools
#from Timing.TimingAnalyzer.jwk_miniAOD_tools import miniAOD_customizeAllData
#from PhysicsTools.PatAlgos.slimming.miniAOD_tools import miniAOD_customizeAllData

#call to customisation function miniAOD_customizeAllData imported from PhysicsTools.PatAlgos.slimming.miniAOD_tools
#process = miniAOD_customizeAllData(process)

# End of customisation functions

from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
if options.deleteEarly :
	process = customiseEarlyDelete(process)




