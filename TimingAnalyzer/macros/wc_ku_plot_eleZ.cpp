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

    string histoutfilename(outfilename+".root");
    TFile* fOutFile = new TFile( histoutfilename.c_str(), "RECREATE" );
    std::cout << "fOutFile : " << fOutFile << std::endl;


//     set branches to get from fInFile : fInTree
    std::cout << "set branches to get from fInFile : fInTree" << std::endl;

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
    fInTree->SetBranchAddress("phoseedtime_0", &phoseedtime_0, &b_phoseedtime_0);
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
    fInTree->SetBranchAddress("phoseedtime_1", &phoseedtime_1, &b_phoseedtime_1);
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

    int zdiv = 480;
    float zstart = -12.0;
    float zend = 12.0;
    int dzdiv = 480;
    float dzstart = -0.2;
    float dzend = 0.2;

    auto hist_dz0 = new TH1F(histname_dz0.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend);
    hist_dz0->Sumw2();
    auto hist_dz1 = new TH1F(histname_dz1.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend);
    hist_dz1->Sumw2();
    auto hist_adz01 = new TH1F(histname_adz01.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend);
    hist_adz01->Sumw2();
    auto hist_ddz01 = new TH1F(histname_ddz01.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend);
    hist_ddz01->Sumw2();
    auto hist_dz0v1 = new TH2F(histname_dz0v1.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend,dzdiv,dzstart,dzend);
    //theHist_mean->GetXaxis()->SetTitle(fXxTitle.c_str());
    //theHist_mean->GetYaxis()->SetTitle(fXyTitle.c_str());
    //theHist_mean->GetZaxis()->SetTitle(fZmTitle.c_str());
    hist_dz0v1->Sumw2();

    auto hist_z0 = new TH1F(histname_z0.c_str(),histtitletmp.c_str(),zdiv,zstart,zend);
    hist_z0->Sumw2();
    auto hist_z1 = new TH1F(histname_z1.c_str(),histtitletmp.c_str(),zdiv,zstart,zend);
    hist_z1->Sumw2();
    auto hist_dz0z1 = new TH1F(histname_dz0z1.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend);
    hist_dz0z1->Sumw2();
    auto hist_z0v1 = new TH2F(histname_z0v1.c_str(),histtitletmp.c_str(),zdiv,zstart,zend,zdiv,zstart,zend);
    hist_z0v1->Sumw2();
    auto hist_adz01vdz0z1 = new TH2F(histname_adz01vdz0z1.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend,dzdiv,dzstart,dzend);
    hist_adz01vdz0z1->Sumw2();
    auto hist_adz01vgzmass = new TH2F(histname_adz01vgzmass.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend,dzdiv,50.0,170.0);
    hist_adz01vgzmass->Sumw2();
    auto hist_adz01vdt = new TH2F(histname_adz01vdt.c_str(),histtitletmp.c_str(),dzdiv,dzstart,dzend,dzdiv,-6.0,6.0);
    hist_adz01vdt->Sumw2();
    auto hist_gzmassvdt = new TH2F(histname_gzmassvdt.c_str(),histtitletmp.c_str(),dzdiv,50.0,170.0,dzdiv,-6.0,6.0);
    hist_gzmassvdt->Sumw2();

    //std::cout << "Getting calibration values and plotting for " << cmbs << std::endl;

    fInFile->cd();
    const auto nEntries = fInTree->GetEntries();
    for (auto entry = 0U; entry < nEntries; entry++){
        // if( entry%int(nEntries*0.1) == 0 ) std::cout << "Proccessed " << entry/nEntries << "\% of " << nEntries << " entries." << std::endl;
	     if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;        
        //std::cout << "Getting Entries" << std::endl;

	     fInFile->cd();

        b_gZmass->GetEntry(entry);
        b_gdR->GetEntry(entry);
        b_elTrackZ_0->GetEntry(entry);
        b_elTrackZ_1->GetEntry(entry);
        b_vtxZ->GetEntry(entry);

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


        ///////std::cout << "Fill Hists" << std::endl;

		  auto dz0 = elTrackZ_0 - vtxZ;
        auto dz1 = elTrackZ_1 - vtxZ;
        hist_dz0->Fill(dz0);
        hist_dz1->Fill(dz1);
        hist_dz0v1->Fill(dz0,dz1);
        hist_ddz01->Fill(abs(dz0)-abs(dz1));

        hist_z0->Fill(elTrackZ_0);
        hist_z1->Fill(elTrackZ_1);
        hist_z0v1->Fill(elTrackZ_0,elTrackZ_1);
        auto dz0z1 = elTrackZ_0-elTrackZ_1;
        hist_dz0z1->Fill(dz0z1);
		  auto adz01 = (dz0+dz1)/2.f;
        hist_adz01->Fill(adz01);
        hist_adz01vgzmass->Fill(dz0,gZmass);
        hist_adz01vgzmass->Fill(dz1,gZmass);
        hist_adz01vdz0z1->Fill(adz01,dz0z1);
        auto dt = (phoseedtime_0-phoseedtime_1); //+(phoseedTOF_0-phoseedTOF_1);       
        hist_adz01vdt->Fill(dz0,dt);
        hist_adz01vdt->Fill(dz1,dt);
        hist_gzmassvdt->Fill(gZmass,dt);

    }


    //Common::Scale(theHist,false,fXVarBins,fYVarBins);
    fOutFile->cd();
    hist_dz0->Write();
    hist_dz1->Write();
    hist_dz0v1->Write();
    hist_ddz01->Write();
    hist_z0->Write();
    hist_z1->Write();
    hist_z0v1->Write();
    hist_dz0z1->Write();
    hist_adz01vdz0z1->Write();
    hist_adz01vgzmass->Write();
    hist_adz01->Write();
    hist_adz01vdt->Write();
    hist_gzmassvdt->Write();

    delete hist_dz0;
    delete hist_dz1;
    delete hist_dz0v1;
    delete hist_ddz01;
    delete hist_z0;
    delete hist_z1;
    delete hist_z0v1;
    delete hist_dz0z1;
    delete hist_adz01vdz0z1;
    delete hist_adz01vgzmass;
    delete hist_adz01;
    delete hist_adz01vdt;
    delete hist_gzmassvdt;

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
