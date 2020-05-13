CC=g++
CFLAGS = -pthread -std=c++1z -m64 -pthread -lm -ldl -rdynamic
LIBS = -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc
INCLUDES = -I/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_5/external/slc7_amd64_gcc700/bin/../../../../../../../slc7_amd64_gcc700/lcg/root/6.12.07-gnimlf5/include 
LFLAGS = -L/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_2_5/external/slc7_amd64_gcc700/bin/../../../../../../../slc7_amd64_gcc700/lcg/root/6.12.07-gnimlf5/lib

p1=runTimeFitter
p2=wc_runKUSkimmer_kurh_chain_v2a_ele
p3=wc_ku_plot2dResolution
#p4=wc_ku_plot2dResolution_chain
#p5=wc_ku_plot2dResolution_mf
p6=wc_ku_InterCali_aveRecHit_isoot_kurhs_fliter_red
#p7=wc_ku_cali_ksrhCollectionPlots

all: $(p1) $(p2) $(p3) $(6)
# $(p4) $(p5) $(p7)

$(p1): $(p1).cpp
	$(CC) -o $(p1).obj $(p1).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)
 
$(p2): $(p2).cpp
	$(CC) -o $(p2).obj $(p2).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

$(p3): $(p3).cpp
	$(CC) -o $(p3).obj $(p3).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

#$(p1): $(p4).cpp
#   $(CC) -o $(p4).obj $(p4).cpp $(CFLAGS)

#$(p1): $(p5).cpp
#   $(CC) -o $(p5).obj $(p5).cpp $(CFLAGS)

$(p6): $(p6).cpp
	$(CC) -o $(p6).obj $(p6).cpp $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)

#$(p1): $(p7).cpp
#   $(CC) -o $(p7).obj $(p7).cpp $(CFLAGS)

