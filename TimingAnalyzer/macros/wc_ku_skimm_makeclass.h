//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar  7 14:16:31 2020 by ROOT version 6.12/07
// from TTree disphotree/disphotree
// found on file: local_skims/global_chain/dispho_ot_mini_Run2016B.root
//////////////////////////////////////////////////////////

#ifndef disphotree_h
#define disphotree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class disphotree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

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

   disphotree(TTree *tree=0);
   virtual ~disphotree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef disphotree_cxx
disphotree::disphotree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("local_skims/global_chain/dispho_ot_mini_Run2016B.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("local_skims/global_chain/dispho_ot_mini_Run2016B.root");
      }
      f->GetObject("disphotree",tree);

   }
   Init(tree);
}

disphotree::~disphotree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t disphotree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t disphotree::LoadTree(Long64_t entry)
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

void disphotree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   out_npho_recHits_0 = 0;
   out_npho_recHits_1 = 0;
   out_npho_recHits_2 = 0;
   out_npho_recHits_3 = 0;
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
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("vtxX", &vtxX, &b_vtxX);
   fChain->SetBranchAddress("vtxY", &vtxY, &b_vtxY);
   fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("nrechits", &nrechits, &b_nrechits);
   fChain->SetBranchAddress("nkurechits", &nkurechits, &b_nkurechits);
   fChain->SetBranchAddress("out_npho_recHits_0", &out_npho_recHits_0, &b_out_npho_recHits_0);
   fChain->SetBranchAddress("out_npho_recHits_1", &out_npho_recHits_1, &b_out_npho_recHits_1);
   fChain->SetBranchAddress("out_npho_recHits_2", &out_npho_recHits_2, &b_out_npho_recHits_2);
   fChain->SetBranchAddress("out_npho_recHits_3", &out_npho_recHits_3, &b_out_npho_recHits_3);
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
   fChain->SetBranchAddress("phoseedped12_0", &phoseedped12_0, &b_phoseedped12_0);
   fChain->SetBranchAddress("phoseedped6_0", &phoseedped6_0, &b_phoseedped6_0);
   fChain->SetBranchAddress("phoseedped1_0", &phoseedped1_0, &b_phoseedped1_0);
   fChain->SetBranchAddress("phoseedpedrms12_0", &phoseedpedrms12_0, &b_phoseedpedrms12_0);
   fChain->SetBranchAddress("phoseedpedrms6_0", &phoseedpedrms6_0, &b_phoseedpedrms6_0);
   fChain->SetBranchAddress("phoseedpedrms1_0", &phoseedpedrms1_0, &b_phoseedpedrms1_0);
   fChain->SetBranchAddress("phoseedkutime_0", &phoseedkutime_0, &b_phoseedkutime_0);
   fChain->SetBranchAddress("phoseedkuID_0", &phoseedkuID_0, &b_phoseedkuID_0);
   fChain->SetBranchAddress("phoseedkuStctime_0", &phoseedkuStctime_0, &b_phoseedkuStctime_0);
   fChain->SetBranchAddress("phoseedkuStcID_0", &phoseedkuStcID_0, &b_phoseedkuStcID_0);
   fChain->SetBranchAddress("phoseedkuNotStctime_0", &phoseedkuNotStctime_0, &b_phoseedkuNotStctime_0);
   fChain->SetBranchAddress("phoseedkuNotStcID_0", &phoseedkuNotStcID_0, &b_phoseedkuNotStcID_0);
   fChain->SetBranchAddress("phoseedkuWootStctime_0", &phoseedkuWootStctime_0, &b_phoseedkuWootStctime_0);
   fChain->SetBranchAddress("phoseedkuWootStcID_0", &phoseedkuWootStcID_0, &b_phoseedkuWootStcID_0);
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
   fChain->SetBranchAddress("phoseedped12_1", &phoseedped12_1, &b_phoseedped12_1);
   fChain->SetBranchAddress("phoseedped6_1", &phoseedped6_1, &b_phoseedped6_1);
   fChain->SetBranchAddress("phoseedped1_1", &phoseedped1_1, &b_phoseedped1_1);
   fChain->SetBranchAddress("phoseedpedrms12_1", &phoseedpedrms12_1, &b_phoseedpedrms12_1);
   fChain->SetBranchAddress("phoseedpedrms6_1", &phoseedpedrms6_1, &b_phoseedpedrms6_1);
   fChain->SetBranchAddress("phoseedpedrms1_1", &phoseedpedrms1_1, &b_phoseedpedrms1_1);
   fChain->SetBranchAddress("phoseedkutime_1", &phoseedkutime_1, &b_phoseedkutime_1);
   fChain->SetBranchAddress("phoseedkuID_1", &phoseedkuID_1, &b_phoseedkuID_1);
   fChain->SetBranchAddress("phoseedkuStctime_1", &phoseedkuStctime_1, &b_phoseedkuStctime_1);
   fChain->SetBranchAddress("phoseedkuStcID_1", &phoseedkuStcID_1, &b_phoseedkuStcID_1);
   fChain->SetBranchAddress("phoseedkuNotStctime_1", &phoseedkuNotStctime_1, &b_phoseedkuNotStctime_1);
   fChain->SetBranchAddress("phoseedkuNotStcID_1", &phoseedkuNotStcID_1, &b_phoseedkuNotStcID_1);
   fChain->SetBranchAddress("phoseedkuWootStctime_1", &phoseedkuWootStctime_1, &b_phoseedkuWootStctime_1);
   fChain->SetBranchAddress("phoseedkuWootStcID_1", &phoseedkuWootStcID_1, &b_phoseedkuWootStcID_1);
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
   fChain->SetBranchAddress("phohasPixSeed_1", &phohasPixSeed_1, &b_phohasPixSeed_1);
   fChain->SetBranchAddress("phoootID_1", &phoootID_1, &b_phoootID_1);
   fChain->SetBranchAddress("phoseedTT_1", &phoseedTT_1, &b_phoseedTT_1);
   fChain->SetBranchAddress("phonrechits_1", &phonrechits_1, &b_phonrechits_1);
   fChain->SetBranchAddress("phoE_2", &phoE_2, &b_phoE_2);
   fChain->SetBranchAddress("phopt_2", &phopt_2, &b_phopt_2);
   fChain->SetBranchAddress("phoeta_2", &phoeta_2, &b_phoeta_2);
   fChain->SetBranchAddress("phophi_2", &phophi_2, &b_phophi_2);
   fChain->SetBranchAddress("phoscE_2", &phoscE_2, &b_phoscE_2);
   fChain->SetBranchAddress("phosceta_2", &phosceta_2, &b_phosceta_2);
   fChain->SetBranchAddress("phoscphi_2", &phoscphi_2, &b_phoscphi_2);
   fChain->SetBranchAddress("photdz_2", &photdz_2, &b_photdz_2);
   fChain->SetBranchAddress("phosieie_2", &phosieie_2, &b_phosieie_2);
   fChain->SetBranchAddress("phosmaj_2", &phosmaj_2, &b_phosmaj_2);
   fChain->SetBranchAddress("phosmin_2", &phosmin_2, &b_phosmin_2);
   fChain->SetBranchAddress("phosuisseX_2", &phosuisseX_2, &b_phosuisseX_2);
   fChain->SetBranchAddress("phoseedE_2", &phoseedE_2, &b_phoseedE_2);
   fChain->SetBranchAddress("phoseedtime_2", &phoseedtime_2, &b_phoseedtime_2);
   fChain->SetBranchAddress("phoseedTOF_2", &phoseedTOF_2, &b_phoseedTOF_2);
   fChain->SetBranchAddress("phoseedID_2", &phoseedID_2, &b_phoseedID_2);
   fChain->SetBranchAddress("phoseedI1_2", &phoseedI1_2, &b_phoseedI1_2);
   fChain->SetBranchAddress("phoseedI2_2", &phoseedI2_2, &b_phoseedI2_2);
   fChain->SetBranchAddress("phoseedEcal_2", &phoseedEcal_2, &b_phoseedEcal_2);
   fChain->SetBranchAddress("phoseedadcToGeV_2", &phoseedadcToGeV_2, &b_phoseedadcToGeV_2);
   fChain->SetBranchAddress("phoseedped12_2", &phoseedped12_2, &b_phoseedped12_2);
   fChain->SetBranchAddress("phoseedped6_2", &phoseedped6_2, &b_phoseedped6_2);
   fChain->SetBranchAddress("phoseedped1_2", &phoseedped1_2, &b_phoseedped1_2);
   fChain->SetBranchAddress("phoseedpedrms12_2", &phoseedpedrms12_2, &b_phoseedpedrms12_2);
   fChain->SetBranchAddress("phoseedpedrms6_2", &phoseedpedrms6_2, &b_phoseedpedrms6_2);
   fChain->SetBranchAddress("phoseedpedrms1_2", &phoseedpedrms1_2, &b_phoseedpedrms1_2);
   fChain->SetBranchAddress("phoseedkutime_2", &phoseedkutime_2, &b_phoseedkutime_2);
   fChain->SetBranchAddress("phoseedkuID_2", &phoseedkuID_2, &b_phoseedkuID_2);
   fChain->SetBranchAddress("phoseedkuStctime_2", &phoseedkuStctime_2, &b_phoseedkuStctime_2);
   fChain->SetBranchAddress("phoseedkuStcID_2", &phoseedkuStcID_2, &b_phoseedkuStcID_2);
   fChain->SetBranchAddress("phoseedkuNotStctime_2", &phoseedkuNotStctime_2, &b_phoseedkuNotStctime_2);
   fChain->SetBranchAddress("phoseedkuNotStcID_2", &phoseedkuNotStcID_2, &b_phoseedkuNotStcID_2);
   fChain->SetBranchAddress("phoseedkuWootStctime_2", &phoseedkuWootStctime_2, &b_phoseedkuWootStctime_2);
   fChain->SetBranchAddress("phoseedkuWootStcID_2", &phoseedkuWootStcID_2, &b_phoseedkuWootStcID_2);
   fChain->SetBranchAddress("phoseedootA0_2", &phoseedootA0_2, &b_phoseedootA0_2);
   fChain->SetBranchAddress("phoseedootA1_2", &phoseedootA1_2, &b_phoseedootA1_2);
   fChain->SetBranchAddress("phoseedootA2_2", &phoseedootA2_2, &b_phoseedootA2_2);
   fChain->SetBranchAddress("phoseedootA3_2", &phoseedootA3_2, &b_phoseedootA3_2);
   fChain->SetBranchAddress("phoseedootA4_2", &phoseedootA4_2, &b_phoseedootA4_2);
   fChain->SetBranchAddress("phoseedootA5_2", &phoseedootA5_2, &b_phoseedootA5_2);
   fChain->SetBranchAddress("phoseedootA6_2", &phoseedootA6_2, &b_phoseedootA6_2);
   fChain->SetBranchAddress("phoseedootA7_2", &phoseedootA7_2, &b_phoseedootA7_2);
   fChain->SetBranchAddress("phoseedootA8_2", &phoseedootA8_2, &b_phoseedootA8_2);
   fChain->SetBranchAddress("phoseedootA9_2", &phoseedootA9_2, &b_phoseedootA9_2);
   fChain->SetBranchAddress("phoseedootMax_2", &phoseedootMax_2, &b_phoseedootMax_2);
   fChain->SetBranchAddress("phoseedootMbefore_2", &phoseedootMbefore_2, &b_phoseedootMbefore_2);
   fChain->SetBranchAddress("phoseedootMafter_2", &phoseedootMafter_2, &b_phoseedootMafter_2);
   fChain->SetBranchAddress("phoseedootSign_2", &phoseedootSign_2, &b_phoseedootSign_2);
   fChain->SetBranchAddress("phoseedootVsum_2", &phoseedootVsum_2, &b_phoseedootVsum_2);
   fChain->SetBranchAddress("phoisOOT_2", &phoisOOT_2, &b_phoisOOT_2);
   fChain->SetBranchAddress("phoisEB_2", &phoisEB_2, &b_phoisEB_2);
   fChain->SetBranchAddress("phohasPixSeed_2", &phohasPixSeed_2, &b_phohasPixSeed_2);
   fChain->SetBranchAddress("phoootID_2", &phoootID_2, &b_phoootID_2);
   fChain->SetBranchAddress("phoseedTT_2", &phoseedTT_2, &b_phoseedTT_2);
   fChain->SetBranchAddress("phonrechits_2", &phonrechits_2, &b_phonrechits_2);
   fChain->SetBranchAddress("phoE_3", &phoE_3, &b_phoE_3);
   fChain->SetBranchAddress("phopt_3", &phopt_3, &b_phopt_3);
   fChain->SetBranchAddress("phoeta_3", &phoeta_3, &b_phoeta_3);
   fChain->SetBranchAddress("phophi_3", &phophi_3, &b_phophi_3);
   fChain->SetBranchAddress("phoscE_3", &phoscE_3, &b_phoscE_3);
   fChain->SetBranchAddress("phosceta_3", &phosceta_3, &b_phosceta_3);
   fChain->SetBranchAddress("phoscphi_3", &phoscphi_3, &b_phoscphi_3);
   fChain->SetBranchAddress("photdz_3", &photdz_3, &b_photdz_3);
   fChain->SetBranchAddress("phosieie_3", &phosieie_3, &b_phosieie_3);
   fChain->SetBranchAddress("phosmaj_3", &phosmaj_3, &b_phosmaj_3);
   fChain->SetBranchAddress("phosmin_3", &phosmin_3, &b_phosmin_3);
   fChain->SetBranchAddress("phosuisseX_3", &phosuisseX_3, &b_phosuisseX_3);
   fChain->SetBranchAddress("phoseedE_3", &phoseedE_3, &b_phoseedE_3);
   fChain->SetBranchAddress("phoseedtime_3", &phoseedtime_3, &b_phoseedtime_3);
   fChain->SetBranchAddress("phoseedTOF_3", &phoseedTOF_3, &b_phoseedTOF_3);
   fChain->SetBranchAddress("phoseedID_3", &phoseedID_3, &b_phoseedID_3);
   fChain->SetBranchAddress("phoseedI1_3", &phoseedI1_3, &b_phoseedI1_3);
   fChain->SetBranchAddress("phoseedI2_3", &phoseedI2_3, &b_phoseedI2_3);
   fChain->SetBranchAddress("phoseedEcal_3", &phoseedEcal_3, &b_phoseedEcal_3);
   fChain->SetBranchAddress("phoseedadcToGeV_3", &phoseedadcToGeV_3, &b_phoseedadcToGeV_3);
   fChain->SetBranchAddress("phoseedped12_3", &phoseedped12_3, &b_phoseedped12_3);
   fChain->SetBranchAddress("phoseedped6_3", &phoseedped6_3, &b_phoseedped6_3);
   fChain->SetBranchAddress("phoseedped1_3", &phoseedped1_3, &b_phoseedped1_3);
   fChain->SetBranchAddress("phoseedpedrms12_3", &phoseedpedrms12_3, &b_phoseedpedrms12_3);
   fChain->SetBranchAddress("phoseedpedrms6_3", &phoseedpedrms6_3, &b_phoseedpedrms6_3);
   fChain->SetBranchAddress("phoseedpedrms1_3", &phoseedpedrms1_3, &b_phoseedpedrms1_3);
   fChain->SetBranchAddress("phoseedkutime_3", &phoseedkutime_3, &b_phoseedkutime_3);
   fChain->SetBranchAddress("phoseedkuID_3", &phoseedkuID_3, &b_phoseedkuID_3);
   fChain->SetBranchAddress("phoseedkuStctime_3", &phoseedkuStctime_3, &b_phoseedkuStctime_3);
   fChain->SetBranchAddress("phoseedkuStcID_3", &phoseedkuStcID_3, &b_phoseedkuStcID_3);
   fChain->SetBranchAddress("phoseedkuNotStctime_3", &phoseedkuNotStctime_3, &b_phoseedkuNotStctime_3);
   fChain->SetBranchAddress("phoseedkuNotStcID_3", &phoseedkuNotStcID_3, &b_phoseedkuNotStcID_3);
   fChain->SetBranchAddress("phoseedkuWootStctime_3", &phoseedkuWootStctime_3, &b_phoseedkuWootStctime_3);
   fChain->SetBranchAddress("phoseedkuWootStcID_3", &phoseedkuWootStcID_3, &b_phoseedkuWootStcID_3);
   fChain->SetBranchAddress("phoseedootA0_3", &phoseedootA0_3, &b_phoseedootA0_3);
   fChain->SetBranchAddress("phoseedootA1_3", &phoseedootA1_3, &b_phoseedootA1_3);
   fChain->SetBranchAddress("phoseedootA2_3", &phoseedootA2_3, &b_phoseedootA2_3);
   fChain->SetBranchAddress("phoseedootA3_3", &phoseedootA3_3, &b_phoseedootA3_3);
   fChain->SetBranchAddress("phoseedootA4_3", &phoseedootA4_3, &b_phoseedootA4_3);
   fChain->SetBranchAddress("phoseedootA5_3", &phoseedootA5_3, &b_phoseedootA5_3);
   fChain->SetBranchAddress("phoseedootA6_3", &phoseedootA6_3, &b_phoseedootA6_3);
   fChain->SetBranchAddress("phoseedootA7_3", &phoseedootA7_3, &b_phoseedootA7_3);
   fChain->SetBranchAddress("phoseedootA8_3", &phoseedootA8_3, &b_phoseedootA8_3);
   fChain->SetBranchAddress("phoseedootA9_3", &phoseedootA9_3, &b_phoseedootA9_3);
   fChain->SetBranchAddress("phoseedootMax_3", &phoseedootMax_3, &b_phoseedootMax_3);
   fChain->SetBranchAddress("phoseedootMbefore_3", &phoseedootMbefore_3, &b_phoseedootMbefore_3);
   fChain->SetBranchAddress("phoseedootMafter_3", &phoseedootMafter_3, &b_phoseedootMafter_3);
   fChain->SetBranchAddress("phoseedootSign_3", &phoseedootSign_3, &b_phoseedootSign_3);
   fChain->SetBranchAddress("phoseedootVsum_3", &phoseedootVsum_3, &b_phoseedootVsum_3);
   fChain->SetBranchAddress("phoisOOT_3", &phoisOOT_3, &b_phoisOOT_3);
   fChain->SetBranchAddress("phoisEB_3", &phoisEB_3, &b_phoisEB_3);
   fChain->SetBranchAddress("phohasPixSeed_3", &phohasPixSeed_3, &b_phohasPixSeed_3);
   fChain->SetBranchAddress("phoootID_3", &phoootID_3, &b_phoootID_3);
   fChain->SetBranchAddress("phoseedTT_3", &phoseedTT_3, &b_phoseedTT_3);
   fChain->SetBranchAddress("phonrechits_3", &phonrechits_3, &b_phonrechits_3);
   Notify();
}

Bool_t disphotree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void disphotree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t disphotree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef disphotree_cxx
