//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jun  1 19:31:53 2019 by ROOT version 6.10/09
// from TTree disphotree/disphotree
// found on file: dispho_DiXtal_v4_deg2017B_raw94_297101.root
//////////////////////////////////////////////////////////

#ifndef dispho_skim_v4_h
#define dispho_skim_v4_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class dispho_skim_v4 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TFile 	  *outTfile;

   Float_t 	binmax;
   Float_t 	nbins;
   Float_t      step;
   Int_t	maxbin;
   Int_t 	nTbins;
   Float_t 	tBin;
   Int_t	od_nTbins;
   Float_t      od_tBin;

   vector<vector< TH1F* >>	twodeeMax; //(nbins, vector< TH1F* >(nbins,  TH1F* ));
   vector< TH1F* > 		onedeeMax_0; //(nbins,  TH1F* );
   vector< TH1F* > 		onedeeMax_1; //(nbins,  TH1F* );
   vector< int >		onedeeMaxCount_0;
   vector< int >                onedeeMaxCount_1;

   vector<vector< TH1F* >>      twodeeBefore; //(nbins, vector< TH1F* >(nbins,  TH1F* ));
   vector< TH1F* >              onedeeBefore_0; //(nbins,  TH1F* );
   vector< TH1F* >              onedeeBefore_1; //(nbins,  TH1F* );
   vector< int >                onedeeBeforeCount_0;
   vector< int >                onedeeBeforeCount_1;

   vector<vector< TH1F* >>      twodeeAfter; //(nbins, vector< TH1F* >(nbins,  TH1F* ));
   vector< TH1F* >              onedeeAfter_0; //(nbins,  TH1F* );
   vector< TH1F* >              onedeeAfter_1; //(nbins,  TH1F* );
   vector< int >                onedeeAfterCount_0;
   vector< int >                onedeeAfterCount_1;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          lumi;
   ULong64_t       event;
   Float_t         gZmass;
   Float_t         gdR;
   UInt_t          bunch_crossing;
   UInt_t          num_bunch;
   UInt_t          subtrain_position;
   UInt_t          train_position;
   UInt_t          subtrain_number;
   UInt_t          train_number;
   Int_t           nxtal_sep;
   Bool_t          hltSignal;
   Bool_t          hltRefPhoID;
   Bool_t          hltRefDispID;
   Bool_t          hltRefHT;
   Bool_t          hltPho50;
   Bool_t          hltPho200;
   Bool_t          hltDiPho70;
   Bool_t          hltDiPho3022M90;
   Bool_t          hltDiPho30PV18PV;
   Bool_t          hltEle32WPT;
   Bool_t          hltDiEle33MW;
   Bool_t          hltJet500;
   Int_t           nvtx;
   Float_t         vtxX;
   Float_t         vtxY;
   Float_t         vtxZ;
   Float_t         rho;
   Float_t         t1pfMETpt;
   Float_t         t1pfMETphi;
   Float_t         t1pfMETsumEt;
   Int_t           njets;
   Int_t           nrechits;
   Int_t           nurechits;
   Int_t           ndigis;
   Int_t           nphotons;
   Float_t         phoE_0;
   Float_t         phopt_0;
   Float_t         phoeta_0;
   Float_t         phophi_0;
   Float_t         phoscE_0;
   Float_t         phosceta_0;
   Float_t         phoscphi_0;
   Float_t         phoHoE_0;
   Float_t         phor9_0;
   Float_t         photdz_0;
   Float_t         phoChgHadIso_0;
   Float_t         phoNeuHadIso_0;
   Float_t         phoPhoIso_0;
   Float_t         phoEcalPFClIso_0;
   Float_t         phoHcalPFClIso_0;
   Float_t         phoTrkIso_0;
   Float_t         phosieie_0;
   Float_t         phosmaj_0;
   Float_t         phosmin_0;
   Float_t         phosuisseX_0;
   Float_t         phoseedE_0;
   Float_t         phoseedtime_0;
   Float_t         phoseedTOF_0;
   Int_t           phoseedisGS6_0;
   Int_t           phoseedisGS1_0;
   Float_t         phoseedadcToGeV_0;
   Float_t         phoseedped12_0;
   Float_t         phoseedped6_0;
   Float_t         phoseedped1_0;
   Float_t         phoseedpedrms12_0;
   Float_t         phoseedpedrms6_0;
   Float_t         phoseedpedrms1_0;
   Float_t         phoseedootA0_0;
   Float_t         phoseedootA1_0;
   Float_t         phoseedootA2_0;
   Float_t         phoseedootA3_0;
   Float_t         phoseedootA4_0;
   Float_t         phoseedootA5_0;
   Float_t         phoseedootA6_0;
   Float_t         phoseedootA7_0;
   Float_t         phoseedootA8_0;
   Float_t         phoseedootA9_0;
   Float_t         phoseedootMax_0;
   Float_t         phoseedootMbefore_0;
   Float_t         phoseedootMafter_0;
   Int_t           phoseedootSign_0;
   Float_t         phoseedootVsum_0;
   Bool_t          phoisOOT_0;
   Bool_t          phoisEB_0;
   Bool_t          phoisHLT_0;
   Bool_t          phoisTrk_0;
   Bool_t          phopassEleVeto_0;
   Bool_t          phohasPixSeed_0;
   Int_t           phogedID_0;
   Int_t           phoootID_0;
   Int_t           phoseedTT_0;
   Int_t           phonrechits_0;
   Int_t           phonrechitsLT120_0;
   Float_t         phomeantime_0;
   Float_t         phomeantimeLT120_0;
   Float_t         phoweightedtime_0;
   Float_t         phoweightedtimeLT120_0;
   Float_t         phoweightedtimeTOF_0;
   Float_t         phoweightedtimeLT120TOF_0;
   Float_t         phoE_1;
   Float_t         phopt_1;
   Float_t         phoeta_1;
   Float_t         phophi_1;
   Float_t         phoscE_1;
   Float_t         phosceta_1;
   Float_t         phoscphi_1;
   Float_t         phoHoE_1;
   Float_t         phor9_1;
   Float_t         photdz_1;
   Float_t         phoChgHadIso_1;
   Float_t         phoNeuHadIso_1;
   Float_t         phoPhoIso_1;
   Float_t         phoEcalPFClIso_1;
   Float_t         phoHcalPFClIso_1;
   Float_t         phoTrkIso_1;
   Float_t         phosieie_1;
   Float_t         phosmaj_1;
   Float_t         phosmin_1;
   Float_t         phosuisseX_1;
   Float_t         phoseedE_1;
   Float_t         phoseedtime_1;
   Float_t         phoseedTOF_1;
   Int_t           phoseedisGS6_1;
   Int_t           phoseedisGS1_1;
   Float_t         phoseedadcToGeV_1;
   Float_t         phoseedped12_1;
   Float_t         phoseedped6_1;
   Float_t         phoseedped1_1;
   Float_t         phoseedpedrms12_1;
   Float_t         phoseedpedrms6_1;
   Float_t         phoseedpedrms1_1;
   Float_t         phoseedootA0_1;
   Float_t         phoseedootA1_1;
   Float_t         phoseedootA2_1;
   Float_t         phoseedootA3_1;
   Float_t         phoseedootA4_1;
   Float_t         phoseedootA5_1;
   Float_t         phoseedootA6_1;
   Float_t         phoseedootA7_1;
   Float_t         phoseedootA8_1;
   Float_t         phoseedootA9_1;
   Float_t         phoseedootMax_1;
   Float_t         phoseedootMbefore_1;
   Float_t         phoseedootMafter_1;
   Int_t           phoseedootSign_1;
   Float_t         phoseedootVsum_1;
   Bool_t          phoisOOT_1;
   Bool_t          phoisEB_1;
   Bool_t          phoisHLT_1;
   Bool_t          phoisTrk_1;
   Bool_t          phopassEleVeto_1;
   Bool_t          phohasPixSeed_1;
   Int_t           phogedID_1;
   Int_t           phoootID_1;
   Int_t           phoseedTT_1;
   Int_t           phonrechits_1;
   Int_t           phonrechitsLT120_1;
   Float_t         phomeantime_1;
   Float_t         phomeantimeLT120_1;
   Float_t         phoweightedtime_1;
   Float_t         phoweightedtimeLT120_1;
   Float_t         phoweightedtimeTOF_1;
   Float_t         phoweightedtimeLT120TOF_1;
   Float_t         evtwgt;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_gZmass;   //!
   TBranch        *b_gdR;   //!
   TBranch        *b_bunch_crossing;   //!
   TBranch        *b_num_bunch;   //!
   TBranch        *b_subtrain_position;   //!
   TBranch        *b_train_position;   //!
   TBranch        *b_subtrain_number;   //!
   TBranch        *b_train_number;   //!
   TBranch        *b_nxtal_sep;   //!
   TBranch        *b_hltSignal;   //!
   TBranch        *b_hltRefPhoID;   //!
   TBranch        *b_hltRefDispID;   //!
   TBranch        *b_hltRefHT;   //!
   TBranch        *b_hltPho50;   //!
   TBranch        *b_hltPho200;   //!
   TBranch        *b_hltDiPho70;   //!
   TBranch        *b_hltDiPho3022M90;   //!
   TBranch        *b_hltDiPho30PV18PV;   //!
   TBranch        *b_hltEle32WPT;   //!
   TBranch        *b_hltDiEle33MW;   //!
   TBranch        *b_hltJet500;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_vtxX;   //!
   TBranch        *b_vtxY;   //!
   TBranch        *b_vtxZ;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_t1pfMETpt;   //!
   TBranch        *b_t1pfMETphi;   //!
   TBranch        *b_t1pfMETsumEt;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_nrechits;   //!
   TBranch        *b_nurechits;   //!
   TBranch        *b_ndigis;   //!
   TBranch        *b_nphotons;   //!
   TBranch        *b_phoE_0;   //!
   TBranch        *b_phopt_0;   //!
   TBranch        *b_phoeta_0;   //!
   TBranch        *b_phophi_0;   //!
   TBranch        *b_phoscE_0;   //!
   TBranch        *b_phosceta_0;   //!
   TBranch        *b_phoscphi_0;   //!
   TBranch        *b_phoHoE_0;   //!
   TBranch        *b_phor9_0;   //!
   TBranch        *b_photdz_0;   //!
   TBranch        *b_phoChgHadIso_0;   //!
   TBranch        *b_phoNeuHadIso_0;   //!
   TBranch        *b_phoPhoIso_0;   //!
   TBranch        *b_phoEcalPFClIso_0;   //!
   TBranch        *b_phoHcalPFClIso_0;   //!
   TBranch        *b_phoTrkIso_0;   //!
   TBranch        *b_phosieie_0;   //!
   TBranch        *b_phosmaj_0;   //!
   TBranch        *b_phosmin_0;   //!
   TBranch        *b_phosuisseX_0;   //!
   TBranch        *b_phoseedE_0;   //!
   TBranch        *b_phoseedtime_0;   //!
   TBranch        *b_phoseedTOF_0;   //!
   TBranch        *b_phoseedisGS6_0;   //!
   TBranch        *b_phoseedisGS1_0;   //!
   TBranch        *b_phoseedadcToGeV_0;   //!
   TBranch        *b_phoseedped12_0;   //!
   TBranch        *b_phoseedped6_0;   //!
   TBranch        *b_phoseedped1_0;   //!
   TBranch        *b_phoseedpedrms12_0;   //!
   TBranch        *b_phoseedpedrms6_0;   //!
   TBranch        *b_phoseedpedrms1_0;   //!
   TBranch        *b_phoseedootA0_0;   //!
   TBranch        *b_phoseedootA1_0;   //!
   TBranch        *b_phoseedootA2_0;   //!
   TBranch        *b_phoseedootA3_0;   //!
   TBranch        *b_phoseedootA4_0;   //!
   TBranch        *b_phoseedootA5_0;   //!
   TBranch        *b_phoseedootA6_0;   //!
   TBranch        *b_phoseedootA7_0;   //!
   TBranch        *b_phoseedootA8_0;   //!
   TBranch        *b_phoseedootA9_0;   //!
   TBranch        *b_phoseedootMax_0;   //!
   TBranch        *b_phoseedootMbefore_0;   //!
   TBranch        *b_phoseedootMafter_0;   //!
   TBranch        *b_phoseedootSign_0;   //!
   TBranch        *b_phoseedootVsum_0;   //!
   TBranch        *b_phoisOOT_0;   //!
   TBranch        *b_phoisEB_0;   //!
   TBranch        *b_phoisHLT_0;   //!
   TBranch        *b_phoisTrk_0;   //!
   TBranch        *b_phopassEleVeto_0;   //!
   TBranch        *b_phohasPixSeed_0;   //!
   TBranch        *b_phogedID_0;   //!
   TBranch        *b_phoootID_0;   //!
   TBranch        *b_phoseedTT_0;   //!
   TBranch        *b_phonrechits_0;   //!
   TBranch        *b_phonrechitsLT120_0;   //!
   TBranch        *b_phomeantime_0;   //!
   TBranch        *b_phomeantimeLT120_0;   //!
   TBranch        *b_phoweightedtime_0;   //!
   TBranch        *b_phoweightedtimeLT120_0;   //!
   TBranch        *b_phoweightedtimeTOF_0;   //!
   TBranch        *b_phoweightedtimeLT120TOF_0;   //!
   TBranch        *b_phoE_1;   //!
   TBranch        *b_phopt_1;   //!
   TBranch        *b_phoeta_1;   //!
   TBranch        *b_phophi_1;   //!
   TBranch        *b_phoscE_1;   //!
   TBranch        *b_phosceta_1;   //!
   TBranch        *b_phoscphi_1;   //!
   TBranch        *b_phoHoE_1;   //!
   TBranch        *b_phor9_1;   //!
   TBranch        *b_photdz_1;   //!
   TBranch        *b_phoChgHadIso_1;   //!
   TBranch        *b_phoNeuHadIso_1;   //!
   TBranch        *b_phoPhoIso_1;   //!
   TBranch        *b_phoEcalPFClIso_1;   //!
   TBranch        *b_phoHcalPFClIso_1;   //!
   TBranch        *b_phoTrkIso_1;   //!
   TBranch        *b_phosieie_1;   //!
   TBranch        *b_phosmaj_1;   //!
   TBranch        *b_phosmin_1;   //!
   TBranch        *b_phosuisseX_1;   //!
   TBranch        *b_phoseedE_1;   //!
   TBranch        *b_phoseedtime_1;   //!
   TBranch        *b_phoseedTOF_1;   //!
   TBranch        *b_phoseedisGS6_1;   //!
   TBranch        *b_phoseedisGS1_1;   //!
   TBranch        *b_phoseedadcToGeV_1;   //!
   TBranch        *b_phoseedped12_1;   //!
   TBranch        *b_phoseedped6_1;   //!
   TBranch        *b_phoseedped1_1;   //!
   TBranch        *b_phoseedpedrms12_1;   //!
   TBranch        *b_phoseedpedrms6_1;   //!
   TBranch        *b_phoseedpedrms1_1;   //!
   TBranch        *b_phoseedootA0_1;   //!
   TBranch        *b_phoseedootA1_1;   //!
   TBranch        *b_phoseedootA2_1;   //!
   TBranch        *b_phoseedootA3_1;   //!
   TBranch        *b_phoseedootA4_1;   //!
   TBranch        *b_phoseedootA5_1;   //!
   TBranch        *b_phoseedootA6_1;   //!
   TBranch        *b_phoseedootA7_1;   //!
   TBranch        *b_phoseedootA8_1;   //!
   TBranch        *b_phoseedootA9_1;   //!
   TBranch        *b_phoseedootMax_1;   //!
   TBranch        *b_phoseedootMbefore_1;   //!
   TBranch        *b_phoseedootMafter_1;   //!
   TBranch        *b_phoseedootSign_1;   //!
   TBranch        *b_phoseedootVsum_1;   //!
   TBranch        *b_phoisOOT_1;   //!
   TBranch        *b_phoisEB_1;   //!
   TBranch        *b_phoisHLT_1;   //!
   TBranch        *b_phoisTrk_1;   //!
   TBranch        *b_phopassEleVeto_1;   //!
   TBranch        *b_phohasPixSeed_1;   //!
   TBranch        *b_phogedID_1;   //!
   TBranch        *b_phoootID_1;   //!
   TBranch        *b_phoseedTT_1;   //!
   TBranch        *b_phonrechits_1;   //!
   TBranch        *b_phonrechitsLT120_1;   //!
   TBranch        *b_phomeantime_1;   //!
   TBranch        *b_phomeantimeLT120_1;   //!
   TBranch        *b_phoweightedtime_1;   //!
   TBranch        *b_phoweightedtimeLT120_1;   //!
   TBranch        *b_phoweightedtimeTOF_1;   //!
   TBranch        *b_phoweightedtimeLT120TOF_1;   //!
   TBranch        *b_evtwgt;   //!

//   dispho_skim_v4(TTree *tree=0);
   dispho_skim_v4(string intree, string filename);
   virtual ~dispho_skim_v4();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void	    MakePlots();
};

#endif

#ifdef dispho_skim_v4_cxx
//dispho_skim_v4::dispho_skim_v4(TTree *tree) : fChain(0) 
//{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("dispho_DiXtal_v4_deg2017B_raw94_297101.root");
//      if (!f || !f->IsOpen()) {
//         f = new TFile("dispho_DiXtal_v4_deg2017B_raw94_297101.root");
//      }
//      f->GetObject("disphotree",tree);
//
//   }
//   Init(tree);
//}
//
dispho_skim_v4::dispho_skim_v4(string intree, string filename)
{ 
   std::cout << "Creating out tfile." << std::endl; 
   outTfile = new TFile(filename.c_str(),"RECREATE");
   std::cout << "Getting in tfile and tTree." << std::endl;
   TTree *tree = 0;
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(intree.c_str());
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("dispho_DiXtal_v2_2016.root");
      if (!f || !f->IsOpen()) {
//         f = new TFile("dispho_DiXtal_v2_2016.root");
         f = new TFile(intree.c_str());
      }
      f->cd();
      f->GetObject("disphotree",tree);
   
   }
   std::cout << "Intilizing Tree." << std::endl;
   Init(tree);

   //96 0 0.24
   binmax = 0.128;
   nbins = 64;
   //  signed
   //binmax = 0.064;
   //nbins = 32;

   step = binmax/nbins;
   maxbin = nbins - 1;

   nTbins = 256;
   tBin = 6.4;

   od_nTbins = 128;
   od_tBin = 0.16;

   TH1F* tmpHist;

   vector< TH1F* > th1fv;

   std::cout << "Intilizing vector arrays." << std::endl;
   
    for( int i = 0; i < nbins; i++ ){

		twodeeMax.push_back(th1fv);
   		onedeeMaxCount_0.push_back(0);
   		onedeeMaxCount_1.push_back(0);
		string tmp1m = "onedeeMaxhist_0"+std::to_string(i);
		onedeeMax_0.push_back( new TH1F(tmp1m.c_str(),"",nTbins,(-1*tBin),tBin) );
		string tmp2m = "onedeeMaxhist_1"+std::to_string(i);
		onedeeMax_1.push_back( new TH1F(tmp2m.c_str(),"",nTbins,(-1*tBin),tBin) );

                twodeeBefore.push_back(th1fv);
                onedeeBeforeCount_0.push_back(0);
                onedeeBeforeCount_1.push_back(0);
                string tmp1b = "onedeeBeforehist_0"+std::to_string(i);
                onedeeBefore_0.push_back( new TH1F(tmp1b.c_str(),"",nTbins,(-1*tBin),tBin) );
                string tmp2b = "onedeeBeforehist_1"+std::to_string(i);
                onedeeBefore_1.push_back( new TH1F(tmp2b.c_str(),"",nTbins,(-1*tBin),tBin) );

                twodeeAfter.push_back(th1fv);
                onedeeAfterCount_0.push_back(0);
                onedeeAfterCount_1.push_back(0);
                string tmp1a = "onedeeAfterhist_0"+std::to_string(i);
                onedeeAfter_0.push_back( new TH1F(tmp1a.c_str(),"",nTbins,(-1*tBin),tBin) );
                string tmp2a = "onedeeAfterhist_1"+std::to_string(i);
                onedeeAfter_1.push_back( new TH1F(tmp2a.c_str(),"",nTbins,(-1*tBin),tBin) );

		for( int j = 0; j < nbins; j++ ){

			string tmp3m = "twodeeMaxhist_"+std::to_string(i)+"_"+std::to_string(j);
			twodeeMax[i].push_back( new TH1F(tmp3m.c_str(),"",nTbins,(-1*tBin),tBin) );

                        string tmp3b = "twodeeBeforehist_"+std::to_string(i)+"_"+std::to_string(j); 
                        twodeeBefore[i].push_back( new TH1F(tmp3b.c_str(),"",nTbins,(-1*tBin),tBin) );
 
                        string tmp3a = "twodeeAfterhist_"+std::to_string(i)+"_"+std::to_string(j); 
                        twodeeAfter[i].push_back( new TH1F(tmp3a.c_str(),"",nTbins,(-1*tBin),tBin) );

		} //(nbins, vector<vector<Float_t>>(nbins, vector<Float_t>));
   }

}

dispho_skim_v4::~dispho_skim_v4()
{
   outTfile->Close();
   delete outTfile;
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t dispho_skim_v4::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t dispho_skim_v4::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void dispho_skim_v4::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("gZmass", &gZmass, &b_gZmass);
   fChain->SetBranchAddress("gdR", &gdR, &b_gdR);
   fChain->SetBranchAddress("bunch_crossing", &bunch_crossing, &b_bunch_crossing);
   fChain->SetBranchAddress("num_bunch", &num_bunch, &b_num_bunch);
   fChain->SetBranchAddress("subtrain_position", &subtrain_position, &b_subtrain_position);
   fChain->SetBranchAddress("train_position", &train_position, &b_train_position);
   fChain->SetBranchAddress("subtrain_number", &subtrain_number, &b_subtrain_number);
   fChain->SetBranchAddress("train_number", &train_number, &b_train_number);
   fChain->SetBranchAddress("nxtal_sep", &nxtal_sep, &b_nxtal_sep);
   fChain->SetBranchAddress("hltSignal", &hltSignal, &b_hltSignal);
   fChain->SetBranchAddress("hltRefPhoID", &hltRefPhoID, &b_hltRefPhoID);
   fChain->SetBranchAddress("hltRefDispID", &hltRefDispID, &b_hltRefDispID);
   fChain->SetBranchAddress("hltRefHT", &hltRefHT, &b_hltRefHT);
   fChain->SetBranchAddress("hltPho50", &hltPho50, &b_hltPho50);
   fChain->SetBranchAddress("hltPho200", &hltPho200, &b_hltPho200);
   fChain->SetBranchAddress("hltDiPho70", &hltDiPho70, &b_hltDiPho70);
   fChain->SetBranchAddress("hltDiPho3022M90", &hltDiPho3022M90, &b_hltDiPho3022M90);
   fChain->SetBranchAddress("hltDiPho30PV18PV", &hltDiPho30PV18PV, &b_hltDiPho30PV18PV);
   fChain->SetBranchAddress("hltEle32WPT", &hltEle32WPT, &b_hltEle32WPT);
   fChain->SetBranchAddress("hltDiEle33MW", &hltDiEle33MW, &b_hltDiEle33MW);
   fChain->SetBranchAddress("hltJet500", &hltJet500, &b_hltJet500);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("vtxX", &vtxX, &b_vtxX);
   fChain->SetBranchAddress("vtxY", &vtxY, &b_vtxY);
   fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("t1pfMETpt", &t1pfMETpt, &b_t1pfMETpt);
   fChain->SetBranchAddress("t1pfMETphi", &t1pfMETphi, &b_t1pfMETphi);
   fChain->SetBranchAddress("t1pfMETsumEt", &t1pfMETsumEt, &b_t1pfMETsumEt);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("nrechits", &nrechits, &b_nrechits);
   fChain->SetBranchAddress("nurechits", &nurechits, &b_nurechits);
   fChain->SetBranchAddress("ndigis", &ndigis, &b_ndigis);
   fChain->SetBranchAddress("nphotons", &nphotons, &b_nphotons);
   fChain->SetBranchAddress("phoE_0", &phoE_0, &b_phoE_0);
   fChain->SetBranchAddress("phopt_0", &phopt_0, &b_phopt_0);
   fChain->SetBranchAddress("phoeta_0", &phoeta_0, &b_phoeta_0);
   fChain->SetBranchAddress("phophi_0", &phophi_0, &b_phophi_0);
   fChain->SetBranchAddress("phoscE_0", &phoscE_0, &b_phoscE_0);
   fChain->SetBranchAddress("phosceta_0", &phosceta_0, &b_phosceta_0);
   fChain->SetBranchAddress("phoscphi_0", &phoscphi_0, &b_phoscphi_0);
   fChain->SetBranchAddress("phoHoE_0", &phoHoE_0, &b_phoHoE_0);
   fChain->SetBranchAddress("phor9_0", &phor9_0, &b_phor9_0);
   fChain->SetBranchAddress("photdz_0", &photdz_0, &b_photdz_0);
   fChain->SetBranchAddress("phoChgHadIso_0", &phoChgHadIso_0, &b_phoChgHadIso_0);
   fChain->SetBranchAddress("phoNeuHadIso_0", &phoNeuHadIso_0, &b_phoNeuHadIso_0);
   fChain->SetBranchAddress("phoPhoIso_0", &phoPhoIso_0, &b_phoPhoIso_0);
   fChain->SetBranchAddress("phoEcalPFClIso_0", &phoEcalPFClIso_0, &b_phoEcalPFClIso_0);
   fChain->SetBranchAddress("phoHcalPFClIso_0", &phoHcalPFClIso_0, &b_phoHcalPFClIso_0);
   fChain->SetBranchAddress("phoTrkIso_0", &phoTrkIso_0, &b_phoTrkIso_0);
   fChain->SetBranchAddress("phosieie_0", &phosieie_0, &b_phosieie_0);
   fChain->SetBranchAddress("phosmaj_0", &phosmaj_0, &b_phosmaj_0);
   fChain->SetBranchAddress("phosmin_0", &phosmin_0, &b_phosmin_0);
   fChain->SetBranchAddress("phosuisseX_0", &phosuisseX_0, &b_phosuisseX_0);
   fChain->SetBranchAddress("phoseedE_0", &phoseedE_0, &b_phoseedE_0);
   fChain->SetBranchAddress("phoseedtime_0", &phoseedtime_0, &b_phoseedtime_0);
   fChain->SetBranchAddress("phoseedTOF_0", &phoseedTOF_0, &b_phoseedTOF_0);
   fChain->SetBranchAddress("phoseedisGS6_0", &phoseedisGS6_0, &b_phoseedisGS6_0);
   fChain->SetBranchAddress("phoseedisGS1_0", &phoseedisGS1_0, &b_phoseedisGS1_0);
   fChain->SetBranchAddress("phoseedadcToGeV_0", &phoseedadcToGeV_0, &b_phoseedadcToGeV_0);
   fChain->SetBranchAddress("phoseedped12_0", &phoseedped12_0, &b_phoseedped12_0);
   fChain->SetBranchAddress("phoseedped6_0", &phoseedped6_0, &b_phoseedped6_0);
   fChain->SetBranchAddress("phoseedped1_0", &phoseedped1_0, &b_phoseedped1_0);
   fChain->SetBranchAddress("phoseedpedrms12_0", &phoseedpedrms12_0, &b_phoseedpedrms12_0);
   fChain->SetBranchAddress("phoseedpedrms6_0", &phoseedpedrms6_0, &b_phoseedpedrms6_0);
   fChain->SetBranchAddress("phoseedpedrms1_0", &phoseedpedrms1_0, &b_phoseedpedrms1_0);
   fChain->SetBranchAddress("phoseedootA0_0", &phoseedootA0_0, &b_phoseedootA0_0);
   fChain->SetBranchAddress("phoseedootA1_0", &phoseedootA1_0, &b_phoseedootA1_0);
   fChain->SetBranchAddress("phoseedootA2_0", &phoseedootA2_0, &b_phoseedootA2_0);
   fChain->SetBranchAddress("phoseedootA3_0", &phoseedootA3_0, &b_phoseedootA3_0);
   fChain->SetBranchAddress("phoseedootA4_0", &phoseedootA4_0, &b_phoseedootA4_0);
   fChain->SetBranchAddress("phoseedootA5_0", &phoseedootA5_0, &b_phoseedootA5_0);
   fChain->SetBranchAddress("phoseedootA6_0", &phoseedootA6_0, &b_phoseedootA6_0);
   fChain->SetBranchAddress("phoseedootA7_0", &phoseedootA7_0, &b_phoseedootA7_0);
   fChain->SetBranchAddress("phoseedootA8_0", &phoseedootA8_0, &b_phoseedootA8_0);
   fChain->SetBranchAddress("phoseedootA9_0", &phoseedootA9_0, &b_phoseedootA9_0);
   fChain->SetBranchAddress("phoseedootMax_0", &phoseedootMax_0, &b_phoseedootMax_0);
   fChain->SetBranchAddress("phoseedootMbefore_0", &phoseedootMbefore_0, &b_phoseedootMbefore_0);
   fChain->SetBranchAddress("phoseedootMafter_0", &phoseedootMafter_0, &b_phoseedootMafter_0);
   fChain->SetBranchAddress("phoseedootSign_0", &phoseedootSign_0, &b_phoseedootSign_0);
   fChain->SetBranchAddress("phoseedootVsum_0", &phoseedootVsum_0, &b_phoseedootVsum_0);
   fChain->SetBranchAddress("phoisOOT_0", &phoisOOT_0, &b_phoisOOT_0);
   fChain->SetBranchAddress("phoisEB_0", &phoisEB_0, &b_phoisEB_0);
   fChain->SetBranchAddress("phoisHLT_0", &phoisHLT_0, &b_phoisHLT_0);
   fChain->SetBranchAddress("phoisTrk_0", &phoisTrk_0, &b_phoisTrk_0);
   fChain->SetBranchAddress("phopassEleVeto_0", &phopassEleVeto_0, &b_phopassEleVeto_0);
   fChain->SetBranchAddress("phohasPixSeed_0", &phohasPixSeed_0, &b_phohasPixSeed_0);
   fChain->SetBranchAddress("phogedID_0", &phogedID_0, &b_phogedID_0);
   fChain->SetBranchAddress("phoootID_0", &phoootID_0, &b_phoootID_0);
   fChain->SetBranchAddress("phoseedTT_0", &phoseedTT_0, &b_phoseedTT_0);
   fChain->SetBranchAddress("phonrechits_0", &phonrechits_0, &b_phonrechits_0);
   fChain->SetBranchAddress("phonrechitsLT120_0", &phonrechitsLT120_0, &b_phonrechitsLT120_0);
   fChain->SetBranchAddress("phomeantime_0", &phomeantime_0, &b_phomeantime_0);
   fChain->SetBranchAddress("phomeantimeLT120_0", &phomeantimeLT120_0, &b_phomeantimeLT120_0);
   fChain->SetBranchAddress("phoweightedtime_0", &phoweightedtime_0, &b_phoweightedtime_0);
   fChain->SetBranchAddress("phoweightedtimeLT120_0", &phoweightedtimeLT120_0, &b_phoweightedtimeLT120_0);
   fChain->SetBranchAddress("phoweightedtimeTOF_0", &phoweightedtimeTOF_0, &b_phoweightedtimeTOF_0);
   fChain->SetBranchAddress("phoweightedtimeLT120TOF_0", &phoweightedtimeLT120TOF_0, &b_phoweightedtimeLT120TOF_0);
   fChain->SetBranchAddress("phoE_1", &phoE_1, &b_phoE_1);
   fChain->SetBranchAddress("phopt_1", &phopt_1, &b_phopt_1);
   fChain->SetBranchAddress("phoeta_1", &phoeta_1, &b_phoeta_1);
   fChain->SetBranchAddress("phophi_1", &phophi_1, &b_phophi_1);
   fChain->SetBranchAddress("phoscE_1", &phoscE_1, &b_phoscE_1);
   fChain->SetBranchAddress("phosceta_1", &phosceta_1, &b_phosceta_1);
   fChain->SetBranchAddress("phoscphi_1", &phoscphi_1, &b_phoscphi_1);
   fChain->SetBranchAddress("phoHoE_1", &phoHoE_1, &b_phoHoE_1);
   fChain->SetBranchAddress("phor9_1", &phor9_1, &b_phor9_1);
   fChain->SetBranchAddress("photdz_1", &photdz_1, &b_photdz_1);
   fChain->SetBranchAddress("phoChgHadIso_1", &phoChgHadIso_1, &b_phoChgHadIso_1);
   fChain->SetBranchAddress("phoNeuHadIso_1", &phoNeuHadIso_1, &b_phoNeuHadIso_1);
   fChain->SetBranchAddress("phoPhoIso_1", &phoPhoIso_1, &b_phoPhoIso_1);
   fChain->SetBranchAddress("phoEcalPFClIso_1", &phoEcalPFClIso_1, &b_phoEcalPFClIso_1);
   fChain->SetBranchAddress("phoHcalPFClIso_1", &phoHcalPFClIso_1, &b_phoHcalPFClIso_1);
   fChain->SetBranchAddress("phoTrkIso_1", &phoTrkIso_1, &b_phoTrkIso_1);
   fChain->SetBranchAddress("phosieie_1", &phosieie_1, &b_phosieie_1);
   fChain->SetBranchAddress("phosmaj_1", &phosmaj_1, &b_phosmaj_1);
   fChain->SetBranchAddress("phosmin_1", &phosmin_1, &b_phosmin_1);
   fChain->SetBranchAddress("phosuisseX_1", &phosuisseX_1, &b_phosuisseX_1);
   fChain->SetBranchAddress("phoseedE_1", &phoseedE_1, &b_phoseedE_1);
   fChain->SetBranchAddress("phoseedtime_1", &phoseedtime_1, &b_phoseedtime_1);
   fChain->SetBranchAddress("phoseedTOF_1", &phoseedTOF_1, &b_phoseedTOF_1);
   fChain->SetBranchAddress("phoseedisGS6_1", &phoseedisGS6_1, &b_phoseedisGS6_1);
   fChain->SetBranchAddress("phoseedisGS1_1", &phoseedisGS1_1, &b_phoseedisGS1_1);
   fChain->SetBranchAddress("phoseedadcToGeV_1", &phoseedadcToGeV_1, &b_phoseedadcToGeV_1);
   fChain->SetBranchAddress("phoseedped12_1", &phoseedped12_1, &b_phoseedped12_1);
   fChain->SetBranchAddress("phoseedped6_1", &phoseedped6_1, &b_phoseedped6_1);
   fChain->SetBranchAddress("phoseedped1_1", &phoseedped1_1, &b_phoseedped1_1);
   fChain->SetBranchAddress("phoseedpedrms12_1", &phoseedpedrms12_1, &b_phoseedpedrms12_1);
   fChain->SetBranchAddress("phoseedpedrms6_1", &phoseedpedrms6_1, &b_phoseedpedrms6_1);
   fChain->SetBranchAddress("phoseedpedrms1_1", &phoseedpedrms1_1, &b_phoseedpedrms1_1);
   fChain->SetBranchAddress("phoseedootA0_1", &phoseedootA0_1, &b_phoseedootA0_1);
   fChain->SetBranchAddress("phoseedootA1_1", &phoseedootA1_1, &b_phoseedootA1_1);
   fChain->SetBranchAddress("phoseedootA2_1", &phoseedootA2_1, &b_phoseedootA2_1);
   fChain->SetBranchAddress("phoseedootA3_1", &phoseedootA3_1, &b_phoseedootA3_1);
   fChain->SetBranchAddress("phoseedootA4_1", &phoseedootA4_1, &b_phoseedootA4_1);
   fChain->SetBranchAddress("phoseedootA5_1", &phoseedootA5_1, &b_phoseedootA5_1);
   fChain->SetBranchAddress("phoseedootA6_1", &phoseedootA6_1, &b_phoseedootA6_1);
   fChain->SetBranchAddress("phoseedootA7_1", &phoseedootA7_1, &b_phoseedootA7_1);
   fChain->SetBranchAddress("phoseedootA8_1", &phoseedootA8_1, &b_phoseedootA8_1);
   fChain->SetBranchAddress("phoseedootA9_1", &phoseedootA9_1, &b_phoseedootA9_1);
   fChain->SetBranchAddress("phoseedootMax_1", &phoseedootMax_1, &b_phoseedootMax_1);
   fChain->SetBranchAddress("phoseedootMbefore_1", &phoseedootMbefore_1, &b_phoseedootMbefore_1);
   fChain->SetBranchAddress("phoseedootMafter_1", &phoseedootMafter_1, &b_phoseedootMafter_1);
   fChain->SetBranchAddress("phoseedootSign_1", &phoseedootSign_1, &b_phoseedootSign_1);
   fChain->SetBranchAddress("phoseedootVsum_1", &phoseedootVsum_1, &b_phoseedootVsum_1);
   fChain->SetBranchAddress("phoisOOT_1", &phoisOOT_1, &b_phoisOOT_1);
   fChain->SetBranchAddress("phoisEB_1", &phoisEB_1, &b_phoisEB_1);
   fChain->SetBranchAddress("phoisHLT_1", &phoisHLT_1, &b_phoisHLT_1);
   fChain->SetBranchAddress("phoisTrk_1", &phoisTrk_1, &b_phoisTrk_1);
   fChain->SetBranchAddress("phopassEleVeto_1", &phopassEleVeto_1, &b_phopassEleVeto_1);
   fChain->SetBranchAddress("phohasPixSeed_1", &phohasPixSeed_1, &b_phohasPixSeed_1);
   fChain->SetBranchAddress("phogedID_1", &phogedID_1, &b_phogedID_1);
   fChain->SetBranchAddress("phoootID_1", &phoootID_1, &b_phoootID_1);
   fChain->SetBranchAddress("phoseedTT_1", &phoseedTT_1, &b_phoseedTT_1);
   fChain->SetBranchAddress("phonrechits_1", &phonrechits_1, &b_phonrechits_1);
   fChain->SetBranchAddress("phonrechitsLT120_1", &phonrechitsLT120_1, &b_phonrechitsLT120_1);
   fChain->SetBranchAddress("phomeantime_1", &phomeantime_1, &b_phomeantime_1);
   fChain->SetBranchAddress("phomeantimeLT120_1", &phomeantimeLT120_1, &b_phomeantimeLT120_1);
   fChain->SetBranchAddress("phoweightedtime_1", &phoweightedtime_1, &b_phoweightedtime_1);
   fChain->SetBranchAddress("phoweightedtimeLT120_1", &phoweightedtimeLT120_1, &b_phoweightedtimeLT120_1);
   fChain->SetBranchAddress("phoweightedtimeTOF_1", &phoweightedtimeTOF_1, &b_phoweightedtimeTOF_1);
   fChain->SetBranchAddress("phoweightedtimeLT120TOF_1", &phoweightedtimeLT120TOF_1, &b_phoweightedtimeLT120TOF_1);
   fChain->SetBranchAddress("evtwgt", &evtwgt, &b_evtwgt);
   Notify();
}

Bool_t dispho_skim_v4::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void dispho_skim_v4::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t dispho_skim_v4::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef dispho_skim_v4_cxx
