#include "Skimmer_chain.hh"
#include "TROOT.h"
#include "Common.cpp"
#include <iostream>

using namespace std;

//    string xbinstr("VARIABLE 75 100 125 150 175 225 275 325 375 475 600 750 950 1275 1700 2250");
int getBinNumber( float value, std::vector<Double_t> bins ){

	 for( int bin = 0; bin < bins.size(); bin++ ){
         //std::cout << "Matching " << value << " and " << bins[bin] << " for " << bin << std::endl;
			if( bin == 0 ){ 
				if( value < bins[0] ) return 0;
			}
	      else{ 
				if( (value > bins[bin-1]) and (value <= bins[bin]) ) return bin; 
			}
	 }
    return bins.size();

}	 

void makeplots( const string califilename, const string infilename, const string outfilename ){

    std::cout << "Make plots with " << califilename <<  " " << infilename <<  " " << outfilename << std::endl;
    std::cout << "open input files" << std::endl;
    string disphotreename("disphotree");

    auto fInFile = TFile::Open(infilename.c_str(), "update");
    fInFile->cd();
    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());

    //auto fCaliFile = TFile::Open(califilename.c_str(), "update");
    //std::cout << "fInFile : " << fInFile  << " fInTree : " << fInTree << " fCaliFile : " << fCaliFile << std::endl;
    std::cout << "fInFile : " << fInFile  << " fInTree : " << fInTree << std::endl;

    string histoutfilename(outfilename+".root");
    TFile* fOutFile = new TFile( histoutfilename.c_str(), "RECREATE" );
    std::cout << "fOutFile : " << fOutFile << std::endl;


//     set branches to get from fInFile : fInTree
    std::cout << "Set branches to get from fInFile : fInTree" << std::endl;

    double phoseedtimeCaliIc_0(0.0);
    double phoseedtimeCaliIc_1(0.0);

    Float_t gZmass; 
    Float_t gdR;
    Float_t elTrackZ_0;
    Float_t elTrackZ_1;
    Float_t vtxZ;

    TBranch * b_gZmass; 
    TBranch * b_gdR;
    TBranch * b_elTrackZ_0;
    TBranch * b_elTrackZ_1;
    TBranch * b_vtxZ;

    Int_t   phoseedI1_0; // EB: iphi, EE: ix
    Int_t   phoseedI2_0; // EB: ieta, EE: iy
    Int_t   phoseedEcal_0; // EB, EM, EP
    Int_t   phoseedTT_0;
    Float_t phoseedE_0;
    Float_t phoseedadcToGeV_0;
    Float_t phoseedpedrms12_0;
    Float_t phoseedTOF_0;
    Float_t phoseedtime_0;
    Float_t phoseedtimeErr_0;

    Float_t phoseedamplitude_0;
    Float_t phoseedamplitudeError_0;
    Float_t phoseedkuMfootStctime_0;
    Float_t phoseedkuMfootStctimeErr_0;
    Float_t phoseedkuMfootCCStctime_0;
    Float_t phoseedkuMfootCCStctimeErr_0;
    Float_t phoseedootA0_0;
    Float_t phoseedootA1_0;
    Float_t phoseedootA2_0;
    Float_t phoseedootA3_0;
    Float_t phoseedootA4_0;
    Float_t phoseedootA5_0;
    Float_t phoseedootA6_0;
    Float_t phoseedootA7_0;
    Float_t phoseedootA8_0;
    Float_t phoseedootA9_0;
    Float_t phoseedkuamplitude_0;
    Float_t phoseedkuamplitudeError_0;
    Float_t phoseedkuootA0_0;
    Float_t phoseedkuootA1_0;
    Float_t phoseedkuootA2_0;
    Float_t phoseedkuootA3_0;
    Float_t phoseedkuootA4_0;
    Float_t phoseedkuootA5_0;
    Float_t phoseedkuootA6_0;
    Float_t phoseedkuootA7_0;
    Float_t phoseedkuootA8_0;
    Float_t phoseedkuootA9_0;


    TBranch * b_phoseedI1_0;
    TBranch * b_phoseedI2_0;
    TBranch * b_phoseedEcal_0;
    TBranch * b_phoseedTT_0;
    TBranch * b_phoseedE_0;
    TBranch * b_phoseedadcToGeV_0;
    TBranch * b_phoseedpedrms12_0;
    TBranch * b_phoseedTOF_0;
    TBranch * b_phoseedtime_0;
    TBranch * b_phoseedtimeErr_0;

    TBranch * b_phoseedamplitude_0;
    TBranch * b_phoseedamplitudeError_0;
    TBranch * b_phoseedkuMfootStctime_0;
    TBranch * b_phoseedkuMfootStctimeErr_0;
    TBranch * b_phoseedkuMfootCCStctime_0;
    TBranch * b_phoseedkuMfootCCStctimeErr_0;
    TBranch * b_phoseedootA0_0;
    TBranch * b_phoseedootA1_0;
    TBranch * b_phoseedootA2_0;
    TBranch * b_phoseedootA3_0;
    TBranch * b_phoseedootA4_0;
    TBranch * b_phoseedootA5_0;
    TBranch * b_phoseedootA6_0;
    TBranch * b_phoseedootA7_0;
    TBranch * b_phoseedootA8_0;
    TBranch * b_phoseedootA9_0;
    TBranch * b_phoseedkuamplitude_0;
    TBranch * b_phoseedkuamplitudeError_0;
    TBranch * b_phoseedkuootA0_0;
    TBranch * b_phoseedkuootA1_0;
    TBranch * b_phoseedkuootA2_0;
    TBranch * b_phoseedkuootA3_0;
    TBranch * b_phoseedkuootA4_0;
    TBranch * b_phoseedkuootA5_0;
    TBranch * b_phoseedkuootA6_0;
    TBranch * b_phoseedkuootA7_0;
    TBranch * b_phoseedkuootA8_0;
    TBranch * b_phoseedkuootA9_0;

    Int_t   phoseedI1_1; // EB: iphi, EE: ix
    Int_t   phoseedI2_1; // EB: ieta, EE: iy
    Int_t   phoseedEcal_1; // EB, EM, EP
    Int_t   phoseedTT_1;
    Float_t phoseedE_1;
    Float_t phoseedadcToGeV_1;
    Float_t phoseedpedrms12_1;
    Float_t phoseedTOF_1;
    Float_t phoseedtime_1;
    Float_t phoseedtimeErr_1;

    Float_t phoseedamplitude_1;
    Float_t phoseedamplitudeError_1;
    Float_t phoseedkuMfootStctime_1;
    Float_t phoseedkuMfootStctimeErr_1;
    Float_t phoseedkuMfootCCStctime_1;
    Float_t phoseedkuMfootCCStctimeErr_1;
    Float_t phoseedootA0_1;
    Float_t phoseedootA1_1;
    Float_t phoseedootA2_1;
    Float_t phoseedootA3_1;
    Float_t phoseedootA4_1;
    Float_t phoseedootA5_1;
    Float_t phoseedootA6_1;
    Float_t phoseedootA7_1;
    Float_t phoseedootA8_1;
    Float_t phoseedootA9_1;
    Float_t phoseedkuamplitude_1;
    Float_t phoseedkuamplitudeError_1;
    Float_t phoseedkuootA0_1;
    Float_t phoseedkuootA1_1;
    Float_t phoseedkuootA2_1;
    Float_t phoseedkuootA3_1;
    Float_t phoseedkuootA4_1;
    Float_t phoseedkuootA5_1;
    Float_t phoseedkuootA6_1;
    Float_t phoseedkuootA7_1;
    Float_t phoseedkuootA8_1;
    Float_t phoseedkuootA9_1;

    TBranch * b_phoseedI1_1;
    TBranch * b_phoseedI2_1;
    TBranch * b_phoseedEcal_1;
    TBranch * b_phoseedTT_1;
    TBranch * b_phoseedE_1;
    TBranch * b_phoseedadcToGeV_1;
    TBranch * b_phoseedpedrms12_1;
    TBranch * b_phoseedTOF_1;
    TBranch * b_phoseedtime_1;  
    TBranch * b_phoseedtimeErr_1; 
 
    TBranch * b_phoseedamplitude_1;
    TBranch * b_phoseedamplitudeError_1;
    TBranch * b_phoseedkuMfootStctime_1;
    TBranch * b_phoseedkuMfootStctimeErr_1;
    TBranch * b_phoseedkuMfootCCStctime_1;
    TBranch * b_phoseedkuMfootCCStctimeErr_1;
    TBranch * b_phoseedootA0_1;
    TBranch * b_phoseedootA1_1;
    TBranch * b_phoseedootA2_1;
    TBranch * b_phoseedootA3_1;
    TBranch * b_phoseedootA4_1;
    TBranch * b_phoseedootA5_1;
    TBranch * b_phoseedootA6_1;
    TBranch * b_phoseedootA7_1;
    TBranch * b_phoseedootA8_1;
    TBranch * b_phoseedootA9_1;
    TBranch * b_phoseedkuamplitude_1;
    TBranch * b_phoseedkuamplitudeError_1;
    TBranch * b_phoseedkuootA0_1;
    TBranch * b_phoseedkuootA1_1;
    TBranch * b_phoseedkuootA2_1;
    TBranch * b_phoseedkuootA3_1;
    TBranch * b_phoseedkuootA4_1;
    TBranch * b_phoseedkuootA5_1;
    TBranch * b_phoseedkuootA6_1;
    TBranch * b_phoseedkuootA7_1;
    TBranch * b_phoseedkuootA8_1;
    TBranch * b_phoseedkuootA9_1;

	 std::cout << "Setting Branch Addresses 1" << std::endl;
    //fInTree->SetBranchAddress("gZmass", &gZmass, &b_gZmass);
    //fInTree->SetBranchAddress("gdR", &gdR, &b_gdR);
    //fInTree->SetBranchAddress("elTrackZ_0", &elTrackZ_0, &b_elTrackZ_0);
    //fInTree->SetBranchAddress("elTrackZ_1", &elTrackZ_1, &b_elTrackZ_1);
    //fInTree->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);

    //fInTree->SetBranchAddress("phoseedI1_0", &phoseedI1_0, &b_phoseedI1_0);
    //fInTree->SetBranchAddress("phoseedI2_0", &phoseedI2_0, &b_phoseedI2_0);
    //fInTree->SetBranchAddress("phoseedEcal_0", &phoseedEcal_0, &b_phoseedEcal_0);
    fInTree->SetBranchAddress("phoseedTT_0", &phoseedTT_0, &b_phoseedTT_0);
    fInTree->SetBranchAddress("phoseedE_0", &phoseedE_0, &b_phoseedE_0);
    fInTree->SetBranchAddress("phoseedadcToGeV_0", &phoseedadcToGeV_0, &b_phoseedadcToGeV_0);
    fInTree->SetBranchAddress("phoseedpedrms12_0", &phoseedpedrms12_0, &b_phoseedpedrms12_0);
    fInTree->SetBranchAddress("phoseedTOF_0", &phoseedTOF_0, &b_phoseedTOF_0);
    fInTree->SetBranchAddress("phoseedtime_0", &phoseedtime_0, &b_phoseedtime_0);
    //string tvarname_0(tvarname+"_0");
    //fInTree->SetBranchAddress( tvarname_0.c_str(), &phoseedtime_0, &b_phoseedtime_0);
    //string tvarnameErr_0(tvarname+"Err_0");
    //fInTree->SetBranchAddress( tvarnameErr_0.c_str(), &phoseedtimeErr_0, &b_phoseedtimeErr_0);

    std::cout << "Setting Branch Addresses 2" << std::endl;
    fInTree->SetBranchAddress("phoseedamplitude_0", &phoseedamplitude_0, &b_phoseedamplitude_0); 
    fInTree->SetBranchAddress("phoseedamplitudeError_0", &phoseedamplitudeError_0, &b_phoseedamplitudeError_0);
    fInTree->SetBranchAddress("phoseedkuMfootStctime_0", &phoseedkuMfootStctime_0, &b_phoseedkuMfootStctime_0); 
    fInTree->SetBranchAddress("phoseedkuMfootStctimeErr_0", &phoseedkuMfootStctimeErr_0, &b_phoseedkuMfootStctimeErr_0);
    fInTree->SetBranchAddress("phoseedkuMfootCCStctime_0", &phoseedkuMfootCCStctime_0, &b_phoseedkuMfootCCStctime_0);
    fInTree->SetBranchAddress("phoseedkuMfootCCStctimeErr_0", &phoseedkuMfootCCStctimeErr_0, &b_phoseedkuMfootCCStctimeErr_0);
    fInTree->SetBranchAddress("phoseedootA0_0", &phoseedootA0_0, &b_phoseedootA0_0);
    fInTree->SetBranchAddress("phoseedootA1_0", &phoseedootA1_0, &b_phoseedootA1_0);
    fInTree->SetBranchAddress("phoseedootA2_0", &phoseedootA2_0, &b_phoseedootA2_0);
    fInTree->SetBranchAddress("phoseedootA3_0", &phoseedootA3_0, &b_phoseedootA3_0);
    fInTree->SetBranchAddress("phoseedootA4_0", &phoseedootA4_0, &b_phoseedootA4_0);
    //fInTree->SetBranchAddress("phoseedootA5_0", &phoseedootA5_0, &b_phoseedootA5_0);
    fInTree->SetBranchAddress("phoseedootA6_0", &phoseedootA6_0, &b_phoseedootA6_0);
    fInTree->SetBranchAddress("phoseedootA7_0", &phoseedootA7_0, &b_phoseedootA7_0);
    fInTree->SetBranchAddress("phoseedootA8_0", &phoseedootA8_0, &b_phoseedootA8_0);
    fInTree->SetBranchAddress("phoseedootA9_0", &phoseedootA9_0, &b_phoseedootA9_0);
    fInTree->SetBranchAddress("phoseedkuamplitude_0", &phoseedkuamplitude_0, &b_phoseedkuamplitude_0);
    fInTree->SetBranchAddress("phoseedkuamplitudeError_0", &phoseedkuamplitudeError_0, &b_phoseedkuamplitudeError_0);
    fInTree->SetBranchAddress("phoseedkuootA0_0", &phoseedkuootA0_0, &b_phoseedkuootA0_0);
    fInTree->SetBranchAddress("phoseedkuootA1_0", &phoseedkuootA1_0, &b_phoseedkuootA1_0);
    fInTree->SetBranchAddress("phoseedkuootA2_0", &phoseedkuootA2_0, &b_phoseedkuootA2_0);
    fInTree->SetBranchAddress("phoseedkuootA3_0", &phoseedkuootA3_0, &b_phoseedkuootA3_0);
    fInTree->SetBranchAddress("phoseedkuootA4_0", &phoseedkuootA4_0, &b_phoseedkuootA4_0);
    //fInTree->SetBranchAddress("phoseedkuootA5_0", &phoseedkuootA5_0, &b_phoseedkuootA5_0);
    fInTree->SetBranchAddress("phoseedkuootA6_0", &phoseedkuootA6_0, &b_phoseedkuootA6_0);
    fInTree->SetBranchAddress("phoseedkuootA7_0", &phoseedkuootA7_0, &b_phoseedkuootA7_0);
    fInTree->SetBranchAddress("phoseedkuootA8_0", &phoseedkuootA8_0, &b_phoseedkuootA8_0);
    fInTree->SetBranchAddress("phoseedkuootA9_0", &phoseedkuootA9_0, &b_phoseedkuootA9_0);

    std::cout << "Setting Branch Addresses 3" << std::endl;
    //fInTree->SetBranchAddress("phoseedI1_1", &phoseedI1_1, &b_phoseedI1_1);
    //fInTree->SetBranchAddress("phoseedI2_1", &phoseedI2_1, &b_phoseedI2_1);
    //fInTree->SetBranchAddress("phoseedEcal_1", &phoseedEcal_1, &b_phoseedEcal_1);
    fInTree->SetBranchAddress("phoseedTT_1", &phoseedTT_1, &b_phoseedTT_1);
    fInTree->SetBranchAddress("phoseedE_1", &phoseedE_1, &b_phoseedE_1);
    fInTree->SetBranchAddress("phoseedadcToGeV_1", &phoseedadcToGeV_1, &b_phoseedadcToGeV_1);
    fInTree->SetBranchAddress("phoseedpedrms12_1", &phoseedpedrms12_1, &b_phoseedpedrms12_1);
    fInTree->SetBranchAddress("phoseedTOF_1", &phoseedTOF_1, &b_phoseedTOF_1);
    fInTree->SetBranchAddress("phoseedtime_1", &phoseedtime_1, &b_phoseedtime_1);
    //string tvarname_1(tvarname+"_1");
    //fInTree->SetBranchAddress( tvarname_1.c_str(), &phoseedtime_1, &b_phoseedtime_1);
    //string tvarnameErr_1(tvarname+"Err_1");
    //fInTree->SetBranchAddress( tvarnameErr_1.c_str(), &phoseedtimeErr_1, &b_phoseedtimeErr_1);

    std::cout << "Setting Branch Addresses 4" << std::endl;
    fInTree->SetBranchAddress("phoseedamplitude_1", &phoseedamplitude_1, &b_phoseedamplitude_1);  
    fInTree->SetBranchAddress("phoseedamplitudeError_1", &phoseedamplitudeError_1, &b_phoseedamplitudeError_1); 
    fInTree->SetBranchAddress("phoseedkuMfootStctime_1", &phoseedkuMfootStctime_1, &b_phoseedkuMfootStctime_1);  
    fInTree->SetBranchAddress("phoseedkuMfootStctimeErr_1", &phoseedkuMfootStctimeErr_1, &b_phoseedkuMfootStctimeErr_1); 
    fInTree->SetBranchAddress("phoseedkuMfootCCStctime_1", &phoseedkuMfootCCStctime_1, &b_phoseedkuMfootCCStctime_1); 
    fInTree->SetBranchAddress("phoseedkuMfootCCStctimeErr_1", &phoseedkuMfootCCStctimeErr_1, &b_phoseedkuMfootCCStctimeErr_1); 
    fInTree->SetBranchAddress("phoseedootA0_1", &phoseedootA0_1, &b_phoseedootA0_1); 
    fInTree->SetBranchAddress("phoseedootA1_1", &phoseedootA1_1, &b_phoseedootA1_1); 
    fInTree->SetBranchAddress("phoseedootA2_1", &phoseedootA2_1, &b_phoseedootA2_1); 
    fInTree->SetBranchAddress("phoseedootA3_1", &phoseedootA3_1, &b_phoseedootA3_1); 
    fInTree->SetBranchAddress("phoseedootA4_1", &phoseedootA4_1, &b_phoseedootA4_1); 
    //fInTree->SetBranchAddress("phoseedootA5_1", &phoseedootA5_1, &b_phoseedootA5_1); 
    fInTree->SetBranchAddress("phoseedootA6_1", &phoseedootA6_1, &b_phoseedootA6_1); 
    fInTree->SetBranchAddress("phoseedootA7_1", &phoseedootA7_1, &b_phoseedootA7_1);
    fInTree->SetBranchAddress("phoseedootA8_1", &phoseedootA8_1, &b_phoseedootA8_1); 
    fInTree->SetBranchAddress("phoseedootA9_1", &phoseedootA9_1, &b_phoseedootA9_1); 
    fInTree->SetBranchAddress("phoseedkuamplitude_1", &phoseedkuamplitude_1, &b_phoseedkuamplitude_1); 
    fInTree->SetBranchAddress("phoseedkuamplitudeError_1", &phoseedkuamplitudeError_1, &b_phoseedkuamplitudeError_1); 
    fInTree->SetBranchAddress("phoseedkuootA0_1", &phoseedkuootA0_1, &b_phoseedkuootA0_1); 
    fInTree->SetBranchAddress("phoseedkuootA1_1", &phoseedkuootA1_1, &b_phoseedkuootA1_1); 
    fInTree->SetBranchAddress("phoseedkuootA2_1", &phoseedkuootA2_1, &b_phoseedkuootA2_1); 
    fInTree->SetBranchAddress("phoseedkuootA3_1", &phoseedkuootA3_1, &b_phoseedkuootA3_1); 
    fInTree->SetBranchAddress("phoseedkuootA4_1", &phoseedkuootA4_1, &b_phoseedkuootA4_1); 
    //fInTree->SetBranchAddress("phoseedkuootA5_1", &phoseedkuootA5_1, &b_phoseedkuootA5_1); 
    fInTree->SetBranchAddress("phoseedkuootA6_1", &phoseedkuootA6_1, &b_phoseedkuootA6_1); 
    fInTree->SetBranchAddress("phoseedkuootA7_1", &phoseedkuootA7_1, &b_phoseedkuootA7_1); 
    fInTree->SetBranchAddress("phoseedkuootA8_1", &phoseedkuootA8_1, &b_phoseedkuootA8_1); 
    fInTree->SetBranchAddress("phoseedkuootA9_1", &phoseedkuootA9_1, &b_phoseedkuootA9_1); 

    // >> calcs  <<
    std::cout << "Setting up plots " << std::endl;

    //string histname_dz0("hist_dz0");

    TH1F * hist_Ab[10]; 
    TH1F * hist_Aa[10]; 
    TH2F * hist_AavAb[10]; 
    TH1F * hist_dAab[10]; 
    TH2F * hist_dAabvt[10];
    TH2F * hist_dAabvi;
    TH2F * hist_Aavi;
    TH2F * hist_Abvi;

    string histname_Ab[10];
    string histname_Aa[10];
    string histname_AavAb[10];
    string histname_dAab[10];
    string histname_dAabvt[10];
    string histname_dAabvi("hist_dAabvi");
    string histname_Abvi("hist_Abvi");
    string histname_Aavi("hist_Aavi");

    for( int i = 0; i < 10; i++ ){
			auto si = to_string(i);
    		histname_Ab[i]="hist_Ab"+si;
    		histname_Aa[i]="hist_Aa"+si; 
    		histname_AavAb[i]="hist_AavAb"+si; 
    		histname_dAab[i]="hist_dAab"+si; 
    		histname_dAabvt[i]="hist_dAabvt"+si; 
    		//histname_dAabv[i]="hist_dAabv"+si; 

    }

    string histtitletmp("");
    //string fTitle1("Photon Seed Time [ns]");
    //string fTitle2("Photon Seed Time Calibrated [ns]");
    //string fTitle3("Photon Seed Time Filtered [ns]");
    //string fTitle4("Photon Seed Time Filtered Calibrated [ns]");
    //string fXTitle("A_{eff}/#sigma_{n} (EBEB)");
    //string fXxTitle("A_{0}/#sigma_{0} (EBEB)");
    //string fXyTitle("A_{1}/#sigma_{1} (EBEB)");
    //std::vector<Double_t> fXBins;
    //Bool_t fXVarBins = false;
    //string xbinstr("VARIABLE 75 100 125 150 175 225 275 325 375 475 600 750 950 1275 1700 2250");
    //std::vector<TString> fXLabels;
    //string fYTitle("#Delta(t) [ns] (EBEB)");
    //std::vector<Double_t> fYBins;
    //Bool_t fYVarBins = false;
    //string ybinstr("CONSTANT 30 -3 3");
    //string ybinstr("CONSTANT 480 -3 3");
    //std::vector<TString> fYLabels;
    //string fZmTitle("Mean #Delta(t)");
    //string fZrTitle("RMS #Delta(t)");
    //string fZoTitle("Occ #Delta(t)");

    //Common::SetupBins(xbinstr,fXBins,fXVarBins);
    //Common::SetupBins(ybinstr,fYBins,fYVarBins);

    //const auto xbins = &fXBins[0];
    //const auto ybins = &fYBins[0];

    int zdiv = 256;
    float zstart = 0.0;
    float zend = 9600.0;
    int dzdiv = 480;
    float dzstart = -80.0;
    float dzend = 80.0;

    //auto hist_dz0 = new TH1F(histname_dz0.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend);
    //hist_dz0->Sumw2();

    //auto hist_z0 = new TH1F(histname_z0.c_str(),histtitletmp.c_str(),zdiv,zstart,zend);
    //hist_z0->Sumw2();

    for( int i = 0; i < 10; i++ ){ 
    		hist_Ab[i] = new TH1F(histname_Ab[i].c_str(),histtitletmp.c_str(),zdiv,zstart,zend);
    		hist_Aa[i] = new TH1F(histname_Aa[i].c_str(),histtitletmp.c_str(),zdiv,zstart,zend);
    		hist_AavAb[i] = new TH2F(histname_AavAb[i].c_str(),histtitletmp.c_str(),zdiv,zstart,zend,zdiv,zstart,zend);
    		hist_dAab[i] = new TH1F(histname_dAab[i].c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend);
    		hist_dAabvt[i] = new TH2F(histname_dAabvt[i].c_str(),histtitletmp.c_str(),480,-6.0,6.0,dzdiv,dzstart,dzend);
    }
    int dml = zdiv*256;
    hist_dAabvi = new TH2F(histname_dAabvi.c_str(),histtitletmp.c_str(),10,-0.5,9.5,dzdiv,dzstart,dzend);
    hist_Abvi = new TH2F(histname_Abvi.c_str(),histtitletmp.c_str(),10,-0.5,9.5,dml,zstart,zend);
    hist_Aavi = new TH2F(histname_Aavi.c_str(),histtitletmp.c_str(),10,-0.5,9.5,dml,zstart,zend);

    std::cout << "Getting calibration values and filling hists" << std::endl;

    fInFile->cd();
    const auto nEntries = fInTree->GetEntries();
    for (auto entry = 0U; entry < nEntries; entry++){
        // if( entry%int(nEntries*0.1) == 0 ) std::cout << "Proccessed " << entry/nEntries << "\% of " << nEntries << " entries." << std::endl;
	     if( entry%1000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;        
        //std::cout << "Getting Entries" << std::endl;

	     fInFile->cd();

        //b_gZmass->GetEntry(entry);
        //b_gdR->GetEntry(entry);
        //b_elTrackZ_0->GetEntry(entry);
        //b_elTrackZ_1->GetEntry(entry);
        //b_vtxZ->GetEntry(entry);

        //b_phoseedI1_0->GetEntry(entry);
	     //b_phoseedI2_0->GetEntry(entry);	
	     //b_phoseedEcal_0->GetEntry(entry);
        //b_phoseedTT_0->GetEntry(entry);
        //b_phoseedE_0->GetEntry(entry);
        //b_phoseedadcToGeV_0->GetEntry(entry);
        //b_phoseedpedrms12_0->GetEntry(entry);
        b_phoseedTOF_0->GetEntry(entry);
        b_phoseedtime_0->GetEntry(entry);
        //b_phoseedtimeErr_0->GetEntry(entry);

        b_phoseedamplitude_0->GetEntry(entry);
        b_phoseedamplitudeError_0->GetEntry(entry);
        b_phoseedkuMfootStctime_0->GetEntry(entry);
        b_phoseedkuMfootStctimeErr_0->GetEntry(entry);
        b_phoseedkuMfootCCStctime_0->GetEntry(entry);
        b_phoseedkuMfootCCStctimeErr_0->GetEntry(entry);
        b_phoseedootA0_0->GetEntry(entry);
        b_phoseedootA1_0->GetEntry(entry);
        b_phoseedootA2_0->GetEntry(entry);
        b_phoseedootA3_0->GetEntry(entry);
        b_phoseedootA4_0->GetEntry(entry);
        //b_phoseedootA5_0->GetEntry(entry);
        b_phoseedootA6_0->GetEntry(entry);
        b_phoseedootA7_0->GetEntry(entry);
        b_phoseedootA8_0->GetEntry(entry);
        b_phoseedootA9_0->GetEntry(entry);
        b_phoseedkuamplitude_0->GetEntry(entry);
        b_phoseedkuamplitudeError_0->GetEntry(entry);
        b_phoseedkuootA0_0->GetEntry(entry);
        b_phoseedkuootA1_0->GetEntry(entry);
        b_phoseedkuootA2_0->GetEntry(entry);
        b_phoseedkuootA3_0->GetEntry(entry);
        b_phoseedkuootA4_0->GetEntry(entry);
        //b_phoseedkuootA5_0->GetEntry(entry);
        b_phoseedkuootA6_0->GetEntry(entry);
        b_phoseedkuootA7_0->GetEntry(entry);
        b_phoseedkuootA8_0->GetEntry(entry);
        b_phoseedkuootA9_0->GetEntry(entry);

        //b_phoseedI1_1->GetEntry(entry);
        //b_phoseedI2_1->GetEntry(entry);
        //b_phoseedEcal_1->GetEntry(entry);
        //b_phoseedTT_1->GetEntry(entry);
        //b_phoseedE_1->GetEntry(entry);
        //b_phoseedadcToGeV_1->GetEntry(entry);
        //b_phoseedpedrms12_1->GetEntry(entry);
        b_phoseedTOF_1->GetEntry(entry);
        b_phoseedtime_1->GetEntry(entry);
        //b_phoseedtimeErr_1->GetEntry(entry);

        b_phoseedamplitude_1->GetEntry(entry);
        b_phoseedamplitudeError_1->GetEntry(entry);
        b_phoseedkuMfootStctime_1->GetEntry(entry);
        b_phoseedkuMfootStctimeErr_1->GetEntry(entry);
        b_phoseedkuMfootCCStctime_1->GetEntry(entry);
        b_phoseedkuMfootCCStctimeErr_1->GetEntry(entry);
        b_phoseedootA0_1->GetEntry(entry);
        b_phoseedootA1_1->GetEntry(entry);
        b_phoseedootA2_1->GetEntry(entry);
        b_phoseedootA3_1->GetEntry(entry);
        b_phoseedootA4_1->GetEntry(entry);
        //b_phoseedootA5_1->GetEntry(entry);
        b_phoseedootA6_1->GetEntry(entry);
        b_phoseedootA7_1->GetEntry(entry);
        b_phoseedootA8_1->GetEntry(entry);
        b_phoseedootA9_1->GetEntry(entry);
        b_phoseedkuamplitude_1->GetEntry(entry);
        b_phoseedkuamplitudeError_1->GetEntry(entry);
        b_phoseedkuootA0_1->GetEntry(entry);
        b_phoseedkuootA1_1->GetEntry(entry);
        b_phoseedkuootA2_1->GetEntry(entry);
        b_phoseedkuootA3_1->GetEntry(entry);
        b_phoseedkuootA4_1->GetEntry(entry);
        //b_phoseedkuootA5_1->GetEntry(entry);
        b_phoseedkuootA6_1->GetEntry(entry);
        b_phoseedkuootA7_1->GetEntry(entry);
        b_phoseedkuootA8_1->GetEntry(entry);
        b_phoseedkuootA9_1->GetEntry(entry);

        ///////std::cout << "Fill Hists" << std::endl;
	     float amp_0[10] = { phoseedootA0_0, phoseedootA1_0, phoseedootA2_0, phoseedootA3_0, phoseedootA4_0, 
											(phoseedamplitude_0), phoseedootA6_0, phoseedootA7_0, phoseedootA8_0, phoseedootA9_0};
        float amp_1[10] = { phoseedootA0_1, phoseedootA1_1, phoseedootA2_1, phoseedootA3_1, phoseedootA4_1, 
											(phoseedamplitude_1), phoseedootA6_1, phoseedootA7_1, phoseedootA8_1, phoseedootA9_1};
        float ampku_0[10] = { phoseedkuootA0_0, phoseedkuootA1_0, phoseedkuootA2_0, phoseedkuootA3_0, phoseedkuootA4_0, 
											(phoseedkuamplitude_0), phoseedkuootA6_0, phoseedkuootA7_0, phoseedkuootA8_0, phoseedkuootA9_0};
        float ampku_1[10] = { phoseedkuootA0_1, phoseedkuootA1_1, phoseedkuootA2_1, phoseedkuootA3_1, phoseedkuootA4_1, 
											(phoseedkuamplitude_1), phoseedkuootA6_1, phoseedkuootA7_1, phoseedkuootA8_1, phoseedkuootA9_1};

        //hist_->Fill();
    	  for( int i = 0; i < 10; i++ ){  
         		hist_Ab[i]->Fill(ampku_1[i]);
               hist_Ab[i]->Fill(ampku_0[i]);  
         		hist_Aa[i]->Fill(amp_1[i]);
               hist_Aa[i]->Fill(amp_0[i]);
         		hist_AavAb[i]->Fill(amp_0[i],ampku_0[i]);
               hist_AavAb[i]->Fill(amp_1[i],ampku_1[i]);
         		hist_dAab[i]->Fill(amp_0[i]-ampku_0[i]);
               hist_dAab[i]->Fill(amp_1[i]-ampku_1[i]);
         		hist_dAabvt[i]->Fill(phoseedkuMfootStctime_0,amp_0[i]-ampku_0[i]);
               hist_dAabvt[i]->Fill(phoseedkuMfootStctime_1,amp_1[i]-ampku_1[i]);
               hist_dAabvi->Fill(i,amp_0[i]-ampku_0[i]);
               hist_dAabvi->Fill(i,amp_1[i]-ampku_1[i]);
               hist_Aavi->Fill(i,amp_1[i]);
               hist_Abvi->Fill(i,ampku_1[i]);
		  } 
    	  //hist_dAabvi->Fill();


    }


    //Common::Scale(theHist,false,fXVarBins,fYVarBins);
    fOutFile->cd();

    //hist_dz0->Write();
    for( int i = 0; i < 10; i++ ){  
         hist_Ab[i]->Write(); 
         hist_Aa[i]->Write();
         hist_AavAb[i]->Write();
         hist_dAab[i]->Write(); 
         hist_dAabvt[i]->Write();     
    } 
    hist_dAabvi->Write(); 
    hist_Aavi->Write();
    hist_Abvi->Write();

    //delete hist_dz0;
    for( int i = 0; i < 10; i++ ){  
         delete hist_Ab[i]; 
         delete hist_Aa[i]; 
         delete hist_AavAb[i]; 
         delete hist_dAab[i]; 
         delete hist_dAabvt[i];     
    } 
    delete hist_dAabvi; 
    delete hist_Abvi;
    delete hist_Aavi;

    delete fInFile;
    delete fOutFile;
    //delete fCaliFile;

    std::cout << "Thats all Folks!" << std::endl;
}


int main ( int argc, char *argv[] ){

        if( argc != 4 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                auto califilename = argv[1];
                auto infilename = argv[2];
                auto outfilename = argv[3];
                //auto tvarname = argv[4];
					 //auto calimapname = argv[5];
                //auto isd_type = argv[6];
                std::cout << " Running with " << califilename <<  " " << infilename <<  " " << outfilename <<  " " << std::endl;
      			 makeplots( califilename, infilename, outfilename );
        }
        return 1;
}

        //std::cout << "Fill 2D Hist" << std::endl;
        //auto skip = false;
        //auto skip_cali = false;
        //auto kscc_offset = 5000.f;
        //auto outlier = 1000.f;
        //auto offset = 0.f;
        //auto outlier_offset = 0.f;
        //if( tvarname == "phoseedkuMfootCCStctime" ) { outlier  = kscc_offset; } //std::cout << "KsCC ";} 
        //if( tvarname == "phoseedkuWtStctime" ) { outlier  = 500000; } //std::cout << "KsCC ";} 
        //if( (abs(phoseedtime_0 + offset - phoseedtimeCaliIc_0 ) > outlier) or (abs(phoseedtime_1 + offset - phoseedtimeCaliIc_1 ) > outlier) ) skip_cali = true;
        //if( (abs(phoseedtime_0 + offset ) > outlier) or (abs(phoseedtime_1 + offset ) > outlier) ) skip = true;
        //if( tvarname == "phoseedkuMfootCCStctime" ) { skip = false; }
        //if( ( phoseedtimeErr_0 < 0 ) or ( phoseedtimeErr_1 < 0  )  ) { skip = true; }

        //auto yfill = (phoseedtime_0-phoseedtimeCaliIc_0)-(phoseedtime_1-phoseedtimeCaliIc_1)+(phoseedTOF_0-phoseedTOF_1);
        //auto effa0 = (phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0;
        //auto effa0bin = getBinNumber( effa0, fXBins );
        //auto effa1 = (phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1;
        //auto effa1bin = getBinNumber( effa1, fXBins );
        //auto xfill = (effa0*effa1)/sqrt(pow(effa0,2)+pow(effa1,2));

        //auto e_cut = (phoseedE_0>=10)&&(phoseedE_0<=120)&&(phoseedE_1>=10)&&(phoseedE_1<=120);
        //auto eta_cut = (phoseedEcal_0 == ECAL::EB)&&(phoseedEcal_1 == ECAL::EB);
        //auto isd_cut = true; //inclusive
        //if( isd_type == "Different") isd_cut = (phoseedTT_0!=phoseedTT_1); //diffrent
        //if( isd_type == "Same") isd_cut = (phoseedTT_0==phoseedTT_1); //same
        //auto event_good = e_cut && eta_cut && isd_cut;

        //if( event_good and not skip ){
            //std::cout << "Filling " << effa0bin << " " << effa1bin << " with " << yfill << std::endl;
         // (thetdHist[effa0bin][effa1bin])->Fill(yfill);
        //}
