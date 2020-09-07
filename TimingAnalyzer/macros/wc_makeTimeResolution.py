import os
import sys
import shutil
import time

#skiminfile = (sys.argv[1:])[0]

hadd_inlist = [ 'twotier_rt_rtnot_wt_woot_ks_kscc_v8_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319625-319910_dispho' ]

inlist_dataset_1617 = [
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016C-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016D-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016D-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016E-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016F-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017B-31Mar2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017C-31Mar2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017F-31Mar2018-v1_All_dispho_0002.root'
]

inlist_dataset_egamma = [
'twotier_rm_w_ks_kscc_v4_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0000.root',
'twotier_rm_w_ks_kscc_v4_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0000.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0002.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0003.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0004.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0005.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018A-17Sep2018-v2_315257-315488_dispho_0006.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0000.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0002.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0003.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0004.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0005.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0006.root'
]

inlist_debug = [
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018C-17Sep2018-v1_319337-319579_dispho_0002.root',
]

inlist_dataset_double = [
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017F-31Mar2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017F-31Mar2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016H-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0003.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016H-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0004.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016H-17Jul2018-v1_All_dispho_0003.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016B-17Jul2018_ver2-v1_All_dispho_0002.root'
]

inlist_tree_94 = [
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016D-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017F-31Mar2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016D-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017C-31Mar2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016F-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0002.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016G-17Jul2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2017B-31Mar2018-v1_All_dispho_0001.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016E-17Jul2018-v1_All_dispho_0000.root',
'twotier94_rm_w_ks_DoubleEG_MINIAOD_Run2016C-17Jul2018-v1_All_dispho_0000.root'
]

inlist_tree_10 = [
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0000.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0001.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0002.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0003.root',
'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0004.root',
#'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0005.root',
#'twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0006.root',
]

inlist_dataset_egamma_woot = [
'twotier_rm_w_woot_ks_kscc_nolhc_v7_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0000.root',
'twotier_rm_w_woot_ks_kscc_nolhc_v7_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho_0001.root'
]

skiminfile001='twotier_rm_w_ks_kscc_v5_EGamma_MINIAOD_Run2018D-22Jan2019-v2_320673-320824_dispho_0005.root'
skiminfile002='twotier_rt_rtnot_wt_woot_ks_kscc_v8_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho.root'
skiminfile003='ku_multitest_twotier_run18D_323414_dispho.root'
skiminfile004='ku_test_ks_1000_twotier_run18D_323414_dispho.root'
skiminfile005='dispho_raw_Run2018A_315322.root'
skiminfile006='ku_twotier_run18D_320712_dispho.root'
skiminfile007='output_235.root'
skiminfile008='ku_rhcomp_twotier_run18D_dispho.root'
skiminfile009='dispho_mini_Run2018A_315322.root'
skiminfile010='dispho_tt_Run2018B.root'
skiminfile011='dispho_tt_loc_Run2018B_pptest.root'
skiminfile012='dispho_tt_loc_Run2018B_v1_pptest.root'
skiminfile013='dispho_tt_loc_Run2018B_317080-319077_0000_pptest.root'
skiminfile014='dispho_tt_Run2018A.root'
skiminfile015='dispho_tt_Run2018C.root'
skiminfile016='dispho_tt_Run2018D.root'
skiminfile017='dispho_tt_Run2018D_320673-320824.root'
skiminlist018='dispho_tt_Run2018D_320673-320824.txt'
skiminfile019='dispho_tt_Run2018A_315257-315488.root'
skiminlist020='dispho_tt_Run2018A_315257-315488.txt'
skiminfile021='dispho_tt_Run2018B_global.root'
skiminfile022='dispho_tt_Run2018B_local_icv2.root'
skiminfile023='dispho_tt_Run2018B_local.root'
skiminfile024='dispho_2t_eg2018B_local_pptest.root'
skiminfile025='dispho_2t_eg2018B_global_preplot.root'
skiminfile026='dispho_tt_Run2018B_notof.root'
skiminfile027='dispho_2t_glo_Run2018D_320673_320824_v2_mf.root'
skiminfile028='dispho_tt_loc_Run2018C_319337-319579_0001.root'
skiminfile029='dispho_tt_loc_Run2018C_319337-319579_mf.root'  # preplot for average methods
skiminfile030='dispho_tt_loc_Run2018C_319337-319579_0002.root'  # preplot for average methods

skiminfile131='dispho_tt_loc_Run2018D_320673-320824_mf.root'
skiminfile132='dispho_tt_glo_Run2018D_320673_320824_v2_mf.root'
skiminfile133='dispho_tt_loc_Run2018ABCD_sel_mf.root'
skiminfile134='dispho_tt_glo_Run2018pABCD_mf.root'

skiminfile031='twotier_ks_kscc_test_v7_EGamma_MINIAOD_Run2018B-26Sep2018-v1_317080-319077_dispho.root'
skiminfile000='blank.root'

#skiminfile=skiminfile000
#infile=skiminfile134

# for making cali files
mfc='1' # default for non mf
#mfc='7'#dispho_tt_Run2018Dmf
#mfc='22'#dispho_tt_Run2018pABCDmf

#caliinfile='dispho_tt_Run2018B_local_icv2_i25_e5e5.root'
#caliinfile='dispho_tt_Run2018D_global_e5_i25_e5e3.root'
#caliinfile='dispho_tt_Run2018D_global_v2_i25_e5e3.root'
#caliinfile0da1='dispho_tt_all_Run2018D_test_ave_e5.root'
caliinfile0d3='dispho_tt_glo_Run2018Dmf_v2_320673_320824_v3_t2_i100_e5e3.root'
caliinfile0d3b='dispho_tt_glo_Run2018Dmf_v2_320673_320824_v3b_t2_i100_e5e3.root'
caliinfile0d2='dispho_tt_glo_Run2018Dmf_v2_320673_320824_v2_i50_e5e3.root'
caliinfile0d2a='dispho_tt_glo_Run2018Dmf_v2_320673_320824_v2a_i50_e5e3.root'
caliinfile0d2b='dispho_tt_glo_Run2018Dmf_v2_320673_320824_v2b_i50_e5e3.root'
caliinfile0p2='dispho_tt_glo_Run2018pABCDmf_v2_i50_e5e3.root'
caliinfile0p2a='dispho_tt_glo_Run2018pABCDmf_v2a_i50_e5e3.root'
caliinfile0p2b='dispho_tt_glo_Run2018pABCDmf_v2b_i50_e5e3.root'
caliinfile0p3='dispho_tt_glo_Run2018pABCDmf_v3_i100_e5e3.root'
caliinfile0p4a='dispho_tt_glo_Run2018pABCDmf_v4a_i50_e5e3.root'
#caliinfile=caliinfile0p3
#caliinfile=skiminfile131

iterations='50'
#calibranchname='icgv3'
calibranchname='aveE5'
calitreename='disphotree_'+calibranchname
#auto branch_name0("phoseedtimeCali_"+bname+"Ic_0");
#auto branch_name1("phoseedtimeCali_"+bname+"Ic_1");

#cali1infile='dispho_tt_Run2018D_global_e5_i25_e5e3.root'
#cali1infile='dispho_tt_Run2018D_global_v2_step02_i25_e5e3.root'
cali1infile=caliinfile0d2a
#cali2infile='dispho_tt_Run2018D_global_i25_e5e3.root'
#cali2infile='dispho_tt_Run2018D_global_v2_step01_i25_e5e3.root'
cali2infile=caliinfile0d2b
#calioutfile='caliplots_tt_Run2018D_global_v2_step_i25_e5e3.root'
calioutfile='caliplots_tt_Run2018pABCDmf_global_v2a_v2b_i50_e5e3.root'

#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   !!!!   set res for plots    !!!!  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
eta='EBEB'
#eta='EPEM'
era='Full'
res='Local'
#isd_list=['Inclusive','Same','Different']
#isd_list=['Same','Different']
isd_list=['Same']
#isd_list=['Different']
#res='Global'
#isd_list=['Inclusive']

# Final output file
outfile=res+'_'+eta+'_'+era
outfile_e5='mini_e5_'+outfile
kuoutfile='ku_'+outfile
kuStcoutfile='kuStc_'+outfile
kuNotoutfile='kuNot_'+outfile
kuNotStcoutfile='kuNotStc_'+outfile

ku_e5_outfile='ku_e5_'+outfile

kuNotStc_e0_outfile='kuNotStc_e0_'+outfile
kuNotStc_e1_outfile='kuNotStc_e1_'+outfile
kuNotStc_2e1_outfile='kuNotStc_2e1_'+outfile
kuNotStc_4e1_outfile='kuNotStc_4e1_'+outfile
kuNotStc_e2_outfile='kuNotStc_e2_'+outfile
kuNotStc_e5_outfile='kuNotStc_e5_'+outfile
kuNotStc_2e5_outfile='kuNotStc_2e5_'+outfile
kuNotStc_4e5_outfile='kuNotStc_4e5_'+outfile
kuNotStc_e10_outfile='kuNotStc_e10_'+outfile
kuNotStc_cl_outfile='kuNotStc_cl_'+outfile
kuNotStc_ic_outfile='kuNotStc_ic_'+outfile

#kuStc_e0_outfile='kuStc_e0_'+outfile
#kuStc_e1_outfile='kuStc_e1_'+outfile
#kuStc_2e1_outfile='kuStc_2e1_'+outfile
#kuStc_4e1_outfile='kuStc_4e1_'+outfile
#kuStc_e2_outfile='kuStc_e2_'+outfile
kuStc_e5_outfile='kuStc_e5_'+outfile
#kuStc_2e5_outfile='kuStc_2e5_'+outfile
#kuStc_4e5_outfile='kuStc_4e5_'+outfile
#kuStc_e10_outfile='kuStc_e10_'+outfile
#kuStc_cl_outfile='kuStc_cl_'+outfile
kuStc_ic_outfile='kuStc_ic_'+outfile
kuWtStc_e5_outfile='kuWtStc_e5_'+outfile
kuWtStc_outfile='kuWtStc_'+outfile
kuWootStc_e5_outfile='kuWootStc_e5_'+outfile
kuMfootStc_e5_outfile='kuMfootStc_e5_'+outfile
kuMfootStc_outfile='kuMfootStc_'+outfile
kuMfootCCStc_e5_outfile='kuMfootCCStc_e5_'+outfile
kuMfootCCStc_outfile='kuMfootCCStc_'+outfile

# 2D plotter output file
outfile_2D='deltaT_vs_'+outfile
outfile_e5_2D='mini_e5_deltaT_vs_'+outfile
outfile_ku_2D='ku_deltaT_vs_'+kuoutfile
outfile_ku_e5_2D='ku_e5_deltaT_vs_'+kuoutfile
outfile_kuStc_2D='kuStc_deltaT_vs_'+kuoutfile
outfile_kuNot_2D='kuNot_deltaT_vs_'+kuoutfile
outfile_kuNotStc_2D='kuNotStc_deltaT_vs_'+kuoutfile

outfile_kuNotStc_e0_2D='kuNotStc_e0_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e1_2D='kuNotStc_e1_deltaT_vs_'+kuoutfile
outfile_kuNotStc_2e1_2D='kuNotStc_2e1_deltaT_vs_'+kuoutfile
outfile_kuNotStc_4e1_2D='kuNotStc_4e1_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e2_2D='kuNotStc_e2_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e5_2D='kuNotStc_e5_deltaT_vs_'+kuoutfile
outfile_kuNotStc_2e5_2D='kuNotStc_2e5_deltaT_vs_'+kuoutfile
outfile_kuNotStc_4e5_2D='kuNotStc_4e5_deltaT_vs_'+kuoutfile
outfile_kuNotStc_e10_2D='kuNotStc_e10_deltaT_vs_'+kuoutfile
outfile_kuNotStc_cl_2D='kuNotStc_cl_deltaT_vs_'+kuoutfile
outfile_kuNotStc_ic_2D='kuNotStc_ic_deltaT_vs_'+kuoutfile

#outfile_kuStc_e0_2D='kuStc_e0_deltaT_vs_'+kuoutfile
#outfile_kuStc_e1_2D='kuStc_e1_deltaT_vs_'+kuoutfile
#outfile_kuStc_2e1_2D='kuStc_2e1_deltaT_vs_'+kuoutfile
#outfile_kuStc_4e1_2D='kuStc_4e1_deltaT_vs_'+kuoutfile
#outfile_kuStc_e2_2D='kuStc_e2_deltaT_vs_'+kuoutfile
outfile_kuStc_e5_2D='kuStc_e5_deltaT_vs_'+kuoutfile
#outfile_kuStc_2e5_2D='kuStc_2e5_deltaT_vs_'+kuoutfile
#outfile_kuStc_4e5_2D='kuStc_4e5_deltaT_vs_'+kuoutfile
#outfile_kuStc_e10_2D='kuStc_e10_deltaT_vs_'+kuoutfile
#outfile_kuStc_cl_2D='kuStc_cl_deltaT_vs_'+kuoutfile
outfile_kuStc_ic_2D='kuStc_ic_deltaT_vs_'+kuoutfile

outfile_kuWtStc_e5_2D='kuWtStc_e5_deltaT_vs_'+kuoutfile
outfile_kuWtStc_2D='kuWtStc_deltaT_vs_'+kuoutfile
outfile_kuWootStc_e5_2D='kuWootStc_e5_deltaT_vs_'+kuoutfile
outfile_kuMfootStc_e5_2D='kuMfootStc_e5_deltaT_vs_'+kuoutfile
outfile_kuMfootStc_2D='kuMfootStc_deltaT_vs_'+kuoutfile
outfile_kuMfootCCStc_e5_2D='kuMfootCCStc_e5_deltaT_vs_'+kuoutfile
outfile_kuMfootCCStc_2D='kuMfootCCStc_deltaT_vs_'+kuoutfile

timefile='_timefit'
timefilec='_core_timefit'
timefilet='_tail_timefit'
timefile2g='_2gaus_timefit'

#Plot Configs standard
plot_2D='ku_config/tmp_ratio_deltaT_vs_A_eff_EBEB.txt'
plot_2D_v2='ku_config/tmp_ratio_deltaT_vs_E_eff_EBEB.txt'
plot_e5_2D='ku_config/tmp_ratio_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_ku_2D='ku_config/tmp_ku_deltaT_vs_A_eff_EBEB.txt'
plot_ku_e5_2D='ku_config/tmp_ku_deltaT_vs_A_eff_EBEB.txt'

#Plot Configs with KU preplotbration
plot_kuStc_2D='ku_config/tmp_kuStc_deltaT_vs_A_eff_EBEB.txt'
#plot_kuNot_2D='ku_config/tmp_kuNot_cali_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2D='ku_config/tmp_kuNotStc_deltaT_vs_A_eff_EBEB.txt'

plot_kuNotStc_e0_2D='ku_config/tmp_kuNotStc_cali_e0_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e1_2D='ku_config/tmp_kuNotStc_cali_e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2e1_2D='ku_config/tmp_kuNotStc_cali_2e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_4e1_2D='ku_config/tmp_kuNotStc_cali_4e1_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e2_2D='ku_config/tmp_kuNotStc_cali_e2_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e5_2D='ku_config/tmp_kuNotStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_2e5_2D='ku_config/tmp_kuNotStc_cali_2e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_4e5_2D='ku_config/tmp_kuNotStc_cali_4e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_e10_2D='ku_config/tmp_kuNotStc_cali_e10_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_cl_2D='ku_config/tmp_kuNotStc_cali_cl_deltaT_vs_A_eff_EBEB.txt'
plot_kuNotStc_ic_2D='ku_config/tmp_kuNotStc_cali_ic_deltaT_vs_A_eff_EBEB.txt'

#plot_kuStc_e0_2D='ku_config/tmp_kuStc_cali_e0_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_e1_2D='ku_config/tmp_kuStc_cali_e1_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_2e1_2D='ku_config/tmp_kuStc_cali_2e1_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_4e1_2D='ku_config/tmp_kuStc_cali_4e1_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_e2_2D='ku_config/tmp_kuStc_cali_e2_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_e5_2D='ku_config/tmp_kuStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_2e5_2D='ku_config/tmp_kuStc_cali_2e5_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_4e5_2D='ku_config/tmp_kuStc_cali_4e5_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_e10_2D='ku_config/tmp_kuStc_cali_e10_deltaT_vs_A_eff_EBEB.txt'
#plot_kuStc_cl_2D='ku_config/tmp_kuStc_cali_cl_deltaT_vs_A_eff_EBEB.txt'
plot_kuStc_ic_2D='ku_config/tmp_kuStc_cali_ic_deltaT_vs_A_eff_EBEB.txt'
plot_kuWtStc_e5_2D='ku_config/tmp_kuWtStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
plot_kuWootStc_e5_2D='ku_config/tmp_kuWootStc_cali_e5_deltaT_vs_A_eff_EBEB.txt'
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
#calimapname_AveRtStcE5='AveXtalRtStcRecTimeE5'
calimapname_AveRtStcE5='AveXtalRtStcRecTime'
#calimapname_AveRtOOTStcE5='AveXtalRtOOTStcRecTimeE5'
calimapname_AveRtOOTStcE5='AveXtalRtOOTStcRecTime'
calimapname_AveWootStcE5='AveXtalWtOOTStcRecTime'
calimapname_AveRtStcIC='AveXtalRtStcPhoIcRecTime'
calimapname_AveRtOOTStcIC='AveXtalRtOOTStcPhoIcRecTime'
calimapname_AveMiniE5='AveXtalMiniRecTime'
calimapname_AveWtStcE5='AveXtalWtStcRecTime'
calimapname_AveMfootStcE5='AveXtalMfootStcRecTime'
calimapname_AveMfootCCStcE5='AveXtalMfootCCStcRecTime'

base = [ plot_2D, outfile_2D, outfile, tvarname_mini, calimapname_none ]
base_v2 = [ plot_2D_v2, outfile_2D, outfile, tvarname_mini, calimapname_none ]
baseE5 = [ plot_e5_2D, outfile_e5_2D, outfile_e5, tvarname_mini, calimapname_AveMiniE5 ]
ku = [ plot_ku_2D, outfile_ku_2D, kuoutfile, tvarname_ku, calimapname_none ]
kuStc = [ plot_kuStc_2D, outfile_kuStc_2D, kuStcoutfile, tvarname_kuStc, calimapname_none ]
#kuNot = [ plot_kuNot_2D, outfile_kuNot_2D, kuNotoutfile ]
kuNotStc = [ plot_kuNotStc_2D, outfile_kuNotStc_2D, kuNotStcoutfile, tvarname_kuNotStc, calimapname_none ]
#kuNotStcE0 = [ plot_kuNotStc_e0_2D, outfile_kuNotStc_e0_2D, kuNotStc_e0_outfile ]
#kuNotStcE1 = [ plot_kuNotStc_e1_2D, outfile_kuNotStc_e1_2D, kuNotStc_e1_outfile ]
#kuNotStc2E1 = [ plot_kuNotStc_2e1_2D, outfile_kuNotStc_2e1_2D, kuNotStc_2e1_outfile ]
#kuNotStc4E1 = [ plot_kuNotStc_4e1_2D, outfile_kuNotStc_4e1_2D, kuNotStc_4e1_outfile ]
#kuNotStcE2 = [ plot_kuNotStc_e2_2D, outfile_kuNotStc_e2_2D, kuNotStc_e2_outfile ]
kuNotStcE5 = [ plot_kuNotStc_e5_2D, outfile_kuNotStc_e5_2D, kuNotStc_e5_outfile, tvarname_kuNotStc, calimapname_AveRtOOTStcE5 ]
#kuNotStc2E5 = [ plot_kuNotStc_2e5_2D, outfile_kuNotStc_2e5_2D, kuNotStc_2e5_outfile ]
#kuNotStc4E5 = [ plot_kuNotStc_4e5_2D, outfile_kuNotStc_4e5_2D, kuNotStc_4e5_outfile ]
#kuNotStcE10 = [ plot_kuNotStc_e10_2D, outfile_kuNotStc_e10_2D, kuNotStc_e10_outfile ]
#kuNotStcCl = [ plot_kuNotStc_cl_2D, outfile_kuNotStc_cl_2D, kuNotStc_cl_outfile ]
kuNotStcIc= [ plot_kuNotStc_ic_2D, outfile_kuNotStc_ic_2D, kuNotStc_ic_outfile, tvarname_kuNotStc, calimapname_AveRtOOTStcIC ]
#kuStcE0 = [ plot_kuStc_e0_2D, outfile_kuStc_e0_2D, kuStc_e0_outfile ]
#kuStcE1 = [ plot_kuStc_e1_2D, outfile_kuStc_e1_2D, kuStc_e1_outfile ]
#kuStc2E1 = [ plot_kuStc_2e1_2D, outfile_kuStc_2e1_2D, kuStc_2e1_outfile ]
#kuStc4E1 = [ plot_kuStc_4e1_2D, outfile_kuStc_4e1_2D, kuStc_4e1_outfile ]
#kuStcE2 = [ plot_kuStc_e2_2D, outfile_kuStc_e2_2D, kuStc_e2_outfile ]
kuE5 = [ plot_ku_e5_2D, outfile_ku_e5_2D, ku_e5_outfile, tvarname_ku, calimapname_AveRtStcE5 ]
kuStcE5 = [ plot_kuStc_e5_2D, outfile_kuStc_e5_2D, kuStc_e5_outfile, tvarname_kuStc, calimapname_AveRtStcE5 ]
#kuStc2E5 = [ plot_kuStc_2e5_2D, outfile_kuStc_2e5_2D, kuStc_2e5_outfile ]
#kuStc4E5 = [ plot_kuStc_4e5_2D, outfile_kuStc_4e5_2D, kuStc_4e5_outfile ]
#kuStcE10 = [ plot_kuStc_e10_2D, outfile_kuStc_e10_2D, kuStc_e10_outfile ]
#kuStcCl = [ plot_kuStc_cl_2D, outfile_kuStc_cl_2D, kuStc_cl_outfile ]
kuStcIc= [ plot_kuStc_ic_2D, outfile_kuStc_ic_2D, kuStc_ic_outfile, tvarname_kuStc, calimapname_AveRtStcIC ]
kuWtStcE5 = [ plot_kuWtStc_e5_2D, outfile_kuWtStc_e5_2D, kuWtStc_e5_outfile, tvarname_kuWtStc, calimapname_AveWtStcE5 ]
kuWtStc = [ plot_kuWtStc_e5_2D, outfile_kuWtStc_2D, kuWtStc_outfile, tvarname_kuWtStc, calimapname_none ]
#kuWootStcE5 = [ plot_kuWootStc_e5_2D, outfile_kuWootStc_e5_2D, kuWootStc_e5_outfile, tvarname_kuWootStc, calimapname_AveWootStcE5 ]
kuWootStcE5 = [ plot_kuWootStc_e5_2D, outfile_kuWootStc_e5_2D, kuWootStc_e5_outfile, tvarname_kuWootStc, calimapname_AveWootStcE5 ]
kuMfootStcE5 = [ plot_kuMfootStc_e5_2D, outfile_kuMfootStc_e5_2D, kuMfootStc_e5_outfile, tvarname_kuMfootStc, calimapname_AveMfootStcE5 ]
kuMfootStc = [ plot_kuMfootStc_e5_2D, outfile_kuMfootStc_2D, kuMfootStc_outfile, tvarname_kuMfootStc, calimapname_none ]
kuMfootCCStcE5 = [ plot_kuMfootCCStc_e5_2D, outfile_kuMfootCCStc_e5_2D, kuMfootCCStc_e5_outfile, tvarname_kuMfootCCStc, calimapname_AveMfootCCStcE5 ]
kuMfootCCStc = [ plot_kuMfootCCStc_e5_2D, outfile_kuMfootCCStc_2D, kuMfootCCStc_outfile, tvarname_kuMfootCCStc, calimapname_none ]

# set plot list for plots    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#plot_list = [ base, ku, kuStc, kuNot, kuNotStc ]
#plot_list = [ base, ku, kuStc, kuNotStc ]
#plot_list = [ base, kuE5, kuStcE5, kuNotStcE5 ]
#plot_list = [ kuStcIc, kuNotStcIc ]
#plot_list = [kuNotStcE0, kuNotStcE1, kuNotStcE2, kuNotStcE5, kuNotStcE10, kuNotStcCl, kuNotStcIc ]
#plot_list = [kuStcE0, kuStcE1, kuStcE2, kuStcE5, kuStcE10 ] #, kuStcCl, kuStcIc ]
#plot_list = [kuStcE1, kuStc2E1, kuStc4E1, kuStcE5, kuStc2E5, kuStc4E5 ] #, kuStcCl, kuStcIc ]
#plot_list = [ ku, kuStcCl, kuStcIc ]
#plot_list = [ kuWootStcE5 ]
#plot_list = [ kuNotStcE0, kuNotStcE1, kuNotStcE2, kuNotStcE5, kuNotStcE10, kuNotStcCl, kuNotStcIc, kuWootStcE5, kuStcE5, kuNotStc2E1, kuNotStc4E1, kuNotStc2E5 ]
#plot_list = [ kuNotStcIc ]
#plot_list = [ kuNotStcE5, kuNotStc, kuStcE5, kuStc, ku, base ]
#plot_list = [ kuNotStc, kuStc, ku, base ]
plot_list = [ base ]
#plot_list = [ base_v2 ]  #  Effective ENERGY based, change 2d plot to E based version
#plot_list = [ baseE5 ]
#plot_list = [ base, baseE5 ]
#plot_list = [ base, kuStcE5, kuNotStcE5 ]
#plot_list = [ base, kuStcE5, kuNotStcE5, kuWtStcE5, kuWootStcE5, kuMfootStcE5, kuMfootCCStcE5 ]
#plot_list = [ base, kuStcE5, kuNotStcE5, kuWtStcE5, kuWootStcE5]
#plot_list = [ base, baseE5, kuWtStc, kuWtStcE5, kuMfootStc, kuMfootStcE5, kuMfootCCStc, kuMfootCCStcE5 ]
#plot_list = [ baseE5, kuNotStcE5, kuWtStcE5, kuWootStcE5, kuMfootStcE5, kuMfootCCStcE5 ]
#plot_list = [ base, baseE5, kuNotStcE5, kuWtStcE5, kuMfootStcE5, kuMfootCCStcE5 ]

#skiminlist='skimFileListNone.txt'
#skiminlist='dispho_tt_rm_w_ks_kscc_Run2018A_315257-315488.txt'
#skiminlist='dispho_tt_rt_rtnot_wt_woot_ks_kscc_Run2018C_319625-319910.txt'
#skiminlist='dispho_tt_rm_w_ks_Run2016B.txt'
#skiminlist='dispho_tt_rm_w_ks_Run2017F.txt'
#skiminlist='dispho_ot_mini_Run2018B_317080-319077.txt'

#skiminlist='dispho_tt_kurh_Run2016C_v42.txt'

#skiminlist='dispho_tt_kurh_Run2018C_319337-579_short.txt'
#skiminlist='dispho_tt_kurh_Run2018A_315257-315322.txt'
#skiminlist='dispho_tt_kurh_Run2018C_319912-320065.txt'
#skiminlist='dispho_tt_kurh_Run2018C_319337-320065.txt'

#skiminlist='dispho_tt_kurhs_Run2018C_319625_319910.txt' # 20_apr_20 

#skiminlist='dispho_tt_kurh_Run2016C.txt'
#skiminlist='dispho_tt_kurh_Run2017D.txt'

#skiminlist='dispho_ot_mini_Run2018A.txt'
#skiminlist='dispho_ot_mini_Run2018A_mf.txt'
#skiminlist='dispho_ot_mini_Run2018B_317080-319077.txt'
#skiminlist='dispho_mf_test_run2018a_single.txt'
#skiminlist='dispho_mf_test_run2018a_multi.txt'
#skiminlist='dispho_mf_test_run2018a_multi_wc.txt'
#skiminlist='dispho_ot_mini_Run2018C.txt'
#skiminlist='dispho_ot_mini_Run2018D.txt'
#skiminlist='dispho_ot_mini_Run2018D12.txt'
#skiminlist='dispho_ot_mini_Run2018D34.txt'
#skiminlist='dispho_ot_mini_Run2018D567.txt'
#skiminlist='dispho_ot_mini_Run2018_all.txt'

#-----2018D : 2
#skiminlist='dispho_ot_mini_Run2018D_321009-321396.txt'
#skiminlist='dispho_ot_mini_Run2018D_321165-321219.txt'
#skiminlist='dispho_ot_mini_Run2018D_321165-321219_hadd.txt'
#skiminlist='dispho_ot_mini_Run2018D_321221-321305.txt'
#skiminlist='dispho_ot_mini_Run2018D_321311-321396.txt'

#skiminlist='dispho_ot_mini_Run2017B.txt'
#skiminlist='dispho_ot_mini_Run2017C.txt'
#skiminlist='dispho_ot_mini_Run2017D.txt'
#skiminlist='dispho_ot_mini_Run2017E.txt'
#skiminlist='dispho_ot_mini_Run2017F.txt'

#skiminlist='dispho_ot_mini_SP_Run2016C.txt'
#skiminlist='dispho_test_wildcard.txt'

#skiminlist='dispho_ot_mini_GT102X_Run2018A.txt'
#skiminlist='dispho_ot_mini_GT102X_Run2018A_ch.txt'
#skiminlist='dispho_ot_mini_SP_Run2016B.txt'

#  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#skiminlist='dispho_tt_kurhs_v15_Run2018B_317080_319077.txt'
#skiminlist='dispho_tt_kurhs_v17_Run2018B_317080_319077.txt'
#skiminlist='dispho_tt_kurhs_v18_Run2018B_317080_319077.txt'
#skiminlist='dispho_tt_kurhs_v19_Run2018B_317080_319077.txt'

#skiminlist='dispho_tt_kurhs_v15_Run2018D_320673_320824.txt'
#skiminlist='dispho_tt_kurhs_v16_Run2018D_320673_320824.txt'
#skiminlist='dispho_tt_kurhs_v19_Run2018D_320807_320824.txt'
#skiminlist='dispho_tt_kurhs_v20_Run2018D_320807_320824.txt'
#skiminlist='dispho_tt_kurhs_v21_Run2018D_320807_320824.txt'

#skiminlist='dispho_tt_kurhs_v16_Run2017F.txt'

#skiminlist='dispho_mc_kurhs_DYJetsToLL.txt'
#skiminlist='dispho_mc_v28_DYJetsToLL.txt'
#skiminlist='dispho_mc_v29p2_DYJetsToLL.txt'
#skiminlist='dispho_mc_v30_DYJetsToLL.txt'
#skiminlist='dispho_mc_v31_DYJetsToLL.txt'
skiminlist='dispho_mc_v32_DYJetsToLL.txt'

#skiminlist='dispho_ot_mini_Run2018C_319337_319579_ele.txt'
#skiminlist='dispho_ot_mini_Run2018A_ele.txt'
#skiminlist='dispho_ot_mini_Run2018B_ele.txt'
#skiminlist='dispho_ot_mini_Run2018C_ele.txt'
#skiminlist='dispho_ot_mini_Run2018D_ele.txt'

#skiminlist='dispho_ot_mini_Run2017B_ele.txt'
#skiminlist='dispho_ot_mini_Run2017C_ele.txt'
#skiminlist='dispho_ot_mini_Run2017D_ele.txt'
#skiminlist='dispho_ot_mini_Run2017D_ele2.txt'
#skiminlist='dispho_ot_mini_Run2017E_ele.txt'
#skiminlist='dispho_ot_mini_Run2017F_ele.txt'

#skiminlist='dispho_ot_mini_Run2016B_ele.txt'
#skiminlist='dispho_ot_mini_Run2016C_ele.txt'
#skiminlist='dispho_ot_mini_Run2016D_ele.txt'
#skiminlist='dispho_ot_mini_Run2016E_ele.txt'
#skiminlist='dispho_ot_mini_Run2016F_ele.txt'
#skiminlist='dispho_ot_mini_Run2016G_ele.txt'
#skiminlist='dispho_ot_mini_Run2016H_ele.txt'

#skiminlist='dispho_ot_mini_Run2018C_319337_319579_noele.txt'

#skiminlist='dispho_ot_mini_rt3_Run2017B.txt'
#skiminlist='dispho_ot_mini_rt3_Run2017C.txt'
#skiminlist='dispho_ot_mini_rt3_Run2017D.txt'
#skiminlist='dispho_ot_mini_rt3_Run2017E.txt'
#skiminlist='dispho_ot_mini_rt3_Run2017F.txt'
#skiminlist='dispho_ot_mini_se_Run2017.txt'

#skiminlist='dispho_ot_mini_Run2016B.txt'
#skiminlist='dispho_ot_mini_Run2016C.txt'
#skiminlist='dispho_ot_mini_Run2016D.txt'
#skiminlist='dispho_ot_mini_Run2016E.txt'
#skiminlist='dispho_ot_mini_Run2016F.txt'
#skiminlist='dispho_ot_mini_Run2016G.txt'

#skiminlist='dispho_ot_mini_ul_deg_Run2018.txt'
#skiminlist='dispho_ot_mini_ul_deg_Run2018D.txt'
#skiminlist='dispho_ot_mini_ul_gt28_deg_Run2018D.txt'
#skiminlist='dispho_ot_mini_ul_gt28_deg_Run2018C.txt'
#skiminlist='dispho_ot_mini_ul_deg_Run2018ABC.txt'
#skiminlist='dispho_ot_mini_ul_deg_Run2017.txt'
#skiminlist='dispho_ot_mini_ul_deg_Run2016.txt'

#rhcoloutfile="run2018B_317080t319077_rhcolplots_v3_t2.root"
#rhcoloutfile="dispho_tt_kurh_Run2018C_319337-320065_rhcolplots_full.root"
#rhcoloutfile="dispho_tt_kurh_Run2018A_315257-315322_rhcolplots.root"
#rhcoloutfile="dispho_tt_kurh_Run2018C_319337-320065_rhcolplots_cali_ksonly.root"
#rhcoloutfile="dispho_tt_kurh_Run2018C_319337-320065_rhcolplots_full.root"
#rhcoloutfile="dispho_tt_kurh_Run2018C_319337-320065_rhcolplots_cali_full.root"

skimoutfile100='dispho_ot_mini_Run2018A.root'
#skimoutfile101='dispho_ot_mini_Run2018B_317080-319077.root'
skimoutfile102='dispho_ot_mini_Run2018B_v2.root'
skimoutfile103='dispho_ot_mini_Run2018C.root'
skimoutfile104='dispho_ot_mini_Run2018D.root'
skimoutfile105='dispho_ot_mini_GT102X_Run2018A.root'
skimoutfile106='dispho_ot_mini_GT102X_Run2018A_ch.root'
skimoutfile2018ul='dispho_ot_mini_ul_deg_Run2018.root'
skimoutfile2018ABCul='dispho_ot_mini_ul_deg_Run2018ABC.root'
skimoutfile2018Dul='dispho_ot_mini_ul_deg_Run2018D.root'
skimoutfile2018Dulgt28='dispho_ot_mini_ul_gt28_deg_Run2018D.root'
skimoutfile2018Culgt28='dispho_ot_mini_ul_gt28_deg_Run2018C.root'

skimoutfile201='dispho_ot_mini_Run2016B.root'
skimoutfile202='dispho_ot_mini_Run2016C.root'
skimoutfile203='dispho_ot_mini_Run2016D.root'
skimoutfile204='dispho_ot_mini_Run2016E.root'
skimoutfile205='dispho_ot_mini_Run2016F.root'
skimoutfile206='dispho_ot_mini_Run2016G.root'
skimoutfile2016ul='dispho_ot_mini_ul_deg_Run2016.root'

skimoutfile207='dispho_ot_mini_SP_Run2016C.root'
skimoutfile208='dispho_tt_kurh_Run2016C.txt'
skimoutfile209='dispho_tt_kurh_Run2016C_v42.root'

skimoutfile301='dispho_ot_mini_Run2017B.root'
skimoutfile302='dispho_ot_mini_Run2017C.root'
skimoutfile303='dispho_ot_mini_Run2017D.root'
skimoutfile304='dispho_ot_mini_Run2017E.root'
skimoutfile305='dispho_ot_mini_Run2017F.root'

skimoutfile303_noele='dispho_ot_mini_Run2017D_noele_v2.root'
skimoutfile303_ele='dispho_ot_mini_Run2017D_ele_v2.root'

skimoutfile2017se='dispho_ot_mini_se_Run2017.root'
skimoutfile2017ul='dispho_ot_mini_ul_deg_Run2017.root'

skimoutfile001='dispho_tt94_rm_w_ks_Run2016B.root'
skimoutfile002='dispho_tt94_rm_w_ks_Run2017F.root'
skimoutfile003='dispho_tt_rt_rtnot_wt_woot_ks_kscc_Run2018C_319625-319910.root'
skimoutfile004='dispho_tt_rm_w_ks_kscc_Run2018A_315257-315488.root'
skimoutfile005='dispho_tt_kurh_Run2018C_319337-320065.root'

skimoutfile006='dispho_ot_mini_Run2018D_321009-321396.root'
skimoutfile007='dispho_ot_mini_Run2018D_321165-321219.root'
skimoutfile008='dispho_ot_mini_Run2018D_321165-321219_hadd.root'
skimoutfile009='dispho_ot_mini_Run2018D_321221-321305.root'
skimoutfile010='dispho_ot_mini_Run2018D_321311-321396.root'

skimoutfile011='dispho_tt_kurhs_Run2018C_319625_319910.root'
skimoutfile012='dispho_tt_kurhs_v15_Run2018B_317080_319077.root'
skimoutfile0127='dispho_tt_kurhs_v17_Run2018B_317080_319077.root'
skimoutfile0128='dispho_tt_kurhs_v18_Run2018B_317080_319077.root'
skimoutfile013='dispho_tt_kurhs_v15_Run2018D_320673_320824.root'
skimoutfile0136='dispho_tt_kurhs_v16_Run2018D_320673_320824.root'
skimoutfile0139='dispho_tt_kurhs_v19_Run2018D_320807_320824.root'
skimoutfile01320='dispho_tt_kurhs_v20_Run2018D_320807_320824.root'
skimoutfile01321='dispho_tt_kurhs_v21_Run2018D_320807_320824.root'

skimoutfile0146='dispho_tt_kurhs_v16_Run2017F.root'

skimoutfile_mc_dytoll_v20='dispho_mc_kurhs_DYJetsToLL.root'
skimoutfile_mc_dytoll_v28='dispho_mc_v28_DYJetsToLL.root'
skimoutfile_mc_dytoll_v29='dispho_mc_v29_DYJetsToLL_pce0p0.root'
skimoutfile_mc_dytoll_v29v2='dispho_mc_v29p2_DYJetsToLL.root'
skimoutfile_mc_dytoll_v30='dispho_mc_v30_DYJetsToLL.root'
skimoutfile_mc_dytoll_v31='dispho_mc_v31_DYJetsToLL.root'
skimoutfile_mc_dytoll_v32='dispho_mc_v32_DYJetsToLL.root'

skimoutfile501='dispho_tt_kurh_Run2017D.root'
skimoutfile502a='dispho_ot_mini_Run2018C_319337_319579_noele.root'
skimoutfile502b='dispho_ot_mini_Run2018C_319337_319579_ele.root'
skimoutfile502c='dispho_ot_mini_Run2018C_319337_319579_ele0p005.root'

caliinfile0da1='chain_test_multi_mf.root'
caliinfile_test='test_multi_mf.root'

caliinfile6b='dispho_ot_mini_Run2016B_ave_e5_cali.root'
caliinfile6c='dispho_ot_mini_Run2016C_ave_e5_cali.root'
caliinfile6d='dispho_ot_mini_Run2016D_ave_e5_cali.root'
caliinfile6e='dispho_ot_mini_Run2016E_ave_e5_cali.root'
caliinfile6f='dispho_ot_mini_Run2016F_ave_e5_cali.root'
caliinfile6g='dispho_ot_mini_Run2016G_ave_e5_cali.root'

caliinfile6c_sp='dispho_ot_mini_SP_Run2016C_ave_e5_cali_v2.root'

caliinfile8a_gt='dispho_ot_mini_GT102X_Run2018A_ave_e5_cali_v2.root'
caliinfile8a_gtch='dispho_ot_mini_GT102X_Run2018A_ch_ave_e5_cali_v2.root'
caliinfile6b_sp='dispho_ot_mini_SP_Run2016B_ave_e5_cali_v2.root'
caliinfile7b_rt3='dispho_ot_mini_rt3_Run2017B_ave_e5_cali_v2.root'
caliinfile7c_rt3='dispho_ot_mini_rt3_Run2017C_ave_e5_cali_v2.root'
caliinfile7d_rt3='dispho_ot_mini_rt3_Run2017D_ave_e5_cali_v2.root'
caliinfile7e_rt3='dispho_ot_mini_rt3_Run2017E_ave_e5_cali_v2.root'
caliinfile7f_rt3='dispho_ot_mini_rt3_Run2017F_ave_e5_cali_v2.root'

caliinfile7b='dispho_ot_mini_Run2017B_ave_e5_cali.root'
caliinfile7c='dispho_ot_mini_Run2017C_ave_e5_cali.root'
caliinfile7d='dispho_ot_mini_Run2017D_ave_e5_cali.root'
caliinfile7e='dispho_ot_mini_Run2017E_ave_e5_cali.root'
caliinfile7f='dispho_ot_mini_Run2017F_ave_e5_cali.root'

caliinfile8a='dispho_ot_mini_Run2018A_ave_e5_cali.root'
caliinfile8a_mf='dispho_ot_mini_Run2018A_mf_ave_e5_cali.root'
caliinfile8a_e10='dispho_ot_mini_Run2018A_ave_e10_cali.root'
caliinfile8a_e20='dispho_ot_mini_Run2018A_ave_e20_cali.root'

caliinfile8b='dispho_ot_mini_Run2018B_v2_ave_e5_cali.root'
caliinfile8b_mf='dispho_ot_mini_Run2018B_mf_v2_ave_e5_cali.root'

caliinfile8c='dispho_ot_mini_Run2018C_ave_e5_cali.root'
caliinfile8c2='dispho_ot_mini_Run2018C_2_ave_e5_cali.root'
caliinfile8c_e1='dispho_ot_mini_Run2018C_ave_e1_cali.root'
caliinfile8c_e2='dispho_ot_mini_Run2018C_ave_e2_cali.root'
caliinfile8c_e10='dispho_ot_mini_Run2018C_ave_e10_cali.root'
caliinfile8c_e20='dispho_ot_mini_Run2018C_ave_e20_cali.root'
caliinfile8c_pho='dispho_ot_mini_Run2018C_pho_ave_e5_cali.root'

caliinfile8d='dispho_ot_mini_Run2018D_ave_e5_cali.root'
caliinfile8d_oot='dispho_ot_mini_Run2018D_isoot_ave_e5_cali.root'
caliinfile8d_pho='dispho_ot_mini_Run2018D_pho_ave_e5_cali.root'
caliinfile8d_half='dispho_ot_mini_Run2018D_ave_half_e5_cali.root'
caliinfile8d_quad='dispho_ot_mini_Run2018D_ave_quad_e5_cali.root'
caliinfile8d_tenth='dispho_ot_mini_Run2018D_ave_tenth_e5_cali.root'
caliinfile8d_hundth='dispho_ot_mini_Run2018D_ave_hundth_e5_cali.root'
caliinfile8d_e1='dispho_ot_mini_Run2018D_ave_e1_cali.root'

caliinfile8d_e2='dispho_ot_mini_Run2018D_ave_e2_cali.root'
caliinfile8d_e10='dispho_ot_mini_Run2018D_ave_e10_cali.root'
caliinfile8d_e20='dispho_ot_mini_Run2018D_ave_e20_cali.root'
caliinfile8all='dispho_ot_mini_Run2018_all_ave_e5_cali.root'

caliinfile8d009t321396='dispho_ot_mini_Run2018D_321009-321396_ave_e5_cali.root'
caliinfile8d321219='dispho_ot_mini_Run2018D_321165-321219_ave_e5_cali.root'
caliinfile8d321219hadd='dispho_ot_mini_Run2018D_321165-321219_hadd_ave_e5_cali.root'
caliinfile8d321305='dispho_ot_mini_Run2018D_321221-321305_ave_e5_cali.root'
caliinfile8d321396='dispho_ot_mini_Run2018D_321311-321396_ave_e5_cali.root'

caliinfile8b319077='dispho_ot_mini_Run2018B_317080-319077_ave_e5_cali.root'
caliinfile8a315488='dispho_tt_rm_w_ks_kscc_Run2018A_315257-315488_ave_e5_cali.root'
caliinfile8c319910='dispho_tt_rt_rtnot_wt_woot_ks_kscc_Run2018C_319625-319910_ave_e5_cali.root'

caliinfile8c_kurh1='dispho_tt_kurh_Run2018C_319337-320065_ave_e5_cali.root'
caliinfile8c_kurhoot='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_e5_cali.root'
caliinfile8c_kurhootf2='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_filter_e5_cali_v2.root'
#caliinfile8c_kurhootf3='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_filter_e5_cali_v3.root'
#caliinfile8c_kurhootf3='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_filter_e0p5_cali_v3.root'
#caliinfile8c_kurhootf3='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_filter_e1p0_cali_v3.root'
#caliinfile8c_kurhootf3='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_filter_e2p0_cali_v3.root'
caliinfile8c_kurhootf3='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_filter_e10p0_cali_v3.root'
caliinfile8c_kurhootf3='dispho_tt_kurh_Run2018C_319337-320065_ave_isoot_filter_e20p0_cali_v3.root'

caliinfile6c_kurh='dispho_tt_kurh_Run2016C_ave_e5_cali.root'
caliinfile7d_kurh='dispho_tt_kurh_Run2017D_ave_e5_cali.root'
caliinfile6cv42_kurh='dispho_tt_kurh_Run2016Cv42_ave_ofe5_cali.root'
caliinfilett6b='dispho_tt_rm_w_ks_Run2016B_ave_e5_cali.root'
caliinfilett7f='dispho_tt_rm_w_ks_Run2017F_ave_e5i_cali.root'
caliinfile_tt8c_april20='dispho_tt_kurhs_Run2018C_319625_319910_ave_e5_cali.root'

caliinfile_tt8b_v15='dispho_tt_kurhs_v15_Run2018B_317080_319077_ave_e5_cali.root'
caliinfile_tt8b_v17='dispho_tt_kurhs_v17_Run2018B_317080_319077_ave_e5_cali.root'
caliinfile_tt8b_v18='dispho_tt_kurhs_v18_Run2018B_317080_319077_ave_e5_cali2.root'

caliinfile_tt8d_v15='dispho_tt_kurhs_v15_Run2018D_320673_320824_ave_e5_cali.root'
caliinfile_tt8d_v16='dispho_tt_kurhs_v16_Run2018D_320673_320824_ave_e5_cali.root'
caliinfile_tt8d_v19='dispho_tt_kurhs_v19_Run2018D_320807_320824_ave_e5_cali.root'
caliinfile_tt8d_v20='dispho_tt_kurhs_v20_Run2018D_320807_320824_ave_e5_cali.root'
caliinfile_tt8d_v21='dispho_tt_kurhs_v21_Run2018D_320807_320824_ave_e5_cali.root'

caliinfile_tt7f_v16='dispho_tt_kurhs_v16_Run2017F_ave_e5_cali.root'

#caliinfile_ul18='dispho_ot_mini_ul_deg_Run2018_ave_e5_cali.root'
caliinfile_ul18ABC='dispho_ot_mini_ul_deg_Run2018ABC_ave_e5_cali.root'
caliinfile_ul18D='dispho_ot_mini_ul_deg_Run2018D_ave_e5_cali.root'
caliinfile_ul18Dgt28='dispho_ot_mini_ul_gt28_deg_Run2018D_ave_e5_cali.root'
caliinfile_ul17='dispho_ot_mini_ul_deg_Run2017_ave_e5_cali.root'
caliinfile_ul16='dispho_ot_mini_ul_deg_Run2016_ave_e5_cali.root'

caliinfile_mc_dytoll='dispho_mc_kurhs_DYJetsToLL_ave_e5_cali.root'
caliinfile_mcv31_dytoll='dispho_mc_v31_DYJetsToLL_ave_e5_cali.root'

# set cali and infile here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#caliinfile=caliinfile8c_kurhoot
#caliinfile=caliinfile8c
#caliinfile=caliinfile8a
#caliinfile=caliinfile_tt8b_v15
#caliinfile=caliinfile_tt8b_v18
#caliinfile=caliinfile_tt8d_v15
#caliinfile=caliinfile_tt8d_v16
#caliinfile=caliinfile_tt8d_v19
#caliinfile=caliinfile_tt8d_v20
#caliinfile=caliinfile_tt7f_v16
caliinfile=caliinfile_mcv31_dytoll
#caliinfile=caliinfile_tt8d_v21
#caliinfile=caliinfile_ul18ABC
#caliinfile=caliinfile_ul18Dgt28
#caliinfile=caliinfile_ul17
#caliinfile=caliinfile_ul16
#caliinfile='nocali'

#infile=skimoutfile100 # ot 8a
#infile=skimoutfile305
#infile=skimoutfile303_ele
#infile=skimoutfile502c # 18C ele
#infile=skimoutfile012# run2018B V15
#infile=skimoutfile0127# run2018B V17
#infile=skimoutfile0128# run2018B V18
#infile=skimoutfile0136# run2018D V16
#infile=skimoutfile0139# run2018D V19
#infile=skimoutfile0146# run2017F V16
#infile=skimoutfile01320# run2018D V20
#infile=skimoutfile01321# run2018D V21
infile=skimoutfile_mc_dytoll_v32
#infile=skimoutfile2016ul
#infile=skimoutfile2017ul
#infile=skimoutfile2018ul
#infile=skimoutfile2018Dulgt28
#infile=skimoutfile2018Culgt28
#infile='none'

cut_cf='ku_config/tmp_cut_config.txt'  # INCLUSIVE PLOTS
#cut_cf='ku_config/tmp_same_cut_config.txt' # SAME PLOTS
#cut_cf='ku_config/tmp_diff_cut_config.txt' # DIFFRENT PLOTS
misc_cf='misc_config/misc.txt'
varwgt_cf='varwgt_config/empty.txt'
timefit_cf='ku_config/tmp_timefit_config.txt'
timefit_c_cf='ku_config/tmp_timefit_core_config.txt'
timefit_t_cf='ku_config/tmp_timefit_tail_config.txt'
timefit_g2_cf='ku_config/tmp_timefit_gaus2_config.txt'
skim_loc_cf='skim_config/DiXtal_kurecs_Skim.txt'  #  LOCAL SKIMS
skim_loc_mini_cf='skim_config/DiXtal_nokurecs_Skim.txt' #  LOCAL SKIMS nokurhs
#skim_cf='skim_config/DiXtal_Skim.txt'
skim_glo_cf='skim_config/Zee_kurecs_Skim.txt'  #  GLOBAL  SKIMS
skim_glo_mini_cf='skim_config/Zee_nokurecs_Skim.txt'  #  GLOBAL  SKIMS nokurhs
misc_fit_cf='ku_config/tmp_misc_fit.txt'

#indir="/home/t3-ku/jaking/trees/ecal/datasets/"
indir="/home/t3-ku/jaking/datasets/ecalTiming/"
#indir="/home/t3-ku/jaking/datasets/ecalTiming/SingleElectron/"
#indir="/home/t3-ku/jaking/datasets/ecalTiming/EGamma/"
#indir="/home/t3-ku/jaking/datasets/ecalTiming/DoubleEG/"
#indir="/scratch/jaking/"
#indir="../test/"
#indir='/home/t3-ku/jaking/ecaltiming/skimmed_trees/'
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/local_ta/"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/local_tb/"
skimoutdirloc="/home/t3-ku/jaking/ecaltiming/skimmed_trees/local_chain/"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/global_ta/"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/global_tb/"
skimoutdirglo="/home/t3-ku/jaking/ecaltiming/skimmed_trees/global_chain/"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/compiled"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/shell"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/skims_2t_18nov/"
#skimoutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/rhskims/"
skimoutdir="./"
if 'Local' in res : pskimindir=skimoutdirloc
else : pskimindir=skimoutdirglo

#in_skim_list='dispho_ot_mini_Run2018.txt'
#in_skim_list='dispho_ot_mini_Run2018_ele_dZ1p0.txt'
#in_skim_list='dispho_ot_mini_Run2017.txt'
#in_skim_list='dispho_ot_mini_ul_Run2017.txt'
#in_skim_list='dispho_ot_mini_Run2016.txt'
#in_skim_list='dispho_ot_mini_Run2.txt'
#in_skim_list='dispho_ot_mini_ul_Run2.txt'
#in_skim_list='dispho_ot_mini_Eeff_Run2018.txt'
#in_skim_list='dispho_ot_mini_Eeff_Run2017.txt'
#in_skim_list='dispho_ot_mini_Eeff_Run2016.txt'
#in_skim_list='dispho_ot_mini_Eeff_Run2.txt'
#in_skim_list='dispho_ot_mini_ele_pl_Run2018A.txt'
#in_skim_list='dispho_ot_mini_ele_pl_Run2018B.txt'
#in_skim_list='dispho_ot_mini_ele_pl_Run2018C.txt'
#in_skim_list='dispho_ot_mini_ele_pl_Run2018D.txt'
#in_skim_list='dispho_mc_v31_DYJetsToLL_Eta.txt'
in_skim_list='dispho_tt_kurhs_v21_Run2018D_320807_320824_Eta.txt'
#in_skim_list='none'

#caliindir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/global_ta/"
caliindir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/local_chain/"
#caliindir=skimoutdirloc
calioutdir="/home/t3-ku/jaking/ecaltiming/skimmed_trees/"
sldir=''
#sldir='skimfilelists/'

outdir=infile[:-5]
outdir_chain=in_skim_list[:-4]
plotdir='/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/macros/trplots/'
qc='\\",\\"'
qq='" "'
sq=' "'
eq='"'
sp=' '

plotter2d='./runTreePlotter2D.obj '
plotter2dsh='./scripts/runTreePlotter2D.sh '
timefitsh='./scripts/runTimeFitter.sh '
timefit='./runTimeFitter.obj '

skim2a='./wc_runKUSkimmer_v2a.obj '
skim2wt='root -b -q -l wc_runKUSkimmer_v2wt.C\(\\"'
skim_chain_2a='./wc_runKUSkimmer_chain_v2a.obj '
#skim_chain_kurh_2a='./wc_runKUSkimmer_kurh_chain_v2a.obj '
skim_chain_kurh_2a='./wc_runKUSkimmer_kurh_chain_v2a_ele.obj '
skim_chain_kurh_2a_noele='./wc_runKUSkimmer_kurh_chain_v2a_noele.obj '
skim2b='root -b -q -l wc_runKUSkimmer_v2a.C\(\\"'
#skim2='root -b -q -l wc_runKUSkimmer.C\(\\"'
skim_chain_mc_2a='./wc_runKUSkimmer_mc_chain_v2a_ele.obj '

dotimeres3d='./wc_ku_plot3dResolution.obj '

#dotimeres2d='./wc_ku_plot2dResolution.obj '
#dotimeres2d_ch='./wc_ku_plot2dResolution_chain.obj '
dotimeres2d_mf='./wc_ku_plot2dResolution_mf.obj '
dotimeres2d_mf_abseta='./wc_ku_plot2dResolution_mf_abseta.obj '
dotimeres2d_mf_gloeta='./wc_ku_plot2dResolution_mf_glo_eta.obj '
dotimeres2d_mfe='./wc_ku_plot2dResolution_energy_mf.obj '
dotimeres2d_ctu='./wc_ku_plot2dRes_ctu.obj '
dotimeres2d_ctu_mini='./wc_ku_plot2dRes_ctu_mini.obj '
#dotimeres2d_ctu='./wc_ku_plot2dRes_ctu_notof.obj '
dotimeres2dE_ctu='./wc_ku_plot2dResE_ctu.obj '
dotimeres2d_ctu_runs='./wc_ku_plot2dRes_ctu_runs.obj '
#dotimeres2d='./wc_ku_plot2dRes_alt_tof.obj '
#dotimeres2d='./wc_ku_plot2dRes_eb_minus.obj '
#dotimeres2d='./wc_ku_plot2dRes_eb_plus.obj '
#dotimeres2d='./wc_ku_plot2dRes_epem.obj '

doavecali='./wc_ku_InterCali_aveRecHit_v1.obj '
doavecalimini='./wc_ku_InterCali_aveRecHit_mini.obj '
doavecalimini_test='./wc_ku_InterCali_aveRecHit_test.obj '
doavecalimini_mf='./wc_ku_InterCali_aveRecHit_mini_mf.obj '
doavecalimini_test='./cali_cont_test.obj '
doavecalimini_2='./wc_ku_InterCali_aveRecHit_c2_mini_mf.obj '
doavecalimini_4='./wc_ku_InterCali_aveRecHit_c4_mini_mf.obj '
doavecalimini_10='./wc_ku_InterCali_aveRecHit_c10_mini_mf.obj '
doavecalimini_100='./wc_ku_InterCali_aveRecHit_c100_mini_mf.obj '
doavecalimini_e1='./wc_ku_InterCali_aveRecHit_e1_mini.obj '
doavecalimini_e2='./wc_ku_InterCali_aveRecHit_e2_mini.obj '
doavecalimini_e10='./wc_ku_InterCali_aveRecHit_e10_mini.obj '
doavecalimini_e20='./wc_ku_InterCali_aveRecHit_e20_mini.obj '

doocccalimini='./wc_ku_InterCali_occ_mini.obj '
doavecaliminipho='./wc_ku_InterCali_aveRecHit_mini_pho_mf.obj '
doocccalikurh='./wc_ku_InterCali_aveRecHit_kurhs.obj '
doocccalikurhoot='./wc_ku_InterCali_aveRecHit_isoot_kurhs.obj '
#doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter.obj '
doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_red.obj '
#doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_e0p5.obj '
#doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_e1p0.obj '
#doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_e2p0.obj '
#doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_e10p0.obj '
#doocccalikurhootf='./wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_e20p0.obj '

dointercali2='./wc_ku_InterCali_global_v2.obj '
dointercali2a='./wc_ku_InterCali_global_v2a.obj '
dointercali2b='./wc_ku_InterCali_global_v2b.obj '
dointercali3='./wc_ku_InterCali_global_v3.obj '
dointercali3b='./wc_ku_InterCali_global_v3b.obj '
dointercali4a='./wc_ku_InterCali_global_v4a.obj '

doglobalplots='./wc_ku_global_plots.obj '
docaliplot='./wc_ku_CaliPlots.obj '
dorhcolplot='./wc_ku_rhCollectionPlots.obj '
#docalirhcolplot='./wc_ku_cali_rhCollectionPlots.obj '
docalirhcolplot='./wc_ku_cali_ksrhCollectionPlots.obj '
domcplot='./wc_ku_plot_kurh_vs_mc.obj '
domcanaplot='./wc_ku_ana_plot_kurh_vs_mc.obj '
end_skim='\\"\)'

plot1dcali='./wc_ku_plot1dcali.obj '
plotelez='./wc_ku_plot_eleZ.obj '
plotootamp='./wc_ku_plot_ootamps.obj '

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

def do_plots_sh( plot_list ):

    for entry in plot_list :
        #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
	##  makes base 2d plot for time fit
        cmd2d=plotter2dsh+sq+skimoutdir+infile+qq+skimoutdir+infile+qq+cut_cf+qq+varwgt_cf+qq+entry[0]+qq+misc_cf+qq+era+qq+entry[1]+qq+outdir+"/"+eq
        os.system(cmd2d)
	## run fitter, getting 2D plots from before
	filedir="trplots/"+outdir+"/"
        cmdtf=timefitsh+sq+filedir+entry[1]+'.root'+qq+entry[0]+qq+misc_fit_cf+qq+timefit_cf+qq+era+qq+entry[2]+timefile+qq+outdir+"/"+eq
        os.system(cmdtf)

def fmove( infile, outdir ):

	print( 'Checking: ' + infile )	
	if( os.path.exists( infile ) ) :
		print( 'Moving: ' + infile + ' to ' + outdir[-12:] )  
		shutil.move( infile, outdir )
	else : 
		print( 'Error: ' + infile + ' does not exist.' )

def do_3dplots( plot_list ):

   ##########     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     change the local/global type!!!!!!!!!!!!
    print( 'Processing Plot List' )
    date = time.strftime("%d%m%Y")+'_'+time.strftime("%H%M")
    for entry in plot_list :
      for isd_type in isd_list :
        print( 'Producing plots for : ' + entry[0] )
        #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
        ##  makes base 2d plot for time fit
        write_file=entry[1]+'_'+isd_type+'_AvsA'
        plot_file=entry[2]+'_'+isd_type
        cmd3d=dotimeres3d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type
        print( '>>>>>>>>>>>>>>>>>  ' + cmd3d )
        os.system(cmd3d)

def do_plots( plot_list ):

   ##########     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     change the local/global type!!!!!!!!!!!!
    print( 'Processing Plot List' )
    date = time.strftime("%d%m%Y")+'_'+time.strftime("%H%M")
    for entry in plot_list :
      for isd_type in isd_list :
        print( 'Producing plots for : ' + entry[0] )
        #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
        ##  makes base 2d plot for time fit
        write_file=entry[1]+'_'+isd_type
        write_file_3d=entry[1]+'_'+isd_type+'_AvsA'
        plot_file=entry[2]+'_'+isd_type
        ##cmd2d=dotimeres2d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+entry[1]+sp+entry[3]+sp+entry[4]+sp+isd_type
        cmd2d=dotimeres2d_ctu+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type
        #cmd2d=domcplot+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file #+sp+entry[3]+sp+entry[4]+sp+isd_type
        #cmd2d=dotimeres2d_ctu_mini+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type
        #cmd2d=dotimeres2dE_ctu+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type
        #cmd3d=dotimeres3d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file_3d+sp+entry[3]+sp+entry[4]+sp+isd_type
        print( '>>>>>>>>>>>>>>>>>  ' + cmd2d )
        os.system(cmd2d)
        #print( '>>>>>>>>>>>>>>>>>  ' + cmd3d )
        #os.system(cmd3d)
        #----  add clean up
        if 'Local' in res : plotres = '_loc'
        else : plotres = '_glo'
        writedir = plotdir+outdir[0:9]+plotres+outdir[9:]+"_"+"cali"+caliinfile[6:-5]+"_"+date+"/"
        if( not os.path.exists(writedir) ) : os.mkdir(writedir)
        #for ext in [ 'png', 'pdf' ] : 
        #   for sca in [ 'lin', 'log' ] : 
        #      fmove( write_file+'_'+sca+'.'+ext , writedir )
        fmove( write_file+'.root', writedir )
        #fmove( write_file_3d+'.root', writedir )
        #fmove( write_file+'_integrals.log', writedir )
        print( 'Finished TreePlotting for plot: ' + entry[0] )

        #shutil.move(f, 'dest_folder')    
        ## run fitter, getting 2D plots from before
        cmdtf=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_cf+sp+era+sp+plot_file+timefile
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtf )
        os.system(cmdtf)
        cmdtfc=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_c_cf+sp+era+sp+plot_file+timefilec
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtfc )
        #os.system(cmdtfc)
        cmdtft=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_t_cf+sp+era+sp+plot_file+timefilet
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtft )
        #os.system(cmdtft)
        cmdtf2g=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_g2_cf+sp+era+sp+plot_file+timefile2g
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtf2g )
        #os.system(cmdtf2g)

        #-----  add clean up
        for ext in [ 'png', 'pdf' ] :
          for sca in [ 'lin', 'log', 'lin_logx', 'log_logx' ] :
            for typ in [ 'mu', 'sigma' ] :
               #if( ('log' not in sca) and ('mu' not in typ) ) :      
               fmove( typ+'_'+plot_file+'_timefit_'+sca+'.'+ext , writedir )
               #fmove( typ+'_'+plot_file+'_timefit_'+sca+'.'+ext , writedir )
        for tfile in [ timefile, timefilec, timefilet, timefile2g ] :
               fmove( plot_file+tfile+'.root', writedir )
               fmove( plot_file+tfile+'_fitinfo.log', writedir )
        print( 'Finished TimeFitting for plot: ' + entry[0] )
        print( '------------------------------------------------------------' )

def do_plots_runs( plot_list, brun, erun ):

	##########     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     change the local/global type!!!!!!!!!!!!
    print( 'Processing Plot List' )
    date = time.strftime("%d%m%Y")+'_'+time.strftime("%H%M")
    for entry in plot_list :
      for isd_type in isd_list :
        print( 'Producing plots for : ' + entry[0] )
        #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
        ##  makes base 2d plot for time fit
        write_file=entry[1]+'_'+isd_type
        write_file_3d=entry[1]+'_'+isd_type+'_AvsA'
        plot_file=entry[2]+'_'+isd_type
        cmd2d=dotimeres2d_ctu_runs+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type+sp+brun+sp+erun
        #cmd3d=dotimeres3d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file_3d+sp+entry[3]+sp+entry[4]+sp+isd_type
        print( '>>>>>>>>>>>>>>>>>  ' + cmd2d )
        os.system(cmd2d)
        #print( '>>>>>>>>>>>>>>>>>  ' + cmd3d )
        #os.system(cmd3d)
        #----  add clean up
        if 'Local' in res : plotres = '_loc'
        else : plotres = '_glo'
        writedir = plotdir+outdir[0:9]+plotres+outdir[9:]+"_"+"cali"+caliinfile[6:-5]+'_'+brun+'_'+erun+"_"+date+"/"
        if( not os.path.exists(writedir) ) : os.mkdir(writedir)
        #for ext in [ 'png', 'pdf' ] : 
	     #	for sca in [ 'lin', 'log' ] : 
	     #		fmove( write_file+'_'+sca+'.'+ext , writedir )
        fmove( write_file+'.root', writedir )
        fmove( write_file_3d+'.root', writedir )
        #fmove( write_file+'_integrals.log', writedir )
        print( 'Finished TreePlotting for plot: ' + entry[0] )	

	     #shutil.move(f, 'dest_folder')		
        ## run fitter, getting 2D plots from before
        cmdtf=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_cf+sp+era+sp+plot_file+timefile
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtf )
        os.system(cmdtf)
        cmdtfc=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_c_cf+sp+era+sp+plot_file+timefilec
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtfc )
        #os.system(cmdtfc)
        cmdtft=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_t_cf+sp+era+sp+plot_file+timefilet
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtft )
        #os.system(cmdtft)
        cmdtf2g=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_g2_cf+sp+era+sp+plot_file+timefile2g
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtf2g )
        #os.system(cmdtf2g)
	     #-----  add clean up
        for ext in [ 'png', 'pdf' ] : 
		    for sca in [ 'lin', 'log', 'lin_logx', 'log_logx' ] : 
		  	   for typ in [ 'mu', 'sigma' ] :
		  		   #if( ('log' not in sca) and ('mu' not in typ) ) :		 
		  		   fmove( typ+'_'+plot_file+'_timefit_'+sca+'.'+ext , writedir )
		  		   #fmove( typ+'_'+plot_file+'_timefit_'+sca+'.'+ext , writedir )
        for tfile in [ timefile, timefilec, timefilet, timefile2g ] :
               fmove( plot_file+tfile+'.root', writedir )
               fmove( plot_file+tfile+'_fitinfo.log', writedir )
        print( 'Finished TimeFitting for plot: ' + entry[0] )
        print( '------------------------------------------------------------' )

def do_plots_runs_list( plot_list, runlist ):

        for runrange in runlist :
             do_plots_runs( plot_list, str(runrange[0]), str(runrange[1]) )

def do_plots_chain( plot_list, brun, erun, leta, heta  ):

   ##########     <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     change the local/global type!!!!!!!!!!!!
   print( 'Processing Plot List' )
   date = time.strftime("%d%m%Y")+'_'+time.strftime("%H%M")
   for entry in plot_list :
     for isd_type in isd_list :
        print( 'Producing plots for : ' + entry[0] )
        #2d_plot = entry[0]  #2d_outfile = entry[1]  #tf_outile = entry[2]
        ##  makes base 2d plot for time fit
        write_file=entry[1]+'_'+isd_type
        plot_file=entry[2]+'_'+isd_type
        cmd2d=dotimeres2d_mf+pskimindir+sp+in_skim_list+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type+sp+brun+sp+erun+sp+leta+sp+heta
        #cmd2d=dotimeres2d_mf_gloeta+pskimindir+sp+in_skim_list+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type+sp+brun+sp+erun+sp+leta+sp+heta
        #cmd2d=dotimeres2d_mf_abseta+pskimindir+sp+in_skim_list+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type+sp+brun+sp+erun+sp+leta+sp+heta
        #cmd2d=dotimeres2d_mfe+pskimindir+sp+in_skim_list+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_type
        print( '>>>>>>>>>>>>>>>>>  ' + cmd2d )
        os.system(cmd2d)
        #----  add clean up
        if 'Local' in res : plotres = '_loc'
        else : plotres = '_glo'
        #writedir = plotdir+outdir_chain[0:9]+plotres+outdir_chain[9:]+"_"+"cali_none_runs_"+brun+'_'+erun+"_abseta_"+leta.replace('-','m')+'_'+heta.replace('-','m')+'_'+date+"/"
        writedir = plotdir+outdir_chain[0:9]+plotres+outdir_chain[9:]+"_"+"cali_none_runs_"+brun+'_'+erun+"_eta_"+leta.replace('-','m')+'_'+heta.replace('-','m')+'_'+date+"/"
        if( not os.path.exists(writedir) ) : os.mkdir(writedir)
        #for ext in [ 'png', 'pdf' ] : 
        #  for sca in [ 'lin', 'log' ] : 
        #     fmove( entry[1]+'_'+sca+'.'+ext , writedir )
        fmove( write_file+'.root', writedir )
        #fmove( write_file+'_integrals.log', writedir )
        print( 'Finished TreePlotting for plot: ' + entry[0] )

        #shutil.move(f, 'dest_folder')      
        ## run fitter, getting 2D plots from before
        cmdtf=timefit+sp+writedir+write_file+'.root'+sp+entry[0]+sp+misc_fit_cf+sp+timefit_cf+sp+era+sp+plot_file+timefile
        print( '>>>>>>>>>>>>>>>>>  ' + cmdtf )
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

def do_plots_chain_list( plot_list, runlist, etalist  ):

        for runrange in runlist :
              for etarange in etalist :
		             do_plots_chain( plot_list, str(runrange[0]), str(runrange[1]), str(etarange[0]), str(etarange[1])  )

## run skimmer 
def do_skimmer():

         cmdskim=skim2a+indir+sp+skimoutdir+sp+skiminfile+sp+skim_cf
#        cmdskim=skim2b+indir+qc+skimoutdir+qc+skiminfile+qc+skim_cf+end_skim
#        cmdskim=skim2+indir+qc+skimoutdir+qc+skiminfile+qc+skim_cf+end_skim
         print(cmdskim)
         os.system(cmdskim)

def do_skimmer_list(infilelist):
 
	      for skimfile in infilelist :

        	    #cmdskim=skim2a+indir+sp+skimoutdir+sp+skimfile+sp+skim_cf
        	    cmdskim=skim2b+indir+qc+skimoutdir+qc+skimfile+qc+skim_cf+end_skim
             #cmdskim=skim2wt+indir+qc+skimoutdir+qc+skimfile+qc+skim_cf+end_skim
             #print(cmdskim)
             #os.system(cmdskim)

def do_skimmer_chain():
        cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdir+sp++sldir+skiminlist+sp+skim_loc_cf
        #cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdir+sp+sldir+skiminlist+sp+skim_loc_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_glo_chain():

        #cmdskim=skim_chain_2a+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_cf
        cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_glo_mini_chain():

        #cmdskim=skim_chain_2a+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_cf
        cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_mini_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_noele_glo_chain():

        #cmdskim=skim_chain_2a+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_cf
        cmdskim=skim_chain_kurh_2a_noele+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_loc_chain():

        #cmdskim=skim_chain_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_loc_mini_chain():

        cmdskim=skim_chain_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        #cmdskim=skim_chain_kurh_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_loc_mc_chain():

        #cmdskim=skim_chain_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        #cmdskim=skim_chain_mc_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        cmdskim=skim_chain_mc_2a+indir+sp+skimoutdirloc+sp+sldir+skiminlist+sp+skim_loc_cf
        print(cmdskim)
        os.system(cmdskim)

def do_skimmer_glo_mc_chain():

        cmdskim=skim_chain_mc_2a+indir+sp+skimoutdirglo+sp+sldir+skiminlist+sp+skim_glo_cf
        print(cmdskim)
        os.system(cmdskim)

##  run preplot skimmer
def do_avecali():

        cmdintercali=doavecali+indir+sp+sldir+skiminlist+sp+skimoutdir+caliinfile
        print(cmdintercali)
        os.system(cmdintercali)

def do_avecalimini():

        cmdintercali=doavecalimini_mf+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        #cmdintercali=doavecalimini_2+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        #cmdintercali=doavecalimini_4+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        #cmdintercali=doavecalimini_10+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        #cmdintercali=doavecalimini_100+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        #cmdintercali=doavecalimini_test+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        print(cmdintercali)
        os.system(cmdintercali)

def do_avecalikurh():

        #cmdintercali=doocccalikurh+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        cmdintercali=doocccalikurhootf+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        print(cmdintercali)
        os.system(cmdintercali)

def do_occcalimini():

        cmdintercali=doocccalimini+indir+sp+sldir+skiminlist+sp+sldir+skiminlist[0:-4]+'_Ave_Mini_Occ.root'
        print(cmdintercali)
        os.system(cmdintercali)

def do_avecaliminipho():

        cmdintercali=doavecaliminipho+indir+sp+sldir+skiminlist+sp+calioutdir+caliinfile
        print(cmdintercali)
        os.system(cmdintercali)

def do_intercaliXX():

		  #cmdintercali=dointercali2+skimoutdir+skiminfile+sp+skimoutdir+caliinfile2+sp+mfc
        cmdintercali=dointercali2a+skimoutdir+skiminfile+sp+skimoutdir+caliinfile2a+sp+mfc
        #cmdintercali=dointercali2b+skimoutdir+skiminfile+sp+skimoutdir+caliinfile2b+sp+mfc
        #cmdintercali=dointercali3+skimoutdir+skiminfile+sp+skimoutdir+caliinfile3+sp+mfc
        #cmdintercali=dointercali3b+skimoutdir+skiminfile+sp+skimoutdir+caliinfile3b+sp+mfc
        #cmdintercali=dointercali4a+skimoutdir+skiminfile+sp+skimoutdir+caliinfile4a+sp+mfc
        print(cmdintercali)
        os.system(cmdintercali)

#wc_ku_global_plots.obj
def do_globalplots():

        cmdintercali=doglobalplots+skimoutdirglo+sp+in_skim_list+sp+in_skim_list[0:-4]+'_global_plots.root'
        print(cmdintercali)
        os.system(cmdintercali)

#wc_ku_CaliPlots.C
def do_caliplots():

	     cmdcaliplot=docaliplot+caliindir+cali1infile+sp+caliindir+cali2infile+sp+caliindir+calioutfile+sp+iterations
        #print(cmdcaliplot)
        #os.system(cmdcaliplot)

#wc_ku_rhCollectionPlots.C
def do_rhcoloplots():

        #cmdrhcolplot=dorhcolplot+indir+sp+skiminlist+sp+skimoutdir+rhcoloutfile
        cmdrhcolplot=docalirhcolplot+indir+sp+skiminlist+sp+skimoutdir+rhcoloutfile+sp+caliindir+caliinfile
        print(cmdrhcolplot)
        os.system(cmdrhcolplot)

def do_wc_ku_plot1dcali():

        #calimap='AveXtalRtStcRecTimeE5'
        #calimap='AveXtalRtStcRecTime'
        #calimap='AveXtalRtOOTStcRecTimeE5'
        #calimap='AveXtalRtOOTStcRecTime'
        #calimap='AveXtalWtOOTStcRecTime'
        #calimap='AveXtalRtStcPhoIcRecTime'
        #calimap='AveXtalRtOOTStcPhoIcRecTime'
        #calimap='AveXtalMiniRecTime'
        #calimap='AveXtalWtStcRecTime'
        #calimap='AveXtalMfootStcRecTime'
        calimap='AveXtalMfootCCStcRecTime'

        cmd1dcaliplot=plot1dcali+caliindir+caliinfile+sp+calimap
        print(cmd1dcaliplot)
        os.system(cmd1dcaliplot)

def do_wc_ku_plot_eleZ():

        #makeplots( califilename, infilename, outfilename, tvarname, calimapname, isd_type )
        #dotimeres3d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_typ
        cmdplotelez=plotelez+caliindir+caliinfile+sp+skimoutdirglo+infile+sp+'./'+infile[:-5]+'_elez_plots'
        print(cmdplotelez)
        os.system(cmdplotelez)

def do_wc_ku_mcplots():

        cmdmcplots=domcplot+caliindir+caliinfile+sp+skimoutdirloc+infile+sp+'./'+infile[:-5]+'_mc_plots'
        print(cmdmcplots)
        os.system(cmdmcplots)

def do_wc_ku_mcanaplots():

        anainfile='ku_mc_test_tt_dispho_6k_v2.root'
        cmdmcplots=domcanaplot+caliindir+caliinfile+sp+anainfile+sp+anainfile[:-5]+'_mc_plots'
        print(cmdmcplots)
        os.system(cmdmcplots)

def do_wc_ku_plot_ootamp():

        #makeplots( califilename, infilename, outfilename, tvarname, calimapname, isd_type )
        #dotimeres3d+caliindir+caliinfile+sp+pskimindir+infile+sp+'./'+write_file+sp+entry[3]+sp+entry[4]+sp+isd_typ
        cmdplotootamp=plotootamp+caliindir+caliinfile+sp+skimoutdirloc+infile+sp+'./'+infile[:-5]+'_ootamp_plots'
        print(cmdplotootamp)
        os.system(cmdplotootamp)

######################################################################################

#do_hadd(hadd_inlist)
##do_skimmer()
##do_skimmer_list(inlist_debug)
##do_skimmer_list(inlist_tree_10)
##do_skimmer_list(inlist_tree_94)
##do_skimmer_list_wt(inlist_dataset_egamma_woot)
##do_skimmer_list(inlist_dataset_1617)
#do_skimmer_chain()                         #########  skimmer set for kurhs false
#do_skimmer_loc_chain()
#do_skimmer_loc_mini_chain()
#do_skimmer_loc_mc_chain()
#do_skimmer_glo_chain()
#do_skimmer_glo_mini_chain()
#do_skimmer_glo_mc_chain()
#do_skimmer_noele_glo_chain()
##do_avecali()
#do_avecalikurh()
#do_avecalimini()
##do_avecaliminipho()
##do_intercaliXX()
#do_3dplots( plot_list )
#do_plots( plot_list )    #######  <<<<<<<<<<<<<<<<<     change the local/global type!!!!!!!!!!!!
#do_plots_runs( plot_list, '1', '400000' ) 
runlist = [[100000,400000]]
#runlist = [[297000,30600]] # full 2017
#runlist = [[315000,326000]] # full 2018
#runlist = [[315000,316000],[315000,318100],[318100,320200],[318100,322800],[320200,322800],[322800,326000],[320200,326000]]
#runlist = [[315000,316000],[315000,318100],[318100,320200]] # pre 18D
#runlist = [[320200,322800],[322800,326000],[320200,326000]] # post 18D
#runlist = [[315250,315300],[315302,315400],[315401,315450],[315451,315600],[315601,315750]]
#runlist = [[315000,316000]] # 2018A
#runlist = [[315000,315300]]
#runlist = [[318100,322800]]
#etalist = [[-90,90]]
#etalist = [[0,90]]
#etalist = [[1,4],[5,10],[11,15],[16,20],[21,25],[26,30],[31,35],[36,40],[41,45],[46,50],[51,55],[56,60],[61,65],[66,70],[71,75],[76,80],[81,85],[5,6],[7,10]]
#etalist = [[0,25],[26,45],[46,65],[66,90]]
#etalist = [[-25,0],[-45,-26],[-65,-46],[-90,-66]]
etalist = [[0,25],[26,45],[46,65],[66,90],[-25,0],[-45,-26],[-65,-46],[-90,-66]]
#etalist = [[46,65]]
#etalist = [[-65,-46]]
#do_plots_runs_list( plot_list, runlist )
#do_plots_chain_list( plot_list, runlist, etalist)
#do_occcalimini()
#do_globalplots()
#do_caliplots()
#do_rhcoloplots()
#do_wc_ku_plot1dcali()
#do_wc_ku_plot_eleZ()
#do_wc_ku_plot_ootamp()
do_wc_ku_mcanaplots()
#do_wc_ku_mcplots()



