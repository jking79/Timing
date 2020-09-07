CC=g++
CFLAGS = -pthread -std=c++1z -m64 -pthread -lm -ldl -rdynamic
LIBS = -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc
INCLUDES = -I/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_5/external/slc7_amd64_gcc700/bin/../../../../../../../slc7_amd64_gcc700/lcg/root/6.12.07-gnimlf5/include 
LFLAGS = -L/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_5/external/slc7_amd64_gcc700/bin/../../../../../../../slc7_amd64_gcc700/lcg/root/6.12.07-gnimlf5/lib

p1=runTimeFitter
p2=wc_runKUSkimmer_kurh_chain_v2a_ele
p3=wc_ku_plot2dResolution
p4=wc_ku_plot_ootamps
p5=wc_ku_plot2dResolution_mf
p5a=wc_ku_plot2dResolution_energy_mf
p6=wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_red
#p7=wc_ku_cali_ksrhCollectionPlots
p8=wc_ku_plot3dResolution
p9=wc_ku_plot2dRes_ctu
p13=wc_ku_plot2dResE_ctu
p10=wc_runKUSkimmer_kurh_chain_v2a_noele
p11=wc_ku_plot1dcali
p12=wc_ku_plot_eleZ
p14=wc_runKUSkimmer_mc_chain_v2a_ele
p15=wc_ku_plot_kurh_vs_mc
p16=wc_ku_plot2dRes_ctu_notof
p17=wc_ku_plot2dRes_ctu_runs
p18=wc_ku_plot2dResolution_mf_abseta
p19=wc_ku_plot2dRes_ctu_mini
p20=wc_ku_plot2dResolution_mf_glo_eta
p21=wc_ku_InterCali_aveRecHit_mini_mf
p22=wc_ku_ana_plot_kurh_vs_mc

all: $(p1) $(p2) $(p3) $(6) $(22)
# $(p4) $(p5) $(p7)

$(p1): $(p1).cpp
	$(CC) -o $(p1).obj $(p1).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)
 
$(p2): $(p2).cpp
	$(CC) -o $(p2).obj $(p2).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p3): $(p3).cpp
	$(CC) -o $(p3).obj $(p3).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p11): $(p11).cpp
	$(CC) -o $(p11).obj $(p11).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p12): $(p12).cpp
	$(CC) -o $(p12).obj $(p12).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p6): $(p6).cpp
	$(CC) -o $(p6).obj $(p6).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p4): $(p4).cpp
	$(CC) -o $(p4).obj $(p4).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p5): $(p5).cpp
	$(CC) -o $(p5).obj $(p5).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p5a): $(p5a).cpp
	$(CC) -o $(p5a).obj $(p5a).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p8): $(p8).cpp
	$(CC) -o $(p8).obj $(p8).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p9): $(p9).cpp
	$(CC) -o $(p9).obj $(p9).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p10): $(p10).cpp
	$(CC) -o $(p10).obj $(p10).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p13): $(p13).cpp
	$(CC) -o $(p13).obj $(p13).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p14): $(p14).cpp
	$(CC) -o $(p14).obj $(p14).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p15): $(p15).cpp
	$(CC) -o $(p15).obj $(p15).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p16): $(p16).cpp
	$(CC) -o $(p16).obj $(p16).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p17): $(p17).cpp
	$(CC) -o $(p17).obj $(p17).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p18): $(p18).cpp
	$(CC) -o $(p18).obj $(p18).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p19): $(p19).cpp
	$(CC) -o $(p19).obj $(p19).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p20): $(p20).cpp
	$(CC) -o $(p20).obj $(p20).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p21): $(p21).cpp
	$(CC) -o $(p21).obj $(p21).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p22): $(p22).cpp
	$(CC) -o $(p22).obj $(p22).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)


