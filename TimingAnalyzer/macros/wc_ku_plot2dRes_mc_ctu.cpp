#include "Skimmer.hh"
#include "TROOT.h"
#include "Common.cpp"
#include <string>
#include <iostream>
#include <sstream>

void NormX(TH2F *& hist) //, const Bool_t isUp, const Bool_t varBinsX, const Bool_t varBinsY)
  {
    std::cout << "Normilizing " << " hist: " << hist->GetName() << std::endl;

    for (auto ibinX = 1; ibinX <= hist->GetXaxis()->GetNbins(); ibinX++){
          //const auto binwidthX = hist->GetXaxis()->GetBinWidth(ibinX);
          const auto norm = hist->Integral(ibinX,ibinX,1,hist->GetYaxis()->GetNbins());
          if( norm == 0.0 ) continue;
          for (auto ibinY = 1; ibinY <= hist->GetYaxis()->GetNbins(); ibinY++){
               //const auto binwidthY = hist->GetYaxis()->GetBinWidth(ibinY);

               // get multiplier/divisor
               //auto multiplier = 1.f;      
               //if (varBinsX) multiplier *= binwidthX;
               //if (varBinsY) multiplier *= binwidthY;

               // get content/error
               auto content = hist->GetBinContent(ibinX,ibinY);
               auto error   = hist->GetBinError  (ibinX,ibinY);

               // scale it
               //if (isUp){ 
               //   content *= multiplier;
               //   error   *= multiplier;
               //} else {
               content /= norm;
               error   /= norm;
               //}

               // set new contents
               hist->SetBinContent(ibinX,ibinY,content);
               hist->SetBinError  (ibinX,ibinY,error);
            }
      }
}

void plot2dResolution( string califilename, string infilename, string outfilename, string tvarname, string calimapname, string isd_type ){

    std::cout << "open input files" << std::endl;
    string disphotreename("disphotree");

    auto fInFile = TFile::Open(infilename.c_str(), "update");
    fInFile->cd();
    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());

    auto fCaliFile = TFile::Open(califilename.c_str(), "update");
    std::cout << "fInFile : " << fInFile  << " fInTree : " << fInTree << " fCaliFile : " << fCaliFile << std::endl;

    string histoutfilename(outfilename+".root");
    TFile* fOutFile = new TFile( histoutfilename.c_str(), "RECREATE" );
    std::cout << "fOutFile : " << fOutFile << std::endl;


//     set branches to get from fInFile : fInTree
    std::cout << "set branches to get from fInFile : fInTree" << std::endl;

    double phoseedtimeCaliIc_0(0.0);
    double phoseedtimeCaliIc_1(0.0);

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
 
    fInTree->SetBranchAddress("phoseedI1_0", &phoseedI1_0, &b_phoseedI1_0);
    fInTree->SetBranchAddress("phoseedI2_0", &phoseedI2_0, &b_phoseedI2_0);
    fInTree->SetBranchAddress("phoseedEcal_0", &phoseedEcal_0, &b_phoseedEcal_0);
    fInTree->SetBranchAddress("phoseedTT_0", &phoseedTT_0, &b_phoseedTT_0);
    fInTree->SetBranchAddress("phoseedE_0", &phoseedE_0, &b_phoseedE_0);
    fInTree->SetBranchAddress("phoseedadcToGeV_0", &phoseedadcToGeV_0, &b_phoseedadcToGeV_0);
    fInTree->SetBranchAddress("phoseedpedrms12_0", &phoseedpedrms12_0, &b_phoseedpedrms12_0);
    fInTree->SetBranchAddress("phoseedTOF_0", &phoseedTOF_0, &b_phoseedTOF_0);
    //fInTree->SetBranchAddress("phoseedkuStctime_0", &phoseedtime_0, &b_phoseedtime_0);
    string tvarname_0(tvarname+"_0");
    fInTree->SetBranchAddress( tvarname_0.c_str(), &phoseedtime_0, &b_phoseedtime_0);
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
    //fInTree->SetBranchAddress("phoseedkuStctime_1", &phoseedtime_1, &b_phoseedtime_1);
    string tvarname_1(tvarname+"_1");
    fInTree->SetBranchAddress( tvarname_1.c_str(), &phoseedtime_1, &b_phoseedtime_1);
    //string tvarnameErr_1(tvarname+"Err_1");
    //fInTree->SetBranchAddress( tvarnameErr_1.c_str(), &phoseedtimeErr_1, &b_phoseedtimeErr_1);

//     get maps from fCaliFile
    std::cout << "get maps from fCaliFile" << std::endl;
    fCaliFile->cd();
    //string cmbs("AveXtalRtOOTStcPhoIcRecTime");
    //string cmbs("AveXtalRtStcRecTimeE5");
    string cmbs(calimapname);
    //string itcnt("_i95");
    string itcnt("");
    string ebmapstring(cmbs+"EBMap"+itcnt);
    string epmapstring(cmbs+"EPMap"+itcnt);
    string emmapstring(cmbs+"EMMap"+itcnt);
    auto ebmapic = (TH2F*)fCaliFile->Get(ebmapstring.c_str());
    auto epmapic = (TH2F*)fCaliFile->Get(epmapstring.c_str());
    auto emmapic = (TH2F*)fCaliFile->Get(emmapstring.c_str());
    std::cout << " Ic hists for " << cmbs << std::endl; 
    std::cout << "  " << ebmapstring << " : " << ebmapic << std::endl;
    std::cout << "  " << epmapstring << " : " << epmapic << std::endl;
    std::cout << "  " << emmapstring << " : " << emmapic << std::endl;

    // >> calcs  <<
    std::cout << "Setting up 2D plot" << std::endl;

    string histname("Data_Hist");
    string histname_c("Data_Hist_Core");
    string histname_t("Data_Hist_Tail");
    string histname_u("Data_Hist_UnScaled");
    string histname_l("Data_Hist_LargeScale");
    string histname1("td_Hist");
    string histname2("tdc_Hist");
    string histname3("tdf_Hist");
    string histname4("tdfc_Hist");
    string fTitle("#Delta(Photon Seed Time) [ns] vs. A_{eff}/#sigma_{n} (EBEB)");
    string fTitle1("Photon Seed Time [ns]");
    string fTitle2("Photon Seed Time Calibrated [ns]");
    string fTitle3("Photon Seed Time Filtered [ns]");
    string fTitle4("Photon Seed Time Filtered Calibrated [ns]");
    string fXTitle("A_{eff}/#sigma_{n} (EBEB)");
    std::vector<Double_t> fXBins;
    Bool_t fXVarBins = false;
    string xbinstr("VARIABLE 75 100 125 150 175 225 275 325 375 475 600 750 950 1275 1700 2250");
    int nMyBins = 17;
    //std::vector<TString> fXLabels;
    string fYTitle("#Delta(Photon Seed Time) [ns] (EBEB)");
    std::vector<Double_t> fYBins;
    std::vector<Double_t> fYLBins;
    Bool_t fYVarBins = false;
    //string ybinstr("CONSTANT 30 -3 3");
    string ybinstr("CONSTANT 768 -3 3");
    string ylbinstr("CONSTANT 480 -30 30");
    //std::vector<TString> fYLabels;
    string fZTitle("");
    std::vector<Double_t> fXetaBins;
    std::vector<Double_t> fYetaBins;


    Common::SetupBins(xbinstr,fXBins,fXVarBins);
    Common::SetupBins(ybinstr,fYBins,fYVarBins);
    Common::SetupBins(ylbinstr,fYLBins,fYVarBins);

    const auto xbins = &fXBins[0];
    const auto ybins = &fYBins[0];
    const auto ylbins = &fYLBins[0];

    int tdiv = 640;
    float tstart = -4.0;
    float tend = 4.0;

    TH1F * effBinHists[nMyBins];
    float ledge[nMyBins] = {0,75,100,125,150,175,225,275,325,375,475,600,750,950,1275,1700,2250};
    float hedge[nMyBins] = {75,100,125,150,175,225,275,325,375,475,600,750,950,1275,1700,2250,100000};
    for( auto ibin = 0; ibin < nMyBins; ibin++ ){
         auto binhistname = "bin" + to_string(ibin) + "hist";
         effBinHists[ibin] = new TH1F(binhistname.c_str(),binhistname.c_str(),512,ledge[ibin],hedge[ibin]);
         effBinHists[ibin]->Sumw2();
    }

    auto theHist = new TH2F(histname.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    auto theHistC = new TH2F(histname_c.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    auto theHistT = new TH2F(histname_t.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    auto theHistU = new TH2F(histname_u.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ybins);
    auto theHistL = new TH2F(histname_l.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fYBins.size()-1,ylbins);

    auto thetdHist = new TH1F(histname1.c_str(),fTitle1.c_str(),tdiv,tstart,tend);
    auto thetdcHist = new TH1F(histname2.c_str(),fTitle2.c_str(),tdiv,tstart,tend);
    auto thetdfHist = new TH1F(histname3.c_str(),fTitle3.c_str(),tdiv,tstart,tend);
    auto thetdfcHist = new TH1F(histname4.c_str(),fTitle4.c_str(),tdiv,tstart,tend);

    theHist->GetXaxis()->SetTitle(fXTitle.c_str());
    theHist->GetYaxis()->SetTitle(fYTitle.c_str());
    theHist->GetZaxis()->SetTitle(fZTitle.c_str());
    theHist->Sumw2();
    theHistC->GetXaxis()->SetTitle(fXTitle.c_str());
    theHistC->GetYaxis()->SetTitle(fYTitle.c_str());
    theHistC->GetZaxis()->SetTitle(fZTitle.c_str());
    theHistC->Sumw2();
    theHistT->GetXaxis()->SetTitle(fXTitle.c_str());
    theHistT->GetYaxis()->SetTitle(fYTitle.c_str());
    theHistT->GetZaxis()->SetTitle(fZTitle.c_str());
    theHistT->Sumw2();
    theHistU->GetXaxis()->SetTitle(fXTitle.c_str());
    theHistU->GetYaxis()->SetTitle(fYTitle.c_str());
    theHistU->GetZaxis()->SetTitle(fZTitle.c_str());
    theHistU->Sumw2();
    theHistL->GetXaxis()->SetTitle(fXTitle.c_str());
    theHistL->GetYaxis()->SetTitle(fYTitle.c_str());
    theHistL->GetZaxis()->SetTitle(fZTitle.c_str());
    theHistL->Sumw2();
    //thetdHist->Sumw2();
    //thetdcHist->Sumw2();
    //thetdfHist->Sumw2();
    //thetdfcHist->Sumw2();

    std::cout << "Getting calibration values and plotting" << std::endl;

    fInFile->cd();
    const auto nEntries = fInTree->GetEntries();
    for (auto entry = 0U; entry < nEntries; entry++){
        // if( entry%int(nEntries*0.1) == 0 ) std::cout << "Proccessed " << entry/nEntries << "\% of " << nEntries << " entries." << std::endl;
	     if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;        

	     fInFile->cd();
        b_phoseedI1_0->GetEntry(entry);
	     b_phoseedI2_0->GetEntry(entry);	
	     b_phoseedEcal_0->GetEntry(entry);
        b_phoseedTT_0->GetEntry(entry);
        b_phoseedE_0->GetEntry(entry);
        b_phoseedadcToGeV_0->GetEntry(entry);
        b_phoseedpedrms12_0->GetEntry(entry);
        b_phoseedTOF_0->GetEntry(entry);
        //std::cout << " geting time var 0 " << std::endl;
        b_phoseedtime_0->GetEntry(entry);
        //b_phoseedtimeErr_0->GetEntry(entry);
        //std::cout << " got time var 0 " << std::endl;

        b_phoseedI1_1->GetEntry(entry);
        b_phoseedI2_1->GetEntry(entry);
        b_phoseedEcal_1->GetEntry(entry);
        b_phoseedTT_1->GetEntry(entry);
        b_phoseedE_1->GetEntry(entry);
        b_phoseedadcToGeV_1->GetEntry(entry);
        b_phoseedpedrms12_1->GetEntry(entry);
        b_phoseedTOF_1->GetEntry(entry);
        b_phoseedtime_1->GetEntry(entry);
        //b_phoseedtimeErr_1->GetEntry(entry);

	     int bin_offset = 86;
	     int adjust = 0.0;

        //std::cout << "Getting Calibration Values" << std::endl;
	     if( calimapname != "none" ){
            	if ( phoseedEcal_0 == ECAL::EB ){
                        phoseedtimeCaliIc_0 = ebmapic->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 ) - adjust;
           	   }else if ( phoseedEcal_0 == ECAL::EP ){
                        phoseedtimeCaliIc_0 = epmapic->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
               }else if (phoseedEcal_0 == ECAL::EM ){
                        phoseedtimeCaliIc_0 = emmapic->GetBinContent( phoseedI2_0, phoseedI1_0 ) - adjust;
               }
        
        	      if ( phoseedEcal_1 == ECAL::EB ){
                        phoseedtimeCaliIc_1 = ebmapic->GetBinContent( phoseedI2_1 + bin_offset, phoseedI1_1 ) - adjust;
               }else if ( phoseedEcal_1 == ECAL::EP ){
                        phoseedtimeCaliIc_1 = epmapic->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
               }else if (phoseedEcal_1 == ECAL::EM ){
                        phoseedtimeCaliIc_1 = emmapic->GetBinContent( phoseedI2_1, phoseedI1_1 ) - adjust;
               }
	     }

        //std::cout << "Fill 2D Hist" << std::endl;
		  auto skip = false;
        auto skip_cali = false;
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

        auto yfill = (phoseedtime_0-phoseedtimeCaliIc_0)-(phoseedtime_1-phoseedtimeCaliIc_1)+(phoseedTOF_0-phoseedTOF_1);
        auto effa0 = (phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0;
        auto effa1 = (phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1;
        auto xfill = (effa0*effa1)/sqrt(pow(effa0,2)+pow(effa1,2));

		  auto e_cut = (phoseedE_0>=10)&&(phoseedE_0<=120)&&(phoseedE_1>=10)&&(phoseedE_1<=120);
	     auto eta_cut = (phoseedEcal_0 == ECAL::EB)&&(phoseedEcal_1 == ECAL::EB);
	     auto isd_cut = true; //inclusive
        if( isd_type == "Different") isd_cut = (phoseedTT_0!=phoseedTT_1); //diffrent
        if( isd_type == "Same") isd_cut = (phoseedTT_0==phoseedTT_1); //same
	     auto event_good = e_cut && eta_cut && isd_cut;

	     if( event_good and not skip ){ 
				theHist->Fill(xfill,yfill);
            if( abs(yfill) <= 0.1 ) theHistC->Fill(xfill,yfill);
            if( abs(yfill) > 0.1 ) theHistT->Fill(xfill,yfill);
            theHistU->Fill(xfill,yfill);
            theHistL->Fill(xfill,yfill);
            //std::cout << "Filling eff bins" << std::endl;
            if( xfill <= 75 ) effBinHists[0]->Fill(xfill);
            else if( xfill <= 100 ) effBinHists[1]->Fill(xfill);
            else if( xfill <= 125 ) effBinHists[2]->Fill(xfill);
            else if( xfill <= 150 ) effBinHists[3]->Fill(xfill);
            else if( xfill <= 175 ) effBinHists[4]->Fill(xfill);
            else if( xfill <= 225 ) effBinHists[5]->Fill(xfill);
            else if( xfill <= 275 ) effBinHists[6]->Fill(xfill);
            else if( xfill <= 325 ) effBinHists[7]->Fill(xfill);
            else if( xfill <= 375 ) effBinHists[8]->Fill(xfill);
            else if( xfill <= 475 ) effBinHists[9]->Fill(xfill);
            else if( xfill <= 600 ) effBinHists[10]->Fill(xfill);
            else if( xfill <= 750 ) effBinHists[11]->Fill(xfill);
            else if( xfill <= 950 ) effBinHists[12]->Fill(xfill);
            else if( xfill <= 1275 ) effBinHists[13]->Fill(xfill);
            else if( xfill <= 1700 ) effBinHists[14]->Fill(xfill);
            else if( xfill <= 2250 ) effBinHists[15]->Fill(xfill);
            else if( xfill > 2250 ) effBinHists[16]->Fill(xfill);
            //else std::cout << "Over 2250" << std::endl;
		  }
        if( event_good ) { thetdHist->Fill(phoseedtime_0); thetdHist->Fill(phoseedtime_1);}
        if( event_good ) { thetdcHist->Fill(phoseedtime_0-phoseedtimeCaliIc_0); thetdcHist->Fill(phoseedtime_1-phoseedtimeCaliIc_1);}
        if( event_good and not skip ) { thetdfHist->Fill(phoseedtime_0); thetdfHist->Fill(phoseedtime_1);}
        if( event_good and not skip ) { thetdfcHist->Fill(phoseedtime_0-phoseedtimeCaliIc_0); thetdfcHist->Fill(phoseedtime_1-phoseedtimeCaliIc_1);}       

    }

    std::cout << "Scaling and Writing Histograms" << std::endl;
    Common::Scale(theHist,false,fXVarBins,fYVarBins);
    Common::Scale(theHistC,false,fXVarBins,fYVarBins);
    Common::Scale(theHistT,false,fXVarBins,fYVarBins);

    fOutFile->cd();
    theHist->Write();
    theHistC->Write();
    theHistT->Write();
    theHistU->Write();
    theHistL->Write();
    thetdHist->Write();
    thetdcHist->Write();
    thetdfHist->Write();
    thetdfcHist->Write();
    for( auto ibin = 0; ibin < nMyBins; ibin++ ){
         effBinHists[ibin]->Write();
    }

    std::cout << "Deleting the Histograms" << std::endl;
    delete theHist;
    delete theHistC;
    delete theHistT;
    delete theHistU;
    delete theHistL;
    std::cout << "Deleting td Histograms" << std::endl;
    delete thetdHist;
    delete thetdcHist;
    delete thetdfHist;
    delete thetdfcHist;
    std::cout << "Deleting bin Histograms" << std::endl;
    for( auto ibin = 0; ibin < nMyBins; ibin++ ){
         if( effBinHists[ibin] ) delete effBinHists[ibin];
    }
    std::cout << "Deleting files" << std::endl;
    delete fInFile;
    delete fOutFile;
    delete fCaliFile;

    std::cout << "Thats all Folks!" << std::endl;
}


int main ( int argc, char *argv[] ){

        if( argc != 7 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                auto califilename = argv[1];
                auto infilename = argv[2];
                auto outfilename = argv[3];
                auto tvarname = argv[4];
					 auto calimapname = argv[5];
                auto isd_type = argv[6];
      			 plot2dResolution( califilename, infilename, outfilename, tvarname, calimapname, isd_type );
        }
        return 1;
}
