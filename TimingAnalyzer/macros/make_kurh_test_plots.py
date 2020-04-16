import os
import sys
import shutil
import time

infile = (sys.argv[1:])[0]

#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   !!!!   set res for plots    !!!!  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
eta='EBEB'
#eta='EPEM'
era='Full'

resl='Local'
#isdl_list=['Inclusive','Same','Different']
isdl_list=['Inclusive']
resg='Global'
isdg_list=['Inclusive']

#res_list=[[resl,isdl_list],[resg,isdg_list]]
res_list=[[resl,isdl_list]]
#res_list=[[resg,isdg_list]]

# Final output file
outfile=eta+'_'+era
outfile_e5='mini_'+outfile
kuoutfile='ku_'+outfile
kuStcoutfile='kuStc_'+outfile
kuNotoutfile='kuNot_'+outfile
kuNotStcoutfile='kuNotStc_'+outfile

ku_e5_outfile='ku_e5_'+outfile
kuNotStc_e5_outfile='kuNotStc_e5_'+outfile
kuStc_e5_outfile='kuStc_e5_'+outfile
kuWtStc_e5_outfile='kuWtStc_e5_'+outfile
kuWootStc_e5_outfile='kuWootStc_e5_'+outfile
kuMfootStc_e5_outfile='kuMfootStc_e5_'+outfile
kuMfootCCStc_e5_outfile='kuMfootCCStc_e5_'+outfile

# 2D plotter output file
outfile_2D='deltaT_vs_'+outfile
outfile_e5_2D='mini_e5_deltaT_vs_'+outfile
outfile_ku_e5_2D='ku_e5_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e5_2D='kuNotStc_e5_deltaT_vs_'+kuoutfile
outfile_kuStc_e5_2D='kuStc_e5_deltaT_vs_'+kuoutfile
outfile_kuWtStc_e5_2D='kuWtStc_e5_deltaT_vs_'+kuoutfile
outfile_kuWootStc_e5_2D='kuWootStc_e5_deltaT_vs_'+kuoutfile
outfile_kuMfootStc_e5_2D='kuMfootStc_e5_deltaT_vs_'+kuoutfile
outfile_kuMfootCCStc_e5_2D='kuMfootCCStc_e5_deltaT_vs_'+kuoutfile

timefile='_timefit'

#Plot Configs standard # not used
plot_2D='ku_config/tmp_ratio_deltaT_vs_A_eff_EBEB.txt'
plot_e5_2D='ku_config/tmp_ratio_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_ku_2D='ku_config/tmp_ku_deltaT_vs_A_eff_EBEB.txt'
plot_ku_e5_2D='ku_config/tmp_ku_deltaT_vs_A_eff_EBEB.txt'

#Plot Configs with KU preplotbration # not used
plot_kuNotStc_e5_2D='ku_config/tmp_kuNotStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_e5_2D='ku_config/tmp_kuStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuWtStc_e5_2D='ku_config/tmp_kuWtStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuMfootStc_e5_2D='ku_config/tmp_kuMfootStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuMfootCCStc_e5_2D='ku_config/tmp_kuMfootCCStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'

tvarname_mini='phoseedtime'
tvarname_ku='phoseedkutime'
tvarname_kuStc='phoseedkuStctime'
tvarname_kuNotStc='phoseedkuNotStctime'
tvarname_kuWtStc='phoseedkuWtStctime'
tvarname_kuWootStc='phoseedkuWootStctime'
tvarname_kuMfootStc='phoseedkuMfootStctime'
tvarname_kuMfootCCStc='phoseedkuMfootCCStctime'

calimapname_none='none'
calimapname_AveRtStcE5='AveXtalRtStcRecTime'
calimapname_AveRtOOTStcE5='AveXtalRtOOTStcRecTime'
calimapname_AveMiniE5='AveXtalMiniRecTime'
calimapname_AveWtStcE5='AveXtalWtStcRecTime'
calimapname_AveMfootStcE5='AveXtalMfootStcRecTime'
calimapname_AveMfootCCStcE5='AveXtalMfootCCStcRecTime'

baseE5 = [ plot_e5_2D, outfile_e5_2D, outfile_e5, tvarname_mini, calimapname_AveMiniE5 ]
kuNotStcE5 = [ plot_kuNotStc_e5_2D, outfile_kuNotStc_e5_2D, kuNotStc_e5_outfile, tvarname_kuNotStc, calimapname_AveRtOOTStcE5 ]
kuWtStcE5 = [ plot_kuWtStc_e5_2D, outfile_kuWtStc_e5_2D, kuWtStc_e5_outfile, tvarname_kuWtStc, calimapname_AveWtStcE5 ]
kuMfootStcE5 = [ plot_kuMfootStc_e5_2D, outfile_kuMfootStc_e5_2D, kuMfootStc_e5_outfile, tvarname_kuMfootStc, calimapname_AveMfootStcE5 ]
kuMfootCCStcE5 = [ plot_kuMfootCCStc_e5_2D, outfile_kuMfootCCStc_e5_2D, kuMfootCCStc_e5_outfile, tvarname_kuMfootCCStc, calimapname_AveMfootCCStcE5 ]

plot_list = [ baseE5, kuNotStcE5, kuWtStcE5, kuMfootStcE5, kuMfootCCStcE5 ]

cut_cf='ku_config/tmp_cut_config.txt'  
misc_cf='misc_config/misc.txt'
varwgt_cf='varwgt_config/empty.txt'
timefit_cf='ku_config/tmp_timefit_config.txt'
skim_loc_cf='skim_config/DiXtal_kurecs_Skim.txt'  #  LOCAL SKIMS
skim_glo_cf='skim_config/Zee_kurecs_Skim.txt'  #  GLOBAL  SKIMS
misc_fit_cf='ku_config/tmp_misc_fit.txt'

indir='./'
outdir='./'
skimoutdir='./'
skimindir='./'
sldir='./'
caliindir='./'
calioutdir='./'
plotdir='./'

qc='\\",\\"'
qq='" "'
sq=' "'
eq='"'
sp=' '

timefit='./runTimeFitter.obj '

skim_chain_kurh_2a='./wc_runKUSkimmer_kurh_chain_v2a_red.obj '

dotimeres2d='./wc_ku_plot2dResolution.obj '
dotimeres2d_ch='./wc_ku_plot2dResolution_chain.obj '
dotimeres2d_mf='./wc_ku_plot2dResolution_mf.obj '

doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_red.obj '

docalirhcolplot='./wc_ku_cali_ksrhCollectionPlots.obj '
end_skim='\\"\)'

#######################################################################################
## make all plots in plot list
def do_hadd( inlist ):

	sub = [ '0000', '0001', '0002', '0003', '0004', '0005', '0006', '0007', '0008', '0009' ]
	for f in inlist :
		for s in sub :
			hadddir = indir+f+'/*/'+s+'/'
			if( not os.system( 'ls '+ hadddir + " >/dev/null 2>/dev/null" ) ) :
				print( 'Hadding : ' + hadddir )
				os.system('hadd '+'/scratch/jaking/'+f+'_'+s+'.root '+hadddir+'out*' )

def fmove( infile, outdir ):

	print( 'Checking: ' + infile )	
	if( os.path.exists( infile ) ) :
		print( 'Moving: ' + infile + ' to ' + outdir[-12:] )  
		shutil.move( infile, outdir )
	else : 
		print( 'Error: ' + infile + ' does not exist.' )

def do_2dplot( plot_list, caliinfile, linfile, ginfile ):

   ##########     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     change the local/global type!!!!!!!!!!!!
    print( 'Processing Plot List' )
    date = time.strftime("%d%m%Y")+'_'+time.strftime("%H%M")
    for entry in plot_list :
      for sublist  in res_list :
        res = sublist[0]
        infile = linfile
        if 'Global' in res : infile = ginfile
        isd_list = sublist[1]
        for isd_type in isd_list :
          print( 'Producing plots for : ' + entry[0] )
          #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
          ##  makes base 2d plot for time fit
          write_file=entry[1]+'_'+res+'_'+isd_type
          plot_file=entry[2]+'_'+res+'_'+isd_type
          #cmd2d=dotimeres2d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+entry[1]+sp+entry[3]+sp+entry[4]+sp+isd_type
          cmd2d=dotimeres2d+caliindir+caliinfile+sp+skimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type
          print( '>>>>>>>>>>>>>>>>>  ' + cmd2d )
          os.system(cmd2d)
          #----  add clean up
          writedir = plotdir+'kurh_plots_'+infile[:-5]+'_'+'cali'+'_'+caliinfile[:-5]+'_'+date+"/"
          if( not os.path.exists(writedir) ) : os.mkdir(writedir)
          #for ext in [ 'png', 'pdf' ] : 
          #   for sca in [ 'lin', 'log' ] : 
          #      fmove( write_file+'_'+sca+'.'+ext , writedir )
          fmove( write_file+'.root', writedir )
          #fmove( write_file+'_integrals.log', writedir )
          print( 'Finished TreePlotting for plot: ' + entry[0] )

def do_plots( plot_list, caliinfile, linfile, ginfile  ):

	##########     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     change the local/global type!!!!!!!!!!!!
    print( 'Processing Plot List' )
    date = time.strftime("%d%m%Y")+'_'+time.strftime("%H%M")
    for entry in plot_list :
      for sublist  in res_list :
        res = sublist[0]
        if 'Local' in res : infile = linfile
        else : infile = ginfile
        isd_list = sublist[1]
        for isd_type in isd_list :
          print( 'Producing plots for : ' + entry[0] )
          #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
          ##  makes base 2d plot for time fit
          write_file=entry[1]+'_'+res+'_'+isd_type
          plot_file=entry[2]+'_'+res+'_'+isd_type
          #cmd2d=dotimeres2d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+entry[1]+sp+entry[3]+sp+entry[4]+sp+isd_type
          cmd2d=dotimeres2d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type
          print( '>>>>>>>>>>>>>>>>>  ' + cmd2d )
          os.system(cmd2d)
          #----  add clean up
          writedir = plotdir+'kurh_plots_'+infile[:-5]+'_'+'cali'+'_'+caliinfile[:-5]+'_'+date+"/"
          if( not os.path.exists(writedir) ) : os.mkdir(writedir)
          #for ext in [ 'png', 'pdf' ] : 
  	     #	for sca in [ 'lin', 'log' ] : 
  	     #		fmove( write_file+'_'+sca+'.'+ext , writedir )
          fmove( write_file+'.root', writedir )
          #fmove( write_file+'_integrals.log', writedir )
          print( 'Finished TreePlotting for plot: ' + entry[0] )	
  
  	     #shutil.move(f, 'dest_folder')		
          ## run fitter, getting 2D plots from before
          cmdtf=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_cf+sp+era+sp+plot_file+timefile
          print( '>>>>>>>>>>>>>>>>>  ' + cmdtf )
  	     #+sp+outdir
          os.system(cmdtf)
  	     #-----  add clean up
          for ext in [ 'png', 'pdf' ] : 
  		    for sca in [ 'lin', 'log', 'lin_logx', 'log_logx' ] : 
  		  	   for typ in [ 'mu', 'sigma' ] :
  		  		   #if( ('log' not in sca) and ('mu' not in typ) ) :		 
  		  		   fmove( typ+'_'+plot_file+'_timefit_'+sca+'.'+ext , writedir )
  		  		   #fmove( typ+'_'+plot_file+'_timefit_'+sca+'.'+ext , writedir )
          fmove( plot_file+'_timefit.root', writedir )
          fmove( plot_file+'_timefit_fitinfo.log', writedir )
          print( 'Finished TimeFitting for plot: ' + entry[0] )
          print( '------------------------------------------------------------' )

## run skimmer 
def do_skimmer_glo_chain(skiminlist):

        #cmdskim=skim_chain_2a+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_cf
        cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdir+sp+sldir+skiminlist+sp+skim_glo_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_loc_chain(skiminlist):

        #cmdskim=skim_chain_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdir+sp+sldir+skiminlist+sp+skim_loc_cf
        print(cmdskim)
        os.system(cmdskim)

##  run cali skimmer
def do_avecalikurh(skiminlist,caliinfile):

        #cmdintercali=doocccalikurh+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        cmdintercali=doocccalikurhootf+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        print(cmdintercali)
        os.system(cmdintercali)

#wc_ku_CaliPlots.C
def do_caliplots():

	     cmdcaliplot=docaliplot+caliindir+cali1infile+sp+caliindir+cali2infile+sp+caliindir+calioutfile+sp+iterations
        #print(cmdcaliplot)
        #os.system(cmdcaliplot)

######################################################################################


lfile=infile[:-5]+'_loc.txt'
lofile=lfile[:-3]+'root'
fl=open(lfile,'w')
fl.write(infile)
fl.close()
do_skimmer_loc_chain(lfile)
os.remove(lfile)
#gfile=infile[:-5]+'_glo.txt'
#gofile=gfile[:-3]+'root'
#fg=open(gfile,'w')
#fg.write(infile)
#fg.close()
#do_skimmer_glo_chain(gfile)
#os.remove(gfile)
cfile=infile[:-5]+'_cali.txt'
cofile=infile[:-5]+'_cali.root'
fc=open(cfile,'w')
fc.write(infile)
fc.close()
do_avecalikurh(cfile,cofile)
os.remove(cfile)
do_2dplot( plot_list, cofile, lofile, '' )
#do_plots( plot_list, cofile, lofile, ''  )



