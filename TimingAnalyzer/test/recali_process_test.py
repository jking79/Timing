import subprocess
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.maxEvents = 10
options.outputFile = "EcalTimeRecalibTEST.root"
options.parseArguments()

process = cms.Process("EcalTimeRecalibTEST")
process.options = cms.untracked.PSet(allowUnscheduled = cms.untracked.bool(True))

process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

# Global tag
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from CondCore.CondDB.CondDB_cfi import *
process.GlobalTag = cms.ESSource("PoolDBESSource",
                                 CondDB.clone(connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')),
                                 globaltag = cms.string('106X_dataRun2_v27'),
                                 # Get time calibration (corrections) tag
                                 toGet = cms.VPSet(
                                     cms.PSet(record = cms.string("EcalTimeCalibConstantsRcd"),
                                              tag = cms.string("EcalTimeCalibConstants_2018_RunD_UL_Corr_v2"),
                                              connect = cms.string("sqlite_file:EcalTimeCalibConstants_2018_RunD_UL_Corr_v2.db"),
                                          )
                                 )
)

# import of standard configurations
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                            "root://cms-xrd-global.cern.ch//store/data/Run2018D/EGamma/MINIAOD/12Nov2019_UL2018-v4/210000/C524DC5B-6606-434B-A2A1-BC9ED8F1762F.root"
                            )
)

# Output definition
output_commands = cms.untracked.vstring(
    "drop *",
    "keep *_reducedEgamma_*RecHits_*",
    "keep *_ecalRecalibRecHit_*_*")

process.output = cms.OutputModule("PoolOutputModule",
                                  splitLevel = cms.untracked.int32(0),
                                  outputCommands = output_commands,
                                  fileName = cms.untracked.string(options.outputFile)
)

# Recalibration module
process.load("RecoLocalCalo.EcalRecProducers.ecalRecalibRecHit_cfi")
process.ecalRecalibRecHit.EBRecHitCollection = cms.InputTag("reducedEgamma", "reducedEBRecHits")
process.ecalRecalibRecHit.EERecHitCollection = cms.InputTag("reducedEgamma", "reducedEERecHits")
process.ecalRecalibRecHit.EBRecalibRecHitCollection = cms.string('recalibEcalRecHitsEB')
process.ecalRecalibRecHit.EERecalibRecHitCollection = cms.string('recalibEcalRecHitsEE')
process.ecalRecalibRecHit.doTimeCalib = True

process.recalib_sequence = cms.Sequence(process.ecalRecalibRecHit)
process.path = cms.Path(process.recalib_sequence)
process.outpath = cms.EndPath(process.output)

process.schedule = cms.Schedule(process.path, process.outpath)
