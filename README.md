# Displaced Photon Analysis Framework

Update to README: this code has been modified to work with CMSSW_10_2_X.
Code belongs to 

cmsrel CMSSW_10_2_5
cd CMSSW_10_2_5/src
cmsenv
git cms-init

git cms-merge-topic cms-egamma:EgammaID_1023
git cms-merge-topic cms-egamma:EgammaPostRecoTools

Two lines need to be edited in RecoEgamma/EgammaTools/python/EgammaPostRecoTools.py
Comment out lines 208 and 210
Add the following lines:
phoSrc = cms.InputTag('slimmedOOTPhotons',processName=cms.InputTag.skipCurrentProcess())
phoCalibSrc = cms.InputTag('slimmedOOTPhotons',processName=cms.InputTag.skipCurrentProcess())

git clone git@github.com:jwill24/Timing.git
git checkout 10_2_X

scram b -j 10


-----------------------

### Notation on variable names in nTuples

- rh = recHit
- sc = SuperCluster
- ph = photon
- pho = photon (used in branch names)
- is* = "bool" for is*
  - isHLT = is matched to HLT object
  - isGen = is matched to gen particle
- genVpion = generator V-pion (from HVDS)
- gengmsb = generator GMSB matched neutralino

- object*
  - E = energy
  - pt = transverse energy

- jet* (vector up to 10)
  - ID = jet cut based ID
  - NHF = neutral hadron energy fraction
  - NEMF = neutral EM energy fraction
  - CHF = charged hadron energy fraction
  - CEMF = charged EM energy fraction
  - MUF = muon energy fraction
  - NHM = neutral multiplicity
  - CHM = charged multiplicity

- rh* = vector of rechit values
  - ID = raw detector ID
  - TOF = time of flight corrected to PV
  - isOOT = if true, recHit is flagged OOT collection
  - isGS6,isGS1 = if true, photon has Gain Swith 6, 1 (reminder, base gain is 12, then 6, then 1)
  - ped* = pedestal noise (Gain 12, 6, 1)
  - pedrms* = pedestal noise error (Gain 12, 6, 1)

- pho* [photons 0-3] 
  - passEleVeto = photon passes electron veto
  - hasPixSeed = photon has pixel seed
  - HoE = hadTowerOverEM (single HCAL tower over EM energy)
  - r9 = seed E / 3x3 E
  - sieie = sigma_ieta,ieta
  - sipip = sigma_iphi,iphi
  - sieip = sigma_ieta,iphi
  - smaj = S_major (semi-major axis)
  - smin = S_minor (semi-minor axis)
  - alpha = angle of smaj to origin
  - suisseX = swisscross, seed energy / four surrounding energy
  - gedID = GED cut-based ID
  - ootID = OOT cut-based ID
  - Iso = Isolation
  - IsoC = Isolation corrected for (rho, pt)
    - ChgHadIso = Charged Hadron Iso
    - NeuHadIso = Neutral Hadron Iso
    - PhoIso = Photon Iso
    - EcalPFClIso = ECAL PF Cluster Iso
    - HcalPFClIso = HCAL PF Cluster Iso
    - TrkIso = Tracker Iso (hollow cone dR < 0.3)
  - recHits = vector of indices inside rh* branches for each photon
  - seed = index of seed rec hit for photon
  - seed* = value of seed rec hit branch
  - weighttime* = cluster weighted time, computed at first level skim
  - is (bools)
    - isEB = seed rechit is from ECAL barrel, else assumed endcap
    - isSignal = photon is matched to gen photon from signal particle
    - isOOT = if true, photon is from OOT collection, else from GED collection
    - isTrk = if true, object is matched to a single track pT > 5 within dR < 0.2

uncertainties:
- *Abs = (Absolute) Uncertainty = energy +/- *Abs
- *Rel = (Relative) Uncertainty = energy * (1 +/- *Rel)
- *SF  = (Scale Factor) = energy * SF

-----------------------

### Core chain of analysis:

Produce ntuples with multicrab:
- test/multicrab_dispho_Data.py
- test/multicrab_dispho_Bkgd.py
- test/multicrab_dispho_GMSB.py
- test/multicrab_dispho_HVDS.py

N.B. XSecs taken from GenXSecAnalyzerTool (see fork of genproductions)

Each script calls config: ```test/dispho.py```. Make sure to configure correctly! Plugins used:
- NTuplizer  : plugins/Dispho.cc/hh and plugins/DisPhoTypes.hh
- HelperUtils: plugins/CommonUtils.cc/hh

Output of ntuples end up in EOS group space: currently configured for /eos/cms/group/phys_exotica/displacedPhotons/nTuples/2017. Now begin macro chain of analysis: 

- cd to ```dispho_work/macros```.
- Produce skims with new time branches, event weights, basic core skim + met flags: scripts/skimAndMerge/*.sh
  - Also makes PU weights...
  - Can launch skims in parallel with loops in background
- Produce data+bkgd mc skims into a single file: scripts/runFastSkimmer.sh
- Produce signal skims into single file: scripts/runSignalSkimmer.sh
- Make sure to do both for GJets CR, QCD CR, and SR selection

- Then run the scripts for making the variable weight trees in CR to SR: scripts/makeWgtsAndPlots.sh
- Then check 1D final plots: scripts/makePlotsForSR.sh
- Finally, run 2D plots for fis: scripts/makeLimits.sh

Plots outputted to lxplus eos user space: /eos/user/k/kmcdermo/www/dispho/plots

--------------------------------

### Old files of interest stored in cms user kmcdermo space

- Backup of older fast skims: /eos/cms/store/user/kmcdermo/nTuples/BACKUP/afs/cern.ch/work/k/kmcdermo/private/dispho/Analysis
  - production directory is older mirror of development directory
  - CMSSW_9_4_10 is copy of since deprecated skims
- Backup of since deprecated skims (original output from CRAB deleted): /eos/cms/store/user/kmcdermo/nTuples/skims
- Backup of since deprecated unskimmed CRAB output for OOT VID studies: /eos/cms/store/user/kmcdermo/nTuples/unskimmed

--------------------------------

### To do:
- switch ctau to tau [ns]
- make sure to use REAL ctau in limit plots... update scripts to read in this value
- make exclusion in 2D vs neutralino mass
- make exclusion in 1D vs REAL ctau (slices of neutralino mass)
