#include "Skimmer.hh"
#include "TROOT.h"
#include "Common.cpp"
#include <iostream>
#include <string>

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

void plot1dcali( const string califilename, const string calimapname ){ 

    //std::cout << " plot3dResolution with " << califilename <<  " " << infilename <<  " " << outfilename <<  " " << tvarname <<  " " << calimapname <<  " " << isd_type <<  " " << std::endl;
    std::cout << "open input files" << std::endl;
    auto fCaliFile = TFile::Open(califilename.c_str(), "update");

    auto endofstr = (califilename.length())-5;
    auto califmtemp = califilename.substr(0,endofstr);
    string histoutfilename(califmtemp+"_"+calimapname+"_1dplot.root");
    TFile* fOutFile = new TFile( histoutfilename.c_str(), "RECREATE" );
    std::cout << "fOutFile " << histoutfilename  <<" : " << fOutFile << std::endl;

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

    string histname1("cali_1d_eb_Hist");
    string histname2("cali_1d_em_Hist");
    string histname3("cali_1d_ep_Hist");
    //string histname4("tdfc_Hist");
    string fTitle("Calibration Constant Distibution");
    string fXTitle("Calibration Constant");

    int tdiv = 960;
    float tstart = -6.0;
    float tend = 6.0;

    auto thetdEBHist = new TH1F(histname1.c_str(),fTitle.c_str(),tdiv,tstart,tend);
    thetdEBHist->GetXaxis()->SetTitle(fXTitle.c_str());
    thetdEBHist->Sumw2();
    auto thetdEPHist = new TH1F(histname2.c_str(),fTitle.c_str(),tdiv,tstart,tend);
    thetdEPHist->GetXaxis()->SetTitle(fXTitle.c_str());
    thetdEPHist->Sumw2();
    auto thetdEMHist = new TH1F(histname3.c_str(),fTitle.c_str(),tdiv,tstart,tend);
    thetdEMHist->GetXaxis()->SetTitle(fXTitle.c_str());
    thetdEMHist->Sumw2();

    std::cout << "Getting calibration values and plotting for " << cmbs << std::endl;
    //new TH2F(hnameEB.c_str(),htitleEB.c_str(),171,-85.5,85.5,360,0.5,360.5);
    //ebmapic->GetBinContent( phoseedI2_0 + bin_offset, phoseedI1_0 )

    for( int ix = 1; ix <= 171; ix++ ){
        for( int iy = 1; iy <= 360; iy++ ){
            auto teb = ebmapic->GetBinContent(ix,iy);
            auto tep = epmapic->GetBinContent(ix,iy);
            auto tem = emmapic->GetBinContent(ix,iy);
				thetdEBHist->Fill(teb);
            thetdEPHist->Fill(tep);
            thetdEMHist->Fill(tem);
        }
    }

    //Common::Scale(theHist,false,fXVarBins,fYVarBins);
    fOutFile->cd();
    thetdEBHist->Write();
    thetdEPHist->Write();
    thetdEMHist->Write();
    //thetdHist->Write();

    delete thetdEBHist;
    delete thetdEPHist;
    delete thetdEMHist;
    //delete thetdHist;

    fOutFile->Close();
    fCaliFile->Close();
    delete fOutFile;
    delete fCaliFile;

    std::cout << "Thats all Folks!" << std::endl;
}


int main ( int argc, char *argv[] ){

        if( argc != 3 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                auto califilename = argv[1];
					 auto calimapname = argv[2];
                std::cout << " Running with " << califilename <<  " " << calimapname << std::endl;
      			 plot1dcali( califilename, calimapname );
        }
        return 1;
}
