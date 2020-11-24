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

    //std::cout << "Make plots with " << califilename <<  " " << infilename <<  " " << outfilename << std::endl;
    std::cout << "open input files" << std::endl;
    string disphotreename("disphotree");

    auto fInFile = TFile::Open(infilename.c_str(), "update");
    fInFile->cd();
    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());

    //string calimapname("E5");
    string calimapname("none");
    auto fCaliFile = TFile::Open(califilename.c_str(), "update");
    std::cout << "fInFile : " << fInFile  << " fInTree : " << fInTree << " fCaliFile : " << fCaliFile << std::endl;

    //string histoutfilename(outfilename+"_cali_"+calimapname+".root");
    string histoutfilename(outfilename+".root");
    TFile* fOutFile = new TFile( histoutfilename.c_str(), "RECREATE" );
    std::cout << "fOutFile : " << fOutFile << std::endl;

//     set branches to get from fInFile : fInTree
//	 tvarname_mini='phoseedtime'
//	 tvarname_ku='phoseedkutime'
//	 tvarname_kuStc='phoseedkuStctime'
//	 tvarname_kuNotStc='phoseedkuNotStctime'
//	 tvarname_kuWtStc='phoseedkuWtStctime'
//	 tvarname_kuWootStc='phoseedkuWootStctime'
//	 tvarname_kuMfootStc='phoseedkuMfootStctime'
//	 tvarname_kuMfootCCStc='phoseedkuMfootCCStctime'
    std::cout << "set branches to get from fInFile : fInTree" << std::endl;

    double icPC_0(0.0);
    double icPC_1(0.0);
    double ic0_0(0.0);
    double ic0_1(0.0);
    double ic1_0(0.0);
    double ic1_1(0.0);
    double ic2_0(0.0);
    double ic2_1(0.0);
    double ic2b_0(0.0);
    double ic2b_1(0.0);
    double ic3_0(0.0);
    double ic3_1(0.0);
    double ic4_0(0.0);
    double ic4_1(0.0);

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
    Float_t phoseedpcTOF_0;
    Float_t phoseedtime_0;
    Float_t phoseedtimeErr_0;
    Float_t phoseedpcmulti_0;
    Float_t phoseedpctime_0;
    Float_t phoseedpce_0;
    Float_t phoseedkuNotStctime_0;
    Float_t phoseedkuWtStctime_0;
    Float_t phoseedkuWootStctime_0;
    Float_t phoseedkuMfootStctime_0;
    Float_t phoseedkuMfootCCStctime_0;

    TBranch * b_phoseedI1_0;
    TBranch * b_phoseedI2_0;
    TBranch * b_phoseedEcal_0;
    TBranch * b_phoseedTT_0;
    TBranch * b_phoseedE_0;
    TBranch * b_phoseedadcToGeV_0;
    TBranch * b_phoseedpedrms12_0;
    TBranch * b_phoseedTOF_0;
    TBranch * b_phoseedpcTOF_0;
    TBranch * b_phoseedtime_0;
    TBranch * b_phoseedtimeErr_0;
    TBranch * b_phoseedpcmulti_0;
    TBranch * b_phoseedpctime_0;
    TBranch * b_phoseedpce_0;
    TBranch * b_phoseedkuNotStctime_0;
    TBranch * b_phoseedkuWtStctime_0;
    TBranch * b_phoseedkuWootStctime_0;
    TBranch * b_phoseedkuMfootStctime_0;
    TBranch * b_phoseedkuMfootCCStctime_0;

    Int_t   phoseedI1_1; // EB: iphi, EE: ix
    Int_t   phoseedI2_1; // EB: ieta, EE: iy
    Int_t   phoseedEcal_1; // EB, EM, EP
    Int_t   phoseedTT_1;
    Float_t phoseedE_1;
    Float_t phoseedadcToGeV_1;
    Float_t phoseedpedrms12_1;
    Float_t phoseedTOF_1;
    Float_t phoseedpcTOF_1;
    Float_t phoseedtime_1;
    Float_t phoseedtimeErr_1;
    Float_t phoseedpcmulti_1;
    Float_t phoseedpctime_1;
    Float_t phoseedpce_1;
    Float_t phoseedkuNotStctime_1;
    Float_t phoseedkuWtStctime_1;
    Float_t phoseedkuWootStctime_1;
    Float_t phoseedkuMfootStctime_1;
    Float_t phoseedkuMfootCCStctime_1;

    TBranch * b_phoseedI1_1;
    TBranch * b_phoseedI2_1;
    TBranch * b_phoseedEcal_1;
    TBranch * b_phoseedTT_1;
    TBranch * b_phoseedE_1;
    TBranch * b_phoseedadcToGeV_1;
    TBranch * b_phoseedpedrms12_1;
    TBranch * b_phoseedTOF_1;
    TBranch * b_phoseedpcTOF_1;
    TBranch * b_phoseedtime_1;  
    TBranch * b_phoseedtimeErr_1;
    TBranch * b_phoseedpcmulti_1; 
    TBranch * b_phoseedpctime_1;
    TBranch * b_phoseedpce_1;
    TBranch * b_phoseedkuNotStctime_1; 
    TBranch * b_phoseedkuWtStctime_1;
    TBranch * b_phoseedkuWootStctime_1;
    TBranch * b_phoseedkuMfootStctime_1;
    TBranch * b_phoseedkuMfootCCStctime_1;

    fInTree->SetBranchAddress("gZmass", &gZmass, &b_gZmass);
    fInTree->SetBranchAddress("gdR", &gdR, &b_gdR);
    fInTree->SetBranchAddress("elTrackZ_0", &elTrackZ_0, &b_elTrackZ_0);
    fInTree->SetBranchAddress("elTrackZ_1", &elTrackZ_1, &b_elTrackZ_1);
    fInTree->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);

    fInTree->SetBranchAddress("phoseedI1_0", &phoseedI1_0, &b_phoseedI1_0);
    fInTree->SetBranchAddress("phoseedI2_0", &phoseedI2_0, &b_phoseedI2_0);
    fInTree->SetBranchAddress("phoseedEcal_0", &phoseedEcal_0, &b_phoseedEcal_0);
    fInTree->SetBranchAddress("phoseedTT_0", &phoseedTT_0, &b_phoseedTT_0);
    fInTree->SetBranchAddress("phoseedE_0", &phoseedE_0, &b_phoseedE_0);
    fInTree->SetBranchAddress("phoseedadcToGeV_0", &phoseedadcToGeV_0, &b_phoseedadcToGeV_0);
    fInTree->SetBranchAddress("phoseedpedrms12_0", &phoseedpedrms12_0, &b_phoseedpedrms12_0);
    fInTree->SetBranchAddress("phoseedTOF_0", &phoseedTOF_0, &b_phoseedTOF_0);
    fInTree->SetBranchAddress("phoseedpcTOF_0", &phoseedpcTOF_0, &b_phoseedpcTOF_0);
    fInTree->SetBranchAddress("phoseedtime_0", &phoseedtime_0, &b_phoseedtime_0);
    fInTree->SetBranchAddress("phoseedpcmulti_0", &phoseedpcmulti_0, &b_phoseedpcmulti_0);
    fInTree->SetBranchAddress("phoseedpctime_0", &phoseedpctime_0, &b_phoseedpctime_0);
    fInTree->SetBranchAddress("phoseedpce_0", &phoseedpce_0, &b_phoseedpce_0);
    //fInTree->SetBranchAddress("phoseedpcltime_0", &phoseedpctime_0, &b_phoseedpctime_0);
    //fInTree->SetBranchAddress("phoseedPcalotime_0", &phoseedpctime_0, &b_phoseedpctime_0);
    fInTree->SetBranchAddress("phoseedkuNotStctime_0", &phoseedkuNotStctime_0, &b_phoseedkuNotStctime_0);
    fInTree->SetBranchAddress("phoseedkuWtStctime_0", &phoseedkuWtStctime_0, &b_phoseedkuWtStctime_0);
    fInTree->SetBranchAddress("phoseedkuWootStctime_0", &phoseedkuWootStctime_0, &b_phoseedkuWootStctime_0);
    fInTree->SetBranchAddress("phoseedkuMfootStctime_0", &phoseedkuMfootStctime_0, &b_phoseedkuMfootStctime_0);
    fInTree->SetBranchAddress("phoseedkuMfootCCStctime_0", &phoseedkuMfootCCStctime_0, &b_phoseedkuMfootCCStctime_0);
    //string tvarname_0(tvarname+"_0");
    //fInTree->SetBranchAddress( tvarname_0.c_str(), &phoseedtime_0, &b_phoseedtime_0);
    //string tvarnameErr_0(tvarname+"Err_0");
    //fInTree->SetBranchAddress( tvarnameErr_0.c_str(), &phoseedtimeErr_0, &b_phoseedtimeErr_0);

    fInTree->SetBranchAddress("phoseedI1_1", &phoseedI1_1, &b_phoseedI1_1);
    fInTree->SetBranchAddress("phoseedI2_1", &phoseedI2_1, &b_phoseedI2_1);
    fInTree->SetBranchAddress("phoseedEcal_1", &phoseedEcal_1, &b_phoseedEcal_1);
    fInTree->SetBranchAddress("phoseedTT_1", &phoseedTT_1, &b_phoseedTT_1);
    fInTree->SetBranchAddress("phoseedE_1", &phoseedE_1, &b_phoseedE_1);
    fInTree->SetBranchAddress("phoseedadcToGeV_1", &phoseedadcToGeV_1, &b_phoseedadcToGeV_1);
    fInTree->SetBranchAddress("phoseedpedrms12_1", &phoseedpedrms12_1, &b_phoseedpedrms12_1);
    fInTree->SetBranchAddress("phoseedTOF_1", &phoseedTOF_1, &b_phoseedTOF_1);
    fInTree->SetBranchAddress("phoseedpcTOF_1", &phoseedpcTOF_1, &b_phoseedpcTOF_1);
    fInTree->SetBranchAddress("phoseedkuNotStctime_1", &phoseedkuNotStctime_1, &b_phoseedkuNotStctime_1);
    fInTree->SetBranchAddress("phoseedtime_1", &phoseedtime_1, &b_phoseedtime_1);
    fInTree->SetBranchAddress("phoseedpcmulti_1", &phoseedpcmulti_1, &b_phoseedpcmulti_1);
    fInTree->SetBranchAddress("phoseedpctime_1", &phoseedpctime_1, &b_phoseedpctime_1);
    fInTree->SetBranchAddress("phoseedpce_1", &phoseedpce_1, &b_phoseedpce_1);
    //fInTree->SetBranchAddress("phoseedpcltime_1", &phoseedpctime_1, &b_phoseedpctime_1);
    //fInTree->SetBranchAddress("phoseedPcalotime_1", &phoseedpctime_1, &b_phoseedpctime_1);
    fInTree->SetBranchAddress("phoseedkuWtStctime_1", &phoseedkuWtStctime_1, &b_phoseedkuWtStctime_1);
    fInTree->SetBranchAddress("phoseedkuWootStctime_1", &phoseedkuWootStctime_1, &b_phoseedkuWootStctime_1);
    fInTree->SetBranchAddress("phoseedkuMfootStctime_1", &phoseedkuMfootStctime_1, &b_phoseedkuMfootStctime_1);
    fInTree->SetBranchAddress("phoseedkuMfootCCStctime_1", &phoseedkuMfootCCStctime_1, &b_phoseedkuMfootCCStctime_1);
    //string tvarname_1(tvarname+"_1");
    //fInTree->SetBranchAddress( tvarname_1.c_str(), &phoseedtime_1, &b_phoseedtime_1);
    //string tvarnameErr_1(tvarname+"Err_1");
    //fInTree->SetBranchAddress( tvarnameErr_1.c_str(), &phoseedtimeErr_1, &b_phoseedtimeErr_1);


    // >> calcs  <<
    //std::cout << "Setting up 2D plot for " << cmbs << std::endl;

    string histname_dz0("hist_dz0");
    string histname_dz1("hist_dz1");
    string histname_adz01("hist_adz01");
    string histname_dz0v1("hist_dz0v1");
    string histname_ddz01("hist_ddz01");
    string histname_z0("hist_z0");
    string histname_z1("hist_z1");
    string histname_z0v1("hist_z0v1");
    string histname_dz0z1("hist_dz0z1");
    string histname_adz01vdz0z1("hist_adz01vdz0z1");
    string histname_adz01vgzmass("hist_adz01vgzmass");
    string histname_adz01vdt("hist_adz01vdt");
    string histname_gzmassvdt("hist_gzmassvdt");

    string histname_pctvratio("hist_pctvratio");
    string histname_pctvwt("hist_pctvwt");
    string histname_pctvkutmf("hist_pctvkutmf");
    string histname_pctvkucc("hist_pctvkucc");

    string histname_dpctvdratio("hist_dpctvdratio");
    string histname_dpctvdwt("hist_dpctvdwt");
    string histname_dpctvdkutmf("hist_dpctvdkutmf");
    string histname_dpctvdkucc("hist_dpctvdkucc");

    string histname_dratiovdwt("hist_dratiovdwt");
    string histname_dratiovdkutmf("hist_dratiovdkutmf");
    string histname_dratiovdkucc("hist_dratiovdkucc");

    string histname_pcalo("hist_pcalo");
    string histname_rawpcalo("hist_rawpcalo");
    string histname_pcTOF("hist_pcTOF");
    string histname_ratio("hist_ratio");
    string histname_wt("hist_wt");
    string histname_kutmf("hist_kutmf");
    string histname_kucc("hist_kucc");
    string histname_kunot("hist_kunot");
    string histname_dummy("hist_dummy");

    string histname_ratiovwt("hist_ratiovwt");
    string histname_ratiovkutmf("hist_ratiovkutmf");
    string histname_ratiovkucc("hist_ratiovkucc");

    string histname_pcalova("hist_pcalova");
    string histname_ratiova("hist_ratiova");
    string histname_wtva("hist_wtva");
    string histname_kutmfva("hist_kutmfva");
    string histname_kuccva("hist_kuccva");

    string histtitletmp("");

    string histname_data("Data_Hist");
    string histname_data_profile("Data_Hist_Profile");
    string histname_data_rt("Data_Hist_rt");
    string histname_data_wt("Data_Hist_wt");
    string histname_data_tmf("Data_Hist_tmf");
    string histname_data_cc("Data_Hist_cc");
    string histname_data_not("Data_Hist_not");
    string histname_data_dum("Data_Hist_dum");
    string histname_data_prt("Data_Hist_Profile_rt");
    string histname_data_pwt("Data_Hist_Profile_wt");
    string histname_data_ptmf("Data_Hist_Profile_tmf");
    string histname_data_pcc("Data_Hist_Profile_cc");
    string histname_data_pnot("Data_Hist_Profile_not");
    string histname_data_pdum("Data_Hist_Profile_dum");
    string fTitle("#Delta(Photon Seed Time) [ns] vs. A_{eff}/#sigma_{n} (EBEB)");
    string fXTitle("A_{eff}/#sigma_{n} (EBEB)");
    std::vector<Double_t> fXBins;
    Bool_t fXVarBins = false;
    //string xbinstr("VARIABLE 75 100 125 150 175 225 275 325 375 475 600 750 950 1275 1700 2250");
    //string xbinstr("VARIABLE 0 2 4 6 8 10 12 14 16 20 24 30 38 52 68 100");
    string xbinstr("VARIABLE 4 6 7 8 9 12 20");
    //int nMyBins = 17;
    int nMyBins = 9;
    string fYTitle("#Delta(Photon Seed Time) [ns] (EBEB)");
    std::vector<Double_t> fYBins;
    Bool_t fYVarBins = false;
    //string ybinstr("CONSTANT 1536 -6 6");
    string ybinstr("CONSTANT 256 -4 4");
    Common::SetupBins(xbinstr,fXBins,fXVarBins);
    Common::SetupBins(ybinstr,fYBins,fYVarBins);
    const auto xbins = &fXBins[0];
    const auto ybins = &fYBins[0];
    auto theHist = new TH2F(histname_data.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist->GetYaxis()->SetTitle(fYTitle.c_str());
    theHist->Sumw2();

    std::cout << "Setting up Data Hist " << std::endl;
    auto theHist_rt = new TH2F(histname_data_rt.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_rt->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_rt->GetYaxis()->SetTitle("#Delta(pcalo-Ratio) [ns] (EBEB)");
    theHist_rt->Sumw2();
    auto theHist_wt = new TH2F(histname_data_wt.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_wt->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_wt->GetYaxis()->SetTitle("#Delta(pcalo-Wt) [ns] (EBEB)");
    theHist_wt->Sumw2();
    auto theHist_tmf = new TH2F(histname_data_tmf.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_tmf->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_tmf->GetYaxis()->SetTitle("#Delta(pcalo-KUTMF) [ns] (EBEB)");
    theHist_tmf->Sumw2();
    auto theHist_cc = new TH2F(histname_data_cc.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_cc->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_cc->GetYaxis()->SetTitle("#Delta(pcalo-KUCC) [ns] (EBEB)");
    theHist_cc->Sumw2();
    auto theHist_not = new TH2F(histname_data_not.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_not->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_not->GetYaxis()->SetTitle("#Delta(pcalo-KUNot) [ns] (EBEB)");
    theHist_not->Sumw2();
    auto theHist_dum = new TH2F(histname_data_dum.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_dum->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_dum->GetYaxis()->SetTitle("#Delta(pcalo-Dummy) [ns] (EBEB)");
    theHist_dum->Sumw2();

    float tdiv = 256;
    float tstart = -10;
    float tend = 10;

    float tpdiv = 512;
    float tpstart = 0;
    float tpend = 40;

    float stddiv = 256;
    //  +/- 2 sd
    float pcalotdiv = stddiv;
    //float pcalotstart = 1.9884;
    //float pcalotstart = 3.7;
    //float pcalotstart = -0.0537;
    //float pcalotstart = -0.6987;
    float pcalotstart = -2.0;
    //float pcalotend = 3.6536;//1.6652
    //float pcalotend = 6.3;//1.495
    //float pcalotend = 0.6539;//0.7076
    //float pcalotend = 1.3013;//2
    float pcalotend = 2.0;//8

    float ratiotdiv = stddiv;
    //float ratiotstart = -1.609;
    //float ratiotstart = -1.2075;
    float ratiotstart = -2.0;
    //float ratiotend = 1.2522;//2.8612
    //float ratiotend = 0.7925;//2
    float ratiotend = 2.0;//2

    float wttdiv = stddiv;
    //float wttstart = -0.9237;
    //float wttstart = -0.6546;
    float wttstart = -2.0;
    //float wttend = 1.5635; //2.4872
    //float wttend = 1.3454; //2
    float wttend = 2.0; //2

    float kutmftdiv = stddiv;
    //float kutmftstart = -0.6794;
    //float kutmftstart = -0.93381;
    float kutmftstart = -2.0;
    //float kutmftend = 0.637;//1.3164
    //float kutmftend = 1.06619;//2
    float kutmftend = 2.0;//2

    float kucctdiv = stddiv;
    //float kucctstart = -3.4418;
    //float kucctstart = -2.96;
    float kucctstart = -2.0;
    //float kucctend = -1.1082;//2.3336
    //float kucctend = -0.96;//2
    float kucctend = 2.0;//2

    float dtdiv = stddiv;
    float dtstart = -2;
    float dtend = 2;

    auto hist_data_profile = new TH1F(histname_data_profile.c_str(),histtitletmp.c_str(),1536,-6.0,6.0);
    hist_data_profile->Sumw2();

    std::cout << "Setting up Data Hist Profile" << std::endl;
    auto hist_data_prt = new TH1F(histname_data_prt.c_str(),histtitletmp.c_str(),1536,-6.0,6.0);
    hist_data_prt->Sumw2();
    auto hist_data_pwt = new TH1F(histname_data_pwt.c_str(),histtitletmp.c_str(),1536,-6.0,6.0);
    hist_data_pwt->Sumw2();
    auto hist_data_ptmf = new TH1F(histname_data_ptmf.c_str(),histtitletmp.c_str(),1536,-6.0,6.0);
    hist_data_ptmf->Sumw2();
    auto hist_data_pcc = new TH1F(histname_data_pcc.c_str(),histtitletmp.c_str(),1536,-6.0,6.0);
    hist_data_pcc->Sumw2();
    auto hist_data_pnot = new TH1F(histname_data_pnot.c_str(),histtitletmp.c_str(),1536,-6.0,6.0);
    hist_data_pnot->Sumw2();
    auto hist_data_pdum = new TH1F(histname_data_pdum.c_str(),histtitletmp.c_str(),1536,-6.0,6.0);
    hist_data_pdum->Sumw2();

    auto hist_ratio = new TH1F(histname_ratio.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_ratio->Sumw2();
    auto hist_pcalo = new TH1F(histname_pcalo.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_pcalo->Sumw2();
    auto hist_pcTOF = new TH1F(histname_pcTOF.c_str(),histtitletmp.c_str(),tpdiv,tpstart,tpend);
    hist_pcTOF->Sumw2();
    auto hist_rawpcalo = new TH1F(histname_rawpcalo.c_str(),histtitletmp.c_str(),tpdiv,tpstart,tpend);
    hist_rawpcalo->Sumw2();
    auto hist_wt = new TH1F(histname_wt.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_wt->Sumw2();
    auto hist_kutmf = new TH1F(histname_kutmf.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_kutmf->Sumw2();
    auto hist_kucc = new TH1F(histname_kucc.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_kucc->Sumw2();
    auto hist_kunot = new TH1F(histname_kunot.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_kunot->Sumw2();
    auto hist_dummy = new TH1F(histname_dummy.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_dummy->Sumw2();

    auto hist_pctvratio = new TH2F(histname_pctvratio.c_str(),histtitletmp.c_str(),ratiotdiv,ratiotstart,ratiotend,pcalotdiv,pcalotstart,pcalotend);
    hist_pctvratio->Sumw2();
    auto hist_pctvwt = new TH2F(histname_pctvwt.c_str(),histtitletmp.c_str(),wttdiv,wttstart,wttend,pcalotdiv,pcalotstart,pcalotend);
    hist_pctvwt->Sumw2();
    auto hist_pctvkutmf = new TH2F(histname_pctvkutmf.c_str(),histtitletmp.c_str(),kutmftdiv,kutmftstart,kutmftend,pcalotdiv,pcalotstart,pcalotend);
    hist_pctvkutmf->Sumw2();
    auto hist_pctvkucc = new TH2F(histname_pctvkucc.c_str(),histtitletmp.c_str(),kucctdiv,kucctstart,kucctend,pcalotdiv,pcalotstart,pcalotend);
    hist_pctvkucc->Sumw2();

//    auto hist_dpctvdratio = new TH2F(histname_dpctvdratio.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
//    hist_dpctvdratio->Sumw2();
//    auto hist_dpctvdwt = new TH2F(histname_dpctvdwt.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
//    hist_dpctvdwt->Sumw2();
//    auto hist_dpctvdkutmf = new TH2F(histname_dpctvdkutmf.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
//    hist_dpctvdkutmf->Sumw2();
//    auto hist_dpctvdkucc = new TH2F(histname_dpctvdkucc.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
//    hist_dpctvdkucc->Sumw2();
//
//    auto hist_dratiovdwt = new TH2F(histname_dratiovdwt.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
//    hist_dratiovdwt->Sumw2();
//    auto hist_dratiovdkutmf = new TH2F(histname_dratiovdkutmf.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
//    hist_dratiovdkutmf->Sumw2();
//    auto hist_dratiovdkucc = new TH2F(histname_dratiovdkucc.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
//    hist_dratiovdkucc->Sumw2();
//
//    auto hist_ratiovwt = new TH2F(histname_ratiovwt.c_str(),histtitletmp.c_str(),wttdiv,wttstart,wttend,ratiotdiv,ratiotstart,ratiotend);
//    hist_ratiovwt->Sumw2();
//    auto hist_ratiovkutmf = new TH2F(histname_ratiovkutmf.c_str(),histtitletmp.c_str(),kutmftdiv,kutmftstart,kutmftend,ratiotdiv,ratiotstart,ratiotend);
//    hist_ratiovkutmf->Sumw2();
//    auto hist_ratiovkucc = new TH2F(histname_ratiovkucc.c_str(),histtitletmp.c_str(),kucctdiv,kucctstart,kucctend,ratiotdiv,ratiotstart,ratiotend);
//    hist_ratiovkucc->Sumw2();
//
//    auto hist_ratiova = new TH2F(histname_ratiova.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
//    hist_ratiova->Sumw2();
//    auto hist_pcalova = new TH2F(histname_pcalova.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
//    hist_pcalova->Sumw2();
//    auto hist_wtva = new TH2F(histname_wtva.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
//    hist_wtva->Sumw2();
//    auto hist_kutmfva = new TH2F(histname_kutmfva.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
//    hist_kutmfva->Sumw2();
//    auto hist_kuccva = new TH2F(histname_kuccva.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
//    hist_kuccva->Sumw2();

    //std::cout << "Getting calibration values and plotting for " << cmbs << std::endl;
//     get maps from fCaliFile
    std::cout << "get maps from fCaliFile" << std::endl;
    fCaliFile->cd();
    string cmbs0("AveXtalRtOOTStcRecTime");
    //string cmbs("AveXtalRtStcRecTimeE5");
    string cmbs1("AveXtalMiniRecTime");
    string cmbs2("AveXtalWtStcRecTime");
    string cmbs3("AveXtalMfootStcRecTime");
    string cmbs4("AveXtalMfootCCStcRecTime");
    string cmbs2b("AveXtalWtOOTStcRecTime");

    //string cmbs(calimapname);
    //string itcnt("_i95");
    string itcnt("");
    string ebmapstringPC("AveXtaldpCaloTimeRecTimeEBMap");
    string ebmapstring0(cmbs0+"EBMap"+itcnt);
    string ebmapstring1(cmbs1+"EBMap"+itcnt);
    string ebmapstring2(cmbs2+"EBMap"+itcnt);
    string ebmapstring2b(cmbs2b+"EBMap"+itcnt);
    string ebmapstring3(cmbs3+"EBMap"+itcnt);
    string ebmapstring4(cmbs4+"EBMap"+itcnt);
    //string epmapstring(cmbs+"EPMap"+itcnt);
    string epmapstring0(cmbs0+"EPMap"+itcnt);
    string epmapstring1(cmbs1+"EPMap"+itcnt);
    string epmapstring2(cmbs2+"EPMap"+itcnt);
    string epmapstring2b(cmbs2b+"EPMap"+itcnt);
    string epmapstring3(cmbs3+"EPMap"+itcnt);
    string epmapstring4(cmbs4+"EPMap"+itcnt);
    //string emmapstring(cmbs+"EMMap"+itcnt);
    string emmapstring0(cmbs0+"EMMap"+itcnt);
    string emmapstring1(cmbs1+"EMMap"+itcnt);
    string emmapstring2(cmbs2+"EMMap"+itcnt);
    string emmapstring2b(cmbs2b+"EMMap"+itcnt);
    string emmapstring3(cmbs3+"EMMap"+itcnt);
    string emmapstring4(cmbs4+"EMMap"+itcnt);

    auto ebmapicPC = (TH2F*)fInFile->Get(ebmapstringPC.c_str());

    auto ebmapic0 = (TH2F*)fCaliFile->Get(ebmapstring0.c_str());
    auto ebmapic1 = (TH2F*)fCaliFile->Get(ebmapstring1.c_str());
    auto ebmapic2 = (TH2F*)fCaliFile->Get(ebmapstring2.c_str());
    auto ebmapic2b = (TH2F*)fCaliFile->Get(ebmapstring2b.c_str());
    auto ebmapic3 = (TH2F*)fCaliFile->Get(ebmapstring3.c_str());
    auto ebmapic4 = (TH2F*)fCaliFile->Get(ebmapstring4.c_str());
    //auto epmapic = (TH2F*)fCaliFile->Get(epmapstring.c_str());
    auto epmapic1 = (TH2F*)fCaliFile->Get(epmapstring1.c_str());
    auto epmapic2 = (TH2F*)fCaliFile->Get(epmapstring2.c_str());
    auto epmapic3 = (TH2F*)fCaliFile->Get(epmapstring3.c_str());
    auto epmapic4 = (TH2F*)fCaliFile->Get(epmapstring4.c_str());
    //auto emmapic = (TH2F*)fCaliFile->Get(emmapstring.c_str());
    auto emmapic1 = (TH2F*)fCaliFile->Get(emmapstring1.c_str());
    auto emmapic2 = (TH2F*)fCaliFile->Get(emmapstring2.c_str());
    auto emmapic3 = (TH2F*)fCaliFile->Get(emmapstring3.c_str());
    auto emmapic4 = (TH2F*)fCaliFile->Get(emmapstring4.c_str());
    //std::cout << " Ic hists for " << cmbs << std::endl;
    std::cout << "  " << ebmapstring0 << " : " << ebmapic0 << std::endl;
    std::cout << "  " << ebmapstring1 << " : " << ebmapic1 << std::endl;
    std::cout << "  " << ebmapstring2 << " : " << ebmapic2 << std::endl;
    std::cout << "  " << ebmapstring2b << " : " << ebmapic2b << std::endl;
    std::cout << "  " << ebmapstring3 << " : " << ebmapic3 << std::endl;
    std::cout << "  " << ebmapstring4 << " : " << ebmapic4 << std::endl;
    //std::cout << "  " << epmapstring << " : " << epmapic << std::endl;
    //std::cout << "  " << emmapstring << " : " << emmapic << std::endl;


    fInFile->cd();
    const auto nEntries = fInTree->GetEntries();
    auto counter = 0;
    for (auto entry = 0U; entry < nEntries; entry++){
        // if( entry%int(nEntries*0.1) == 0 ) std::cout << "Proccessed " << entry/nEntries << "\% of " << nEntries << " entries." << std::endl;
	     if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;        
        //std::cout << "Getting Entries Pho 0" << std::endl;
        //if( counter > 25082 ) continue;
        //if( counter > 3865 ) continue;
	     fInFile->cd();

        //b_gZmass->GetEntry(entry);
        //b_gdR->GetEntry(entry);
        //b_elTrackZ_0->GetEntry(entry);
        //b_elTrackZ_1->GetEntry(entry);
        //b_vtxZ->GetEntry(entry);

        b_phoseedI1_0->GetEntry(entry);
	     b_phoseedI2_0->GetEntry(entry);	
	     b_phoseedEcal_0->GetEntry(entry);
        b_phoseedTT_0->GetEntry(entry);
        b_phoseedE_0->GetEntry(entry);
        b_phoseedadcToGeV_0->GetEntry(entry);
        b_phoseedpedrms12_0->GetEntry(entry);
        b_phoseedTOF_0->GetEntry(entry);
        //std::cout << "half way 0" << std::endl;
        b_phoseedpcTOF_0->GetEntry(entry);
        b_phoseedtime_0->GetEntry(entry);
        //b_phoseedtimeErr_0->GetEntry(entry);
        b_phoseedpcmulti_0->GetEntry(entry);
        b_phoseedpctime_0->GetEntry(entry);
        b_phoseedpce_0->GetEntry(entry);
        //std::cout << "3/4 way 0" << std::endl;
        b_phoseedkuNotStctime_0->GetEntry(entry);
        b_phoseedkuWtStctime_0->GetEntry(entry);
        b_phoseedkuWootStctime_0->GetEntry(entry);
        b_phoseedkuMfootStctime_0->GetEntry(entry);
        b_phoseedkuMfootCCStctime_0->GetEntry(entry);

        //std::cout << "Getting Entries Pho 1" << std::endl;

        b_phoseedI1_1->GetEntry(entry);
        b_phoseedI2_1->GetEntry(entry);
        b_phoseedEcal_1->GetEntry(entry);
        b_phoseedTT_1->GetEntry(entry);
        b_phoseedE_1->GetEntry(entry);
        b_phoseedadcToGeV_1->GetEntry(entry);
        b_phoseedpedrms12_1->GetEntry(entry);
        b_phoseedTOF_1->GetEntry(entry);
        b_phoseedpcTOF_1->GetEntry(entry);
        b_phoseedtime_1->GetEntry(entry);
        //b_phoseedtimeErr_1->GetEntry(entry);
        b_phoseedpcmulti_1->GetEntry(entry);
        b_phoseedpctime_1->GetEntry(entry);
        b_phoseedpce_1->GetEntry(entry);
        b_phoseedkuNotStctime_1->GetEntry(entry);
        b_phoseedkuWtStctime_1->GetEntry(entry);
        b_phoseedkuWootStctime_1->GetEntry(entry);
        b_phoseedkuMfootStctime_1->GetEntry(entry);
        b_phoseedkuMfootCCStctime_1->GetEntry(entry);

        //std::cout << "Fill Hists" << std::endl;
        //if( (phoseedE_0 < 5.f) or (phoseedE_1 < 5.f) ) continue;

        //auto amp_0 = (phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0;
        auto amp_0 = phoseedpce_0;
        //auto amp_1 = (phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1;
        auto amp_1 = phoseedpce_1;
        auto effA = (amp_0*amp_1)/sqrt((amp_0*amp_0)+(amp_1*amp_1));

        //if( (amp_0 < 10.f) or (amp_1 < 10.f) ) continue;
        //if( effA < 20.f ) continue;
        //if( (phoseedEcal_0 == ECAL::EB) || (phoseedEcal_1 == ECAL::EB) ) continue;
        if( (phoseedEcal_0 == ECAL::EP) || (phoseedEcal_1 == ECAL::EP) ) continue;
        if( (phoseedEcal_0 == ECAL::EM) || (phoseedEcal_1 == ECAL::EM) ) continue;
        //if( not( phoseedI2_0 == phoseedI2_1 ) ) continue; // ieta
        //if( not( phoseedI1_0 == phoseedI1_1 ) ) continue; // iphi
        //std::cout << " ------------------- " << std::endl;
        //std::cout << " ieta : " << phoseedI2_0 << " - " << phoseedI2_1 << std::endl;
        //std::cout << " iphi : " << phoseedI1_0 << " - " << phoseedI1_1 << std::endl;
        //if( phoseedrhID > 840000000 ){ continue; }
        //if( phoseedpctime_0 < 0.0 ){ continue; }

        int bin_offset = 86;

        if( calimapname != "none" ){
               if ( phoseedEcal_0 == ECAL::EB ){
                        icPC_0 = ebmapicPC->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
                        ic0_0 = ebmapic0->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
                        ic1_0 = ebmapic1->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
                        ic2_0 = ebmapic2->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
                        ic2b_0 = ebmapic2b->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
                        ic3_0 = ebmapic3->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
                        ic4_0 = ebmapic4->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
               }else if ( phoseedEcal_0 == ECAL::EP ){
                        ic1_0 = epmapic1->GetBinContent( phoseedI2_0, phoseedI1_0 );
                        ic2_0 = epmapic2->GetBinContent( phoseedI2_0, phoseedI1_0 );
                        ic3_0 = epmapic3->GetBinContent( phoseedI2_0, phoseedI1_0 );
                        ic4_0 = epmapic4->GetBinContent( phoseedI2_0, phoseedI1_0 );
               }else if (phoseedEcal_0 == ECAL::EM ){
                        ic1_0 = emmapic1->GetBinContent( phoseedI2_0, phoseedI1_0 );
                        ic2_0 = emmapic2->GetBinContent( phoseedI2_0, phoseedI1_0 );
                        ic3_0 = emmapic3->GetBinContent( phoseedI2_0, phoseedI1_0 );
                        ic4_0 = emmapic4->GetBinContent( phoseedI2_0, phoseedI1_0 );
               }

               if ( phoseedEcal_1 == ECAL::EB ){
                        icPC_1 = ebmapicPC->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 );
                        ic0_1 = ebmapic0->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 );
                        ic1_1 = ebmapic1->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 );
                        ic2_1 = ebmapic2->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 );
                        ic2b_1 = ebmapic2b->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 );
                        ic3_1 = ebmapic3->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 );
                        ic4_1 = ebmapic4->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 );
               }else if ( phoseedEcal_1 == ECAL::EP ){
                        ic1_1 = epmapic1->GetBinContent( phoseedI2_1, phoseedI1_1 );
                        ic2_1 = epmapic2->GetBinContent( phoseedI2_1, phoseedI1_1 );
                        ic3_1 = epmapic3->GetBinContent( phoseedI2_1, phoseedI1_1 );
                        ic4_1 = epmapic4->GetBinContent( phoseedI2_1, phoseedI1_1 );
               }else if (phoseedEcal_1 == ECAL::EM ){
                        ic1_1 = emmapic1->GetBinContent( phoseedI2_1, phoseedI1_1 );
                        ic2_0 = emmapic2->GetBinContent( phoseedI2_1, phoseedI1_1 );
                        ic3_0 = emmapic3->GetBinContent( phoseedI2_1, phoseedI1_1 );
                        ic4_0 = emmapic4->GetBinContent( phoseedI2_1, phoseedI1_1 );
               }
        }

        auto tof_cor_0 = phoseedTOF_0;
        auto tof_cor_1 = phoseedTOF_1;

		  auto time_0 = phoseedtime_0 + tof_cor_0 - ic1_0;
        auto time_1 = phoseedtime_1 + tof_cor_1 - ic1_1;

        auto kuNotStctime_0 = phoseedkuNotStctime_0 + tof_cor_0 - ic0_0;
        auto kuNotStctime_1 = phoseedkuNotStctime_1 + tof_cor_1 - ic0_1;
        auto kuWtStctime_0 = phoseedkuWtStctime_0 + tof_cor_0 - ic2_0;
        auto kuWtStctime_1 = phoseedkuWtStctime_1 + tof_cor_1 - ic2_1;
        auto kuWootStctime_0 = phoseedkuWootStctime_0 + tof_cor_0 - ic2b_0;
        auto kuWootStctime_1 = phoseedkuWootStctime_1 + tof_cor_1 - ic2b_1;
        auto kuMfootStctime_0 = phoseedkuMfootStctime_0 + tof_cor_0 - ic3_0;
        auto kuMfootStctime_1 = phoseedkuMfootStctime_1 + tof_cor_1 - ic3_1;
        auto kuMfootCCStctime_0 = phoseedkuMfootCCStctime_0 + tof_cor_0 - ic4_0;
        auto kuMfootCCStctime_1 = phoseedkuMfootCCStctime_1 + tof_cor_1 - ic4_1;

        //auto time_0 = phoseedtime_0 - ic1_0;
        //auto time_1 = phoseedtime_1 - ic1_1;
        //auto kuWtStctime_0 = phoseedkuWtStctime_0 - ic2_0;
        //auto kuWtStctime_1 = phoseedkuWtStctime_1 - ic2_1;
        //auto kuMfootStctime_0 = phoseedkuMfootStctime_0 - ic3_0;
        //auto kuMfootStctime_1 = phoseedkuMfootStctime_1 - ic3_1;
        //auto kuMfootCCStctime_0 = phoseedkuMfootCCStctime_0 - ic4_0;
        //auto kuMfootCCStctime_1 = phoseedkuMfootCCStctime_1 - ic4_1;

        if( (phoseedpctime_0 < 0.0 ) || (phoseedpctime_1 < 0.0 ) )  continue;
        auto pctime_0 = phoseedpctime_0 - phoseedpcTOF_0;
        //auto pctime_0 = phoseedpctime_0;
        //auto pctime_0c = phoseedpctime_0; // - icPC_0;
        //auto pctime_0c = phoseedpctime_0 - icPC_0;
        auto pctime_1 = phoseedpctime_1 - phoseedpcTOF_1;
        //auto pctime_1 = phoseedpctime_1;
        //auto pctime_1c = phoseedpctime_1;  // - icPC_1;
        //auto pctime_1c = phoseedpctime_1 - icPC_1;

        auto yfillrt0 = pctime_0 - time_0;
        auto yfillrt1 = pctime_1 - time_1;
        auto yfillnot0 = pctime_0 - kuNotStctime_0;
        auto yfillnot1 = pctime_1 - kuNotStctime_1;
        auto yfillwt0 = pctime_0 - kuWtStctime_0;
        auto yfillwt1 = pctime_1 - kuWtStctime_1;
        auto yfilldum0 = pctime_0 - kuWootStctime_0;
        auto yfilldum1 = pctime_1 - kuWootStctime_1;
        auto yfilltmf0 = pctime_0 - kuMfootStctime_0;
        auto yfilltmf1 = pctime_1 - kuMfootStctime_1;
        auto yfillcc0 = pctime_0 - kuMfootCCStctime_0;
        auto yfillcc1 = pctime_1 - kuMfootCCStctime_1;
        auto yfill = pctime_0 - pctime_1;
        auto yfillc = (pctime_0 - pctime_1) - icPC_0;

        //auto effa0 = ((phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0)/sqrt(2);
        auto effa0 = phoseedpce_0/sqrt(2);
        //auto effa1 = ((phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1)/sqrt(2);
        auto effa1 = phoseedpce_1/sqrt(2);
        auto xfill = (effa0*effa1)/sqrt(pow(effa0,2)+pow(effa1,2));

        auto e_cut = (phoseedE_0>=10)&&(phoseedE_0<=120)&&(phoseedE_1>=10)&&(phoseedE_1<=120);
        auto eta_cut = (phoseedEcal_0 == ECAL::EB)&&(phoseedEcal_1 == ECAL::EB);
        //auto isd_cut = true; //inclusive
        auto pccut = (phoseedpctime_0>0)&&(phoseedpctime_1>0);
        //auto isd_cut = (phoseedTT_0!=phoseedTT_1); //diffrent
        auto isd_cut = (phoseedTT_0==phoseedTT_1); //same
      //auto multi_cut = ((phoseedpcmulti_0 == 1)&&(phoseedpcmulti_1 > 1))||((phoseedpcmulti_0 > 1)&&(phoseedpcmulti_1 == 1)); 
        auto multi_cut = true;
        auto event_good = e_cut && eta_cut && isd_cut && pccut && multi_cut;

        if( event_good ){ 
            counter++;
            theHist->Fill(xfill,yfill);
            hist_data_profile->Fill(yfill);
        //}

            theHist_rt->Fill(effa0,yfillrt0);
            hist_data_prt->Fill(yfillrt0);
            theHist_wt->Fill(effa0,yfillwt0);
            hist_data_pwt->Fill(yfillwt0);
            theHist_not->Fill(effa0,yfillnot0);
            hist_data_pnot->Fill(yfillnot0);
            theHist_dum->Fill(effa0,yfilldum0);
            hist_data_pdum->Fill(yfilldum0);
            theHist_tmf->Fill(effa0,yfilltmf0);
            hist_data_ptmf->Fill(yfilltmf0);
            theHist_cc->Fill(effa0,yfillcc0);
            hist_data_pcc->Fill(yfillcc0);

            theHist_rt->Fill(effa1,yfillrt1);
            hist_data_prt->Fill(yfillrt1);
            theHist_wt->Fill(effa1,yfillwt1);
            hist_data_pwt->Fill(yfillwt1);
            theHist_not->Fill(effa1,yfillnot1);
            hist_data_pnot->Fill(yfillnot1);
            theHist_dum->Fill(effa1,yfilldum1);
            hist_data_pdum->Fill(yfilldum1);
            theHist_tmf->Fill(effa1,yfilltmf1);
            hist_data_ptmf->Fill(yfilltmf1);
            theHist_cc->Fill(effa1,yfillcc1);
            hist_data_pcc->Fill(yfillcc1);

		  hist_ratio->Fill(time_0);
        hist_pcalo->Fill(pctime_0);
        hist_rawpcalo->Fill(phoseedpctime_0);
        hist_pcTOF->Fill(phoseedpcTOF_0);
        hist_wt->Fill(kuWtStctime_0);
        hist_kutmf->Fill(kuMfootStctime_0);
        hist_kucc->Fill(kuMfootCCStctime_0);
        hist_kunot->Fill(kuNotStctime_0);
        hist_dummy->Fill(kuWootStctime_0);

        //hist_ratiova->Fill(amp_0,time_0);
        //hist_pcalova->Fill(amp_0,pctime_0);
        //hist_wtva->Fill(amp_0,kuWtStctime_0);
        //hist_kutmfva->Fill(amp_0,kuMfootStctime_0);
        //hist_kuccva->Fill(amp_0,kuMfootCCStctime_0);

        hist_ratio->Fill(time_1);
        hist_pcalo->Fill(pctime_1);
        hist_rawpcalo->Fill(phoseedpctime_1);
        hist_pcTOF->Fill(phoseedpcTOF_1);
        hist_wt->Fill(kuWtStctime_1);
        hist_kutmf->Fill(kuMfootStctime_1);
        hist_kucc->Fill(kuMfootCCStctime_1);
        hist_kunot->Fill(kuNotStctime_1);
        hist_dummy->Fill(kuWootStctime_1);

        //hist_ratiova->Fill(amp_1,time_1);
        //hist_pcalova->Fill(amp_1,pctime_1);
        //hist_wtva->Fill(amp_1,kuWtStctime_1);
        //hist_kutmfva->Fill(amp_1,kuMfootStctime_1);
        //hist_kuccva->Fill(amp_1,kuMfootCCStctime_1);

        hist_pctvratio->Fill(time_0,pctime_0);
        hist_pctvwt->Fill(kuWtStctime_0,pctime_0);
        hist_pctvkutmf->Fill(kuMfootStctime_0,pctime_0);
        hist_pctvkucc->Fill(kuMfootCCStctime_0,pctime_0);

        hist_pctvratio->Fill(time_1,pctime_1);
        hist_pctvwt->Fill(kuWtStctime_1,pctime_1);
        hist_pctvkutmf->Fill(kuMfootStctime_1,pctime_1);
        hist_pctvkucc->Fill(kuMfootCCStctime_1,pctime_1);

        //hist_dpctvdratio->Fill(time_0-time_1,pctime_0-pctime_1);
        //hist_dpctvdwt->Fill(kuWtStctime_0-kuWtStctime_1,pctime_0-pctime_1);
        //hist_dpctvdkutmf->Fill(kuMfootStctime_0-kuMfootStctime_1,pctime_0-pctime_1);
        //hist_dpctvdkucc->Fill(kuMfootCCStctime_0-kuMfootCCStctime_1,pctime_0-pctime_1);

        //hist_dratiovdwt->Fill(kuWtStctime_0-kuWtStctime_1,time_0-time_1);
        //hist_dratiovdkutmf->Fill(kuMfootStctime_0-kuMfootStctime_1,time_0-time_1);
        //hist_dratiovdkucc->Fill(kuMfootCCStctime_0-kuMfootCCStctime_1,time_0-time_1);

        //hist_ratiovwt->Fill(kuWtStctime_0,time_0);
        //hist_ratiovkutmf->Fill(kuMfootStctime_0,time_0);
        //hist_ratiovkucc->Fill(kuMfootCCStctime_0,time_0);

        //hist_ratiovwt->Fill(kuWtStctime_1,time_1);
        //hist_ratiovkutmf->Fill(kuMfootStctime_1,time_1);
        //hist_ratiovkucc->Fill(kuMfootCCStctime_1,time_1);
        } // if event good 
    }

    Common::Scale(theHist,false,fXVarBins,fYVarBins);

    fOutFile->cd();

    theHist->Write();
    hist_data_profile->Write();

    theHist_rt->Write();
    hist_data_prt->Write();
    theHist_wt->Write();
    hist_data_pwt->Write();
    theHist_not->Write();
    hist_data_pnot->Write();
    theHist_dum->Write();
    hist_data_pdum->Write();
    theHist_tmf->Write();
    hist_data_ptmf->Write();
    theHist_cc->Write();
    hist_data_pcc->Write();

    hist_ratio->Write();
    hist_pcalo->Write();
    hist_rawpcalo->Write();
    hist_pcTOF->Write();
    hist_wt->Write();
    hist_kutmf->Write();
    hist_kucc->Write();
    hist_kunot->Write();
    hist_dummy->Write();

    //hist_ratiova->Write();
    //hist_pcalova->Write();
    //hist_wtva->Write();
    //hist_kutmfva->Write();
    //hist_kuccva->Write();

    hist_pctvratio->Write();
    hist_pctvwt->Write();
    hist_pctvkutmf->Write();
    hist_pctvkucc->Write();

    //hist_dpctvdratio->Write();
    //hist_dpctvdwt->Write();
    //hist_dpctvdkutmf->Write();
    //hist_dpctvdkucc->Write();

    //hist_dratiovdwt->Write();
    //hist_dratiovdkutmf->Write();
    //hist_dratiovdkucc->Write();

    //hist_ratiovwt->Write();
    //hist_ratiovkutmf->Write();
    //hist_ratiovkucc->Write();

    delete theHist;
    delete hist_data_profile;

    delete theHist_rt;
    delete hist_data_prt;
    delete theHist_wt;
    delete hist_data_pwt;
    delete theHist_dum;
    delete hist_data_pdum;
    delete theHist_not;
    delete hist_data_pnot;
    delete theHist_cc;
    delete hist_data_pcc;
    delete theHist_tmf;
    delete hist_data_ptmf;

    delete hist_pctvratio;
    delete hist_pctvwt;
    delete hist_pctvkutmf;
    delete hist_pctvkucc;

    //delete hist_dpctvdratio;
    //delete hist_dpctvdwt;
    //delete hist_dpctvdkutmf;
    //delete hist_dpctvdkucc;

    //delete hist_dratiovdwt;
    //delete hist_dratiovdkutmf;
    //delete hist_dratiovdkucc;

    //delete hist_ratiovwt;
    //delete hist_ratiovkutmf;
    //delete hist_ratiovkucc;

    delete hist_ratio;
    delete hist_pcalo;
    delete hist_rawpcalo;
    delete hist_pcTOF;
    delete hist_wt;
    delete hist_kutmf;
    delete hist_kucc;
    delete hist_kunot;
    delete hist_dummy;

    //delete hist_ratiova;
    //delete hist_pcalova;
    //delete hist_wtva;
    //delete hist_kutmfva;
    //delete hist_kuccva;

    delete fInFile;
    delete fOutFile;
    delete fCaliFile;

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
