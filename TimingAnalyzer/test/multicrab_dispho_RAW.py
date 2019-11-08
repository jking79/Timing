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


#def subcrab( runs ):
#def subcrab( runs, events, reqmem ):
def subcrab( runs, events, lumi, era, ram ):
    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        # External files needed by CRAB
        #inputDir     = '/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        #inputDir     = '/home/t3-ku/jaking/ecaltiming/ku_cmssw_ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/test/input/'
        inputDir     = '/home/t3-ku/jaking/ecaltiming/CMSSW_9_4_10/src/Timing/TimingAnalyzer/test/'
        inputPaths   = 'HLTpathsWExtras.txt'
        inputFilters = 'HLTfilters.txt'
        inputFlags   = 'METflags.txt'
        #inputJSON    = 'golden2016.json'
        #inputJSON    = 'golden2017.json'
        inputJSON    = lumi

        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
        from CRABClient.UserUtilities import config
        config = config()

        config.General.workArea    = options.workArea
        #config.General.requestName = None

        config.JobType.pluginName  = 'Analysis'
        config.JobType.psetName    = 'jwk_raw_dispho.py'
        #config.JobType.numCores    = 8
        config.JobType.maxMemoryMB = ram
        #config.JobType.maxJobRuntimeMin = 1600
        config.JobType.pyCfgParams = None
        config.JobType.inputFiles  = [ inputDir+inputPaths , inputDir+inputFilters , inputDir+inputFlags ]

        config.Data.inputDataset = None
        config.Data.lumiMask     = inputJSON
        #config.Data.splitting    = 'LumiBased'
        config.Data.splitting    = 'EventAwareLumiBased'
        #config.Data.splitting    = 'Automatic'
        config.Data.unitsPerJob  =  4000    
	# unitsPerJob = 1000 for 321122-321128 and maxMemoryMB = 4000  on EventAwareLumiBased
	config.Data.runRange	= runs #'321122-321128'

        #config.Data.outputDatasetTag = 'reducedRAW_EGamma_ntuple'
        config.Data.publication      = False
        config.Site.storageSite      = 'T2_US_Nebraska'
        config.Data.outLFNDirBase    = '/store/user/jaking/ecalTiming/'
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDataAndOpts = [era]

            #['/DoubleEG/Run2016B-v2/RAW'],
            #['/DoubleEG/Run2016C-v2/RAW'],
            #['/DoubleEG/Run2016D-v2/RAW'],
            #['/DoubleEG/Run2016E-v2/RAW'],
            #['/DoubleEG/Run2016F-v1/RAW'],
            #['/DoubleEG/Run2016G-v1/RAW'],
            #['/DoubleEG/Run2016H-v1/RAW'],
            
	    #['/DoubleEG/Run2017A-v1/RAW'],
            #['/DoubleEG/Run2017B-v1/RAW'],
            #['/DoubleEG/Run2017C-v1/RAW'],
            #['/DoubleEG/Run2017D-v1/RAW'],
            #['/DoubleEG/Run2017E-v1/RAW'],
            #['/DoubleEG/Run2017F-v1/RAW'],

	    #'/store/data/Run2018D/EGamma/RAW/v1/000/321/218/00000/5A0A07C1-FE9E-E811-BEDA-FA163E108FC3.root'
 
        for inDO in inputDataAndOpts:
            # inDO[0] is of the form /A/B/C. Since A+B is unique for each inDS, use this in the CRAB request name.
	    #print( inDO[0] )
            primaryDataset = inDO[0].split('/')[1]
            runEra         = inDO[0].split('/')[2]
	    dataset	   = inDO[0].split('/')[3]
	    #infilename	   = inDO[0].split('/')[11]
	    #trial          = "valtest2_cmssw94" # 2017 raw event list
	    #trial	   = "valtest3_cmssw94" # 2016 no event list
            trial          = "valtest5_cmssw94" # 2016/7 deg event list

            config.General.requestName   = trial+"_"+primaryDataset+"_"+runEra+"_"+runs+"_"+dataset+"_dispho"
            config.Data.outputDatasetTag = trial+"_"+primaryDataset+"_"+dataset+"_"+runEra+"_"+runs+"_dispho"

#            config.General.requestName   = primaryDataset+"_"+runEra+"_"+dataset+"_"+infilename[:-5]
#            config.Data.outputDatasetTag = primaryDataset+"_"+runEra+"_"+dataset+"_"+infilename[:-5]

            # for 2016/2017 RAW
            config.JobType.pyCfgParams   = ['globalTag=94X_dataRun2_v6',#'nThreads='+str(config.JobType.numCores), 
                                            'inputPaths='+inputPaths,'inputFilters='+inputFilters,'inputFlags='+inputFlags,
                                            'onlyGED=True', 'outputFileName=output.root', 'lhcInfoValid=False', 'rlelist='+events ]

            config.Data.inputDataset     = inDO[0]
            #config.Data.outputDatasetTag = '%s_%s' % (config.General.workArea, config.General.requestName)
            # Submit.
            try:
                print "Submitting for input dataset %s for runs %s" % (inDO[0], runs)
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

def submit_sample_runs():

	el_path = "/home/t3-ku/jaking/trees/ecal/run_lumi_event_lists/"
	ram = 2500
	lumi = 'golden2016.json'
	era = ['/DoubleEG/Run2016C-v2/RAW']
#	subcrab( "275657-275778", el_path + "sel_deg2016/sel_275657v275778_DEG2016C.txt",lumi,era,ram )
#	subcrab( "275782-275832", el_path + "sel_deg2016/sel_275782v275832_DEG2016C.txt",lumi,era,ram )
#	subcrab( "275833-275836", el_path + "sel_deg2016/sel_275833v275836_DEG2016C.txt",lumi,era,ram )
#	subcrab( "275837-275838", el_path + "sel_deg2016/sel_275837v275837_DEG2016C.txt",lumi,era,ram )
#	subcrab( "275847-275848", el_path + "sel_deg2016/sel_275847v275847_DEG2016C.txt",lumi,era,ram )
#	subcrab( "275886-275890", el_path + "sel_deg2016/sel_275886v275890_DEG2016C.txt",lumi,era,ram )
#	subcrab( "275911-275920", el_path + "sel_deg2016/sel_275911v275920_DEG2016C.txt",lumi,era,ram )
#	subcrab( "275921-276242", el_path + "sel_deg2016/sel_275921v276242_DEG2016C.txt",lumi,era,ram )
#	subcrab( "276243-276244", el_path + "sel_deg2016/sel_276243v276244_DEG2016C.txt",lumi,era,ram )
#	subcrab( "276282-276283", el_path + "sel_deg2016/sel_276282v276283_DEG2016C.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2016D-v2/RAW']
#/?	subcrab( "276315-276318", el_path + "sel_deg2016/sel_276315v276318_DEG2016D.txt",lumi,era,ram )
#/	subcrab( "276355-276363", el_path + "sel_deg2016/sel_276355v276363_DEG2016D.txt",lumi,era,ram )
#/	subcrab( "276384-276385", el_path + "sel_deg2016/sel_276384v276384_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276437-276454", el_path + "sel_deg2016/sel_276437v276454_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276458-276501", el_path + "sel_deg2016/sel_276458v276501_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276502-276525", el_path + "sel_deg2016/sel_276502v276525_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276527-276545", el_path + "sel_deg2016/sel_276527v276545_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276581-276586", el_path + "sel_deg2016/sel_276581v276586_DEG2016D.txt",lumi,era,ram )
#/	subcrab( "276587-276588", el_path + "sel_deg2016/sel_276587v276587_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276653-276775", el_path + "sel_deg2016/sel_276653v276775_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276776-276794", el_path + "sel_deg2016/sel_276776v276794_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276807-276810", el_path + "sel_deg2016/sel_276807v276810_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276811-276812", el_path + "sel_deg2016/sel_276811v276811_DEG2016D.txt",lumi,era,ram )
#	subcrab( "276831-276832", el_path + "sel_deg2016/sel_276831v276831_DEG2016E.txt",lumi,era,ram )

        era = ['goes to taperecall'] #['/DoubleEG/Run2016E-v2/RAW']
#	subcrab( "276834-276835", el_path + "sel_deg2016/sel_276834v276834_DEG2016E.txt",lumi,era,ram )
#	subcrab( "276870-276871", el_path + "sel_deg2016/sel_276870v276870_DEG2016E.txt",lumi,era,ram )
#	subcrab( "276935-276948", el_path + "sel_deg2016/sel_276935v276948_DEG2016E.txt",lumi,era,ram )
#	subcrab( "276950-276951", el_path + "sel_deg2016/sel_276950v276950_DEG2016E.txt",lumi,era,ram )
#	subcrab( "277069-277073", el_path + "sel_deg2016/sel_277069v277073_DEG2016E.txt",lumi,era,ram )
#	subcrab( "277076-277087", el_path + "sel_deg2016/sel_277076v277087_DEG2016E.txt",lumi,era,ram )
#	subcrab( "277094-277096", el_path + "sel_deg2016/sel_277094v277096_DEG2016E.txt",lumi,era,ram )
#	subcrab( "277112-277166", el_path + "sel_deg2016/sel_277112v277166_DEG2016E.txt",lumi,era,ram )
#	subcrab( "277168-277169", el_path + "sel_deg2016/sel_277168v277168_DEG2016E.txt",lumi,era,ram )
#	subcrab( "277180-277194", el_path + "sel_deg2016/sel_277180v277194_DEG2016E.txt",lumi,era,ram )
#	subcrab( "277305-277991", el_path + "sel_deg2016/sel_277305v277991_DEG2016E.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2016F-v1/RAW']
#	subcrab( "277992-278018", el_path + "sel_deg2016/sel_277992v278018_DEG2016F.txt",lumi,era,ram )
#	subcrab( "278167-278168", el_path + "sel_deg2016/sel_278167v278167_DEG2016F.txt",lumi,era,ram )
#	subcrab( "278175-278290", el_path + "sel_deg2016/sel_278175v278290_DEG2016F.txt",lumi,era,ram )
#	subcrab( "278308-278309", el_path + "sel_deg2016/sel_278308v278308_DEG2016F.txt",lumi,era,ram )
#	subcrab( "278310-278349", el_path + "sel_deg2016/sel_278310v278349_DEG2016F.txt",lumi,era,ram )
#	subcrab( "278366-278406", el_path + "sel_deg2016/sel_278366v278406_DEG2016F.txt",lumi,era,ram )
#	subcrab( "278509-278770", el_path + "sel_deg2016/sel_278509v278770_DEG2016F.txt",lumi,era,ram )
#	subcrab( "278801-278808", el_path + "sel_deg2016/sel_278801v278808_DEG2016F.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2016G-v1/RAW']
#	subcrab( "278820-278822", el_path + "sel_deg2016/sel_278820v278822_DEG2016G.txt",lumi,era,ram )
#	subcrab( "278873-278963", el_path + "sel_deg2016/sel_278873v278963_DEG2016G.txt",lumi,era,ram )
#	subcrab( "278969-278970", el_path + "sel_deg2016/sel_278969v278969_DEG2016G.txt",lumi,era,ram )
#	subcrab( "278975-279116", el_path + "sel_deg2016/sel_278975v279116_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279479-279654", el_path + "sel_deg2016/sel_279479v279654_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279656-279691", el_path + "sel_deg2016/sel_279656v279691_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279694-279695", el_path + "sel_deg2016/sel_279694v279694_DEG2016G.txt",lumi,era,ram )
#/	subcrab( "279715-279760", el_path + "sel_deg2016/sel_279715v279760_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279766-279767", el_path + "sel_deg2016/sel_279766v279767_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279766-279794", el_path + "sel_deg2016/sel_279766v279794_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279823-279844", el_path + "sel_deg2016/sel_279823v279844_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279887-279931", el_path + "sel_deg2016/sel_279887v279931_DEG2016G.txt",lumi,era,ram )
#	subcrab( "279966-280017", el_path + "sel_deg2016/sel_279966v280017_DEG2016G.txt",lumi,era,ram )
#/	subcrab( "280018-280191", el_path + "sel_deg2016/sel_280018v280191_DEG2016G.txt",lumi,era,ram )
#/	subcrab( "280194-280251", el_path + "sel_deg2016/sel_280194v280251_DEG2016G.txt",lumi,era,ram )
#s	subcrab( "280327-280364", el_path + "sel_deg2016/sel_280327v280364_DEG2016G.txt",lumi,era,ram )
#	subcrab( "280383-280385", el_path + "sel_deg2016/sel_280383v280385_DEG2016G.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2016H-v1/RAW']
#	subcrab( "281639-281693", el_path + "sel_deg2016/sel_281639v281693_DEG2016H.txt",lumi,era,ram )
#	subcrab( "281707-281727", el_path + "sel_deg2016/sel_281707v281727_DEG2016H.txt",lumi,era,ram )
#	subcrab( "281797-281975", el_path + "sel_deg2016/sel_281797v281975_DEG2016H.txt",lumi,era,ram )
#	subcrab( "281976-281977", el_path + "sel_deg2016/sel_281976v281976_DEG2016H.txt",lumi,era,ram )
#	subcrab( "282033-282092", el_path + "sel_deg2016/sel_282033v282092_DEG2016H.txt",lumi,era,ram )
#	subcrab( "282708-282735", el_path + "sel_deg2016/sel_282708v282735_DEG2016H.txt",lumi,era,ram )
#	subcrab( "282800-282814", el_path + "sel_deg2016/sel_282800v282814_DEG2016H.txt",lumi,era,ram )
#	subcrab( "282842-283270", el_path + "sel_deg2016/sel_282842v283270_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283283-283308", el_path + "sel_deg2016/sel_283283v283308_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283353-283407", el_path + "sel_deg2016/sel_283353v283407_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283408-283409", el_path + "sel_deg2016/sel_283408v283408_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283416-283820", el_path + "sel_deg2016/sel_283416v283820_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283830-283876", el_path + "sel_deg2016/sel_283830v283876_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283877-283884", el_path + "sel_deg2016/sel_283877v283884_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283885-283933", el_path + "sel_deg2016/sel_283885v283933_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283934-283946", el_path + "sel_deg2016/sel_283934v283946_DEG2016H.txt",lumi,era,ram )
#	subcrab( "283964-284043", el_path + "sel_deg2016/sel_283964v284043_DEG2016H.txt",lumi,era,ram )

        lumi = 'golden2017.json'
        era = ['/DoubleEG/Run2017B-v1/RAW']
#/      subcrab( "297050-297101", el_path + "sel_deg2017/sel_297050v297101_DEG2017B.txt",lumi,era,ram )
#/      subcrab( "297113-297219", el_path + "sel_deg2017/sel_297113v297219_DEG2017B.txt",lumi,era,ram )
#/      subcrab( "297224-297411", el_path + "sel_deg2017/sel_297224v297411_DEG2017B.txt",lumi,era,ram )
#/      subcrab( "297424-297486", el_path + "sel_deg2017/sel_297424v297486_DEG2017B.txt",lumi,era,ram )
#/      subcrab( "297487-297557", el_path + "sel_deg2017/sel_297487v297557_DEG2017B.txt",lumi,era,ram )
        subcrab( "297558-297606", el_path + "sel_deg2017/sel_297558v297606_DEG2017B.txt",lumi,era,ram )
#/      subcrab( "297620-299061", el_path + "sel_deg2017/sel_297620v299061_DEG2017B.txt",lumi,era,ram )
#       subcrab( "299062-299185", el_path + "sel_deg2017/sel_299062v299185_DEG2017B.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2017C-v1/RAW']
#/      subcrab( "299327-299480", el_path + "sel_deg2017/sel_299327v299480_DEG2017C.txt",lumi,era,ram )
#       subcrab( "299481-299597", el_path + "sel_deg2017/sel_299481v299597_DEG2017C.txt",lumi,era,ram )
#       subcrab( "299649-300155", el_path + "sel_deg2017/sel_299649v300155_DEG2017C.txt",lumi,era,ram )
#       subcrab( "300156-300237", el_path + "sel_deg2017/sel_300156v300237_DEG2017C.txt",lumi,era,ram )
#       subcrab( "300238-300375", el_path + "sel_deg2017/sel_300238v300375_DEG2017C.txt",lumi,era,ram )
#       subcrab( "300389-300466", el_path + "sel_deg2017/sel_300389v300466_DEG2017C.txt",lumi,era,ram )
#       subcrab( "300467-300558", el_path + "sel_deg2017/sel_300467v300558_DEG2017C.txt",lumi,era,ram )
#       subcrab( "300560-300633", el_path + "sel_deg2017/sel_300560v300633_DEG2017C.txt",lumi,era,ram )
#       subcrab( "300635-300777", el_path + "sel_deg2017/sel_300635v300777_DEG2017C.txt",lumi,era,ram )
#       subcrab( "300780-300817", el_path + "sel_deg2017/sel_300780v300817_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301046-301283", el_path + "sel_deg2017/sel_301046v301283_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301298-301384", el_path + "sel_deg2017/sel_301298v301384_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301391-301448", el_path + "sel_deg2017/sel_301391v301448_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301449-301476", el_path + "sel_deg2017/sel_301449v301476_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301519-301627", el_path + "sel_deg2017/sel_301519v301627_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301664-301941", el_path + "sel_deg2017/sel_301664v301941_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301958-301959", el_path + "sel_deg2017/sel_301959v301959_DEG2017C.txt",lumi,era,ram )
#       subcrab( "301960-301997", el_path + "sel_deg2017/sel_301960v301997_DEG2017C.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2017D-v1/RAW']
#/      subcrab( "301998-302031", el_path + "sel_deg2017/sel_301998v302031_DEG2017D.txt",lumi,era,ram )
        subcrab( "302033-302163", el_path + "sel_deg2017/sel_302033v302163_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302165-302240", el_path + "sel_deg2017/sel_302165v302240_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302262-302322", el_path + "sel_deg2017/sel_302262v302322_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302328-302392", el_path + "sel_deg2017/sel_302328v302392_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302393-302448", el_path + "sel_deg2017/sel_302393v302448_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302472-302485", el_path + "sel_deg2017/sel_302472v302485_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302492-302572", el_path + "sel_deg2017/sel_302492v302572_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302573-302597", el_path + "sel_deg2017/sel_302573v302597_DEG2017D.txt",lumi,era,ram )
#       subcrab( "302634-302663", el_path + "sel_deg2017/sel_302634v302663_DEG2017D.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2017E-v1/RAW']
#       subcrab( "303825-303838", el_path + "sel_deg2017/sel_303825v303838_DEG2017E.txt",lumi,era,ram )
#       subcrab( "303885-303948", el_path + "sel_deg2017/sel_303885v303948_DEG2017E.txt",lumi,era,ram )
#       subcrab( "303998-304062", el_path + "sel_deg2017/sel_303998v304062_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304119-304125", el_path + "sel_deg2017/sel_304119v304125_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304144-304145", el_path + "sel_deg2017/sel_304144v304144_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304158-304169", el_path + "sel_deg2017/sel_304158v304169_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304170-304292", el_path + "sel_deg2017/sel_304170v304292_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304333-304366", el_path + "sel_deg2017/sel_304333v304366_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304446-304508", el_path + "sel_deg2017/sel_304446v304508_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304562-304654", el_path + "sel_deg2017/sel_304562v304654_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304655-304671", el_path + "sel_deg2017/sel_304655v304671_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304672-304777", el_path + "sel_deg2017/sel_304672v304777_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304778-304779", el_path + "sel_deg2017/sel_304778v304778_DEG2017E.txt",lumi,era,ram )
#       subcrab( "304797-304798", el_path + "sel_deg2017/sel_304797v304797_DEG2017E.txt",lumi,era,ram )

        era = ['/DoubleEG/Run2017F-v1/RAW']
#       subcrab( "305044-305063", el_path + "sel_deg2017/sel_305044v305063_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305064-305065", el_path + "sel_deg2017/sel_305064v305064_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305081-305112", el_path + "sel_deg2017/sel_305081v305112_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305113-305202", el_path + "sel_deg2017/sel_305113v305202_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305204-305208", el_path + "sel_deg2017/sel_305204v305208_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305234-305248", el_path + "sel_deg2017/sel_305234v305248_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305252-305314", el_path + "sel_deg2017/sel_305252v305314_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305336-305365", el_path + "sel_deg2017/sel_305336v305365_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305366-305377", el_path + "sel_deg2017/sel_305366v305377_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305405-305516", el_path + "sel_deg2017/sel_305405v305516_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305517-305589", el_path + "sel_deg2017/sel_305517v305589_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305590-305636", el_path + "sel_deg2017/sel_305590v305636_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305766-305814", el_path + "sel_deg2017/sel_305766v305814_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305821-305842", el_path + "sel_deg2017/sel_305821v305842_DEG2017F.txt",lumi,era,ram )
#       subcrab( "305862-306042", el_path + "sel_deg2017/sel_305862v306042_DEG2017F.txt",lumi,era,ram )
#       subcrab( "306048-306122", el_path + "sel_deg2017/sel_306048v306122_DEG2017F.txt",lumi,era,ram )
#       subcrab( "306125-306126", el_path + "sel_deg2017/sel_306125v306125_DEG2017F.txt",lumi,era,ram )
#       subcrab( "306126-306138", el_path + "sel_deg2017/sel_306126v306138_DEG2017F.txt",lumi,era,ram )
#       subcrab( "306139-306153", el_path + "sel_deg2017/sel_306139v306153_DEG2017F.txt",lumi,era,ram )
#       subcrab( "306154-306155", el_path + "sel_deg2017/sel_306154v306155_DEG2017F.txt",lumi,era,ram )
#       subcrab( "306169-306456", el_path + "sel_deg2017/sel_306169v306456_DEG2017F.txt",lumi,era,ram )
#       subcrab( "306457-306459", el_path + "sel_deg2017/sel_306457v306459_DEG2017F.txt",lumi,era,ram )


submit_sample_runs()

