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


void wc_ku_InterCali_aveRecHit_v1( string indir, string infilelist, string outfilename ){

    const int  nAlgos = 2; // RtStc, RtOOTStc //, WtOOTStc
    //const int  nPhotons = 4;
    const double offset = 100.0;
    const int bin_offset = 86;

    const double ri_ecut = 5.0;

    const string treename("tree/disphotree");

//    auto fInFile = TFile::Open(infilename.c_str(), "update");
//    auto fInTree = (TTree*)fInFile->Get(disphotreename.c_str());

    std::ifstream infile(infilelist);
    auto fInTree = new TChain(treename.c_str());
    std::cout << "Adding files to TChain." << std::endl;
    std::string str;
    while (std::getline(infile,str)){
        auto tfilename = indir + "/" + str;
        std::cout << "--  adding file: " << tfilename << std::endl;
        fInTree->Add(tfilename.c_str());
    }

    std::vector<Float_t> *   fInRecHits_E = 0;
    std::vector<UInt_t> *   fInRecHits_ID = 0;
    std::vector<Float_t> *   fInRecHits_time = 0;
    std::vector<Float_t> *   fInRecHits_TOF = 0;
    std::vector<Float_t> *   kurhtime = 0;
    std::vector<UInt_t> *   kurhID = 0;
    std::vector<Float_t> *   kuStcrhtime = 0;
    std::vector<Float_t> *   kuNotrhtime = 0;
    std::vector<Float_t> *   kuNotStcrhtime = 0;
    std::vector<Float_t> *   kuWootStcrhtime = 0;

//{sumXtalRtStcRecTime, sumXtalRtOOTStcRecTime }; //, sumXtalWtOOTStcRecTime };

    std::map<UInt_t,Float_t> sumXtalRtStcRecTime;
    std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTime;
    std::map<UInt_t,Float_t> sumXtalWtOOTStcRecTime;
    std::map<UInt_t,Float_t> numXtalIcRecTime;

    bool isOOT_0;
    bool isOOT_1;
    bool isOOT_2;
    bool isOOT_3;
    double smin_0;
    double smin_1;
    double smin_2;
    double smin_3;
    double smaj_0;
    double smaj_1;
    double smaj_2;
    double smaj_3;
    UInt_t seedID_0;
    UInt_t seedID_1;
    double seedE_0;
    double seedE_1;
    double seedTOF_0;
    double seedTOF_1;

    TBranch * b_fInRecHits_E;
    TBranch * b_fInRecHits_ID;
    TBranch * b_fInRecHits_time;
    TBranch * b_fInRecHits_TOF;
    TBranch * b_kurhtime;
    TBranch * b_kurhID;
    TBranch * b_kuStcrhtime;
    TBranch * b_kuNotrhtime;
    TBranch * b_kuNotStcrhtime;
    TBranch * b_kuWootStcrhtime;
    TBranch * b_isOOT_0;
    TBranch * b_isOOT_1;
    TBranch * b_isOOT_2;
    TBranch * b_isOOT_3;
    TBranch * b_smin_0;
    TBranch * b_smin_1;
    TBranch * b_smin_2;
    TBranch * b_smin_3;
    TBranch * b_smaj_0;
    TBranch * b_smaj_1;
    TBranch * b_smaj_2;
    TBranch * b_smaj_3;
    TBranch * b_seedID_0;
    TBranch * b_seedID_1;
    TBranch * b_seedE_0;
    TBranch * b_seedE_1;
    TBranch * b_seedTOF_0;
    TBranch * b_seedTOF_1;

    fInTree->SetBranchAddress("rhE",&fInRecHits_E,&b_fInRecHits_E);
    fInTree->SetBranchAddress("rhID",&fInRecHits_ID,&b_fInRecHits_ID);
    fInTree->SetBranchAddress("rhtime",&fInRecHits_time,&b_fInRecHits_time);
    fInTree->SetBranchAddress("rhTOF",&fInRecHits_TOF,&b_fInRecHits_TOF);
    fInTree->SetBranchAddress("kurhtime",&kurhtime,&b_kurhtime);
    fInTree->SetBranchAddress("kurhID",&kurhID,&b_kurhID);
    fInTree->SetBranchAddress("kuStcrhtime",&kuStcrhtime,&b_kuStcrhtime);
    //fInTree->SetBranchAddress("kuNotrhtime",&kuNotrhtime,&b_kuNotrhtime);
    fInTree->SetBranchAddress("kuNotStcrhtime",&kuNotStcrhtime,&b_kuNotStcrhtime);
    //fInTree->SetBranchAddress("kuWootStcrhtime",&kuWootStcrhtime,&b_kuWootStcrhtime);

    TH2F * IcMapEB[nAlgos]; 
    TH2F * IcMapEP[nAlgos]; 
    TH2F * IcMapEM[nAlgos]; 

    std::cout << "Opening Outfile : " << outfilename << std::endl;
    TFile* fOutFile = new TFile( outfilename.c_str(), "RECREATE" );
    fOutFile->cd();

    string algostring[4] = { "RtStc", "RtOOTStc", "WtStc", "WtOOTStc" };
    for( auto i = 0; i < nAlgos; i++){
	string hnameEB( "AveXtal"+algostring[i]+"RecTimeEBMap"); 
        string htitleEB( "AveXtal "+algostring[i]+" RecTimeEBMap EB ");
        IcMapEB[i] = new TH2F(hnameEB.c_str(),htitleEB.c_str(),171,-85.5,85.5,360,0.5,360.5);
        IcMapEB[i]->Sumw2();
        string hnameEP( "AveXtal"+algostring[i]+"RecTimeEPMap"); 
        string htitleEP( "AveXtal "+algostring[i]+" RecTimeEPMap EB ");
        IcMapEP[i] = new TH2F(hnameEP.c_str(),htitleEP.c_str(),100,0.5,100.5,100,0.5,100.5);
        IcMapEP[i]->Sumw2();
        string hnameEM( "AveXtal"+algostring[i]+"RecTimeEMMap"); 
        string htitleEM( "AveXtal "+algostring[i]+" RecTimeEBMap EM ");
        IcMapEM[i] = new TH2F(hnameEM.c_str(),htitleEM.c_str(),100,0.5,100.5,100,0.5,100.5);
        IcMapEM[i]->Sumw2();
    }

    std::cout << "Setting up DetIDs." << std::endl;
    std::map<UInt_t,DetIDStruct> DetIDMap;
    SetupDetIDsEB( DetIDMap );
    SetupDetIDsEE( DetIDMap );

    // >> calcs  <<

    std::cout << "Starting entry loops "<< std::endl;
    const auto nEntries = fInTree->GetEntries();
    for (auto entry = 0U; entry < nEntries; entry++){
	if( entry%100000 == 0 ) std::cout << "Proccessed " << entry << " of " << nEntries << " entries." << std::endl;

        //b_npho_recHits_0->GetEntry(entry);
        //b_npho_recHits_1->GetEntry(entry);
        //std::cout << "GetEntries rh for photons 0,1 Finished "<< std::endl;
        //b_npho_recHits_2->GetEntry(entry);
        //std::cout << "GetEntries rh for photons 2 Finished "<< std::endl;
        //b_npho_recHits_3->GetEntry(entry);
        //std::cout << "GetEntries rh for photons 3 Finished "<< std::endl;
        //b_seedID_0->GetEntry(entry);
        //b_seedID_1->GetEntry(entry);
        //b_seedE_0->GetEntry(entry);
        //b_seedE_1->GetEntry(entry);
        //std::cout << "GetEntries seed Finished "<< std::endl;
        //b_isOOT_0->GetEntry(entry);
        //b_isOOT_1->GetEntry(entry);
        //b_isOOT_2->GetEntry(entry);
        //b_isOOT_3->GetEntry(entry);
        //std::cout << "GetEntries isOOT Finished "<< std::endl;
        //b_smin_0->GetEntry(entry);
        //b_smin_1->GetEntry(entry);
        //b_smin_2->GetEntry(entry);
        //b_smin_3->GetEntry(entry);
        //b_smaj_0->GetEntry(entry);
        //b_smaj_1->GetEntry(entry);
        //b_smaj_2->GetEntry(entry);
        //b_smaj_3->GetEntry(entry);
        //std::cout << "GetEntries smin smaj Finished "<< std::endl;
        b_fInRecHits_E->GetEntry(entry);
        b_fInRecHits_ID->GetEntry(entry);
        b_fInRecHits_time->GetEntry(entry);
        b_fInRecHits_TOF->GetEntry(entry);
        //std::cout << "GetEntries rh info Finished "<< std::endl;
        b_kurhtime->GetEntry(entry);
        b_kurhID->GetEntry(entry);
        b_kuStcrhtime->GetEntry(entry);
        //b_kuNotrhtime->GetEntry(entry);
        b_kuNotStcrhtime->GetEntry(entry);
        //b_kuWootStcrhtime->GetEntry(entry);
        //std::cout << "GetEntries kurh times Finished "<< std::endl;

	//double cl_smin[nPhotons] = { smin_0, smin_1, smin_2, smin_3};
        //double cl_smaj[nPhotons] = { smaj_0, smaj_1, smaj_2, smaj_3};
        //bool cl_isOOT[nPhotons] = { isOOT_0, isOOT_1, isOOT_2, isOOT_3};

        // skip OOT for now
        //inpho.b_isOOT->GetEntry(entry);
        //if (cl_isOOT[ipho]) continue;

        //inpho.b_smin->GetEntry(entry);
        //inpho.b_smaj->GetEntry(entry);

        //if (cl_smin[ipho] > 0.3) continue;
        //if (cl_smaj[ipho] > 0.5) continue;

        const auto nRecHits1 = (*fInRecHits_ID).size(); //(cluster[ipho0])->size();
        //std::cout << "Looping over first recHits"  << std::endl;
        for (auto i = 0U; i < nRecHits1; i++){
             const auto rh_i = i; //(*(cluster[ipho0]))[i]; // position within event rec hits vector
             const auto E_i  = (*fInRecHits_E) [rh_i];
             const auto id_i = (*fInRecHits_ID)[rh_i];
             const auto tof_i = (*fInRecHits_TOF)[rh_i];
             auto RtStc_t_i = 0.0;
             auto RtOOTStc_t_i = 0.0;
             auto WtOOTStc_t_i = 0.0;
             //std::cout << "Getting KU times " << std::endl;
	     if( E_i < ri_ecut ) continue;
             for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
             		if( (*kurhID)[kuseed] == id_i ){
                             RtStc_t_i = (*kuStcrhtime)[kuseed];
                             RtOOTStc_t_i = (*kuNotStcrhtime)[kuseed];
    //                       WtOOTStc_t_i = (*kuWootStcrhtime)[kuseed];
                             break;
                     	}

             }
	     //std::cout << "Getting maps " << std::endl;
             RtStc_t_i += tof_i;
             RtOOTStc_t_i += tof_i;
             // WtOOTStc_t_i += tof_i;
             sumXtalRtStcRecTime[id_i] += RtStc_t_i;
             sumXtalRtOOTStcRecTime[id_i] += RtOOTStc_t_i;
             //sumXtalWtOOTStcRecTime[id_i] += WtOOTStc_t_i;
             numXtalIcRecTime[id_i] += 1;
        } // end loop over rechits
        //std::cout << "RecHits Loop done "<< std::endl;
    }  //  end entry loop

    //double  norm[nAlgos] = { normRtStc, normRtOOTStc };
    std::map<UInt_t,Float_t> *  icmaps[nAlgos] = {&sumXtalRtStcRecTime, &sumXtalRtOOTStcRecTime }; //, sumXtalWtOOTStcRecTime };

    for( auto ai = 0; ai < nAlgos; ai++ ){
	 double drift = 0.0;
	 for( std::map<UInt_t,Float_t>::iterator it=(*icmaps[ai]).begin(); it!=(*icmaps[ai]).end(); ++it){ drift += (((*icmaps[ai])[it->first])/(numXtalIcRecTime[it->first])); }
         for( std::map<UInt_t,Float_t>::iterator it=(*icmaps[ai]).begin(); it!=(*icmaps[ai]).end(); ++it){
                   const auto & fill_idinfo = DetIDMap[it->first];
                   const auto & map_time = (((*icmaps[ai])[it->first])/(numXtalIcRecTime[it->first]) - (drift/(icmaps[ai]->size()))) + offset;
		   //std::cout << "Fill hist for Algo " << i << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                   if( fill_idinfo.ecal == ECAL::EB ){
//		   std::cout << "Fill EB hist for Algo " << ai << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                           (IcMapEB[ai])->Fill( fill_idinfo.i2, fill_idinfo.i1, map_time );
                   } else if( fill_idinfo.ecal == ECAL::EP ){
//                 std::cout << "Fill EP hist for Algo " << ai << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                           (IcMapEP[ai])->Fill( fill_idinfo.i2, fill_idinfo.i1, map_time );
                   } else if( fill_idinfo.ecal == ECAL::EM ){
//                 std::cout << "Fill EM hist for Algo " << ai << " at " << fill_idinfo.i2 << " " << fill_idinfo.i1 << " with " << map_time << " for iter " << iter << std::endl;
                           (IcMapEM[ai])->Fill( fill_idinfo.i2, fill_idinfo.i1, map_time );
                   }
         }
    }

    sumXtalRtStcRecTime.clear();
    sumXtalRtOOTStcRecTime.clear();
    sumXtalWtOOTStcRecTime.clear();
    numXtalIcRecTime.clear();

    fOutFile->cd();

    std::cout << "Write AveXtal Rechit Time Maps" << std::endl;
    for( auto i = 0; i < nAlgos; i++){
		IcMapEB[i]->Write();
        	IcMapEP[i]->Write();
        	IcMapEM[i]->Write();
    }

    delete fInTree;
    delete fOutFile;

}

int main ( int argc, char *argv[] ){

        if( argc != 4 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                auto indir = argv[1];
                auto infilelist = argv[2];
                auto outfilename = argv[3];
                wc_ku_InterCali_aveRecHit_v1( indir, infilelist, outfilename );
        }
        return 1;
}

