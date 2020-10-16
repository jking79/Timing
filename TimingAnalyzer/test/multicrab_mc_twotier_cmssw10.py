#! /usr/bin/env python

import os
from optparse import OptionParser

from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException
from in_r18D_list import file_list 

def getOptions():
    """
    Parse and return the arguments provided by the user.
    """
    usage = ("Usage: %prog --crabCmd CMD [--workArea WAD --crabCmdOpts OPTS]"
             "\nThe multicrab command executes 'crab CMD OPTS' for each project directory contained in WAD"
             "\nUse multicrab -h for help")

    parser = OptionParser(usage=usage)

    parser.add_option('-c', '--crabCmd',
                      dest = 'crabCmd',
                      default = 'submit',
                      help = "crab command",
                      metavar = 'CMD')

    parser.add_option('-w', '--workArea',
                      dest = 'workArea',
                      default = 'myworkingArea',
                      help = "work area directory (only if CMD != 'submit')",
                      metavar = 'WAD')

    parser.add_option('-o', '--crabCmdOpts',
                      dest = 'crabCmdOpts',
                      default = '',
                      help = "options for crab command CMD",
                      metavar = 'OPTS')

    (options, arguments) = parser.parse_args()

    if arguments:
        parser.error("Found positional argument(s): %s." % (arguments))
    if not options.crabCmd:
        parser.error("(-c CMD, --crabCmd=CMD) option not provided.")
    if options.crabCmd != 'submit':
        if not options.workArea:
            parser.error("(-w WAR, --workArea=WAR) option not provided.")
        if not os.path.isdir(options.workArea):
            parser.error("'%s' is not a valid directory." % (options.workArea))

    return options


#def subcrab( runs ):
def subcrab( runs, events, reqmem ):

    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        # External files needed by CRAB
        #inputDir     = '/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        #inputDir     = '/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        inputDir     = '/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        inputPaths   = 'HLTpathsWExtras.txt'
        inputFilters = 'HLTfilters.txt'
        inputFlags   = 'METflags.txt'
        #inputJSON    = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'

        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
        from CRABClient.UserUtilities import config
        config = config()

        config.General.workArea    = options.workArea
        #config.General.requestName = None

        config.JobType.pluginName  = 'Analysis'
        #config.JobType.pluginName  = 'PrivateMC'
        #config.JobType.psetName    = 'jwk_raw_dispho.py'
        #config.JobType.psetName    = 'dispho_rawlist_twotier.py'
        #config.JobType.psetName    = 'dispho_raw_twotier.py'
        config.JobType.psetName    = 'dispho_mc_twotier_multi.py'
        #config.JobType.numCores    = 8
        #config.JobType.maxMemoryMB = 2250 #reqmem
        #config.JobType.maxJobRuntimeMin = 2750
        config.JobType.pyCfgParams = None
        config.JobType.inputFiles  = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]

        config.Data.inputDataset = None
        #config.Data.useParent      = True
	     #config.Data.secondaryInputDataset = secInputPaths
        #config.Data.useParent      = False
        #config.Data.lumiMask     = inputJSON
        #config.Data.splitting    = 'LumiBased'
        config.Data.splitting    = 'EventAwareLumiBased'
        #config.Data.splitting    = 'Automatic'
        #config.Data.runRange  = runs #'321122-321128'
        config.Data.unitsPerJob  =  10000    
        #config.Data.totalUnits   =  10000
	     # unitsPerJob = 1000 for 321122-321128 and maxMemoryMB = 4000  on EventAwareLumiBased

        #config.Data.outputDatasetTag = 'reducedRAW_EGamma_ntuple'
	     
        config.JobType.allowUndistributedCMSSW = True
        config.Data.publication      = False
        config.Site.storageSite      = 'T2_US_Nebraska'
        config.Data.outLFNDirBase    = '/store/user/jaking/ecalTiming/'
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDataAndOpts = [
            ['/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/MINIAODSIM'],
	    ]
 
        for inDO in inputDataAndOpts:
            # inDO[0] is of the form /A/B/C. Since A+B is unique for each inDS, use this in the CRAB request name.
	    #print( inDO[0] )
            primaryDataset = inDO[0].split('/')[1]
            runEra         = inDO[0].split('/')[2]
            dataset	   = inDO[0].split('/')[3]
	    #infilename	   = inDO[0].split('/')[11]

            #trial          = "tt_kurhs_nolhc_v17"  # as v15 w/ NM pull 17May20   replaced Wt with KansasDummy
            #trial          = "tt_kurhs_nolhc_v18"  # as v15 w/ NM pull 17May20   replaced Wt with KansasDummy and pulling amplitudes from KS uncali rechit collection
            #trial          = "tt_kurhs_nolhc_v19"  # as v18 w/ NM pull 22May20   replaced Wt with KansasDummy and pulling amplitudes from KS uncali rechit collection
            #trial          = "tt_kurhs_mc_v20"  # as v19 w/ NM pull 29May20 _+ new GT for D  replaced Wt with KansasDummy and pulling amplitudes from KS uncali rechit collection
            #trial          = "tt_kurhs_pc_mc_v21"  # as v20 + mc and pcalo
            #trial          = "tt_kurhs_pc_mc_v23"  # v21  ( v22 try 2 think mcValid was false first time ) v23 changed pcalo detid to rawid 
            #trial          = "tt_kurhs_pc_mc_v25"  # v22 try 3  change method of pulling pcalo info   v24 skip
            #trial          = "tt_kurhs_pc_mc_v26"  # v22 try 4  change method of pulling pcalo info
            #trial          = "tt_kurhs_pc_mc_v27"  # added geant track id from pcalo to output
            #trial          = "tt_kurhs_pc_mc_v28"  # as v27 plus depth, bx, event from pcalo, Wt is wt method not dummy
            #trial          = "tt_kurhs_pc_mc_v29"  # as v28 added pCalotime to match kuootstc collection.
            #trial          = "tt_kurhs_pc_mc_v30"  # as v29 with pcalo double checked and expanded.
            #trial          = "tt_kurhs_pc_mc_v31"  # as v30 with p_dv  pulled.
            #trial          = "tt_kurhs_pc_mc_v32"  # as v31 with pcalo time produced in ana by rechit.
            trial          = "tt_kurhs_pc_mc_v32a"  # as v32 w/ rechit Emin set to 0.1 GeV instead of 1.0 GeV

            rname = trial+'_'+primaryDataset+'_'+dataset+'_request_dispho'
            config.General.requestName = trial+'_'+primaryDataset+'_'+dataset+'_request_dispho'
            outdatatag = trial+'_'+primaryDataset+'_'+dataset+'_output_dispho'
            config.Data.outputDatasetTag = trial+'_'+primaryDataset+'_'+dataset+'_output_dispho'


            config.JobType.pyCfgParams   = ['globalTag=102X_upgrade2018_realistic_v20',#'nThreads='+str(config.JobType.numCores), 
                                            'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags, 
                                            'onlyGED=True', 'outputFileName=output.root', #'rlelist='+events,
					                             'kuRechitValid=True','lhcInfoValid=False', 'rawCollectionsValid=True','mcValid=True' ]

            config.Data.inputDataset     = inDO[0]
            config.Data.secondaryInputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18DR-FlatPU28to62NZS_102X_upgrade2018_realistic_v15-v1/GEN-SIM-RAW'
            # Submit.
            try:
                print "Submitting for input dataset %s for runs %s" % (inDO[0], runs)
                print "Request Name: "+rname
                print "Output DatasetTag: "+outdatatag
                crabCommand(options.crabCmd, config = config, *options.crabCmdOpts.split())
                os.system("rm -rf %s/crab_%s/inputs" % (config.General.workArea, config.General.requestName))
            except HTTPException as hte:
                print "Submission for input dataset %s failed: %s" % (inDO[0], hte.headers)
            except ClientException as cle:
                print "Submission for input dataset %s failed: %s" % (inDO[0], cle)

    # All other commands can be simply executed.
    elif options.workArea:

        for dir in os.listdir(options.workArea):
            projDir = os.path.join(options.workArea, dir)
            if not os.path.isdir(projDir):
                continue
            # Execute the crab command.
            msg = "Executing (the equivalent of): crab %s --dir %s %s" % (options.crabCmd, projDir, options.crabCmdOpts)
            print "-"*len(msg)
            print msg
            print "-"*len(msg)
            try:
                crabCommand(options.crabCmd, dir = projDir, *options.crabCmdOpts.split())
            except HTTPException as hte:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, hte.headers)
            except ClientException as cle:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, cle)


def submit_mc_run():

            subcrab( "ALL","",2500 )


submit_mc_run()









