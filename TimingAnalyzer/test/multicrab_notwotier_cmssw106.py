#! /usr/bin/env python

import os
from optparse import OptionParser

from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

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


def docrab( dataset ):

    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        # External files needed by CRAB
        inputDir     = '/home/t3-ku/jaking/ecaltiming/CMSSW_10_6_20_recali/src/Timing/TimingAnalyzer/test/input/'
        inputPaths   = 'HLTpathsWExtras.txt'
        inputFilters = 'HLTfilters.txt'
        inputFlags   = 'METflags.txt'
        inputCaliDB   = 'EcalTimeCalibConstants_2018_RunD_UL_Corr_v2.db'
        #inputJSON    = 'golden2016.json'
        #inputJSON    = 'golden2017.json'
        inputJSON    = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
        inputRuns  =   'FULL'

        secInputPaths = dataset[1] 

        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
        from CRABClient.UserUtilities import config
        config = config()

        config.General.workArea    = options.workArea
        config.General.requestName = None

        config.JobType.pluginName  = 'Analysis'
        #config.JobType.psetName    = 'dispho_twotier.py'
        #config.JobType.psetName    = 'dispho_raw_twotier.py'
        #config.JobType.psetName    = 'dispho_raw_twotier_2017D_multi.py'
        config.JobType.psetName    = 'dispho_noraw_notwotier_nomulti.py'
        #config.JobType.numCores    = 8
        config.JobType.pyCfgParams = None
        config.JobType.inputFiles  = [ inputDir+inputPaths, inputDir+inputFilters, inputDir+inputFlags, inputDir+inputCaliDB ]

        config.Data.inputDataset   = None
        #config.Data.useParent      = True
        #config.Data.secondaryInputDataset = secInputPaths
        config.Data.lumiMask       = inputJSON
        config.Data.splitting      = 'EventAwareLumiBased'
        #config.Data.unitsPerJob    = 25000
        #config.Data.splitting     = 'Automatic'
        config.Data.unitsPerJob   = 100000
        #config.Data.runRange       = inputRuns

        config.JobType.allowUndistributedCMSSW = True
        config.Data.publication    = False
        config.Site.storageSite    = 'T2_US_Nebraska'
        config.Data.outLFNDirBase  = '/store/user/jaking/ecalTiming/'
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDataAndOpts = [[dataset[0]]]

        for inDO in inputDataAndOpts:
	    print( inDO )
            # inDO[0] is of the form /A/B/C. Since A+B is unique for each inDS, use this in the CRAB request name.
            primaryDataset = inDO[0].split('/')[1]
	    print( primaryDataset )
            runEra         = inDO[0].split('/')[2]
            print( runEra )
            dataset        = inDO[0].split('/')[3]
            print( dataset )
            
            #trial          = "onetier_mini_v9_2017_rt3" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "onetier_mini_v9_early" # as 41 above  onetier_mini_nolhc_v9
	         #trial          = "onetier_mini_singlephoton_v9" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "ot_106_mini_v10_2018_redele" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "ot_106_mini_v10_2018D_gt28_redele" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "ot_106_mini_v10_2018C_gt28_redele" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "ot_106_mini_v10_2018_gt28_redele" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "ot_106_mini_v10_2017_redele" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "ot_106_mini_v10_2016_redele" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "onetier_mini_v10_2016_redele" # as 41 above  onetier_mini_nolhc_v9
            #trial          = "ot_106_mini_v11_t4_2018D_gt28_redele" # +recali rechit collection produced
            trial          = "ot_106_mini_v12_t5_2018D_gt27_redele" # redo

            #runs           = inputRuns
            runs	   = "Full"

            #config.General.requestName   = primaryDataset+"_"+runEra+"_v7"
            config.General.requestName   = trial+"_"+primaryDataset+"_"+runEra+"_"+runs+"_"+dataset+"_dispho"
            config.Data.outputDatasetTag = trial+"_"+primaryDataset+"_"+dataset+"_"+runEra+"_"+runs+"_dispho"

            #config.Data.secondaryInputDataset = secInputPaths

#>>>>>>>>>>>>>>>>>>>     #2018   #globalTag=106X_dataRun2_v28
            #config.JobType.pyCfgParams   = ['globalTag=106X_dataRun2_v28',#'nThreads='+str(config.JobType.numCores),
#>>>>>>>>>>>>>>>>>>>	    #2017   #globalTag=106X_dataRun2_v20
            #config.JobType.pyCfgParams   = ['globalTag=106X_dataRun2_v20',#'nThreads='+str(config.JobType.numCores),
#>>>>>>>>>>>>>>>>>>>	    #2016  #globalTag=106X_dataRun2_v27
            config.JobType.pyCfgParams   = ['globalTag=106X_dataRun2_v27',#'nThreads='+str(config.JobType.numCores),
                                            'inputPaths='+inputPaths,'inputFilters='+inputFilters,
                                            'inputFlags='+inputFlags, 'onlyGED=True',
                                            'outputFileName=output.root', 'kuRechitValid=False','rawCollectionsValid=False']


            config.Data.inputDataset     = inDO[0]
            #config.Data.outputDatasetTag = '%s_%s' % (config.General.workArea, config.General.requestName)
	         #config.Data.secondaryInputDataset = secInputPaths
            # Submit.
            try:
                print "Submitting for input dataset %s" % (inDO[0])
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


##33333333333333333333333333333333333333333333333333333333333

def run_multi():

        datasets = [

# Dataset: /EGamma/Run2018-12Nov2019_UL2018-/MINIAOD

            #['/EGamma/Run2018A-12Nov2019_UL2018-v2/MINIAOD',''],
            #['/EGamma/Run2018B-12Nov2019_UL2018-v2/MINIAOD',''],
            #['/EGamma/Run2018C-12Nov2019_UL2018-v2/MINIAOD',''],
            ['/EGamma/Run2018D-12Nov2019_UL2018-v4/MINIAOD',''],
    
# Dataset: /DoubleEG/Run2016-21Feb2020_UL2016-/MINIAOD

            #['/DoubleEG/Run2016B-21Feb2020_ver2_UL2016_HIPM-v1/MINIAOD',''],
            #['/DoubleEG/Run2016C-21Feb2020_UL2016_HIPM-v1/MINIAOD',''],
            #['/DoubleEG/Run2016D-21Feb2020_UL2016_HIPM-v1/MINIAOD',''],
            #['/DoubleEG/Run2016E-21Feb2020_UL2016_HIPM-v1/MINIAOD',''],
            #['/DoubleEG/Run2016F-21Feb2020_UL2016-v1/MINIAOD',''],
            #['/DoubleEG/Run2016G-21Feb2020_UL2016-v1/MINIAOD',''],
            #['/DoubleEG/Run2016H-21Feb2020_UL2016-v1/MINIAOD',''],

# Dataset: /DoubleEG/Run2017-09Aug2019_UL2017-/MINIAOD

            #['/DoubleEG/Run2017B-09Aug2019_UL2017-v1/MINIAOD',''],
            #['/DoubleEG/Run2017C-09Aug2019_UL2017-v1/MINIAOD',''],
            #['/DoubleEG/Run2017D-09Aug2019_UL2017-v1/MINIAOD',''],
            #['/DoubleEG/Run2017E-09Aug2019_UL2017-v1/MINIAOD',''],
            #['/DoubleEG/Run2017F-09Aug2019_UL2017-v1/MINIAOD',''],

# Dataset: /SingleElectron/Run2017-09Aug2019_UL2017-/MINIAOD

             #['/SingleElectron/Run2017B-09Aug2019_UL2017-v1/MINIAOD',''],
             #['/SingleElectron/Run2017C-09Aug2019_UL2017-v1/MINIAOD',''],
             #['/SingleElectron/Run2017C-09Aug2019_UL2017_EcalRecovery-v1/MINIAOD',''],
             #['/SingleElectron/Run2017D-09Aug2019_UL2017-v1/MINIAOD',''],
             #['/SingleElectron/Run2017E-09Aug2019_UL2017-v1/MINIAOD',''],
             #['/SingleElectron/Run2017F-09Aug2019_UL2017_rsb-v2/MINIAOD',''],
             #['/SingleElectron/Run2017F-09Aug2019_UL2017_EcalRecovery-v1/MINIAOD',''],

            ]

	for dataset in datasets :
		docrab( dataset )



run_multi()

