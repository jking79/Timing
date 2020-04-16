#!/usr/bin/env python
"""
This is a small script that does the equivalent of multicrab.
"""
import os
from httplib import HTTPException
from optparse import OptionParser

from CRABAPI.RawCommand import crabCommand


def getOptions():
    """
    Parse and return the arguments provided by the user.
    """
    usage = ('usage: %prog -c CMD -d DIR [-o OPT]\nThe multicrab command'
                   ' executes "crab CMD OPT" for each task contained in DIR\nUse'
                   ' multicrab -h for help"')

    parser = OptionParser(usage=usage)
    parser.add_option("-c", "--crabCmd", dest="crabCmd",
         help=("The crab command you want to execute for each task in "
               "the DIR"), metavar="CMD")
    parser.add_option("-d", "--projDir", dest="projDir",
         help="The directory where the tasks are located", metavar="DIR")
    parser.add_option("-o", "--crabCmdOptions", dest="crabCmdOptions",
         help=("The options you want to pass to the crab command CMD"
               "tasklistFile"), metavar="OPT", default="")

    (options, args) = parser.parse_args()

    if args:
        parser.error("Found positional argument(s) %s." % args)
    if not options.crabCmd:
        parser.error("(-c CMD, --crabCmd=CMD) option not provided")
    #if not options.projDir:
    #    parser.error("(-d DIR, --projDir=DIR) option not provided")
    #if not os.path.isdir(options.projDir):
    #    parser.error("Directory %s does not exist" % options.projDir)

    return options


def doresubmit():
    """
    Main
    """
    options = getOptions()
    myProjDir='myworkingArea/'
    joblist = [	
	'crab_onetier_mini_nolhc_v9_EGamma_Run2018D-22Jan2019-v2_320673-321007_MINIAOD_dispho',
	'crab_onetier_mini_nolhc_v9_EGamma_Run2018D-22Jan2019-v2_321009-321396_MINIAOD_dispho',
	'crab_onetier_mini_nolhc_v9_EGamma_Run2018D-22Jan2019-v2_321397-321880_MINIAOD_dispho',
	'crab_onetier_mini_nolhc_v9_EGamma_Run2018D-22Jan2019-v2_321887-322332_MINIAOD_dispho',
	'crab_onetier_mini_nolhc_v9_EGamma_Run2018D-22Jan2019-v2_322348-323755_MINIAOD_dispho',
	'crab_onetier_mini_nolhc_v9_EGamma_Run2018D-22Jan2019-v2_323775-324765_MINIAOD_dispho',
	'crab_onetier_mini_nolhc_v9_EGamma_Run2018D-22Jan2019-v2_324769-325170_MINIAOD_dispho'
	]

    # Execute the command with its arguments for each task.
    for task in joblist:
        task = os.path.join(myProjDir, task)
        if not os.path.isdir(task):
            continue
        if str(options.crabCmd) != 'resubmit':
            try :
                print ("Executing (the equivalent of): crab %s %s %s" %
                      (options.crabCmd, task, options.crabCmdOptions))
                crabCommand(options.crabCmd, task, *options.crabCmdOptions.split())
		print (">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
            except HTTPException, hte :
                    print 'Command not executed'
        else:
            print ("Executing (the equivalent of): crab %s %s %s" %
                  (options.crabCmd, task, options.crabCmdOptions))
            os.system('crab resubmit ' + task)

doresubmit()

