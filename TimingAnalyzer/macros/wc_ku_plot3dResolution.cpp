#include "Skimmer.hh"
#include "TROOT.h"
#include "Common.cpp"
#include <iostream>

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

void plot3dResolution( const string califilename, const string infilename, const string outfilename, const string tvarname, const string calimapname, const string isd_type ){

    std::cout << " plot3dResolution with " << califilename <<  " " << infilename <<  " " << outfilename <<  " " << tvarname <<  " " << calimapname <<  " " << isd_type <<  " " << std::endl;
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
    string tvarnameErr_0(tvarname+"Err_0");
    fInTree->SetBranchAddress( tvarnameErr_0.c_str(), &phoseedtimeErr_0, &b_phoseedtimeErr_0);

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
    string tvarnameErr_1(tvarname+"Err_1");
    fInTree->SetBranchAddress( tvarnameErr_1.c_str(), &phoseedtimeErr_1, &b_phoseedtimeErr_1);

//     get maps from fCaliFile
    std::cout << "get maps from fCaliFile" << std::endl;
    fCaliFile->cd();
    //string cmbs("AveXtalRtOOTStcPhoIcRecTime");
    //string cmbs("AveXtalRtStcRecTimeE5");
    string cmbs = calimapname;
    //string cmbs(calimapname);
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
    std::cout << "Setting up 2D plot for " << cmbs << std::endl;

    string histname_mean("Data_Hist_mean");
    string histname_rms("Data_Hist_rms");
    string histname_occ("Data_Hist_occ");
    string histname1("td_Hist");
    //string histname2("tdc_Hist");
    //string histname3("tdf_Hist");
    //string histname4("tdfc_Hist");
    string fTitle("A_{0}/#sigma_{0}  vs. A_{1}/#sigma_{1} (EBEB)");
    string fTitle1("Photon Seed Time [ns]");
    //string fTitle2("Photon Seed Time Calibrated [ns]");
    //string fTitle3("Photon Seed Time Filtered [ns]");
    //string fTitle4("Photon Seed Time Filtered Calibrated [ns]");
    string fXTitle("A_{eff}/#sigma_{n} (EBEB)");
    string fXxTitle("A_{0}/#sigma_{0} (EBEB)");
    string fXyTitle("A_{1}/#sigma_{1} (EBEB)");
    std::vector<Double_t> fXBins;
    Bool_t fXVarBins = false;
    string xbinstr("VARIABLE 75 100 125 150 175 225 275 325 375 475 600 750 950 1275 1700 2250");
    //std::vector<TString> fXLabels;
    string fYTitle("#Delta(t) [ns] (EBEB)");
    std::vector<Double_t> fYBins;
    Bool_t fYVarBins = false;
    //string ybinstr("CONSTANT 30 -3 3");
    string ybinstr("CONSTANT 480 -3 3");
    //std::vector<TString> fYLabels;
    string fZmTitle("Mean #Delta(t)");
    string fZrTitle("RMS #Delta(t)");
    string fZoTitle("Occ #Delta(t)");

    Common::SetupBins(xbinstr,fXBins,fXVarBins);
    Common::SetupBins(ybinstr,fYBins,fYVarBins);

    const auto xbins = &fXBins[0];
    const auto ybins = &fYBins[0];

    int tdiv = 960;
    float tstart = -6.0;
    float tend = 6.0;

    auto theHist_mean = new TH2F(histname_mean.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fXBins.size()-1,xbins);
    theHist_mean->GetXaxis()->SetTitle(fXxTitle.c_str());
    theHist_mean->GetYaxis()->SetTitle(fXyTitle.c_str());
    theHist_mean->GetZaxis()->SetTitle(fZmTitle.c_str());
    theHist_mean->Sumw2();
    auto theHist_rms = new TH2F(histname_rms.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fXBins.size()-1,xbins);
    theHist_rms->GetXaxis()->SetTitle(fXxTitle.c_str());
    theHist_rms->GetYaxis()->SetTitle(fXyTitle.c_str());
    theHist_rms->GetZaxis()->SetTitle(fZrTitle.c_str());
    theHist_rms->Sumw2();
    auto theHist_occ = new TH2F(histname_occ.c_str(),fTitle.c_str(),fXBins.size()-1,xbins,fXBins.size()-1,xbins);
    theHist_occ->GetXaxis()->SetTitle(fXxTitle.c_str());
    theHist_occ->GetYaxis()->SetTitle(fXyTitle.c_str());
    theHist_occ->GetZaxis()->SetTitle(fZoTitle.c_str());
    theHist_occ->Sumw2();

    TH1F *thetdHist[fXBins.size()][fXBins.size()];
    for( int ix = 0; ix <= fXBins.size(); ix++ ){
	 	  for( int iy = 0; iy <= fXBins.size(); iy++ ){
			   auto histnametmp = histname1 + "_" + std::to_string(ix) + "_" + std::to_string(iy);
            auto histtitletmp = fTitle1 + " xBin " + std::to_string(ix) + " yBin " + std::to_string(iy);
            thetdHist[ix][iy] = new TH1F(histnametmp.c_str(),histtitletmp.c_str(),tdiv,tstart,tend);
            (thetdHist[ix][iy])->GetXaxis()->SetTitle(fYTitle.c_str());
            //(thetdHist[ix][iy])->GetYaxis()->SetTitle(fYTitle.c_str());
            //(thetdHist[ix][iy])->GetZaxis()->SetTitle(fZTitle.c_str());
            (thetdHist[ix][iy])->Sumw2();
		  }
	 }

    std::cout << "Getting calibration values and plotting for " << cmbs << std::endl;

    fInFile->cd();
    const auto nEntries = fInTree->GetEntries();
    for (auto entry = 0U; entry < nEntries; entry++){
        // if( entry%int(nEntries*0.1) == 0 ) std::cout << "Proccessed " << entry/nEntries << "\% of " << nEntries << " entries." << std::endl;
	     if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;        
        //std::cout << "Getting Entries" << std::endl;

	     fInFile->cd();
        b_phoseedI1_0->GetEntry(entry);
	     b_phoseedI2_0->GetEntry(entry);	
	     b_phoseedEcal_0->GetEntry(entry);
        b_phoseedTT_0->GetEntry(entry);
        b_phoseedE_0->GetEntry(entry);
        b_phoseedadcToGeV_0->GetEntry(entry);
        b_phoseedpedrms12_0->GetEntry(entry);
        b_phoseedTOF_0->GetEntry(entry);
        b_phoseedtime_0->GetEntry(entry);
        b_phoseedtimeErr_0->GetEntry(entry);

        b_phoseedI1_1->GetEntry(entry);
        b_phoseedI2_1->GetEntry(entry);
        b_phoseedEcal_1->GetEntry(entry);
        b_phoseedTT_1->GetEntry(entry);
        b_phoseedE_1->GetEntry(entry);
        b_phoseedadcToGeV_1->GetEntry(entry);
        b_phoseedpedrms12_1->GetEntry(entry);
        b_phoseedTOF_1->GetEntry(entry);
        b_phoseedtime_1->GetEntry(entry);
        b_phoseedtimeErr_1->GetEntry(entry);

	     int bin_offset = 86;
	     int adjust = 0.0;

		  //std::cout << "Pulling Calimaps for " << cmbs << std::endl;
	     if( cmbs != "none" ){
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
		  if( ( phoseedtimeErr_0 < 0 ) or ( phoseedtimeErr_1 < 0  )  ) { skip = true; }

        auto yfill = (phoseedtime_0-phoseedtimeCaliIc_0)-(phoseedtime_1-phoseedtimeCaliIc_1)+(phoseedTOF_0-phoseedTOF_1);
        auto effa0 = (phoseedE_0/phoseedadcToGeV_0)/phoseedpedrms12_0;
        auto effa0bin = getBinNumber( effa0, fXBins );
        auto effa1 = (phoseedE_1/phoseedadcToGeV_1)/phoseedpedrms12_1;
        auto effa1bin = getBinNumber( effa1, fXBins );
        auto xfill = (effa0*effa1)/sqrt(pow(effa0,2)+pow(effa1,2));

		  auto e_cut = (phoseedE_0>=10)&&(phoseedE_0<=120)&&(phoseedE_1>=10)&&(phoseedE_1<=120);
	     auto eta_cut = (phoseedEcal_0 == ECAL::EB)&&(phoseedEcal_1 == ECAL::EB);
	     auto isd_cut = true; //inclusive
        if( isd_type == "Different") isd_cut = (phoseedTT_0!=phoseedTT_1); //diffrent
        if( isd_type == "Same") isd_cut = (phoseedTT_0==phoseedTT_1); //same
	     auto event_good = e_cut && eta_cut && isd_cut;

	     if( event_good and not skip ){
 				//std::cout << "Filling " << effa0bin << " " << effa1bin << " with " << yfill << std::endl;
				(thetdHist[effa0bin][effa1bin])->Fill(yfill);
		  }

    }

    for( int ix = 0; ix < fXBins.size(); ix++ ){
        for( int iy = 0; iy < fXBins.size(); iy++ ){
            auto mean = (thetdHist[ix][iy])->GetMean(1);
				auto rms = (thetdHist[ix][iy])->GetRMS(1); 
            auto occ = (thetdHist[ix][iy])->Integral();
				theHist_mean->SetBinContent( ix, iy, mean );
            theHist_rms->SetBinContent( ix, iy, rms );
            theHist_occ->SetBinContent( ix, iy, occ );
        }
    }

    //Common::Scale(theHist,false,fXVarBins,fYVarBins);
    fOutFile->cd();
    theHist_mean->Write();
    theHist_rms->Write();
    theHist_occ->Write();
    //thetdHist->Write();
    for( int ix = 0; ix < fXBins.size(); ix++ ){
        for( int iy = 0; iy < fXBins.size(); iy++ ){ 
            (thetdHist[ix][iy])->Write(); 
        }
    }

    delete theHist_mean;
    delete theHist_rms;
    delete theHist_occ;
    //delete thetdHist;
    for( int ix = 0; ix < fXBins.size(); ix++ ){
        for( int iy = 0; iy < fXBins.size(); iy++ ){
            delete (thetdHist[ix][iy]);           
        }
    }
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
                std::cout << " Running with " << califilename <<  " " << infilename <<  " " << outfilename <<  " " << tvarname <<  " " << calimapname <<  " " << isd_type <<  " " << std::endl;
      			 plot3dResolution( califilename, infilename, outfilename, tvarname, calimapname, isd_type );
        }
        return 1;
}
