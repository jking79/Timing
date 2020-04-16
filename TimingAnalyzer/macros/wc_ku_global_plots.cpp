//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar  7 14:16:31 2020 by ROOT version 6.12/07
// from TTree disphotree/disphotree
// found on file: local_skims/global_chain/dispho_ot_mini_Run2016B.root
//////////////////////////////////////////////////////////
// ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TColor.h"
#include "TPaveText.h"
#include "TText.h"
#include "TChain.h"

// STL includes
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <sys/stat.h>

using namespace std;

template <typename T> std::string to_string(T value)
{  
   //create an output string stream
   std::ostringstream os ;
   
   //throw the value into the string stream
   os << value ;
   
   //convert the string stream into a string and return
   return os.str() ;

//you can also do this
//std::string output;
//os >> output;  //throw whats in the string stream into the string
}

enum ECAL {EB, EM, EP, NONE};
std::string ecal_config_path("/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/macros/ecal_config/");

struct DetIDStruct
{
  DetIDStruct() {}
  DetIDStruct(const Int_t inI1, const Int_t inI2, const Int_t inTT, const Int_t & inEcal) : i1(inI1), i2(inI2), TT(inTT), ecal(inEcal)  {}

  Int_t i1; // EB: iphi, EE: ix
  Int_t i2; // EB: ieta, EE: iy
  Int_t TT; // trigger tower
  Int_t ecal; // EB, EM, EP
};


void SetupDetIDsEB( std::map<UInt_t,DetIDStruct> &DetIDMap )
{
    const std::string detIDConfigEB(ecal_config_path+"fullinfo_detids_EB.txt");
    std::ifstream infile( detIDConfigEB, std::ios::in);

    UInt_t cmsswId, dbID;
    Int_t hashedId, iphi, ieta, absieta, FED, SM, TT25, iTT, strip5, Xtal, phiSM, etaSM;
    TString pos;

    while (infile >> cmsswId >> dbID >> hashedId >> iphi >> ieta >> absieta >> pos >> FED >> SM >> TT25 >> iTT >> strip5 >> Xtal >> phiSM >> etaSM)
    {
        //std::cout << "DetID Input Line: " << cmsswId << " " << iphi << " "  << ieta << " " << EB << std::endl;
        DetIDMap[cmsswId] = {iphi,ieta,TT25,EB};
        auto idinfo = DetIDMap[cmsswId];
        //std::cout << "DetID set to : " << idinfo.i1 << " " << idinfo.i2 << " " << idinfo.ecal << std::endl;
    }
}

void SetupDetIDsEE( std::map<UInt_t,DetIDStruct> &DetIDMap )
{
    const std::string detIDConfigEE(ecal_config_path+"fullinfo_detids_EE.txt");
    std::ifstream infile( detIDConfigEE, std::ios::in);

    UInt_t cmsswId, dbID;
    Int_t hashedId, side, ix, iy, SC, iSC, Fed, TTCCU, strip, Xtal, quadrant;
    TString EE;

    while (infile >> cmsswId >> dbID >> hashedId >> side >> ix >> iy >> SC >> iSC >> Fed >> EE >> TTCCU >> strip >> Xtal >> quadrant)
    {
        ECAL ec = EM;
        if( side > 0 ) ec = EP;
        //std::cout << "DetID Input Line: " << cmsswId << " " << ix << " "  << iy << " " << ec << std::endl; 
        DetIDMap[cmsswId] = {ix,iy,TTCCU,ec};
        auto idinfo = DetIDMap[cmsswId];
        //std::cout << "DetID set to : " << idinfo.i1 << " " << idinfo.i2 << " " << idinfo.ecal << std::endl;
    }
}

void wc_ku_global_plots( string indir, string infilelist, string outfilename ){
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
   Int_t           nvtx;
   Float_t         vtxX;
   Float_t         vtxY;
   Float_t         vtxZ;
   Float_t         rho;
   Int_t           nrechits;
   Int_t           nkurechits;
   vector<int>     *out_npho_recHits_0;
   vector<int>     *out_npho_recHits_1;
   vector<int>     *out_npho_recHits_2;
   vector<int>     *out_npho_recHits_3;
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
   Float_t         photdz_0;
   Float_t         phosieie_0;
   Float_t         phosmaj_0;
   Float_t         phosmin_0;
   Float_t         phosuisseX_0;
   Float_t         phoseedE_0;
   Float_t         phoseedtime_0;
   Float_t         phoseedTOF_0;
   UInt_t          phoseedID_0;
   Int_t           phoseedI1_0;
   Int_t           phoseedI2_0;
   Int_t           phoseedEcal_0;
   Float_t         phoseedadcToGeV_0;
   Float_t         phoseedped12_0;
   Float_t         phoseedped6_0;
   Float_t         phoseedped1_0;
   Float_t         phoseedpedrms12_0;
   Float_t         phoseedpedrms6_0;
   Float_t         phoseedpedrms1_0;
   Float_t         phoseedkutime_0;
   UInt_t          phoseedkuID_0;
   Float_t         phoseedkuStctime_0;
   UInt_t          phoseedkuStcID_0;
   Float_t         phoseedkuNotStctime_0;
   UInt_t          phoseedkuNotStcID_0;
   Float_t         phoseedkuWootStctime_0;
   UInt_t          phoseedkuWootStcID_0;
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
   Bool_t          phohasPixSeed_0;
   Int_t           phoootID_0;
   Int_t           phoseedTT_0;
   Int_t           phonrechits_0;
   Float_t         phoE_1;
   Float_t         phopt_1;
   Float_t         phoeta_1;
   Float_t         phophi_1;
   Float_t         phoscE_1;
   Float_t         phosceta_1;
   Float_t         phoscphi_1;
   Float_t         photdz_1;
   Float_t         phosieie_1;
   Float_t         phosmaj_1;
   Float_t         phosmin_1;
   Float_t         phosuisseX_1;
   Float_t         phoseedE_1;
   Float_t         phoseedtime_1;
   Float_t         phoseedTOF_1;
   UInt_t          phoseedID_1;
   Int_t           phoseedI1_1;
   Int_t           phoseedI2_1;
   Int_t           phoseedEcal_1;
   Float_t         phoseedadcToGeV_1;
   Float_t         phoseedped12_1;
   Float_t         phoseedped6_1;
   Float_t         phoseedped1_1;
   Float_t         phoseedpedrms12_1;
   Float_t         phoseedpedrms6_1;
   Float_t         phoseedpedrms1_1;
   Float_t         phoseedkutime_1;
   UInt_t          phoseedkuID_1;
   Float_t         phoseedkuStctime_1;
   UInt_t          phoseedkuStcID_1;
   Float_t         phoseedkuNotStctime_1;
   UInt_t          phoseedkuNotStcID_1;
   Float_t         phoseedkuWootStctime_1;
   UInt_t          phoseedkuWootStcID_1;
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
   Bool_t          phohasPixSeed_1;
   Int_t           phoootID_1;
   Int_t           phoseedTT_1;
   Int_t           phonrechits_1;
   Float_t         phoE_2;
   Float_t         phopt_2;
   Float_t         phoeta_2;
   Float_t         phophi_2;
   Float_t         phoscE_2;
   Float_t         phosceta_2;
   Float_t         phoscphi_2;
   Float_t         photdz_2;
   Float_t         phosieie_2;
   Float_t         phosmaj_2;
   Float_t         phosmin_2;
   Float_t         phosuisseX_2;
   Float_t         phoseedE_2;
   Float_t         phoseedtime_2;
   Float_t         phoseedTOF_2;
   UInt_t          phoseedID_2;
   Int_t           phoseedI1_2;
   Int_t           phoseedI2_2;
   Int_t           phoseedEcal_2;
   Float_t         phoseedadcToGeV_2;
   Float_t         phoseedped12_2;
   Float_t         phoseedped6_2;
   Float_t         phoseedped1_2;
   Float_t         phoseedpedrms12_2;
   Float_t         phoseedpedrms6_2;
   Float_t         phoseedpedrms1_2;
   Float_t         phoseedkutime_2;
   UInt_t          phoseedkuID_2;
   Float_t         phoseedkuStctime_2;
   UInt_t          phoseedkuStcID_2;
   Float_t         phoseedkuNotStctime_2;
   UInt_t          phoseedkuNotStcID_2;
   Float_t         phoseedkuWootStctime_2;
   UInt_t          phoseedkuWootStcID_2;
   Float_t         phoseedootA0_2;
   Float_t         phoseedootA1_2;
   Float_t         phoseedootA2_2;
   Float_t         phoseedootA3_2;
   Float_t         phoseedootA4_2;
   Float_t         phoseedootA5_2;
   Float_t         phoseedootA6_2;
   Float_t         phoseedootA7_2;
   Float_t         phoseedootA8_2;
   Float_t         phoseedootA9_2;
   Float_t         phoseedootMax_2;
   Float_t         phoseedootMbefore_2;
   Float_t         phoseedootMafter_2;
   Int_t           phoseedootSign_2;
   Float_t         phoseedootVsum_2;
   Bool_t          phoisOOT_2;
   Bool_t          phoisEB_2;
   Bool_t          phohasPixSeed_2;
   Int_t           phoootID_2;
   Int_t           phoseedTT_2;
   Int_t           phonrechits_2;
   Float_t         phoE_3;
   Float_t         phopt_3;
   Float_t         phoeta_3;
   Float_t         phophi_3;
   Float_t         phoscE_3;
   Float_t         phosceta_3;
   Float_t         phoscphi_3;
   Float_t         photdz_3;
   Float_t         phosieie_3;
   Float_t         phosmaj_3;
   Float_t         phosmin_3;
   Float_t         phosuisseX_3;
   Float_t         phoseedE_3;
   Float_t         phoseedtime_3;
   Float_t         phoseedTOF_3;
   UInt_t          phoseedID_3;
   Int_t           phoseedI1_3;
   Int_t           phoseedI2_3;
   Int_t           phoseedEcal_3;
   Float_t         phoseedadcToGeV_3;
   Float_t         phoseedped12_3;
   Float_t         phoseedped6_3;
   Float_t         phoseedped1_3;
   Float_t         phoseedpedrms12_3;
   Float_t         phoseedpedrms6_3;
   Float_t         phoseedpedrms1_3;
   Float_t         phoseedkutime_3;
   UInt_t          phoseedkuID_3;
   Float_t         phoseedkuStctime_3;
   UInt_t          phoseedkuStcID_3;
   Float_t         phoseedkuNotStctime_3;
   UInt_t          phoseedkuNotStcID_3;
   Float_t         phoseedkuWootStctime_3;
   UInt_t          phoseedkuWootStcID_3;
   Float_t         phoseedootA0_3;
   Float_t         phoseedootA1_3;
   Float_t         phoseedootA2_3;
   Float_t         phoseedootA3_3;
   Float_t         phoseedootA4_3;
   Float_t         phoseedootA5_3;
   Float_t         phoseedootA6_3;
   Float_t         phoseedootA7_3;
   Float_t         phoseedootA8_3;
   Float_t         phoseedootA9_3;
   Float_t         phoseedootMax_3;
   Float_t         phoseedootMbefore_3;
   Float_t         phoseedootMafter_3;
   Int_t           phoseedootSign_3;
   Float_t         phoseedootVsum_3;
   Bool_t          phoisOOT_3;
   Bool_t          phoisEB_3;
   Bool_t          phohasPixSeed_3;
   Int_t           phoootID_3;
   Int_t           phoseedTT_3;
   Int_t           phonrechits_3;

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
   TBranch        *b_nvtx;   //!
   TBranch        *b_vtxX;   //!
   TBranch        *b_vtxY;   //!
   TBranch        *b_vtxZ;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_nrechits;   //!
   TBranch        *b_nkurechits;   //!
   TBranch        *b_out_npho_recHits_0;   //!
   TBranch        *b_out_npho_recHits_1;   //!
   TBranch        *b_out_npho_recHits_2;   //!
   TBranch        *b_out_npho_recHits_3;   //!
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
   TBranch        *b_photdz_0;   //!
   TBranch        *b_phosieie_0;   //!
   TBranch        *b_phosmaj_0;   //!
   TBranch        *b_phosmin_0;   //!
   TBranch        *b_phosuisseX_0;   //!
   TBranch        *b_phoseedE_0;   //!
   TBranch        *b_phoseedtime_0;   //!
   TBranch        *b_phoseedTOF_0;   //!
   TBranch        *b_phoseedID_0;   //!
   TBranch        *b_phoseedI1_0;   //!
   TBranch        *b_phoseedI2_0;   //!
   TBranch        *b_phoseedEcal_0;   //!
   TBranch        *b_phoseedadcToGeV_0;   //!
   TBranch        *b_phoseedped12_0;   //!
   TBranch        *b_phoseedped6_0;   //!
   TBranch        *b_phoseedped1_0;   //!
   TBranch        *b_phoseedpedrms12_0;   //!
   TBranch        *b_phoseedpedrms6_0;   //!
   TBranch        *b_phoseedpedrms1_0;   //!
   TBranch        *b_phoseedkutime_0;   //!
   TBranch        *b_phoseedkuID_0;   //!
   TBranch        *b_phoseedkuStctime_0;   //!
   TBranch        *b_phoseedkuStcID_0;   //!
   TBranch        *b_phoseedkuNotStctime_0;   //!
   TBranch        *b_phoseedkuNotStcID_0;   //!
   TBranch        *b_phoseedkuWootStctime_0;   //!
   TBranch        *b_phoseedkuWootStcID_0;   //!
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
   TBranch        *b_phohasPixSeed_0;   //!
   TBranch        *b_phoootID_0;   //!
   TBranch        *b_phoseedTT_0;   //!
   TBranch        *b_phonrechits_0;   //!
   TBranch        *b_phoE_1;   //!
   TBranch        *b_phopt_1;   //!
   TBranch        *b_phoeta_1;   //!
   TBranch        *b_phophi_1;   //!
   TBranch        *b_phoscE_1;   //!
   TBranch        *b_phosceta_1;   //!
   TBranch        *b_phoscphi_1;   //!
   TBranch        *b_photdz_1;   //!
   TBranch        *b_phosieie_1;   //!
   TBranch        *b_phosmaj_1;   //!
   TBranch        *b_phosmin_1;   //!
   TBranch        *b_phosuisseX_1;   //!
   TBranch        *b_phoseedE_1;   //!
   TBranch        *b_phoseedtime_1;   //!
   TBranch        *b_phoseedTOF_1;   //!
   TBranch        *b_phoseedID_1;   //!
   TBranch        *b_phoseedI1_1;   //!
   TBranch        *b_phoseedI2_1;   //!
   TBranch        *b_phoseedEcal_1;   //!
   TBranch        *b_phoseedadcToGeV_1;   //!
   TBranch        *b_phoseedped12_1;   //!
   TBranch        *b_phoseedped6_1;   //!
   TBranch        *b_phoseedped1_1;   //!
   TBranch        *b_phoseedpedrms12_1;   //!
   TBranch        *b_phoseedpedrms6_1;   //!
   TBranch        *b_phoseedpedrms1_1;   //!
   TBranch        *b_phoseedkutime_1;   //!
   TBranch        *b_phoseedkuID_1;   //!
   TBranch        *b_phoseedkuStctime_1;   //!
   TBranch        *b_phoseedkuStcID_1;   //!
   TBranch        *b_phoseedkuNotStctime_1;   //!
   TBranch        *b_phoseedkuNotStcID_1;   //!
   TBranch        *b_phoseedkuWootStctime_1;   //!
   TBranch        *b_phoseedkuWootStcID_1;   //!
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
   TBranch        *b_phohasPixSeed_1;   //!
   TBranch        *b_phoootID_1;   //!
   TBranch        *b_phoseedTT_1;   //!
   TBranch        *b_phonrechits_1;   //!
   TBranch        *b_phoE_2;   //!
   TBranch        *b_phopt_2;   //!
   TBranch        *b_phoeta_2;   //!
   TBranch        *b_phophi_2;   //!
   TBranch        *b_phoscE_2;   //!
   TBranch        *b_phosceta_2;   //!
   TBranch        *b_phoscphi_2;   //!
   TBranch        *b_photdz_2;   //!
   TBranch        *b_phosieie_2;   //!
   TBranch        *b_phosmaj_2;   //!
   TBranch        *b_phosmin_2;   //!
   TBranch        *b_phosuisseX_2;   //!
   TBranch        *b_phoseedE_2;   //!
   TBranch        *b_phoseedtime_2;   //!
   TBranch        *b_phoseedTOF_2;   //!
   TBranch        *b_phoseedID_2;   //!
   TBranch        *b_phoseedI1_2;   //!
   TBranch        *b_phoseedI2_2;   //!
   TBranch        *b_phoseedEcal_2;   //!
   TBranch        *b_phoseedadcToGeV_2;   //!
   TBranch        *b_phoseedped12_2;   //!
   TBranch        *b_phoseedped6_2;   //!
   TBranch        *b_phoseedped1_2;   //!
   TBranch        *b_phoseedpedrms12_2;   //!
   TBranch        *b_phoseedpedrms6_2;   //!
   TBranch        *b_phoseedpedrms1_2;   //!
   TBranch        *b_phoseedkutime_2;   //!
   TBranch        *b_phoseedkuID_2;   //!
   TBranch        *b_phoseedkuStctime_2;   //!
   TBranch        *b_phoseedkuStcID_2;   //!
   TBranch        *b_phoseedkuNotStctime_2;   //!
   TBranch        *b_phoseedkuNotStcID_2;   //!
   TBranch        *b_phoseedkuWootStctime_2;   //!
   TBranch        *b_phoseedkuWootStcID_2;   //!
   TBranch        *b_phoseedootA0_2;   //!
   TBranch        *b_phoseedootA1_2;   //!
   TBranch        *b_phoseedootA2_2;   //!
   TBranch        *b_phoseedootA3_2;   //!
   TBranch        *b_phoseedootA4_2;   //!
   TBranch        *b_phoseedootA5_2;   //!
   TBranch        *b_phoseedootA6_2;   //!
   TBranch        *b_phoseedootA7_2;   //!
   TBranch        *b_phoseedootA8_2;   //!
   TBranch        *b_phoseedootA9_2;   //!
   TBranch        *b_phoseedootMax_2;   //!
   TBranch        *b_phoseedootMbefore_2;   //!
   TBranch        *b_phoseedootMafter_2;   //!
   TBranch        *b_phoseedootSign_2;   //!
   TBranch        *b_phoseedootVsum_2;   //!
   TBranch        *b_phoisOOT_2;   //!
   TBranch        *b_phoisEB_2;   //!
   TBranch        *b_phohasPixSeed_2;   //!
   TBranch        *b_phoootID_2;   //!
   TBranch        *b_phoseedTT_2;   //!
   TBranch        *b_phonrechits_2;   //!
   TBranch        *b_phoE_3;   //!
   TBranch        *b_phopt_3;   //!
   TBranch        *b_phoeta_3;   //!
   TBranch        *b_phophi_3;   //!
   TBranch        *b_phoscE_3;   //!
   TBranch        *b_phosceta_3;   //!
   TBranch        *b_phoscphi_3;   //!
   TBranch        *b_photdz_3;   //!
   TBranch        *b_phosieie_3;   //!
   TBranch        *b_phosmaj_3;   //!
   TBranch        *b_phosmin_3;   //!
   TBranch        *b_phosuisseX_3;   //!
   TBranch        *b_phoseedE_3;   //!
   TBranch        *b_phoseedtime_3;   //!
   TBranch        *b_phoseedTOF_3;   //!
   TBranch        *b_phoseedID_3;   //!
   TBranch        *b_phoseedI1_3;   //!
   TBranch        *b_phoseedI2_3;   //!
   TBranch        *b_phoseedEcal_3;   //!
   TBranch        *b_phoseedadcToGeV_3;   //!
   TBranch        *b_phoseedped12_3;   //!
   TBranch        *b_phoseedped6_3;   //!
   TBranch        *b_phoseedped1_3;   //!
   TBranch        *b_phoseedpedrms12_3;   //!
   TBranch        *b_phoseedpedrms6_3;   //!
   TBranch        *b_phoseedpedrms1_3;   //!
   TBranch        *b_phoseedkutime_3;   //!
   TBranch        *b_phoseedkuID_3;   //!
   TBranch        *b_phoseedkuStctime_3;   //!
   TBranch        *b_phoseedkuStcID_3;   //!
   TBranch        *b_phoseedkuNotStctime_3;   //!
   TBranch        *b_phoseedkuNotStcID_3;   //!
   TBranch        *b_phoseedkuWootStctime_3;   //!
   TBranch        *b_phoseedkuWootStcID_3;   //!
   TBranch        *b_phoseedootA0_3;   //!
   TBranch        *b_phoseedootA1_3;   //!
   TBranch        *b_phoseedootA2_3;   //!
   TBranch        *b_phoseedootA3_3;   //!
   TBranch        *b_phoseedootA4_3;   //!
   TBranch        *b_phoseedootA5_3;   //!
   TBranch        *b_phoseedootA6_3;   //!
   TBranch        *b_phoseedootA7_3;   //!
   TBranch        *b_phoseedootA8_3;   //!
   TBranch        *b_phoseedootA9_3;   //!
   TBranch        *b_phoseedootMax_3;   //!
   TBranch        *b_phoseedootMbefore_3;   //!
   TBranch        *b_phoseedootMafter_3;   //!
   TBranch        *b_phoseedootSign_3;   //!
   TBranch        *b_phoseedootVsum_3;   //!
   TBranch        *b_phoisOOT_3;   //!
   TBranch        *b_phoisEB_3;   //!
   TBranch        *b_phohasPixSeed_3;   //!
   TBranch        *b_phoootID_3;   //!
   TBranch        *b_phoseedTT_3;   //!
   TBranch        *b_phonrechits_3;   //!

   // Set object pointer
   out_npho_recHits_0 = 0;
   out_npho_recHits_1 = 0;
   out_npho_recHits_2 = 0;
   out_npho_recHits_3 = 0;

   const string treename("disphotree");

   std::cout << "Opening Outfile : " << outfilename << std::endl;
   TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
   fOutFile->cd();

	//  Set up Histograms
	//string hname_("");
	//string htitle_("");
	//hist_ = new TH2F(hname_.c_str(),htitle_.c_str(),171,-85.5,85.5,360,0.5,360.5);
	//hist_ = new TH1F(hname_.c_str(),htitle_.c_str(),171,-85.5,85.5);
//   Float_t         gZmass;
   string hname_gZmass("gZmass");
   string htitle_gZmass("gZmass");
   auto hist_gZmass = new TH1F(hname_gZmass.c_str(),htitle_gZmass.c_str(),512,40,168);
//   Float_t         gdR;
	string hname_gdR("gdR");
   string htitle_gdR("gdR");
   auto hist_gdR = new TH1F(hname_gdR.c_str(),htitle_gdR.c_str(),512,0,5.12);
//   Int_t           nvtx;
   string hname_nvtx("nvtx");
   string htitle_nvtx("nvtx");
   auto hist_nvtx = new TH1F(hname_nvtx.c_str(),htitle_nvtx.c_str(),85,0,85);
//   Float_t         vtxX;
   string hname_vtxX("vtxX");
   string htitle_vtxX("vtxX");
   auto hist_vtxX = new TH1F(hname_vtxX.c_str(),htitle_vtxX.c_str(),256,0,0.128);
//   Float_t         vtxY;
   string hname_vtxY("vtxY");
   string htitle_vtxY("vtxY");
   auto hist_vtxY = new TH1F(hname_vtxY.c_str(),htitle_vtxY.c_str(),256,0,0.128);
//   Float_t         vtxZ;
   string hname_vtxZ("vtxZ");
   string htitle_vtxZ("vtxZ");
   auto hist_vtxZ = new TH1F(hname_vtxZ.c_str(),htitle_vtxZ.c_str(),256,-16,16);
//   Float_t         rho;
   string hname_rho("rho");
   string htitle_rho("rho");
   auto hist_rho = new TH1F(hname_rho.c_str(),htitle_rho.c_str(),512,0,64);

//   Float_t         phoE_0;
   string hname_phoE_0("phoE_0");
   string htitle_phoE_0("phoE_0");
   auto hist_phoE_0 = new TH1F(hname_phoE_0.c_str(),htitle_phoE_0.c_str(),512,0,512);
   string hname_phoE_1("phoE_1");
   string htitle_phoE_1("phoE_1");
   auto hist_phoE_1 = new TH1F(hname_phoE_1.c_str(),htitle_phoE_1.c_str(),512,0,512);
   string hname_phoE_d("phoE_d");
   string htitle_phoE_d("delta phoE");
   auto hist_phoE_d = new TH1F(hname_phoE_d.c_str(),htitle_phoE_d.c_str(),1024,-512,512);
//   Float_t         phopt_0;
   string hname_phopt_0("phopt_0");
   string htitle_phopt_0("phopt_0");
   auto hist_phopt_0 = new TH1F(hname_phopt_0.c_str(),htitle_phopt_0.c_str(),256,0,256);
   string hname_phopt_1("phopt_1");
   string htitle_phopt_1("phopt_1");
   auto hist_phopt_1 = new TH1F(hname_phopt_1.c_str(),htitle_phopt_1.c_str(),256,0,256);
   string hname_phopt_d("phopt_d");
   string htitle_phopt_d("delta phopt");
   auto hist_phopt_d = new TH1F(hname_phopt_d.c_str(),htitle_phopt_d.c_str(),512,-256,256);
//   Float_t         phoeta_0;
   string hname_phoeta_0("phoeta_0");
   string htitle_phoeta_0("phoeta_0");
   auto hist_phoeta_0 = new TH1F(hname_phoeta_0.c_str(),htitle_phoeta_0.c_str(),128,-3.2,3.2);
   string hname_phoeta_1("phoeta_1");
   string htitle_phoeta_1("phoeta_1");
   auto hist_phoeta_1 = new TH1F(hname_phoeta_1.c_str(),htitle_phoeta_1.c_str(),128,-3.2,3.2);
   string hname_phoeta_d("phoeta_d");
   string htitle_phoeta_d("delta phoeta");
   auto hist_phoeta_d = new TH1F(hname_phoeta_d.c_str(),htitle_phoeta_d.c_str(),256,-6.4,6.4);
//   Float_t         phophi_0;
   string hname_phophi_0("phophi_0");
   string htitle_phophi_0("phophi_0");
   auto hist_phophi_0 = new TH1F(hname_phophi_0.c_str(),htitle_phophi_0.c_str(),128,-3.2,3.2);
   string hname_phophi_1("phophi_1");
   string htitle_phophi_1("phophi_1");
   auto hist_phophi_1 = new TH1F(hname_phophi_1.c_str(),htitle_phophi_1.c_str(),128,-3.2,3.2);
   string hname_phophi_d("phophi_d");
   string htitle_phophi_d("delta phophi");
   auto hist_phophi_d = new TH1F(hname_phophi_d.c_str(),htitle_phophi_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscE_0;
   string hname_phoscE_0("phoscE_0");
   string htitle_phoscE_0("phoscE_0");
   auto hist_phoscE_0 = new TH1F(hname_phoscE_0.c_str(),htitle_phoscE_0.c_str(),512,0,512);
   string hname_phoscE_1("phoscE_1");
   string htitle_phoscE_1("phoscE_1");
   auto hist_phoscE_1 = new TH1F(hname_phoscE_1.c_str(),htitle_phoscE_1.c_str(),512,0,512);
   string hname_phoscE_d("phoscE_d");
   string htitle_phoscE_d("delta phoscE");
   auto hist_phoscE_d = new TH1F(hname_phoscE_d.c_str(),htitle_phoscE_d.c_str(),1024,-512,512);
//   Float_t         phosceta_0;
   string hname_phosceta_0("phosceta_0");
   string htitle_phosceta_0("phosceta_0");
   auto hist_phosceta_0 = new TH1F(hname_phosceta_0.c_str(),htitle_phosceta_0.c_str(),128,-3.2,3.2);
   string hname_phosceta_1("phosceta_1");
   string htitle_phosceta_1("phosceta_1");
   auto hist_phosceta_1 = new TH1F(hname_phosceta_1.c_str(),htitle_phosceta_1.c_str(),128,-3.2,3.2);
   string hname_phosceta_d("phosceta_d");
   string htitle_phosceta_d("delta phosceta");
   auto hist_phosceta_d = new TH1F(hname_phosceta_d.c_str(),htitle_phosceta_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscphi_0;
   string hname_phoscphi_0("phoscphi_0");
   string htitle_phoscphi_0("phoscphi_0");
   auto hist_phoscphi_0 = new TH1F(hname_phoscphi_0.c_str(),htitle_phoscphi_0.c_str(),128,-3.2,3.2);
   string hname_phoscphi_1("phoscphi_1");
   string htitle_phoscphi_1("phoscphi_1");
   auto hist_phoscphi_1 = new TH1F(hname_phoscphi_1.c_str(),htitle_phoscphi_1.c_str(),128,-3.2,3.2);
   string hname_phoscphi_d("phoscphi_d");
   string htitle_phoscphi_d("delta phoscphi");
   auto hist_phoscphi_d = new TH1F(hname_phoscphi_d.c_str(),htitle_phoscphi_d.c_str(),256,-6.4,6.4);
//   Float_t         photdz_0;
   string hname_photdz_0("photdz_0");
   string htitle_photdz_0("photdz_0");
   auto hist_photdz_0 = new TH1F(hname_photdz_0.c_str(),htitle_photdz_0.c_str(),128,-25.6,25.6);
   string hname_photdz_1("photdz_1");
   string htitle_photdz_1("photdz_1");
   auto hist_photdz_1 = new TH1F(hname_photdz_1.c_str(),htitle_photdz_1.c_str(),128,-25.6,25.6);
   string hname_photdz_d("photdz_d");
   string htitle_photdz_d("delta photdz");
   auto hist_photdz_d = new TH1F(hname_photdz_d.c_str(),htitle_photdz_d.c_str(),256,-51.2,51.2);
//   Float_t         phosieie_0;
   string hname_phosieie_0("phosieie_0");
   string htitle_phosieie_0("phosieie_0");
   auto hist_phosieie_0 = new TH1F(hname_phosieie_0.c_str(),htitle_phosieie_0.c_str(),32,0,0.032);
   string hname_phosieie_1("phosieie_1");
   string htitle_phosieie_1("phosieie_1");
   auto hist_phosieie_1 = new TH1F(hname_phosieie_1.c_str(),htitle_phosieie_1.c_str(),32,0,0.032);
   string hname_phosieie_d("phosieie_d");
   string htitle_phosieie_d("delta phosieie");
   auto hist_phosieie_d = new TH1F(hname_phosieie_d.c_str(),htitle_phosieie_d.c_str(),64,-0.032,0.032);
//   Float_t         phosmaj_0;
   string hname_phosmaj_0("phosmaj_0");
   string htitle_phosmaj_0("phosmaj_0");
   auto hist_phosmaj_0 = new TH1F(hname_phosmaj_0.c_str(),htitle_phosmaj_0.c_str(),256,0,6.4);
   string hname_phosmaj_1("phosmaj_1");
   string htitle_phosmaj_1("phosmaj_1");
   auto hist_phosmaj_1 = new TH1F(hname_phosmaj_1.c_str(),htitle_phosmaj_1.c_str(),256,0,6.4);
   string hname_phosmaj_d("phosmaj_d");
   string htitle_phosmaj_d("delta phosmaj");
   auto hist_phosmaj_d = new TH1F(hname_phosmaj_d.c_str(),htitle_phosmaj_d.c_str(),512,-6.4,6.4);
//   Float_t         phosmin_0;
   string hname_phosmin_0("phosmin_0");
   string htitle_phosmin_0("phosmin_0");
   auto hist_phosmin_0 = new TH1F(hname_phosmin_0.c_str(),htitle_phosmin_0.c_str(),256,0,0.64);
   string hname_phosmin_1("phosmin_1");
   string htitle_phosmin_1("phosmin_1");
   auto hist_phosmin_1 = new TH1F(hname_phosmin_1.c_str(),htitle_phosmin_1.c_str(),256,0,0.64);
   string hname_phosmin_d("phosmin_d");
   string htitle_phosmin_d("delta phosmin");
   auto hist_phosmin_d = new TH1F(hname_phosmin_d.c_str(),htitle_phosmin_d.c_str(),512,-0.64,0.64);
//   Float_t         phosuisseX_0;
   string hname_phosuisseX_0("phosuisseX_0");
   string htitle_phosuisseX_0("phosuisseX_0");
   auto hist_phosuisseX_0 = new TH1F(hname_phosuisseX_0.c_str(),htitle_phosuisseX_0.c_str(),256,-1.6,1.6);
   string hname_phosuisseX_1("phosuisseX_1");
   string htitle_phosuisseX_1("phosuisseX_1");
   auto hist_phosuisseX_1 = new TH1F(hname_phosuisseX_1.c_str(),htitle_phosuisseX_1.c_str(),256,-1.6,1.6);
   string hname_phosuisseX_d("phosuisseX_d");
   string htitle_phosuisseX_d("delta phosuisseX");
   auto hist_phosuisseX_d = new TH1F(hname_phosuisseX_d.c_str(),htitle_phosuisseX_d.c_str(),512,-3.2,3.2);
//   Float_t         phoseedE_0;
   string hname_phoseedE_0("phoseedE_0");
   string htitle_phoseedE_0("phoseedE_0");
   auto hist_phoseedE_0 = new TH1F(hname_phoseedE_0.c_str(),htitle_phoseedE_0.c_str(),512,0,512);
   string hname_phoseedE_1("phoseedE_1");
   string htitle_phoseedE_1("phoseedE_1");
   auto hist_phoseedE_1 = new TH1F(hname_phoseedE_1.c_str(),htitle_phoseedE_1.c_str(),512,0,512);
   string hname_phoseedE_d("phoseedE_d");
   string htitle_phoseedE_d("delta phoseedE");
   auto hist_phoseedE_d = new TH1F(hname_phoseedE_d.c_str(),htitle_phoseedE_d.c_str(),1024,-512,512);
//   Int_t           phonrechits_0;
   string hname_phonrechits_0("phonrechits_0");
   string htitle_phonrechits_0("phonrechits_0");
   auto hist_phonrechits_0 = new TH1F(hname_phonrechits_0.c_str(),htitle_phonrechits_0.c_str(),32,0,32);
   string hname_phonrechits_1("phonrechits_1");
   string htitle_phonrechits_1("phonrechits_1");
   auto hist_phonrechits_1 = new TH1F(hname_phonrechits_1.c_str(),htitle_phonrechits_1.c_str(),32,0,32);
   string hname_phonrechits_d("phonrechits_d");
   string htitle_phonrechits_d("delta phonrechits");
   auto hist_phonrechits_d = new TH1F(hname_phonrechits_d.c_str(),htitle_phonrechits_d.c_str(),64,-32,32);

//   Int_t           phoseedI1_0;
//   Int_t           phoseedI2_0;
   string hname_phoseedMap_0("phoseedMap_0");
   string htitle_phoseedMap_0("phoseedMap_0");
   string hname_phoseedMap_1("phoseedMap_1");
   string htitle_phoseedMap_1("phoseedMap_1");
   string hname_phoseedMap_01("phoseedMap_01");
   string htitle_phoseedMap_01("phoseedMap_01");
   auto hist_phoseedMap_0 = new TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
   auto hist_phoseedMap_1 = new TH2F(hname_phoseedMap_1.c_str(),htitle_phoseedMap_1.c_str(),171,-85.5,85.5,360,0.5,360.5);
   auto hist_phoseedMap_01 = new TH2F(hname_phoseedMap_01.c_str(),htitle_phoseedMap_01.c_str(),171,-85.5,85.5,360,0.5,360.5);

//		phoseedTOF_1
   string hname_phoseedTOF_0("phoseedTOF_0");
   string htitle_phoseedTOF_0("phoseedTOF_0");
   auto hist_phoseedTOF_0 = new TH1F(hname_phoseedTOF_0.c_str(),htitle_phoseedTOF_0.c_str(),256,0,0.4096);
   string hname_phoseedTOF_1("phoseedTOF_1");
   string htitle_phoseedTOF_1("phoseedTOF_1");
   auto hist_phoseedTOF_1 = new TH1F(hname_phoseedTOF_1.c_str(),htitle_phoseedTOF_1.c_str(),256,0,0.4096);
   string hname_phoseedTOF_d("phoseedTOF_d");
   string htitle_phoseedTOF_d("delta phoseedTOF");
   auto hist_phoseedTOF_d =new TH1F(hname_phoseedTOF_d.c_str(),htitle_phoseedTOF_d.c_str(),512,-0.4096,0.4096);
   string hname_phoseedTOFMap_01("phoseedTOFMap_01");
   string htitle_phoseedTOFMap_01("phoseedTOFMap_01");
   auto hist_phoseedTOFMap_01 = new TH2F(hname_phoseedTOFMap_01.c_str(),htitle_phoseedTOFMap_01.c_str(),171,-85.5,85.5,360,0.5,360.5);

//    phoseedtime_1
   string hname_phoseedtime_0("phoseedtime_0");
   string htitle_phoseedtime_0("phoseedtime_0");
   auto hist_phoseedtime_0 = new TH1F(hname_phoseedtime_0.c_str(),htitle_phoseedtime_0.c_str(),256,-4.096,4.096);
   string hname_phoseedtime_1("phoseedtime_1");
   string htitle_phoseedtime_1("phoseedtime_1");
   auto hist_phoseedtime_1 = new TH1F(hname_phoseedtime_1.c_str(),htitle_phoseedtime_1.c_str(),256,-4.096,4.096);
   string hname_phoseedtime_d("phoseedtime_d");
   string htitle_phoseedtime_d("delta phoseedtime");
   auto hist_phoseedtime_d = new TH1F(hname_phoseedtime_d.c_str(),htitle_phoseedtime_d.c_str(),512,-8.192,8.192);
   string hname_phoseedtimeMap_01("phoseedtimeMap_01");
   string htitle_phoseedtimeMap_01("phoseedtimeMap_01");
   auto hist_phoseedtimeMap_01 = new TH2F(hname_phoseedtimeMap_01.c_str(),htitle_phoseedtimeMap_01.c_str(),171,-85.5,85.5,360,0.5,360.5);

////		phoseedID_1
//   string hname_phoseedID_0("phoseedID_0");
//   string htitle_phoseedID_0("phoseedID_0");
//   auto hist_phoseedID_0 = new TH1F(hname_phoseedID_0.c_str(),htitle_phoseedID_0.c_str(),131072,836,840);
//   string hname_phoseedID_1("phoseedID_1");
//   string htitle_phoseedID_1("phoseedID_1");
//   auto hist_phoseedID_1 = new TH1F(hname_phoseedID_1.c_str(),htitle_phoseedID_1.c_str(),131072,836,840);
//   string hname_phoseedID_d("phoseedID_d");
//   string htitle_phoseedID_d("delta phoseedID");
//   auto hist_phoseedID_d = new TH1F(hname_phoseedID_d.c_str(),htitle_phoseedID_d.c_str(),131072,-2,2);
//
////		phoseedadcToGeV_1
//   string hname_phoseedadcToGeV_0("phoseedadcToGeV_0");
//   string htitle_phoseedadcToGeV_0("phoseedadcToGeV_0");
//   auto hist_phoseedadcToGeV_0 = new TH1F(hname_phoseedadcToGeV_0.c_str(),htitle_phoseedadcToGeV_0.c_str(),32,0,2);
//   string hname_phoseedadcToGeV_1("phoseedadcToGeV_1");
//   string htitle_phoseedadcToGeV_1("phoseedadcToGeV_1");
//   auto hist_phoseedadcToGeV_1 = new TH1F(hname_phoseedadcToGeV_1.c_str(),htitle_phoseedadcToGeV_1.c_str(),32,0,2);
//   string hname_phoseedadcToGeV_d("phoseedadcToGeV_d");
//   string htitle_phoseedadcToGeV_d("delta phoseedadcToGeV");
//   auto hist_phoseedadcToGeV_d = new TH1F(hname_phoseedadcToGeV_d.c_str(),htitle_phoseedadcToGeV_d.c_str(),64,-2,2);


   std::ifstream infile(infilelist);
   std::string str;
   auto fChain = new TChain(treename.c_str());
   std::cout << "Adding files to TChain." << std::endl;
   while (std::getline(infile,str)){
      std::stringstream ss(str);
      std::string infilename;
      std::string califilename;
      ss >> infilename >> califilename;
   	auto tfilename = indir + "/" + infilename;
   	std::cout << "--  adding file: " << tfilename << std::endl;
   	fChain->Add(tfilename.c_str());
   }

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("gZmass", &gZmass, &b_gZmass);
   fChain->SetBranchAddress("gdR", &gdR, &b_gdR);
//   fChain->SetBranchAddress("bunch_crossing", &bunch_crossing, &b_bunch_crossing);
//   fChain->SetBranchAddress("num_bunch", &num_bunch, &b_num_bunch);
//   fChain->SetBranchAddress("subtrain_position", &subtrain_position, &b_subtrain_position);
//   fChain->SetBranchAddress("train_position", &train_position, &b_train_position);
//   fChain->SetBranchAddress("subtrain_number", &subtrain_number, &b_subtrain_number);
//   fChain->SetBranchAddress("train_number", &train_number, &b_train_number);
//   fChain->SetBranchAddress("nxtal_sep", &nxtal_sep, &b_nxtal_sep);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("vtxX", &vtxX, &b_vtxX);
   fChain->SetBranchAddress("vtxY", &vtxY, &b_vtxY);
   fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("nrechits", &nrechits, &b_nrechits);
   fChain->SetBranchAddress("nkurechits", &nkurechits, &b_nkurechits);
//   fChain->SetBranchAddress("out_npho_recHits_0", &out_npho_recHits_0, &b_out_npho_recHits_0);
//   fChain->SetBranchAddress("out_npho_recHits_1", &out_npho_recHits_1, &b_out_npho_recHits_1);
//   fChain->SetBranchAddress("out_npho_recHits_2", &out_npho_recHits_2, &b_out_npho_recHits_2);
//   fChain->SetBranchAddress("out_npho_recHits_3", &out_npho_recHits_3, &b_out_npho_recHits_3);
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
   fChain->SetBranchAddress("photdz_0", &photdz_0, &b_photdz_0);
   fChain->SetBranchAddress("phosieie_0", &phosieie_0, &b_phosieie_0);
   fChain->SetBranchAddress("phosmaj_0", &phosmaj_0, &b_phosmaj_0);
   fChain->SetBranchAddress("phosmin_0", &phosmin_0, &b_phosmin_0);
   fChain->SetBranchAddress("phosuisseX_0", &phosuisseX_0, &b_phosuisseX_0);
   fChain->SetBranchAddress("phoseedE_0", &phoseedE_0, &b_phoseedE_0);
   fChain->SetBranchAddress("phoseedtime_0", &phoseedtime_0, &b_phoseedtime_0);
   fChain->SetBranchAddress("phoseedTOF_0", &phoseedTOF_0, &b_phoseedTOF_0);
   fChain->SetBranchAddress("phoseedID_0", &phoseedID_0, &b_phoseedID_0);
   fChain->SetBranchAddress("phoseedI1_0", &phoseedI1_0, &b_phoseedI1_0);
   fChain->SetBranchAddress("phoseedI2_0", &phoseedI2_0, &b_phoseedI2_0);
   fChain->SetBranchAddress("phoseedEcal_0", &phoseedEcal_0, &b_phoseedEcal_0);
   fChain->SetBranchAddress("phoseedadcToGeV_0", &phoseedadcToGeV_0, &b_phoseedadcToGeV_0);
//   fChain->SetBranchAddress("phoseedped12_0", &phoseedped12_0, &b_phoseedped12_0);
//   fChain->SetBranchAddress("phoseedped6_0", &phoseedped6_0, &b_phoseedped6_0);
//   fChain->SetBranchAddress("phoseedped1_0", &phoseedped1_0, &b_phoseedped1_0);
//   fChain->SetBranchAddress("phoseedpedrms12_0", &phoseedpedrms12_0, &b_phoseedpedrms12_0);
//   fChain->SetBranchAddress("phoseedpedrms6_0", &phoseedpedrms6_0, &b_phoseedpedrms6_0);
//   fChain->SetBranchAddress("phoseedpedrms1_0", &phoseedpedrms1_0, &b_phoseedpedrms1_0);
//   fChain->SetBranchAddress("phoseedkutime_0", &phoseedkutime_0, &b_phoseedkutime_0);
//   fChain->SetBranchAddress("phoseedkuID_0", &phoseedkuID_0, &b_phoseedkuID_0);
//   fChain->SetBranchAddress("phoseedkuStctime_0", &phoseedkuStctime_0, &b_phoseedkuStctime_0);
//   fChain->SetBranchAddress("phoseedkuStcID_0", &phoseedkuStcID_0, &b_phoseedkuStcID_0);
//   fChain->SetBranchAddress("phoseedkuNotStctime_0", &phoseedkuNotStctime_0, &b_phoseedkuNotStctime_0);
//   fChain->SetBranchAddress("phoseedkuNotStcID_0", &phoseedkuNotStcID_0, &b_phoseedkuNotStcID_0);
//   fChain->SetBranchAddress("phoseedkuWootStctime_0", &phoseedkuWootStctime_0, &b_phoseedkuWootStctime_0);
//   fChain->SetBranchAddress("phoseedkuWootStcID_0", &phoseedkuWootStcID_0, &b_phoseedkuWootStcID_0);
//   fChain->SetBranchAddress("phoseedootA0_0", &phoseedootA0_0, &b_phoseedootA0_0);
//   fChain->SetBranchAddress("phoseedootA1_0", &phoseedootA1_0, &b_phoseedootA1_0);
//   fChain->SetBranchAddress("phoseedootA2_0", &phoseedootA2_0, &b_phoseedootA2_0);
//   fChain->SetBranchAddress("phoseedootA3_0", &phoseedootA3_0, &b_phoseedootA3_0);
//   fChain->SetBranchAddress("phoseedootA4_0", &phoseedootA4_0, &b_phoseedootA4_0);
//   fChain->SetBranchAddress("phoseedootA5_0", &phoseedootA5_0, &b_phoseedootA5_0);
//   fChain->SetBranchAddress("phoseedootA6_0", &phoseedootA6_0, &b_phoseedootA6_0);
//   fChain->SetBranchAddress("phoseedootA7_0", &phoseedootA7_0, &b_phoseedootA7_0);
//   fChain->SetBranchAddress("phoseedootA8_0", &phoseedootA8_0, &b_phoseedootA8_0);
//   fChain->SetBranchAddress("phoseedootA9_0", &phoseedootA9_0, &b_phoseedootA9_0);
//   fChain->SetBranchAddress("phoseedootMax_0", &phoseedootMax_0, &b_phoseedootMax_0);
//   fChain->SetBranchAddress("phoseedootMbefore_0", &phoseedootMbefore_0, &b_phoseedootMbefore_0);
//   fChain->SetBranchAddress("phoseedootMafter_0", &phoseedootMafter_0, &b_phoseedootMafter_0);
//   fChain->SetBranchAddress("phoseedootSign_0", &phoseedootSign_0, &b_phoseedootSign_0);
//   fChain->SetBranchAddress("phoseedootVsum_0", &phoseedootVsum_0, &b_phoseedootVsum_0);
   fChain->SetBranchAddress("phoisOOT_0", &phoisOOT_0, &b_phoisOOT_0);
   fChain->SetBranchAddress("phoisEB_0", &phoisEB_0, &b_phoisEB_0);
   fChain->SetBranchAddress("phohasPixSeed_0", &phohasPixSeed_0, &b_phohasPixSeed_0);
   fChain->SetBranchAddress("phoootID_0", &phoootID_0, &b_phoootID_0);
   fChain->SetBranchAddress("phoseedTT_0", &phoseedTT_0, &b_phoseedTT_0);
   fChain->SetBranchAddress("phonrechits_0", &phonrechits_0, &b_phonrechits_0);
   fChain->SetBranchAddress("phoE_1", &phoE_1, &b_phoE_1);
   fChain->SetBranchAddress("phopt_1", &phopt_1, &b_phopt_1);
   fChain->SetBranchAddress("phoeta_1", &phoeta_1, &b_phoeta_1);
   fChain->SetBranchAddress("phophi_1", &phophi_1, &b_phophi_1);
   fChain->SetBranchAddress("phoscE_1", &phoscE_1, &b_phoscE_1);
   fChain->SetBranchAddress("phosceta_1", &phosceta_1, &b_phosceta_1);
   fChain->SetBranchAddress("phoscphi_1", &phoscphi_1, &b_phoscphi_1);
   fChain->SetBranchAddress("photdz_1", &photdz_1, &b_photdz_1);
   fChain->SetBranchAddress("phosieie_1", &phosieie_1, &b_phosieie_1);
   fChain->SetBranchAddress("phosmaj_1", &phosmaj_1, &b_phosmaj_1);
   fChain->SetBranchAddress("phosmin_1", &phosmin_1, &b_phosmin_1);
   fChain->SetBranchAddress("phosuisseX_1", &phosuisseX_1, &b_phosuisseX_1);
   fChain->SetBranchAddress("phoseedE_1", &phoseedE_1, &b_phoseedE_1);
   fChain->SetBranchAddress("phoseedtime_1", &phoseedtime_1, &b_phoseedtime_1);
   fChain->SetBranchAddress("phoseedTOF_1", &phoseedTOF_1, &b_phoseedTOF_1);
   fChain->SetBranchAddress("phoseedID_1", &phoseedID_1, &b_phoseedID_1);
   fChain->SetBranchAddress("phoseedI1_1", &phoseedI1_1, &b_phoseedI1_1);
   fChain->SetBranchAddress("phoseedI2_1", &phoseedI2_1, &b_phoseedI2_1);
   fChain->SetBranchAddress("phoseedEcal_1", &phoseedEcal_1, &b_phoseedEcal_1);
   fChain->SetBranchAddress("phoseedadcToGeV_1", &phoseedadcToGeV_1, &b_phoseedadcToGeV_1);
//   fChain->SetBranchAddress("phoseedped12_1", &phoseedped12_1, &b_phoseedped12_1);
//   fChain->SetBranchAddress("phoseedped6_1", &phoseedped6_1, &b_phoseedped6_1);
//   fChain->SetBranchAddress("phoseedped1_1", &phoseedped1_1, &b_phoseedped1_1);
//   fChain->SetBranchAddress("phoseedpedrms12_1", &phoseedpedrms12_1, &b_phoseedpedrms12_1);
//   fChain->SetBranchAddress("phoseedpedrms6_1", &phoseedpedrms6_1, &b_phoseedpedrms6_1);
//   fChain->SetBranchAddress("phoseedpedrms1_1", &phoseedpedrms1_1, &b_phoseedpedrms1_1);
//   fChain->SetBranchAddress("phoseedkutime_1", &phoseedkutime_1, &b_phoseedkutime_1);
//   fChain->SetBranchAddress("phoseedkuID_1", &phoseedkuID_1, &b_phoseedkuID_1);
//   fChain->SetBranchAddress("phoseedkuStctime_1", &phoseedkuStctime_1, &b_phoseedkuStctime_1);
//   fChain->SetBranchAddress("phoseedkuStcID_1", &phoseedkuStcID_1, &b_phoseedkuStcID_1);
//   fChain->SetBranchAddress("phoseedkuNotStctime_1", &phoseedkuNotStctime_1, &b_phoseedkuNotStctime_1);
//   fChain->SetBranchAddress("phoseedkuNotStcID_1", &phoseedkuNotStcID_1, &b_phoseedkuNotStcID_1);
//   fChain->SetBranchAddress("phoseedkuWootStctime_1", &phoseedkuWootStctime_1, &b_phoseedkuWootStctime_1);
//   fChain->SetBranchAddress("phoseedkuWootStcID_1", &phoseedkuWootStcID_1, &b_phoseedkuWootStcID_1);
//   fChain->SetBranchAddress("phoseedootA0_1", &phoseedootA0_1, &b_phoseedootA0_1);
//   fChain->SetBranchAddress("phoseedootA1_1", &phoseedootA1_1, &b_phoseedootA1_1);
//   fChain->SetBranchAddress("phoseedootA2_1", &phoseedootA2_1, &b_phoseedootA2_1);
//   fChain->SetBranchAddress("phoseedootA3_1", &phoseedootA3_1, &b_phoseedootA3_1);
//   fChain->SetBranchAddress("phoseedootA4_1", &phoseedootA4_1, &b_phoseedootA4_1);
//   fChain->SetBranchAddress("phoseedootA5_1", &phoseedootA5_1, &b_phoseedootA5_1);
//   fChain->SetBranchAddress("phoseedootA6_1", &phoseedootA6_1, &b_phoseedootA6_1);
//   fChain->SetBranchAddress("phoseedootA7_1", &phoseedootA7_1, &b_phoseedootA7_1);
//   fChain->SetBranchAddress("phoseedootA8_1", &phoseedootA8_1, &b_phoseedootA8_1);
//   fChain->SetBranchAddress("phoseedootA9_1", &phoseedootA9_1, &b_phoseedootA9_1);
//   fChain->SetBranchAddress("phoseedootMax_1", &phoseedootMax_1, &b_phoseedootMax_1);
//   fChain->SetBranchAddress("phoseedootMbefore_1", &phoseedootMbefore_1, &b_phoseedootMbefore_1);
//   fChain->SetBranchAddress("phoseedootMafter_1", &phoseedootMafter_1, &b_phoseedootMafter_1);
//   fChain->SetBranchAddress("phoseedootSign_1", &phoseedootSign_1, &b_phoseedootSign_1);
//   fChain->SetBranchAddress("phoseedootVsum_1", &phoseedootVsum_1, &b_phoseedootVsum_1);
   fChain->SetBranchAddress("phoisOOT_1", &phoisOOT_1, &b_phoisOOT_1);
   fChain->SetBranchAddress("phoisEB_1", &phoisEB_1, &b_phoisEB_1);
   fChain->SetBranchAddress("phohasPixSeed_1", &phohasPixSeed_1, &b_phohasPixSeed_1);
   fChain->SetBranchAddress("phoootID_1", &phoootID_1, &b_phoootID_1);
   fChain->SetBranchAddress("phoseedTT_1", &phoseedTT_1, &b_phoseedTT_1);
   fChain->SetBranchAddress("phonrechits_1", &phonrechits_1, &b_phonrechits_1);
//   fChain->SetBranchAddress("phoE_2", &phoE_2, &b_phoE_2);
//   fChain->SetBranchAddress("phopt_2", &phopt_2, &b_phopt_2);
//   fChain->SetBranchAddress("phoeta_2", &phoeta_2, &b_phoeta_2);
//   fChain->SetBranchAddress("phophi_2", &phophi_2, &b_phophi_2);
//   fChain->SetBranchAddress("phoscE_2", &phoscE_2, &b_phoscE_2);
//   fChain->SetBranchAddress("phosceta_2", &phosceta_2, &b_phosceta_2);
//   fChain->SetBranchAddress("phoscphi_2", &phoscphi_2, &b_phoscphi_2);
//   fChain->SetBranchAddress("photdz_2", &photdz_2, &b_photdz_2);
//   fChain->SetBranchAddress("phosieie_2", &phosieie_2, &b_phosieie_2);
//   fChain->SetBranchAddress("phosmaj_2", &phosmaj_2, &b_phosmaj_2);
//   fChain->SetBranchAddress("phosmin_2", &phosmin_2, &b_phosmin_2);
//   fChain->SetBranchAddress("phosuisseX_2", &phosuisseX_2, &b_phosuisseX_2);
//   fChain->SetBranchAddress("phoseedE_2", &phoseedE_2, &b_phoseedE_2);
//   fChain->SetBranchAddress("phoseedtime_2", &phoseedtime_2, &b_phoseedtime_2);
//   fChain->SetBranchAddress("phoseedTOF_2", &phoseedTOF_2, &b_phoseedTOF_2);
//   fChain->SetBranchAddress("phoseedID_2", &phoseedID_2, &b_phoseedID_2);
//   fChain->SetBranchAddress("phoseedI1_2", &phoseedI1_2, &b_phoseedI1_2);
//   fChain->SetBranchAddress("phoseedI2_2", &phoseedI2_2, &b_phoseedI2_2);
//   fChain->SetBranchAddress("phoseedEcal_2", &phoseedEcal_2, &b_phoseedEcal_2);
//   fChain->SetBranchAddress("phoseedadcToGeV_2", &phoseedadcToGeV_2, &b_phoseedadcToGeV_2);
//   fChain->SetBranchAddress("phoseedped12_2", &phoseedped12_2, &b_phoseedped12_2);
//   fChain->SetBranchAddress("phoseedped6_2", &phoseedped6_2, &b_phoseedped6_2);
//   fChain->SetBranchAddress("phoseedped1_2", &phoseedped1_2, &b_phoseedped1_2);
//   fChain->SetBranchAddress("phoseedpedrms12_2", &phoseedpedrms12_2, &b_phoseedpedrms12_2);
//   fChain->SetBranchAddress("phoseedpedrms6_2", &phoseedpedrms6_2, &b_phoseedpedrms6_2);
//   fChain->SetBranchAddress("phoseedpedrms1_2", &phoseedpedrms1_2, &b_phoseedpedrms1_2);
//   fChain->SetBranchAddress("phoseedkutime_2", &phoseedkutime_2, &b_phoseedkutime_2);
//   fChain->SetBranchAddress("phoseedkuID_2", &phoseedkuID_2, &b_phoseedkuID_2);
//   fChain->SetBranchAddress("phoseedkuStctime_2", &phoseedkuStctime_2, &b_phoseedkuStctime_2);
//   fChain->SetBranchAddress("phoseedkuStcID_2", &phoseedkuStcID_2, &b_phoseedkuStcID_2);
//   fChain->SetBranchAddress("phoseedkuNotStctime_2", &phoseedkuNotStctime_2, &b_phoseedkuNotStctime_2);
//   fChain->SetBranchAddress("phoseedkuNotStcID_2", &phoseedkuNotStcID_2, &b_phoseedkuNotStcID_2);
//   fChain->SetBranchAddress("phoseedkuWootStctime_2", &phoseedkuWootStctime_2, &b_phoseedkuWootStctime_2);
//   fChain->SetBranchAddress("phoseedkuWootStcID_2", &phoseedkuWootStcID_2, &b_phoseedkuWootStcID_2);
//   fChain->SetBranchAddress("phoseedootA0_2", &phoseedootA0_2, &b_phoseedootA0_2);
//   fChain->SetBranchAddress("phoseedootA1_2", &phoseedootA1_2, &b_phoseedootA1_2);
//   fChain->SetBranchAddress("phoseedootA2_2", &phoseedootA2_2, &b_phoseedootA2_2);
//   fChain->SetBranchAddress("phoseedootA3_2", &phoseedootA3_2, &b_phoseedootA3_2);
//   fChain->SetBranchAddress("phoseedootA4_2", &phoseedootA4_2, &b_phoseedootA4_2);
//   fChain->SetBranchAddress("phoseedootA5_2", &phoseedootA5_2, &b_phoseedootA5_2);
//   fChain->SetBranchAddress("phoseedootA6_2", &phoseedootA6_2, &b_phoseedootA6_2);
//   fChain->SetBranchAddress("phoseedootA7_2", &phoseedootA7_2, &b_phoseedootA7_2);
//   fChain->SetBranchAddress("phoseedootA8_2", &phoseedootA8_2, &b_phoseedootA8_2);
//   fChain->SetBranchAddress("phoseedootA9_2", &phoseedootA9_2, &b_phoseedootA9_2);
//   fChain->SetBranchAddress("phoseedootMax_2", &phoseedootMax_2, &b_phoseedootMax_2);
//   fChain->SetBranchAddress("phoseedootMbefore_2", &phoseedootMbefore_2, &b_phoseedootMbefore_2);
//   fChain->SetBranchAddress("phoseedootMafter_2", &phoseedootMafter_2, &b_phoseedootMafter_2);
//   fChain->SetBranchAddress("phoseedootSign_2", &phoseedootSign_2, &b_phoseedootSign_2);
//   fChain->SetBranchAddress("phoseedootVsum_2", &phoseedootVsum_2, &b_phoseedootVsum_2);
//   fChain->SetBranchAddress("phoisOOT_2", &phoisOOT_2, &b_phoisOOT_2);
//   fChain->SetBranchAddress("phoisEB_2", &phoisEB_2, &b_phoisEB_2);
//   fChain->SetBranchAddress("phohasPixSeed_2", &phohasPixSeed_2, &b_phohasPixSeed_2);
//   fChain->SetBranchAddress("phoootID_2", &phoootID_2, &b_phoootID_2);
//   fChain->SetBranchAddress("phoseedTT_2", &phoseedTT_2, &b_phoseedTT_2);
//   fChain->SetBranchAddress("phonrechits_2", &phonrechits_2, &b_phonrechits_2);
//   fChain->SetBranchAddress("phoE_3", &phoE_3, &b_phoE_3);
//   fChain->SetBranchAddress("phopt_3", &phopt_3, &b_phopt_3);
//   fChain->SetBranchAddress("phoeta_3", &phoeta_3, &b_phoeta_3);
//   fChain->SetBranchAddress("phophi_3", &phophi_3, &b_phophi_3);
//   fChain->SetBranchAddress("phoscE_3", &phoscE_3, &b_phoscE_3);
//   fChain->SetBranchAddress("phosceta_3", &phosceta_3, &b_phosceta_3);
//   fChain->SetBranchAddress("phoscphi_3", &phoscphi_3, &b_phoscphi_3);
//   fChain->SetBranchAddress("photdz_3", &photdz_3, &b_photdz_3);
//   fChain->SetBranchAddress("phosieie_3", &phosieie_3, &b_phosieie_3);
//   fChain->SetBranchAddress("phosmaj_3", &phosmaj_3, &b_phosmaj_3);
//   fChain->SetBranchAddress("phosmin_3", &phosmin_3, &b_phosmin_3);
//   fChain->SetBranchAddress("phosuisseX_3", &phosuisseX_3, &b_phosuisseX_3);
//   fChain->SetBranchAddress("phoseedE_3", &phoseedE_3, &b_phoseedE_3);
//   fChain->SetBranchAddress("phoseedtime_3", &phoseedtime_3, &b_phoseedtime_3);
//   fChain->SetBranchAddress("phoseedTOF_3", &phoseedTOF_3, &b_phoseedTOF_3);
//   fChain->SetBranchAddress("phoseedID_3", &phoseedID_3, &b_phoseedID_3);
//   fChain->SetBranchAddress("phoseedI1_3", &phoseedI1_3, &b_phoseedI1_3);
//   fChain->SetBranchAddress("phoseedI2_3", &phoseedI2_3, &b_phoseedI2_3);
//   fChain->SetBranchAddress("phoseedEcal_3", &phoseedEcal_3, &b_phoseedEcal_3);
//   fChain->SetBranchAddress("phoseedadcToGeV_3", &phoseedadcToGeV_3, &b_phoseedadcToGeV_3);
//   fChain->SetBranchAddress("phoseedped12_3", &phoseedped12_3, &b_phoseedped12_3);
//   fChain->SetBranchAddress("phoseedped6_3", &phoseedped6_3, &b_phoseedped6_3);
//   fChain->SetBranchAddress("phoseedped1_3", &phoseedped1_3, &b_phoseedped1_3);
//   fChain->SetBranchAddress("phoseedpedrms12_3", &phoseedpedrms12_3, &b_phoseedpedrms12_3);
//   fChain->SetBranchAddress("phoseedpedrms6_3", &phoseedpedrms6_3, &b_phoseedpedrms6_3);
//   fChain->SetBranchAddress("phoseedpedrms1_3", &phoseedpedrms1_3, &b_phoseedpedrms1_3);
//   fChain->SetBranchAddress("phoseedkutime_3", &phoseedkutime_3, &b_phoseedkutime_3);
//   fChain->SetBranchAddress("phoseedkuID_3", &phoseedkuID_3, &b_phoseedkuID_3);
//   fChain->SetBranchAddress("phoseedkuStctime_3", &phoseedkuStctime_3, &b_phoseedkuStctime_3);
//   fChain->SetBranchAddress("phoseedkuStcID_3", &phoseedkuStcID_3, &b_phoseedkuStcID_3);
//   fChain->SetBranchAddress("phoseedkuNotStctime_3", &phoseedkuNotStctime_3, &b_phoseedkuNotStctime_3);
//   fChain->SetBranchAddress("phoseedkuNotStcID_3", &phoseedkuNotStcID_3, &b_phoseedkuNotStcID_3);
//   fChain->SetBranchAddress("phoseedkuWootStctime_3", &phoseedkuWootStctime_3, &b_phoseedkuWootStctime_3);
//   fChain->SetBranchAddress("phoseedkuWootStcID_3", &phoseedkuWootStcID_3, &b_phoseedkuWootStcID_3);
//   fChain->SetBranchAddress("phoseedootA0_3", &phoseedootA0_3, &b_phoseedootA0_3);
//   fChain->SetBranchAddress("phoseedootA1_3", &phoseedootA1_3, &b_phoseedootA1_3);
//   fChain->SetBranchAddress("phoseedootA2_3", &phoseedootA2_3, &b_phoseedootA2_3);
//   fChain->SetBranchAddress("phoseedootA3_3", &phoseedootA3_3, &b_phoseedootA3_3);
//   fChain->SetBranchAddress("phoseedootA4_3", &phoseedootA4_3, &b_phoseedootA4_3);
//   fChain->SetBranchAddress("phoseedootA5_3", &phoseedootA5_3, &b_phoseedootA5_3);
//   fChain->SetBranchAddress("phoseedootA6_3", &phoseedootA6_3, &b_phoseedootA6_3);
//   fChain->SetBranchAddress("phoseedootA7_3", &phoseedootA7_3, &b_phoseedootA7_3);
//   fChain->SetBranchAddress("phoseedootA8_3", &phoseedootA8_3, &b_phoseedootA8_3);
//   fChain->SetBranchAddress("phoseedootA9_3", &phoseedootA9_3, &b_phoseedootA9_3);
//   fChain->SetBranchAddress("phoseedootMax_3", &phoseedootMax_3, &b_phoseedootMax_3);
//   fChain->SetBranchAddress("phoseedootMbefore_3", &phoseedootMbefore_3, &b_phoseedootMbefore_3);
//   fChain->SetBranchAddress("phoseedootMafter_3", &phoseedootMafter_3, &b_phoseedootMafter_3);
//   fChain->SetBranchAddress("phoseedootSign_3", &phoseedootSign_3, &b_phoseedootSign_3);
//   fChain->SetBranchAddress("phoseedootVsum_3", &phoseedootVsum_3, &b_phoseedootVsum_3);
//   fChain->SetBranchAddress("phoisOOT_3", &phoisOOT_3, &b_phoisOOT_3);
//   fChain->SetBranchAddress("phoisEB_3", &phoisEB_3, &b_phoisEB_3);
//   fChain->SetBranchAddress("phohasPixSeed_3", &phohasPixSeed_3, &b_phohasPixSeed_3);
//   fChain->SetBranchAddress("phoootID_3", &phoootID_3, &b_phoootID_3);
//   fChain->SetBranchAddress("phoseedTT_3", &phoseedTT_3, &b_phoseedTT_3);
//   fChain->SetBranchAddress("phonrechits_3", &phonrechits_3, &b_phonrechits_3);

   std::cout << "Setting up DetIDs." << std::endl;
   std::map<UInt_t,DetIDStruct> DetIDMap;
   SetupDetIDsEB( DetIDMap );
   SetupDetIDsEE( DetIDMap );


   std::cout << "Starting entry loops "<< std::endl;
   const auto nEntries = fChain->GetEntries();
   for (auto centry = 0U; centry < nEntries; centry++){
		if( centry%100000 == 0 ) std::cout << "Proccessed " << centry << " of " << nEntries << " entries." << std::endl;
      //if( entry > 10000 ) break;
      //if( entry%100 == 0 ) continue; 

		auto entry = fChain->LoadTree(centry);

//    Fill histograms
//    b_->GetEntry(entry);
//   Float_t         gZmass;
	   b_gZmass->GetEntry(entry);
      hist_gZmass->Fill(gZmass);// TH1F(hname_gZmass.c_str(),htitlegZmass.c_str(),128,40,168);
//   Float_t         gdR;
      b_gdR->GetEntry(entry);
      hist_gdR->Fill(gdR);// TH1F(hname_gdR.c_str(),htitle_gdR.c_str(),64,0,5.12);
//   Int_t           nvtx;
      b_nvtx->GetEntry(entry);
      hist_nvtx->Fill(nvtx);// TH1F(hname_nvtx.c_str(),htitle_nvtx.c_str(),64,0,64);
//   Float_t         vtxX;
      b_vtxX->GetEntry(entry);
      hist_vtxX->Fill(vtxX);// TH1F(hname_vtxX.c_str(),htitle_vtxX.c_str(),128,0,0.128);
//   Float_t         vtxY;
      b_vtxY->GetEntry(entry);
      hist_vtxY->Fill(vtxY);// TH1F(hname_vtxY.c_str(),htitle_vtxY.c_str(),128,0,0.128);
//   Float_t         vtxZ;
      b_vtxZ->GetEntry(entry);
      hist_vtxZ->Fill(vtxZ);// TH1F(hname_vtxZ.c_str(),htitle_vtxZ.c_str(),128,-16,16);
//   Float_t         rho;
      b_rho->GetEntry(entry);
      hist_rho->Fill(rho);// TH1F(hname_rho.c_str(),htitle_rho.c_str(),64,0,32);

//   Float_t         phoE_0;
      b_phoE_0->GetEntry(entry);
      b_phoE_1->GetEntry(entry);
      hist_phoE_0->Fill(phoE_0);// TH1F(hname_phoE_0.c_str(),htitle_phoE_0.c_str(),512,0,512);
      hist_phoE_1->Fill(phoE_1);// TH1F(hname_phoE_1.c_str(),htitle_phoE_1.c_str(),512,0,512);
      hist_phoE_d->Fill(phoE_0-phoE_1);// TH1F(hname_phoE_d.c_str(),htitle_phoE_d.c_str(),1024,-512,512);
//   Float_t         phopt_0;
      b_phopt_0->GetEntry(entry);
      b_phopt_1->GetEntry(entry);
      hist_phopt_0->Fill(phopt_0);// TH1F(hname_phopt_0.c_str(),htitle_phopt_0.c_str(),256,0,256);
      hist_phopt_1->Fill(phopt_1);// TH1F(hname_phopt_1.c_str(),htitle_phopt_1.c_str(),256,0,256);
      hist_phopt_d->Fill(phopt_0-phopt_1);// TH1F(hname_phopt_d.c_str(),htitle_phopt_d.c_str(),512,-256,256);
//   Float_t         phoeta_0;
      b_phoeta_0->GetEntry(entry);
      b_phoeta_1->GetEntry(entry);
      hist_phoeta_0->Fill(phoeta_0);// TH1F(hname_phoeta_0.c_str(),htitle_phoeta_0.c_str(),128,-3.2,3.2);
      hist_phoeta_1->Fill(phoeta_1);// TH1F(hname_phoeta_0.c_str(),htitle_phoeta_0.c_str(),128,-3.2,3.2);
      hist_phoeta_d->Fill(phoeta_0-phoeta_1);// TH1F(hname_phoeta_d.c_str(),htitle_phoeta_d.c_str(),256,-6.4,6.4);
//   Float_t         phophi_0;
      b_phophi_0->GetEntry(entry);
      b_phophi_1->GetEntry(entry);
      hist_phophi_0->Fill(phophi_0);// TH1F(hname_phophi_0.c_str(),htitle_phophi_0.c_str(),128,-3.2,3.2);
      hist_phophi_1->Fill(phophi_1);// TH1F(hname_phophi_1.c_str(),htitle_phophi_1.c_str(),128,-3.2,3.2);
      hist_phophi_d->Fill(phophi_0-phophi_1);// TH1F(hname_phophi_d.c_str(),htitle_phophi_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscE_0;
      b_phoscE_0->GetEntry(entry);
      b_phoscE_1->GetEntry(entry);
      hist_phoscE_0->Fill(phoscE_0);// TH1F(hname_phoscE_0.c_str(),htitle_phoscE_0.c_str(),512,0,512);
      hist_phoscE_1->Fill(phoscE_1);// TH1F(hname_phoscE_1.c_str(),htitle_phoscE_1.c_str(),512,0,512);
      hist_phoscE_d->Fill(phoscE_0-phoscE_1);// TH1F(hname_phoscE_d.c_str(),htitle_phoscE_d.c_str(),1024,-512,512);
//   Float_t         phosceta_0;
      b_phosceta_0->GetEntry(entry);
      b_phosceta_1->GetEntry(entry);
      hist_phosceta_0->Fill(phosceta_0);// TH1F(hname_phosceta_0.c_str(),htitle_phosceta_0.c_str(),128,-3.2,3.2);
      hist_phosceta_1->Fill(phosceta_1);// TH1F(hname_phosceta_1.c_str(),htitle_phosceta_1.c_str(),128,-3.2,3.2);
      hist_phosceta_d->Fill(phosceta_0-phosceta_1);// TH1F(hname_phosceta_d.c_str(),htitle_phosceta_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscphi_0;
      b_phoscphi_0->GetEntry(entry);
      b_phoscphi_1->GetEntry(entry);
      hist_phoscphi_0->Fill(phoscphi_0);// TH1F(hname_phoscphi_0.c_str(),htitle_phoscphi_0.c_str(),128,-3.2,3.2);
      hist_phoscphi_1->Fill(phoscphi_1);// TH1F(hname_phoscphi_1.c_str(),htitle_phoscphi_1.c_str(),128,-3.2,3.2);
      hist_phoscphi_d->Fill(phoscphi_0-phoscphi_1);// TH1F(hname_phoscphi_d.c_str(),htitle_phoscphi_d.c_str(),256,-6.4,6.4);
//   Float_t         photdz_0;
      b_photdz_0->GetEntry(entry);
      b_photdz_1->GetEntry(entry);
      hist_photdz_0->Fill(photdz_0);// TH1F(hname_photdz_0.c_str(),htitle_photdz_0.c_str(),128,-25.6,25.6);
      hist_photdz_1->Fill(photdz_1);// TH1F(hname_photdz_1.c_str(),htitle_photdz_1.c_str(),128,-25.6,25.6);
      hist_photdz_d->Fill(photdz_0-photdz_1);// TH1F(hname_photdz_d.c_str(),htitle_photdz_d.c_str(),256,-51.2,51.2);
//   Float_t         phosieie_0;
      b_phosieie_0->GetEntry(entry);
      b_phosieie_1->GetEntry(entry);
      hist_phosieie_0->Fill(phosieie_0);// TH1F(hname_phosieie_0.c_str(),htitle_phosieie_0.c_str(),32,0,0.032);
      hist_phosieie_1->Fill(phosieie_1);// TH1F(hname_phosieie_1.c_str(),htitle_phosieie_1.c_str(),32,0,0.032);
      hist_phosieie_d->Fill(phosieie_0-phosieie_1);// TH1F(hname_phosieie_d.c_str(),htitle_phosieie_d.c_str(),64,-0.032,0.032);
//   Float_t         phosmaj_0;
      b_phosmaj_0->GetEntry(entry);
      b_phosmaj_1->GetEntry(entry);
      hist_phosmaj_0->Fill(phosmaj_0);// TH1F(hname_phosmaj_0.c_str(),htitle_phosmaj_0.c_str(),256,0,64);
      hist_phosmaj_1->Fill(phosmaj_1);// TH1F(hname_phosmaj_1.c_str(),htitle_phosmaj_1.c_str(),256,0,64);
      hist_phosmaj_d->Fill(phosmaj_0-phosmaj_1);// TH1F(hname_phosmaj_d.c_str(),htitle_phosmaj_d.c_str(),512,-64,64);
//   Float_t         phosmin_0;
      b_phosmin_0->GetEntry(entry);
      b_phosmin_1->GetEntry(entry);
      hist_phosmin_0->Fill(phosmin_0);// TH1F(hname_phosmin_0.c_str(),htitle_phosmin_0.c_str(),256,0,0.64);
      hist_phosmin_1->Fill(phosmin_1);// TH1F(hname_phosmin_1.c_str(),htitle_phosmin_1.c_str(),256,0,0.64);
      hist_phosmin_d->Fill(phosmin_0-phosmin_1);// TH1F(hname_phosmin_d.c_str(),htitle_phosmin_d.c_str(),512,-0.64,0.64);
//   Float_t         phosuisseX_0;
      b_phosuisseX_0->GetEntry(entry);
      b_phosuisseX_1->GetEntry(entry);
      hist_phosuisseX_0->Fill(phosuisseX_0);// TH1F(hname_phosuisseX_0.c_str(),htitle_phosuisseX_0.c_str(),256,-1.6,1.6);
      hist_phosuisseX_1->Fill(phosuisseX_1);// TH1F(hname_phosuisseX_1.c_str(),htitle_phosuisseX_1.c_str(),256,-1.6,1.6);
      hist_phosuisseX_d->Fill(phosuisseX_0-phosuisseX_1);// TH1F(hname_phosuisseX_d.c_str(),htitle_phosuisseX_d.c_str(),512,-3.2,3.2);
//   Float_t         phoseedE_0;
      b_phoseedE_0->GetEntry(entry);
      b_phoseedE_1->GetEntry(entry);
      hist_phoseedE_0->Fill(phoseedE_0);// TH1F(hname_phoseedE_0.c_str(),htitle_phoseedE_0.c_str(),512,0,512);
      hist_phoseedE_1->Fill(phoseedE_1);// TH1F(hname_phoseedE_1.c_str(),htitle_phoseedE_1.c_str(),512,0,512);
      hist_phoseedE_d->Fill(phoseedE_0-phoseedE_1);// TH1F(hname_phoseedE_d.c_str(),htitle_phoseedE_d.c_str(),1024,-512,512);
//   Int_t           phonrechits_0;
      b_phonrechits_0->GetEntry(entry);
      b_phonrechits_1->GetEntry(entry);
      hist_phonrechits_0->Fill(phonrechits_0);// TH1F(hname_phonrechits_0.c_str(),htitle_phonrechits_0.c_str(),32,0,32);
      hist_phonrechits_1->Fill(phonrechits_1);// TH1F(hname_phonrechits_1.c_str(),htitle_phonrechits_1.c_str(),32,0,32);
      hist_phonrechits_d->Fill(phonrechits_0-phonrechits_1);// TH1F(hname_phonrechits_d.c_str(),htitle_phonrechits_d.c_str(),64,-32,32);
 
//   Int_t           phoseedI1_0;
//   Int_t           phoseedI2_0;
      b_phoseedI1_0->GetEntry(entry);
      b_phoseedI2_0->GetEntry(entry);
      b_phoisEB_0->GetEntry(entry);
      b_phoseedI1_1->GetEntry(entry);
      b_phoseedI2_1->GetEntry(entry);
      b_phoisEB_1->GetEntry(entry);
		if( phoisEB_0 and phoisEB_1 ){
      	hist_phoseedMap_0->Fill(phoseedI2_0,phoseedI1_0,1);// TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
      	hist_phoseedMap_1->Fill(phoseedI2_1,phoseedI1_1,1);// TH2F(hname_phoseedMap_1.c_str(),htitle_phoseedMap_1.c_str(),171,-85.5,85.5,360,0.5,360.5);
			hist_phoseedMap_01->Fill(phoseedI2_0,phoseedI1_0,1);
			hist_phoseedMap_01->Fill(phoseedI2_1,phoseedI1_1,1);
		}

//    phoseedTOF_1
		b_phoseedTOF_0->GetEntry(entry);
      b_phoseedTOF_1->GetEntry(entry);
      hist_phoseedTOF_0->Fill(phoseedTOF_0);// TH1F(hname_phoseedTOF_0.c_str(),htitle_phoseedTOF_0.c_str(),32,0,32);
      hist_phoseedTOF_1->Fill(phoseedTOF_1);// TH1F(hname_phoseedTOF_1.c_str(),htitle_phoseedTOF_1.c_str(),32,0,32);
      hist_phoseedTOF_d->Fill(phoseedTOF_0-phoseedTOF_1);// TH1F(hname_phoseedTOF_d.c_str(),htitle_phoseedTOF_d.c_str(),64,-32,32);
      if( phoisEB_0 and phoisEB_1 ){
         hist_phoseedTOFMap_01->Fill(phoseedI2_0,phoseedI1_0,phoseedTOF_0);// TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
         hist_phoseedTOFMap_01->Fill(phoseedI2_1,phoseedI1_1,phoseedTOF_1);// TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
      }

//    phoseedtime_1
      b_phoseedtime_0->GetEntry(entry);
      b_phoseedtime_1->GetEntry(entry);
      hist_phoseedtime_0->Fill(phoseedtime_0);// TH1F(hname_phoseedtime_0.c_str(),htitle_phoseedtime_0.c_str(),256,-6.4,6.4);
      hist_phoseedtime_1->Fill(phoseedtime_1);// TH1F(hname_phoseedtime_1.c_str(),htitle_phoseedtime_1.c_str(),256,-6.4,6.4);
      hist_phoseedtime_d->Fill(phoseedtime_0-phoseedtime_1);// TH1F(hname_phoseedtime_d.c_str(),htitle_phoseedtime_d.c_str(),512,-12.8,12.8);
      if( phoisEB_0 and phoisEB_1 ){
         hist_phoseedtimeMap_01->Fill(phoseedI2_0,phoseedI1_0,phoseedtime_0);// TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
         hist_phoseedtimeMap_01->Fill(phoseedI2_1,phoseedI1_1,phoseedtime_1);// TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
      }



////    phoseedID_1
//      b_phoseedID_0->GetEntry(entry);
//      b_phoseedID_1->GetEntry(entry);
//		int ID_div = 1000000;
//      hist_phoseedID_0->Fill(phoseedID_0/ID_div);// TH1F(hname_phoseedID_0.c_str(),htitle_phoseedID_0.c_str(),32,838,840);
//      hist_phoseedID_1->Fill(phoseedID_1/ID_div);// TH1F(hname_phoseedID_1.c_str(),htitle_phoseedID_1.c_str(),32,838,840);
//      hist_phoseedID_d->Fill((phoseedID_0-phoseedID_1)/ID_div);// TH1F(hname_phoseedID_d.c_str(),htitle_phoseedID_d.c_str(),64,-2,2);
//
////    phoseedadcToGeV_1
//      b_phoseedadcToGeV_0->GetEntry(entry);
//      b_phoseedadcToGeV_1->GetEntry(entry);
//      hist_phoseedadcToGeV_0->Fill(phoseedadcToGeV_0);// TH1F(hname_phoseedadcToGeV_0.c_str(),htitle_phoseedadcToGeV_0.c_str(),32,0,2);
//      hist_phoseedadcToGeV_1->Fill(phoseedadcToGeV_1);// TH1F(hname_phoseedadcToGeV_1.c_str(),htitle_phoseedadcToGeV_1.c_str(),32,0,2);
//      hist_phoseedadcToGeV_d->Fill(phoseedadcToGeV_0-phoseedadcToGeV_1);// TH1F(hname_phoseedadcToGeV_d.c_str(),htitle_phoseedadcToGeV_d.c_str(),64,-2,2);


	}//  loop over events finished

	hist_phoseedTOFMap_01->Divide(hist_phoseedMap_01);
   hist_phoseedtimeMap_01->Divide(hist_phoseedMap_01);

//   Write Hitograms
//   Float_t         gZmass;
   hist_gZmass->Write();// TH1F(hname_gZmass.c_str(),htitlegZmass.c_str(),128,40,168);
//   Float_t         gdR;
   hist_gdR->Write();// TH1F(hname_gdR.c_str(),htitle_gdR.c_str(),64,0,5.12);
//   Int_t           nvtx;
   hist_nvtx->Write();// TH1F(hname_nvtx.c_str(),htitle_nvtx.c_str(),64,0,64);
//   Float_t         vtxX;
   hist_vtxX->Write();// TH1F(hname_vtxX.c_str(),htitle_vtxX.c_str(),128,0,0.128);
//   Float_t         vtxY;
   hist_vtxY->Write();// TH1F(hname_vtxY.c_str(),htitle_vtxY.c_str(),128,0,0.128);
//   Float_t         vtxZ;
   hist_vtxZ->Write();// TH1F(hname_vtxZ.c_str(),htitle_vtxZ.c_str(),128,-16,16);
//   Float_t         rho;
   hist_rho->Write();// TH1F(hname_rho.c_str(),htitle_rho.c_str(),64,0,32);

//   Float_t         phoE_0;
   hist_phoE_0->Write();// TH1F(hname_phoE_0.c_str(),htitle_phoE_0.c_str(),512,0,512);
   hist_phoE_1->Write();// TH1F(hname_phoE_1.c_str(),htitle_phoE_1.c_str(),512,0,512);
   hist_phoE_d->Write();// TH1F(hname_phoE_d.c_str(),htitle_phoE_d.c_str(),1024,-512,512);
//   Float_t         phopt_0;
   hist_phopt_0->Write();// TH1F(hname_phopt_0.c_str(),htitle_phopt_0.c_str(),256,0,256);
   hist_phopt_1->Write();// TH1F(hname_phopt_1.c_str(),htitle_phopt_1.c_str(),256,0,256);
   hist_phopt_d->Write();// TH1F(hname_phopt_d.c_str(),htitle_phopt_d.c_str(),512,-256,256);
//   Float_t         phoeta_0;
   hist_phoeta_0->Write();// TH1F(hname_phoeta_0.c_str(),htitle_phoeta_0.c_str(),128,-3.2,3.2);
   hist_phoeta_1->Write();// TH1F(hname_phoeta_0.c_str(),htitle_phoeta_0.c_str(),128,-3.2,3.2);
   hist_phoeta_d->Write();// TH1F(hname_phoeta_d.c_str(),htitle_phoeta_d.c_str(),256,-6.4,6.4);
//   Float_t         phophi_0;
   hist_phophi_0->Write();// TH1F(hname_phophi_0.c_str(),htitle_phophi_0.c_str(),128,-3.2,3.2);
   hist_phophi_1->Write();// TH1F(hname_phophi_1.c_str(),htitle_phophi_1.c_str(),128,-3.2,3.2);
   hist_phophi_d->Write();// TH1F(hname_phophi_d.c_str(),htitle_phophi_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscE_0;
   hist_phoscE_0->Write();// TH1F(hname_phoscE_0.c_str(),htitle_phoscE_0.c_str(),512,0,512);
   hist_phoscE_1->Write();// TH1F(hname_phoscE_1.c_str(),htitle_phoscE_1.c_str(),512,0,512);
   hist_phoscE_d->Write();// TH1F(hname_phoscE_d.c_str(),htitle_phoscE_d.c_str(),1024,-512,512);
//   Float_t         phosceta_0;
   hist_phosceta_0->Write();// TH1F(hname_phosceta_0.c_str(),htitle_phosceta_0.c_str(),128,-3.2,3.2);
   hist_phosceta_1->Write();// TH1F(hname_phosceta_1.c_str(),htitle_phosceta_1.c_str(),128,-3.2,3.2);
   hist_phosceta_d->Write();// TH1F(hname_phosceta_d.c_str(),htitle_phosceta_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscphi_0;
   hist_phoscphi_0->Write();// TH1F(hname_phoscphi_0.c_str(),htitle_phoscphi_0.c_str(),128,-3.2,3.2);
   hist_phoscphi_1->Write();// TH1F(hname_phoscphi_1.c_str(),htitle_phoscphi_1.c_str(),128,-3.2,3.2);
   hist_phoscphi_d->Write();// TH1F(hname_phoscphi_d.c_str(),htitle_phoscphi_d.c_str(),256,-6.4,6.4);
//   Float_t         photdz_0;
   hist_photdz_0->Write();// TH1F(hname_photdz_0.c_str(),htitle_photdz_0.c_str(),128,-25.6,25.6);
   hist_photdz_1->Write();// TH1F(hname_photdz_1.c_str(),htitle_photdz_1.c_str(),128,-25.6,25.6);
   hist_photdz_d->Write();// TH1F(hname_photdz_d.c_str(),htitle_photdz_d.c_str(),256,-51.2,51.2);
//   Float_t         phosieie_0;
   hist_phosieie_0->Write();// TH1F(hname_phosieie_0.c_str(),htitle_phosieie_0.c_str(),32,0,0.032);
   hist_phosieie_1->Write();// TH1F(hname_phosieie_1.c_str(),htitle_phosieie_1.c_str(),32,0,0.032);
   hist_phosieie_d->Write();// TH1F(hname_phosieie_d.c_str(),htitle_phosieie_d.c_str(),64,-0.032,0.032);
//   Float_t         phosmaj_0;
   hist_phosmaj_0->Write();// TH1F(hname_phosmaj_0.c_str(),htitle_phosmaj_0.c_str(),256,0,64);
   hist_phosmaj_1->Write();// TH1F(hname_phosmaj_1.c_str(),htitle_phosmaj_1.c_str(),256,0,64);
   hist_phosmaj_d->Write();// TH1F(hname_phosmaj_d.c_str(),htitle_phosmaj_d.c_str(),512,-64,64);
//   Float_t         phosmin_0;
   hist_phosmin_0->Write();// TH1F(hname_phosmin_0.c_str(),htitle_phosmin_0.c_str(),256,0,0.64);
   hist_phosmin_1->Write();// TH1F(hname_phosmin_1.c_str(),htitle_phosmin_1.c_str(),256,0,0.64);
   hist_phosmin_d->Write();// TH1F(hname_phosmin_d.c_str(),htitle_phosmin_d.c_str(),512,-0.64,0.64);
//   Float_t         phosuisseX_0;
   hist_phosuisseX_0->Write();// TH1F(hname_phosuisseX_0.c_str(),htitle_phosuisseX_0.c_str(),256,-1.6,1.6);
   hist_phosuisseX_1->Write();// TH1F(hname_phosuisseX_1.c_str(),htitle_phosuisseX_1.c_str(),256,-1.6,1.6);
   hist_phosuisseX_d->Write();// TH1F(hname_phosuisseX_d.c_str(),htitle_phosuisseX_d.c_str(),512,-3.2,3.2);
//   Float_t         phoseedE_0;
   hist_phoseedE_0->Write();// TH1F(hname_phoseedE_0.c_str(),htitle_phoseedE_0.c_str(),512,0,512);
   hist_phoseedE_1->Write();// TH1F(hname_phoseedE_1.c_str(),htitle_phoseedE_1.c_str(),512,0,512);
   hist_phoseedE_d->Write();// TH1F(hname_phoseedE_d.c_str(),htitle_phoseedE_d.c_str(),1024,-512,512);
//   Int_t           phonrechits_0;
   hist_phonrechits_0->Write();// TH1F(hname_phonrechits_0.c_str(),htitle_phonrechits_0.c_str(),32,0,32);
   hist_phonrechits_1->Write();// TH1F(hname_phonrechits_1.c_str(),htitle_phonrechits_1.c_str(),32,0,32);
   hist_phonrechits_d->Write();// TH1F(hname_phonrechits_d.c_str(),htitle_phonrechits_d.c_str(),64,-32,32);

//   Int_t           phoseedI1_0;
//   Int_t           phoseedI2_0;
   hist_phoseedMap_0->Write();// TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
   hist_phoseedMap_1->Write();// TH2F(hname_phoseedMap_1.c_str(),htitle_phoseedMap_1.c_str(),171,-85.5,85.5,360,0.5,360.5);

//    phoseedTOF_1
   hist_phoseedTOF_0->Write();// TH1F(hname_phoseedTOF_0.c_str(),htitle_phoseedTOF_0.c_str(),32,0,32);
   hist_phoseedTOF_1->Write();//Fill(phoseedTOF_1);// TH1F(hname_phoseedTOF_1.c_str(),htitle_phoseedTOF_1.c_str(),32,0,32);
   hist_phoseedTOF_d->Write();//Fill(phoseedTOF_0-phoseedTOF_1);// TH1F(hname_phoseedTOF_d.c_str(),htitle_phoseedTOF_d.c_str(),64,-32,32);
	hist_phoseedTOFMap_01->Write();

//    phoseedtime_1
   hist_phoseedtime_0->Write();//Fill(phoseedtime_0);// TH1F(hname_phoseedtime_0.c_str(),htitle_phoseedtime_0.c_str(),256,-6.4,6.4);
   hist_phoseedtime_1->Write();//Fill(phoseedtime_1);// TH1F(hname_phoseedtime_1.c_str(),htitle_phoseedtime_1.c_str(),256,-6.4,6.4);
   hist_phoseedtime_d->Write();//Fill(phoseedtime_0-phoseedtime_1);// TH1F(hname_phoseedtime_d.c_str(),htitle_phoseedtime_d.c_str(),512,-12.8,12.8);
	hist_phoseedtimeMap_01->Write();

////    phoseedID_1
//   hist_phoseedID_0->Write();//Fill(phoseedID_0/ID_div);// TH1F(hname_phoseedID_0.c_str(),htitle_phoseedID_0.c_str(),32,838,840);
//   hist_phoseedID_1->Write();//Fill(phoseedID_1/ID_div);// TH1F(hname_phoseedID_1.c_str(),htitle_phoseedID_1.c_str(),32,838,840);
//   hist_phoseedID_d->Write();//Fill((phoseedID_0-phoseedID_1)/ID_div);// TH1F(hname_phoseedID_d.c_str(),htitle_phoseedID_d.c_str(),64,-2,2);
//
////    phoseedadcToGeV_1
//   hist_phoseedadcToGeV_0->Write();//Fill(phoseedadcToGeV_0);// TH1F(hname_phoseedadcToGeV_0.c_str(),htitle_phoseedadcToGeV_0.c_str(),32,0,2);
//   hist_phoseedadcToGeV_1->Write();//Fill(phoseedadcToGeV_1);// TH1F(hname_phoseedadcToGeV_1.c_str(),htitle_phoseedadcToGeV_1.c_str(),32,0,2);
//   hist_phoseedadcToGeV_d->Write();//Fill(phoseedadcToGeV_0-phoseedadcToGeV_1);// TH1F(hname_phoseedadcToGeV_d.c_str(),htitle_phoseedadcToGeV_d.c_str(),64,-2,2);

//   Delete Hitograms
//   Float_t         gZmass;
   delete hist_gZmass;// TH1F(hname_gZmass.c_str(),htitlegZmass.c_str(),128,40,168);
//   Float_t         gdR;
   delete hist_gdR;// TH1F(hname_gdR.c_str(),htitle_gdR.c_str(),64,0,5.12);
//   Int_t           nvtx;
   delete hist_nvtx;// TH1F(hname_nvtx.c_str(),htitle_nvtx.c_str(),64,0,64);
//   Float_t         vtxX;
   delete hist_vtxX;// TH1F(hname_vtxX.c_str(),htitle_vtxX.c_str(),128,0,0.128);
//   Float_t         vtxY;
   delete hist_vtxY;// TH1F(hname_vtxY.c_str(),htitle_vtxY.c_str(),128,0,0.128);
//   Float_t         vtxZ;
   delete hist_vtxZ;// TH1F(hname_vtxZ.c_str(),htitle_vtxZ.c_str(),128,-16,16);
//   Float_t         rho;
   delete hist_rho;// TH1F(hname_rho.c_str(),htitle_rho.c_str(),64,0,32);
//   Float_t         phoE_0;
   delete hist_phoE_0;// TH1F(hname_phoE_0.c_str(),htitle_phoE_0.c_str(),512,0,512);
   delete hist_phoE_1;// TH1F(hname_phoE_1.c_str(),htitle_phoE_1.c_str(),512,0,512);
   delete hist_phoE_d;// TH1F(hname_phoE_d.c_str(),htitle_phoE_d.c_str(),1024,-512,512);
//   Float_t         phopt_0;
   delete hist_phopt_0;// TH1F(hname_phopt_0.c_str(),htitle_phopt_0.c_str(),256,0,256);
   delete hist_phopt_1;// TH1F(hname_phopt_1.c_str(),htitle_phopt_1.c_str(),256,0,256);
   delete hist_phopt_d;// TH1F(hname_phopt_d.c_str(),htitle_phopt_d.c_str(),512,-256,256);
//   Float_t         phoeta_0;
   delete hist_phoeta_0;// TH1F(hname_phoeta_0.c_str(),htitle_phoeta_0.c_str(),128,-3.2,3.2);
   delete hist_phoeta_1;// TH1F(hname_phoeta_0.c_str(),htitle_phoeta_0.c_str(),128,-3.2,3.2);
   delete hist_phoeta_d;// TH1F(hname_phoeta_d.c_str(),htitle_phoeta_d.c_str(),256,-6.4,6.4);
//   Float_t         phophi_0;
   delete hist_phophi_0;// TH1F(hname_phophi_0.c_str(),htitle_phophi_0.c_str(),128,-3.2,3.2);
   delete hist_phophi_1;// TH1F(hname_phophi_1.c_str(),htitle_phophi_1.c_str(),128,-3.2,3.2);
   delete hist_phophi_d;// TH1F(hname_phophi_d.c_str(),htitle_phophi_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscE_0;
   delete hist_phoscE_0;// TH1F(hname_phoscE_0.c_str(),htitle_phoscE_0.c_str(),512,0,512);
   delete hist_phoscE_1;// TH1F(hname_phoscE_1.c_str(),htitle_phoscE_1.c_str(),512,0,512);
   delete hist_phoscE_d;// TH1F(hname_phoscE_d.c_str(),htitle_phoscE_d.c_str(),1024,-512,512);
//   Float_t         phosceta_0;
   delete hist_phosceta_0;// TH1F(hname_phosceta_0.c_str(),htitle_phosceta_0.c_str(),128,-3.2,3.2);
   delete hist_phosceta_1;// TH1F(hname_phosceta_1.c_str(),htitle_phosceta_1.c_str(),128,-3.2,3.2);
   delete hist_phosceta_d;// TH1F(hname_phosceta_d.c_str(),htitle_phosceta_d.c_str(),256,-6.4,6.4);
//   Float_t         phoscphi_0;
   delete hist_phoscphi_0;// TH1F(hname_phoscphi_0.c_str(),htitle_phoscphi_0.c_str(),128,-3.2,3.2);
   delete hist_phoscphi_1;// TH1F(hname_phoscphi_1.c_str(),htitle_phoscphi_1.c_str(),128,-3.2,3.2);
   delete hist_phoscphi_d;// TH1F(hname_phoscphi_d.c_str(),htitle_phoscphi_d.c_str(),256,-6.4,6.4);
//   Float_t         photdz_0;
   delete hist_photdz_0;// TH1F(hname_photdz_0.c_str(),htitle_photdz_0.c_str(),128,-25.6,25.6);
   delete hist_photdz_1;// TH1F(hname_photdz_1.c_str(),htitle_photdz_1.c_str(),128,-25.6,25.6);
   delete hist_photdz_d;// TH1F(hname_photdz_d.c_str(),htitle_photdz_d.c_str(),256,-51.2,51.2);
//   Float_t         phosieie_0;
   delete hist_phosieie_0;// TH1F(hname_phosieie_0.c_str(),htitle_phosieie_0.c_str(),32,0,0.032);
   delete hist_phosieie_1;// TH1F(hname_phosieie_1.c_str(),htitle_phosieie_1.c_str(),32,0,0.032);
   delete hist_phosieie_d;// TH1F(hname_phosieie_d.c_str(),htitle_phosieie_d.c_str(),64,-0.032,0.032);
//   Float_t         phosmaj_0;
   delete hist_phosmaj_0;// TH1F(hname_phosmaj_0.c_str(),htitle_phosmaj_0.c_str(),256,0,64);
   delete hist_phosmaj_1;// TH1F(hname_phosmaj_1.c_str(),htitle_phosmaj_1.c_str(),256,0,64);
   delete hist_phosmaj_d;// TH1F(hname_phosmaj_d.c_str(),htitle_phosmaj_d.c_str(),512,-64,64);
//   Float_t         phosmin_0;
   delete hist_phosmin_0;// TH1F(hname_phosmin_0.c_str(),htitle_phosmin_0.c_str(),256,0,0.64);
   delete hist_phosmin_1;// TH1F(hname_phosmin_1.c_str(),htitle_phosmin_1.c_str(),256,0,0.64);
   delete hist_phosmin_d;// TH1F(hname_phosmin_d.c_str(),htitle_phosmin_d.c_str(),512,-0.64,0.64);
//   Float_t         phosuisseX_0;
   delete hist_phosuisseX_0;// TH1F(hname_phosuisseX_0.c_str(),htitle_phosuisseX_0.c_str(),256,-1.6,1.6);
   delete hist_phosuisseX_1;// TH1F(hname_phosuisseX_1.c_str(),htitle_phosuisseX_1.c_str(),256,-1.6,1.6);
   delete hist_phosuisseX_d;// TH1F(hname_phosuisseX_d.c_str(),htitle_phosuisseX_d.c_str(),512,-3.2,3.2);
//   Float_t         phoseedE_0;
   delete hist_phoseedE_0;// TH1F(hname_phoseedE_0.c_str(),htitle_phoseedE_0.c_str(),512,0,512);
   delete hist_phoseedE_1;// TH1F(hname_phoseedE_1.c_str(),htitle_phoseedE_1.c_str(),512,0,512);
   delete hist_phoseedE_d;// TH1F(hname_phoseedE_d.c_str(),htitle_phoseedE_d.c_str(),1024,-512,512);
//   Int_t           phonrechits_0;
   delete hist_phonrechits_0;// TH1F(hname_phonrechits_0.c_str(),htitle_phonrechits_0.c_str(),32,0,32);
   delete hist_phonrechits_1;// TH1F(hname_phonrechits_1.c_str(),htitle_phonrechits_1.c_str(),32,0,32);
   delete hist_phonrechits_d;// TH1F(hname_phonrechits_d.c_str(),htitle_phonrechits_d.c_str(),64,-32,32);

//   Int_t           phoseedI1_0;
//   Int_t           phoseedI2_0;
   delete hist_phoseedMap_0;// TH2F(hname_phoseedMap_0.c_str(),htitle_phoseedMap_0.c_str(),171,-85.5,85.5,360,0.5,360.5);
   delete hist_phoseedMap_1;// TH2F(hname_phoseedMap_1.c_str(),htitle_phoseedMap_1.c_str(),171,-85.5,85.5,360,0.5,360.5);

//    phoseedTOF_1
   delete hist_phoseedTOF_0;// TH1F(hname_phoseedTOF_0.c_str(),htitle_phoseedTOF_0.c_str(),32,0,32);
   delete hist_phoseedTOF_1;//Fill(phoseedTOF_1);// TH1F(hname_phoseedTOF_1.c_str(),htitle_phoseedTOF_1.c_str(),32,0,32);
   delete hist_phoseedTOF_d;//Fill(phoseedTOF_0-phoseedTOF_1);// TH1F(hname_phoseedTOF_d.c_str(),htitle_phoseedTOF_d.c_str(),64,-32,32);
   delete hist_phoseedTOFMap_01;

//    phoseedtime_1
   delete hist_phoseedtime_0;//Fill(phoseedtime_0);// TH1F(hname_phoseedtime_0.c_str(),htitle_phoseedtime_0.c_str(),256,-6.4,6.4);
   delete hist_phoseedtime_1;//Fill(phoseedtime_1);// TH1F(hname_phoseedtime_1.c_str(),htitle_phoseedtime_1.c_str(),256,-6.4,6.4);
   delete hist_phoseedtime_d;//Fill(phoseedtime_0-phoseedtime_1);// TH1F(hname_phoseedtime_d.c_str(),htitle_phoseedtime_d.c_str(),512,-12.8,12.8);
   delete hist_phoseedtimeMap_01;

// delete out file
   delete fOutFile;
}

int main ( int argc, char *argv[] ){

   if( argc != 4 ) { std::cout << "Insufficent arguments." << std::endl; }
   else {
   	auto indir = argv[1];
      auto infilelist = argv[2];
      auto outfilename = argv[3];
      wc_ku_global_plots( indir, infilelist, outfilename );
   }
   return 1;
}

//   Float_t         gZmass;
//   Float_t         gdR;
//   Int_t           nvtx;
//   Float_t         vtxX;
//   Float_t         vtxY;
//   Float_t         vtxZ;
//   Float_t         rho;
//
//   Float_t         phoE_0;
//   Float_t         phopt_0;
//   Float_t         phoeta_0;
//   Float_t         phophi_0;
//   Float_t         phoscE_0;
//   Float_t         phosceta_0;
//   Float_t         phoscphi_0;
//   Float_t         photdz_0;
//   Float_t         phosieie_0;
//   Float_t         phosmaj_0;
//   Float_t         phosmin_0;
//   Float_t         phosuisseX_0;
//   Float_t         phoseedE_0;
//   Int_t           phonrechits_0;
//
//   Int_t           phoseedI1_0;
//   Int_t           phoseedI2_0;

