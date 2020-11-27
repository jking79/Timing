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

//enum ECAL {EB, EM, EP, NONE};
std::string ecal_config_path("/home/t3-ku/jaking/ecaltiming/CMSSW_10_2_5/src/Timing/TimingAnalyzer/macros/ecal_config/");

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

void makeplots( const string califilename, const string infilename, const string outfilename ){

    //std::cout << "Make plots with " << califilename <<  " " << infilename <<  " " << outfilename << std::endl;
    std::cout << "open input files" << std::endl;
    string disphotreename("tree/disphotree");

    auto fInFile = TFile::Open(infilename.c_str(), "update");
    fInFile->cd();
    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());

    //string calimapname("E5");
    string calimapname("none");
    //auto fCaliFile = TFile::Open(califilename.c_str(), "update");
    //std::cout << "fInFile : " << fInFile  << " fInTree : "; 
    //std::cout << fInTree << " fCaliFile : " << fCaliFile << std::endl;

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

    std::vector<Float_t> * X = 0;
    std::vector<Float_t> * Y = 0;
    std::vector<Float_t> * Z = 0;
    std::vector<Float_t> * E = 0;
    std::vector<Float_t> * time = 0;
    std::vector<Float_t> * timeErr = 0;
    std::vector<Float_t> * TOF = 0;
    std::vector<Float_t> * pcTOF = 0;
    std::vector<double> * pCalotime = 0;
    std::vector<UInt_t>  * rhID = 0;
    std::vector<Float_t> * adcToGeV = 0;
    std::vector<Float_t> * pedrms12 = 0;

    //std::vector<Float_t> * kuStcrhtime = 0;
    //std::vector<Float_t> * kuStcrhtimeErr = 0;
    //std::vector<UInt_t>  * kuStcrhID = 0;

    std::vector<Float_t> * kuNotStcrhtime = 0;
    std::vector<Float_t> * kuNotStcrhtimeErr = 0;
    std::vector<UInt_t>  * kuNotStcrhID = 0;

    std::vector<Float_t> * kuWtStcrhtime = 0;
    std::vector<Float_t> * kuWtStcrhtimeErr = 0;
    std::vector<UInt_t>  * kuWtStcrhID = 0;

    std::vector<Float_t> * kuWootStcrhtime = 0;
    std::vector<Float_t> * kuWootStcrhtimeErr = 0;
    std::vector<UInt_t>  * kuWootStcrhID = 0;

    std::vector<Float_t> * kuMfootStcrhtime = 0;
    std::vector<Float_t> * kuMfootStcrhtimeErr = 0;
    std::vector<UInt_t>  * kuMfootStcrhID = 0;

    std::vector<Float_t> * kuMfootCCStcrhtime = 0;
    std::vector<Float_t> * kuMfootCCStcrhtimeErr = 0;
    std::vector<UInt_t>  * kuMfootCCStcrhID = 0;

    TBranch * b_X;
    TBranch * b_Y;
    TBranch * b_Z;
    TBranch * b_E;
    TBranch * b_time;
    TBranch * b_pCalotime;
    TBranch * b_timeErr;
    TBranch * b_TOF;
    TBranch * b_pcTOF;
    TBranch * b_rhID;

    TBranch * b_adcToGeV;
    TBranch * b_pedrms12;

    //TBranch * b_kuStcrhtime;
    //TBranch * b_kuStcrhtimeErr;
    //TBranch * b_kuStcrhID;

    TBranch * b_kuNotStcrhtime;
    TBranch * b_kuNotStcrhtimeErr;
    TBranch * b_kuNotStcrhID;

    TBranch * b_kuWtStcrhtime;
    TBranch * b_kuWtStcrhtimeErr;
    TBranch * b_kuWtStcrhID;

    TBranch * b_kuWootStcrhtime;
    TBranch * b_kuWootStcrhtimeErr;
    TBranch * b_kuWootStcrhID;

    TBranch * b_kuMfootStcrhtime;
    TBranch * b_kuMfootStcrhtimeErr;
    TBranch * b_kuMfootStcrhID;

    TBranch * b_kuMfootCCStcrhtime;
    TBranch * b_kuMfootCCStcrhtimeErr;
    TBranch * b_kuMfootCCStcrhID;

    fInTree->SetBranchAddress("rhX", &X, &b_X);
    fInTree->SetBranchAddress("rhY", &Y, &b_Y);
    fInTree->SetBranchAddress("rhZ", &Z, &b_Z);
    fInTree->SetBranchAddress("rhE", &E, &b_E);
    fInTree->SetBranchAddress("rhtime", &time, &b_time);
    fInTree->SetBranchAddress("pCalotime", &pCalotime, &b_pCalotime);
    fInTree->SetBranchAddress("rhtimeErr", &timeErr, &b_timeErr);
    fInTree->SetBranchAddress("rhTOF", &TOF, &b_TOF);
    fInTree->SetBranchAddress("rhpcTOF", &pcTOF, &b_pcTOF);
    fInTree->SetBranchAddress("rhID", &rhID, &b_rhID);

    fInTree->SetBranchAddress("rhadcToGeV", &adcToGeV, &b_adcToGeV);
    fInTree->SetBranchAddress("rhpedrms12", &pedrms12, &b_pedrms12);

   //fInTree->SetBranchAddress("kuStcrhtime", &kuStcrhtime, &b_kuStcrhtime);
   //fInTree->SetBranchAddress("kuStcrhtimeErr", &kuStcrhtimeErr, &b_kuStcrhtimeErr);
   //fInTree->SetBranchAddress("kuStcrhID", &kuStcrhID, &b_kuStcrhID);

   fInTree->SetBranchAddress("kuNotStcrhtime", &kuNotStcrhtime, &b_kuNotStcrhtime);
   fInTree->SetBranchAddress("kuNotStcrhtimeErr", &kuNotStcrhtimeErr, &b_kuNotStcrhtimeErr);
   fInTree->SetBranchAddress("kuNotStcrhID", &kuNotStcrhID, &b_kuNotStcrhID);

   fInTree->SetBranchAddress("kuWtStcrhtime", &kuWtStcrhtime, &b_kuWtStcrhtime);
   fInTree->SetBranchAddress("kuWtStcrhtimeErr", &kuWtStcrhtimeErr, &b_kuWtStcrhtimeErr);
   fInTree->SetBranchAddress("kuWtStcrhID", &kuWtStcrhID, &b_kuWtStcrhID);

   fInTree->SetBranchAddress("kuWootStcrhtime", &kuWootStcrhtime, &b_kuWootStcrhtime);
   fInTree->SetBranchAddress("kuWootStcrhtimeErr", &kuWootStcrhtimeErr, &b_kuWootStcrhtimeErr);
   fInTree->SetBranchAddress("kuWootStcrhID", &kuWootStcrhID, &b_kuWootStcrhID);

   fInTree->SetBranchAddress("kuMfootStcrhtime", &kuMfootStcrhtime, &b_kuMfootStcrhtime);
   fInTree->SetBranchAddress("kuMfootStcrhtimeErr", &kuMfootStcrhtimeErr, &b_kuMfootStcrhtimeErr);
   fInTree->SetBranchAddress("kuMfootStcrhID", &kuMfootStcrhID, &b_kuMfootStcrhID);

   fInTree->SetBranchAddress("kuMfootCCStcrhtime", &kuMfootCCStcrhtime, &b_kuMfootCCStcrhtime);
   fInTree->SetBranchAddress("kuMfootCCStcrhtimeErr", &kuMfootCCStcrhtimeErr, &b_kuMfootCCStcrhtimeErr);
   fInTree->SetBranchAddress("kuMfootCCStcrhID", &kuMfootCCStcrhID, &b_kuMfootCCStcrhID);

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

    std::cout << "Setting up Data Hist" << std::endl;
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
    string xbinstr("VARIABLE 75 100 125 150 175 225 275 325 375 475 600 750 950 1275 1700 2250");
    int nMyBins = 17;
    string fYTitle("#Delta(Photon Seed Time) [ns] (EBEB)");
    std::vector<Double_t> fYBins;
    Bool_t fYVarBins = false;
    //string ybinstr("CONSTANT 1536 -6 6");
    string ybinstr("CONSTANT 256 -4 4");
    Common::SetupBins(xbinstr,fXBins,fXVarBins);
    Common::SetupBins(ybinstr,fYBins,fYVarBins);
    const auto xbins = &fXBins[0];
    const auto ybins = &fYBins[0];

    std::cout << "Setting up Data Hist " << std::endl;
    auto theHist_rt = new TH2F(histname_data_rt.c_str(),fTitle.c_str(),
												fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_rt->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_rt->GetYaxis()->SetTitle("#Delta(pcalo-Ratio) [ns] (EBEB)");
    theHist_rt->Sumw2();
    auto theHist_wt = new TH2F(histname_data_wt.c_str(),fTitle.c_str(),
												fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_wt->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_wt->GetYaxis()->SetTitle("#Delta(pcalo-Wt) [ns] (EBEB)");
    theHist_wt->Sumw2();
    auto theHist_tmf = new TH2F(histname_data_tmf.c_str(),fTitle.c_str(),
												fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_tmf->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_tmf->GetYaxis()->SetTitle("#Delta(pcalo-KUTMF) [ns] (EBEB)");
    theHist_tmf->Sumw2();
    auto theHist_cc = new TH2F(histname_data_cc.c_str(),fTitle.c_str(),
												fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_cc->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_cc->GetYaxis()->SetTitle("#Delta(pcalo-KUCC) [ns] (EBEB)");
    theHist_cc->Sumw2();
    auto theHist_not = new TH2F(histname_data_not.c_str(),fTitle.c_str(),
												fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_not->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_not->GetYaxis()->SetTitle("#Delta(pcalo-KUNot) [ns] (EBEB)");
    theHist_not->Sumw2();

    auto theHist_dum = new TH2F(histname_data_dum.c_str(),fTitle.c_str(),
												fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    theHist_dum->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist_dum->GetYaxis()->SetTitle("#Delta(pcalo-Dummy) [ns] (EBEB)");
    theHist_dum->Sumw2();

    float tdiv = 256;
    float tstart = -6;
    float tend = 6;

    //  +/- 2 sd
    float stddiv = 128;
    float pcalotdiv = stddiv;
    float pcalotstart = -4.0;
    float pcalotend = 4.0;//2

    float ratiotdiv = stddiv;
    float ratiotstart = -4.0;
    float ratiotend = 4.0;//2

    float wttdiv = stddiv;
    float wttstart = -4.0;
    float wttend = 4.0; //2

    float kutmftdiv = stddiv;
    float kutmftstart = -4.0;
    float kutmftend = 4.0;//2

    float kucctdiv = stddiv;
    float kucctstart = -4.0;
    float kucctend = -4.0;//2

    float dtdiv = stddiv;
    float dtstart = -4.0;
    float dtend = 4.0;

    std::cout << "Setting up Data Hist Profile" << std::endl;
    auto hist_data_prt = new TH1F(histname_data_prt.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_data_prt->Sumw2();
    auto hist_data_pwt = new TH1F(histname_data_pwt.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_data_pwt->Sumw2();
    auto hist_data_ptmf = new TH1F(histname_data_ptmf.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_data_ptmf->Sumw2();
    auto hist_data_pcc = new TH1F(histname_data_pcc.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_data_pcc->Sumw2();
    auto hist_data_pnot = new TH1F(histname_data_pnot.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_data_pnot->Sumw2();
    auto hist_data_pdum = new TH1F(histname_data_pdum.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_data_pdum->Sumw2();

    std::cout << "Setting up time distro hists" << std::endl;
    auto hist_ratio = new TH1F(histname_ratio.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_ratio->Sumw2();
    hist_ratio->GetXaxis()->SetTitle("Ratio Method [ns] (EB)");
    auto hist_pcalo = new TH1F(histname_pcalo.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_pcalo->Sumw2();
    hist_pcalo->GetXaxis()->SetTitle("Pcalo Time [ns] (EB)");
    //auto hist_pcTOF = new TH1F(histname_pcTOF.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    //hist_pcTOF->Sumw2();
    //auto hist_rawpcalo = new TH1F(histname_rawpcalo.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    //hist_rawpcalo->Sumw2();
    auto hist_wt = new TH1F(histname_wt.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_wt->Sumw2();
    hist_wt->GetXaxis()->SetTitle("Weight Method [ns] (EB)");
    auto hist_kutmf = new TH1F(histname_kutmf.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_kutmf->Sumw2();
    hist_kutmf->GetXaxis()->SetTitle("KUTMF Method [ns] (EB)");
    auto hist_kucc = new TH1F(histname_kucc.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_kucc->Sumw2();
    hist_kucc->GetXaxis()->SetTitle("KUCC Method [ns] (EB)");
    auto hist_kunot = new TH1F(histname_kunot.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_kunot->Sumw2();
    hist_kunot->GetXaxis()->SetTitle("Ratio noOOT Method [ns] (EB)");
    auto hist_dummy = new TH1F(histname_dummy.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
    hist_dummy->Sumw2();
    hist_dummy->GetXaxis()->SetTitle("Dummy Method [ns] (EB)");

    std::cout << "Setting up pcalo vs method hists" << std::endl;
    auto hist_pctvratio = new TH2F(histname_pctvratio.c_str(),histtitletmp.c_str(),
									pcalotdiv,pcalotstart,pcalotend,ratiotdiv,ratiotstart,ratiotend);
    hist_pctvratio->Sumw2();
    hist_pctvratio->GetXaxis()->SetTitle("Pcalo Time [ns] (EB)");
    hist_pctvratio->GetYaxis()->SetTitle("Ratio Method [ns] (EB)");

    auto hist_pctvwt = new TH2F(histname_pctvwt.c_str(),histtitletmp.c_str(),
									pcalotdiv,pcalotstart,pcalotend,wttdiv,wttstart,wttend);
    hist_pctvwt->Sumw2();
    hist_pctvwt->GetXaxis()->SetTitle("Pcalo Time [ns] (EB)");
    hist_pctvwt->GetYaxis()->SetTitle("Weight Method [ns] (EB)");

    auto hist_pctvkutmf = new TH2F(histname_pctvkutmf.c_str(),histtitletmp.c_str(),
									pcalotdiv,pcalotstart,pcalotend,kutmftdiv,kutmftstart,kutmftend);
    hist_pctvkutmf->Sumw2();
    hist_pctvkutmf->GetXaxis()->SetTitle("Pcalo Time [ns] (EB)");
    hist_pctvkutmf->GetYaxis()->SetTitle("KUTMF Method [ns] (EB)");

    auto hist_pctvkucc = new TH2F(histname_pctvkucc.c_str(),histtitletmp.c_str(),
									pcalotdiv,pcalotstart,pcalotend,kutmftdiv,kutmftstart,kutmftend);
    hist_pctvkucc->Sumw2();
    hist_pctvkucc->GetXaxis()->SetTitle("Pcalo Time [ns] (EB)");
    hist_pctvkucc->GetYaxis()->SetTitle("KUCC Method [ns] (EB)");



    //std::cout << "Setting up dpc vs dmethod hists" << std::endl;
    //auto hist_dpctvdratio = new TH2F(histname_dpctvdratio.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
    //hist_dpctvdratio->Sumw2();
    //auto hist_dpctvdwt = new TH2F(histname_dpctvdwt.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
    //hist_dpctvdwt->Sumw2();
    //auto hist_dpctvdkutmf = new TH2F(histname_dpctvdkutmf.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
    //hist_dpctvdkutmf->Sumw2();
    //auto hist_dpctvdkucc = new TH2F(histname_dpctvdkucc.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
    //hist_dpctvdkucc->Sumw2();

    //std::cout << "Setting up dratio vs dmethod hists" << std::endl;
    //auto hist_dratiovdwt = new TH2F(histname_dratiovdwt.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
    //hist_dratiovdwt->Sumw2();
    //auto hist_dratiovdkutmf = new TH2F(histname_dratiovdkutmf.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
    //hist_dratiovdkutmf->Sumw2();
    //auto hist_dratiovdkucc = new TH2F(histname_dratiovdkucc.c_str(),histtitletmp.c_str(),dtdiv,dtstart,dtend,dtdiv,dtstart,dtend);
    //hist_dratiovdkucc->Sumw2();

    //std::cout << "Setting up ratio vs method hists" << std::endl;
    //auto hist_ratiovwt = new TH2F(histname_ratiovwt.c_str(),histtitletmp.c_str(),wttdiv,wttstart,wttend,ratiotdiv,ratiotstart,ratiotend);
    //hist_ratiovwt->Sumw2();
    //auto hist_ratiovkutmf = new TH2F(histname_ratiovkutmf.c_str(),histtitletmp.c_str(),kutmftdiv,kutmftstart,kutmftend,ratiotdiv,ratiotstart,ratiotend);
    //hist_ratiovkutmf->Sumw2();
    //auto hist_ratiovkucc = new TH2F(histname_ratiovkucc.c_str(),histtitletmp.c_str(),kucctdiv,kucctstart,kucctend,ratiotdiv,ratiotstart,ratiotend);
    //hist_ratiovkucc->Sumw2();

    //std::cout << "Setting up method vs amplitude hists" << std::endl;
    //auto hist_ratiova = new TH2F(histname_ratiova.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
    //hist_ratiova->Sumw2();
    //auto hist_pcalova = new TH2F(histname_pcalova.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
    //hist_pcalova->Sumw2();
    //auto hist_wtva = new TH2F(histname_wtva.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
    //hist_wtva->Sumw2();
    //auto hist_kutmfva = new TH2F(histname_kutmfva.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
    //hist_kutmfva->Sumw2();
    //auto hist_kuccva = new TH2F(histname_kuccva.c_str(),histtitletmp.c_str(),200,0,2000,tdiv,tstart,tend);
    //hist_kuccva->Sumw2();

    //std::cout << "Getting calibration values and plotting for " << cmbs << std::endl;
//     get maps from fCaliFile
    std::cout << "get maps from fCaliFile" << std::endl;
    //fCaliFile->cd();
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

//    std::cout << "Getting Cali Hists" << std::endl;
//    auto ebmapic0 = (TH2F*)fCaliFile->Get(ebmapstring0.c_str());
//    auto ebmapic1 = (TH2F*)fCaliFile->Get(ebmapstring1.c_str());
//    auto ebmapic2 = (TH2F*)fCaliFile->Get(ebmapstring2.c_str());
//    auto ebmapic2b = (TH2F*)fCaliFile->Get(ebmapstring2b.c_str());
//    auto ebmapic3 = (TH2F*)fCaliFile->Get(ebmapstring3.c_str());
//    auto ebmapic4 = (TH2F*)fCaliFile->Get(ebmapstring4.c_str());
//    //auto epmapic = (TH2F*)fCaliFile->Get(epmapstring.c_str());
//    auto epmapic1 = (TH2F*)fCaliFile->Get(epmapstring1.c_str());
//    auto epmapic2 = (TH2F*)fCaliFile->Get(epmapstring2.c_str());
//    auto epmapic3 = (TH2F*)fCaliFile->Get(epmapstring3.c_str());
//    auto epmapic4 = (TH2F*)fCaliFile->Get(epmapstring4.c_str());
//    //auto emmapic = (TH2F*)fCaliFile->Get(emmapstring.c_str());
//    auto emmapic1 = (TH2F*)fCaliFile->Get(emmapstring1.c_str());
//    auto emmapic2 = (TH2F*)fCaliFile->Get(emmapstring2.c_str());
//    auto emmapic3 = (TH2F*)fCaliFile->Get(emmapstring3.c_str());
//    auto emmapic4 = (TH2F*)fCaliFile->Get(emmapstring4.c_str());
//    //std::cout << " Ic hists for " << cmbs << std::endl;
//    std::cout << "  " << ebmapstring0 << " : " << ebmapic0 << std::endl;
//    std::cout << "  " << ebmapstring1 << " : " << ebmapic1 << std::endl;
//    std::cout << "  " << ebmapstring2 << " : " << ebmapic2 << std::endl;
//    std::cout << "  " << ebmapstring2b << " : " << ebmapic2b << std::endl;
//    std::cout << "  " << ebmapstring3 << " : " << ebmapic3 << std::endl;
//    std::cout << "  " << ebmapstring4 << " : " << ebmapic4 << std::endl;
//    //std::cout << "  " << epmapstring << " : " << epmapic << std::endl;
//    //std::cout << "  " << emmapstring << " : " << emmapic << std::endl;

    std::cout << "Setting up DetIDs." << std::endl;
    std::map<UInt_t,DetIDStruct> DetIDMap;
    SetupDetIDsEB( DetIDMap );
    SetupDetIDsEE( DetIDMap );

    fInFile->cd();
    std::cout << "Starting Event Loop " << std::endl;
    const auto nEntries = fInTree->GetEntries();
    for (auto entry = 0U; entry < nEntries; entry++){
        // if( entry%int(nEntries*0.1) == 0 ) std::cout << "Proccessed " << entry/nEntries << "\% of " << nEntries << " entries." << std::endl;
	     if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;        
        //std::cout << "Getting Branches " << std::endl;

	     fInFile->cd();

        //b_X->GetEntry(entry);
        //b_Y->GetEntry(entry);
        //b_Z->GetEntry(entry);
        b_E->GetEntry(entry);
        b_time->GetEntry(entry);
        b_pCalotime->GetEntry(entry);
        b_timeErr->GetEntry(entry);
        b_TOF->GetEntry(entry);
        b_pcTOF->GetEntry(entry);
        b_rhID->GetEntry(entry);
        b_adcToGeV->GetEntry(entry);
        b_pedrms12->GetEntry(entry);

        //b_kuStcrhtime->GetEntry(entry);
        //b_kuStcrhtimeErr->GetEntry(entry);
        //b_kuStcrhID->GetEntry(entry);
        b_kuNotStcrhtime->GetEntry(entry);
        b_kuNotStcrhtimeErr->GetEntry(entry);
        b_kuNotStcrhID->GetEntry(entry);
        b_kuWtStcrhtime->GetEntry(entry);
        b_kuWtStcrhtimeErr->GetEntry(entry);
        b_kuWtStcrhID->GetEntry(entry);
        b_kuWootStcrhtime->GetEntry(entry);
        b_kuWootStcrhtimeErr->GetEntry(entry);
        b_kuWootStcrhID->GetEntry(entry);
        b_kuMfootStcrhtime->GetEntry(entry);
        b_kuMfootStcrhtimeErr->GetEntry(entry);
        b_kuMfootStcrhID->GetEntry(entry);
        b_kuMfootCCStcrhtime->GetEntry(entry);
        b_kuMfootCCStcrhtimeErr->GetEntry(entry);
        b_kuMfootCCStcrhID->GetEntry(entry);

        //std::cout << "Starting RH Loop for " << (*rhID).size() << " rechits " << std::endl;

        for(UInt_t seed = 0; seed < (*rhID).size(); seed++ ){
//  ------------   add Common::DetIDMap :  const auto & sidinfo = Common::DetIDMap[(*fInRecHits.ID)[seed]]; 926

        //std::cout << "Getting seed varibles" << std::endl;
        auto phoseedE_0 = (*E)[seed];
        auto phoseedadcToGeV_0 = (*adcToGeV)[seed];
        auto phoseedpedrms12_0 = (*pedrms12)[seed];
        auto phoseedrhID = (*rhID)[seed];
        //std::cout << "phoseedE_0: " <<  phoseedE_0 << " phoseedrhID: " << phoseedrhID << std::endl;
        //std::cout << "phoseedadcToGeV_0: " << phoseedadcToGeV_0 << std::endl;
        //std::cout << "phoseedpedrms12_0: " <<  phoseedpedrms12_0 << std::endl;

        const auto & sidinfo = DetIDMap[phoseedrhID];

        auto phoseedI1_0 = sidinfo.i1;
        auto phoseedI2_0 = sidinfo.i2;

        auto phoseedTOF_0 = (*TOF)[seed];
        auto phoseedpcTOF_0 = (*pcTOF)[seed];
        //std::cout << "phoseedTOF_0: " <<  phoseedTOF_0 << " phoseedpcTOF_0: " << phoseedpcTOF_0 << std::endl;

        auto phoseedtime_0 = (*time)[seed];
        //std::cout << "phoseedtime_0: " <<  phoseedtime_0 << std::endl;
        auto phoseedpctime_0 = (*pCalotime)[seed];
        //std::cout << "phoseedpctime_0: " <<  phoseedpctime_0 << std::endl;
        auto phoseedkuStctime_0 = 0; //(*kuStcrhtime)[seed];
        //std::cout << "phoseedkuStctime_0: " <<  phoseedkuStctime_0 << std::endl;
        auto phoseedkuNotStctime_0 = (*kuNotStcrhtime)[seed];
        //std::cout << "phoseedkuNotStctime_0: " <<  phoseedkuNotStctime_0 << std::endl;
        auto phoseedkuWtStctime_0 = (*kuWtStcrhtime)[seed];
        //std::cout << "phoseedkuWtStctime_0: " <<  phoseedkuWtStctime_0 << std::endl;
        auto phoseedkuWootStctime_0 = (*kuWootStcrhtime)[seed];
        //std::cout << "phoseedkuWtStctime_0: " <<  phoseedkuWootStctime_0 << std::endl;
        auto phoseedkuMfootStctime_0 = (*kuMfootStcrhtime)[seed];
        //std::cout << "phoseedkuMfootStctime_0: " <<  phoseedkuMfootStctime_0 << std::endl;
        auto phoseedkuMfootCCStctime_0 = (*kuMfootCCStcrhtime)[seed];
        //std::cout << "phoseedkuMfootCCStctime_0: " <<  phoseedkuMfootCCStctime_0 << std::endl;

        auto amp_0 = (phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0;

        //if( (amp_0/std::sqrt(2)) < 20.f ){ std::cout << " - Skip: amplitude" << std::endl; continue; }
        //if( (amp_0/std::sqrt(2)) < 20.f ){ continue; }
        //if( (phoseedEcal_0 == ECAL::EB) || (phoseedEcal_1 == ECAL::EB) ) continue;
        //if( (phoseedEcal_0 == ECAL::EP) || (phoseedEcal_1 == ECAL::EP) ) continue;
        //if( (phoseedEcal_0 == ECAL::EM) || (phoseedEcal_1 == ECAL::EM) ) continue;
        //if( phoseedrhID > 840000000 ){ std::cout << " - Skip: rhID > 840M" << std::endl; continue; }
        if( phoseedrhID > 840000000 ){ continue; }
        //if( phoseedpctime_0 < 0.0 ){ std::cout << " - Skip: pctime < 0" << std::endl; continue; }
        if( phoseedpctime_0 < 0.0 ){ continue; }

        int bin_offset = 86;
        auto phoseedEcal_0 = sidinfo.ecal;

        //std::cout << "Getting ic values" << std::endl;
        //if( calimapname != "none" ){
//        if( false ){
//               if ( phoseedEcal_0 == ECAL::EB ){
//                        ic0_0 = ebmapic0->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
//                        ic1_0 = ebmapic1->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
//                        ic2_0 = ebmapic2->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
//                        ic2b_0 = ebmapic2b->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
//                        ic3_0 = ebmapic3->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
//                        ic4_0 = ebmapic4->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 );
//               }else if ( phoseedEcal_0 == ECAL::EP ){
//                        ic1_0 = epmapic1->GetBinContent( phoseedI2_0, phoseedI1_0 );
//                        ic2_0 = epmapic2->GetBinContent( phoseedI2_0, phoseedI1_0 );
//                        ic3_0 = epmapic3->GetBinContent( phoseedI2_0, phoseedI1_0 );
//                        ic4_0 = epmapic4->GetBinContent( phoseedI2_0, phoseedI1_0 );
//               }else if (phoseedEcal_0 == ECAL::EM ){
//                        ic1_0 = emmapic1->GetBinContent( phoseedI2_0, phoseedI1_0 );
//                        ic2_0 = emmapic2->GetBinContent( phoseedI2_0, phoseedI1_0 );
//                        ic3_0 = emmapic3->GetBinContent( phoseedI2_0, phoseedI1_0 );
//                        ic4_0 = emmapic4->GetBinContent( phoseedI2_0, phoseedI1_0 );
//               }
//
//        }

        //std::cout << "Producing fill values" << std::endl;
        auto tof_cor_0 = phoseedTOF_0;

		  auto time_0 = phoseedtime_0 + tof_cor_0 - ic1_0;
        auto kuNotStctime_0 = phoseedkuNotStctime_0 + tof_cor_0 - ic0_0;
        auto kuWtStctime_0 = phoseedkuWtStctime_0 + tof_cor_0 - ic2_0;
        auto kuWootStctime_0 = phoseedkuWootStctime_0 + tof_cor_0 - ic2b_0;
        auto kuMfootStctime_0 = phoseedkuMfootStctime_0 + tof_cor_0 - ic3_0;
        auto kuMfootCCStctime_0 = phoseedkuMfootCCStctime_0 + tof_cor_0 - ic4_0;

        //if( (phoseedpctime_0 < 0.0 ) ) continue;
				//|| (phoseedpctime_1 < 0.0 ) )  continue;
        auto pctime_0 = phoseedpctime_0 - phoseedpcTOF_0;

        //auto pctime_0 = phoseedpctime_0 + tof_cor_0;

        //auto yfill0 = pctime_0 - time_0;		
        ////(phoseedtime_0-phoseedtimeCaliIc_0)-(phoseedtime_1-phoseedtimeCaliIc_1)+(phoseedTOF_0-phoseedTOF_1);
        auto yfillrt = pctime_0 - time_0;
        auto yfillnot = pctime_0 - kuNotStctime_0;
        auto yfillwt = pctime_0 - kuWtStctime_0;
        auto yfilldum = pctime_0 - kuWootStctime_0;
        auto yfilltmf = pctime_0 - kuMfootStctime_0;
        auto yfillcc = pctime_0 - kuMfootCCStctime_0;

        auto effa0 = ((phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0)/sqrt(2);
        //auto effa1 = ((phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1)/sqrt(2);
        //auto xfill = (effa0*effa1)/sqrt(pow(effa0,2)+pow(effa1,2));

        auto e_cut = (phoseedE_0>=10)&&(phoseedE_0<=120);
					//&&(phoseedE_1>=10)&&(phoseedE_1<=120);
        auto eta_cut = true; //(phoseedEcal_0 == ECAL::EB)&&(phoseedEcal_1 == ECAL::EB);
        auto isd_cut = true; //inclusive
        //auto isd_cut = (phoseedTT_0!=phoseedTT_1); //diffrent
        //auto isd_cut = (phoseedTT_0==phoseedTT_1); //same
        auto event_good = e_cut && eta_cut && isd_cut;

        //std::cout << "Filling data Hists" << std::endl;
        if( event_good ){ 
				theHist_rt->Fill(effa0,yfillrt);
				hist_data_prt->Fill(yfillrt);
            theHist_wt->Fill(effa0,yfillwt);
            hist_data_pwt->Fill(yfillwt);
            theHist_not->Fill(effa0,yfillnot);
            hist_data_pnot->Fill(yfillnot);
            theHist_dum->Fill(effa0,yfilldum);
            hist_data_pdum->Fill(yfilldum);
            theHist_tmf->Fill(effa0,yfilltmf);
            hist_data_ptmf->Fill(yfilltmf);
            theHist_cc->Fill(effa0,yfillcc);
            hist_data_pcc->Fill(yfillcc);

            //std::cout << "Filling dist Hists" << std::endl;
		      hist_ratio->Fill(time_0);
            hist_pcalo->Fill(pctime_0);
            //hist_rawpcalo->Fill(phoseedpctime_0);
            //hist_pcTOF->Fill(phoseedpcTOF_0);
            //std::cout << " - Filling wt method dist Hists" << std::endl;
            hist_wt->Fill(kuWtStctime_0);
            //std::cout << " - Filling kutmf method dist Hists" << std::endl;
            hist_kutmf->Fill(kuMfootStctime_0);
            //std::cout << " - Filling kucc method dist Hists" << std::endl;
            hist_kucc->Fill(kuMfootCCStctime_0);
            //std::cout << " - Filling kunot method dist Hists" << std::endl;
            hist_kunot->Fill(kuNotStctime_0);
            //std::cout << " - Filling kuwoot method dist Hists" << std::endl;
            hist_dummy->Fill(kuWootStctime_0);

            //std::cout << "Filling va Hists" << std::endl;
            //hist_ratiova->Fill(amp_0,time_0);
            //hist_pcalova->Fill(amp_0,pctime_0);
            //hist_wtva->Fill(amp_0,kuWtStctime_0);
            //hist_kutmfva->Fill(amp_0,kuMfootStctime_0);
            //hist_kuccva->Fill(amp_0,kuMfootCCStctime_0);

            //std::cout << "Filling pcvmethod Hists" << std::endl;
            hist_pctvratio->Fill(pctime_0,time_0);
            hist_pctvwt->Fill(pctime_0,kuWtStctime_0);
            hist_pctvkutmf->Fill(pctime_0,kuMfootStctime_0);
            hist_pctvkucc->Fill(pctime_0,kuMfootCCStctime_0);

            //hist_dpctvdratio->Fill(time_0-time_1,pctime_0-pctime_1);
            //hist_dpctvdwt->Fill(kuWtStctime_0-kuWtStctime_1,pctime_0-pctime_1);
            //hist_dpctvdkutmf->Fill(kuMfootStctime_0-kuMfootStctime_1,pctime_0-pctime_1);
            //hist_dpctvdkucc->Fill(kuMfootCCStctime_0-kuMfootCCStctime_1,pctime_0-pctime_1);

            //hist_dratiovdwt->Fill(kuWtStctime_0-kuWtStctime_1,time_0-time_1);
            //hist_dratiovdkutmf->Fill(kuMfootStctime_0-kuMfootStctime_1,time_0-time_1);
            //hist_dratiovdkucc->Fill(kuMfootCCStctime_0-kuMfootCCStctime_1,time_0-time_1);

            //std::cout << "Filling ratiovmethod Hists" << std::endl;
            //hist_ratiovwt->Fill(kuWtStctime_0,time_0);
            //hist_ratiovkutmf->Fill(kuMfootStctime_0,time_0);
            //hist_ratiovkucc->Fill(kuMfootCCStctime_0,time_0);
		   //} else { std::cout << " - Skip : event_good flag " << std::endl; }
         }
        //std::cout << "Next RH" << std::endl;
      }//end of loop over rechits
    //std::cout << "End of RH loop" << std::endl;
    }//end of loop over events

    //std::cout << "Scale, Write, Delete, Done" << std::endl;

    //Common::Scale(theHist,false,fXVarBins,fYVarBins);

    fOutFile->cd();

    std::cout << "Writing Hists" << std::endl;
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
    //hist_rawpcalo->Write();
    //hist_pcTOF->Write();
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

    //std::cout << "Deleting data Hists" << std::endl;
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

    //std::cout << "Deleting pctv Hists" << std::endl;
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

    //std::cout << "Deleting ratiov Hists" << std::endl;
    //delete hist_ratiovwt;
    //delete hist_ratiovkutmf;
    //delete hist_ratiovkucc;

    //std::cout << "Deleting dist Hists" << std::endl;
    delete hist_ratio;
    delete hist_pcalo;
    //delete hist_rawpcalo;
    //delete hist_pcTOF;
    delete hist_wt;
    delete hist_kutmf;
    delete hist_kucc;
    delete hist_kunot;
    delete hist_dummy;

    //std::cout << "Deleting va Hists" << std::endl;
    //delete hist_ratiova;
    //delete hist_pcalova;
    //delete hist_wtva;
    //delete hist_kutmfva;
    //delete hist_kuccva;

    //std::cout << "Not Deleting Files" << std::endl;
    delete fInFile;
    delete fOutFile;
//    delete fCaliFile;

    std::cout << "Thats all Folks!" << std::endl;
}


int main ( int argc, char *argv[] ){

        auto califilename = "none"; //"local_skims/local_chain/dispho_mc_v31_DYJetsToLL_ave_e5_cali.root";
        auto infilename = "ku_mc_test_tt_dispho_6k_v2.root"; 
        auto outfilename = "ku_mc_test_tt_dispho_6k_v2_mc_plots";
        if( argc == 2 ){
               infilename = argv[1];
               outfilename = "ku_mc_v2_plots";
        } 
        else if( argc == 4 ) { //std::cout << "Insufficent arguments." << std::endl; }
        //else {
                califilename = argv[1];
                infilename = argv[2];
                outfilename = argv[3];
                //auto tvarname = argv[4];
					 //auto calimapname = argv[5];
                //auto isd_type = argv[6];
                //std::cout << " Running with " << califilename <<  " " << infilename;
                //std::cout <<  " " << outfilename <<  " " << std::endl;
      			 //makeplots( califilename, infilename, outfilename );
        }
        std::cout << " Running with " << califilename <<  " " << infilename;
        std::cout <<  " " << outfilename <<  " " << std::endl;
        makeplots( califilename, infilename, outfilename );
        return 1;
}
