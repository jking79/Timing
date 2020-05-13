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

#include "Skimmer_chain.hh"

Skimmer::Skimmer(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig)

  : fInDir(indir), fOutDir(outdir), fFileName(filename), fSkimConfig(skimconfig)
{

  // because root is dumb?
//  gROOT->ProcessLine("#include <vector>");

  ////////////////////////
  // Get all the inputs //
  ////////////////////////
  std::cout << "Setting up inputs for skim" << std::endl;

  // Set skim config options 
  Skimmer::SetupDefaults();
  std::cout << "Running SkimConfig" << std::endl;
  Skimmer::SetupSkimConfig();

  // get detids if skim needs it
  //if (fSkim == SkimType::DiXtal) 
  Common::SetupDetIDs();

  // Get era info
  Common::SetupEras();

  // Get input file
  //const TString infilename = Form("%s/%s", fInDir.Data(), fFileName.Data());
  const std::string ifn_str(fFileName.Data());
  std::cout << "Getting input file " << ifn_str << std::endl;
  std::string outfilename(ifn_str.substr(0,(ifn_str.length()-3)) + "root");
  std::cout << "Outfile Name : " << outfilename << std::endl;
  std::ifstream infile(ifn_str);
  //fInFile = TFile::Open(fFilename.Data());
  //Common::CheckValidFile(fInFile,fFilename);
  std::cout << "Finished getting input file " << ifn_str << std::endl;

  // Get input config tree
  std::string indisphochainname(Form("%s/%s",Common::rootdir.Data(),Common::disphotreename.Data()));
  fInTree = new TChain(indisphochainname.c_str());
  std::string str;
  std::cout << "Adding files to TChain." << std::endl;
  while (std::getline(infile,str)){
	const std::string indir(fInDir.Data());
	auto tfilename = indir + "/" + str;
	std::cout << "--  adding file: " << tfilename << std::endl;
        fInTree->Add(tfilename.c_str());
  }
  std::cout << "Finished getting input chain " << indisphochainname << std::endl;


  // Get main input tree and initialize it
  Skimmer::InitInTree();
  std::cout << "Finished InitInTree " << std::endl;

  // Get PU weights input
  fPUWeights.clear();


  /////////////////////////
  // Set all the outputs //
  /////////////////////////
  std::cout << "Setting up output skim" << std::endl;

  // Make the output file, make trees, then init them
  std::string outpath( fOutDir.Data() + outfilename );
  std::cout << "Opening Outfile : " << outpath << std::endl;
  fOutFile = TFile::Open(outpath.c_str(),"recreate");
  fOutFile->cd();
  
  //fOutConfigTree = new TTree(Common::configtreename.Data(),Common::configtreename.Data());
  fOutTree = new TTree(Common::disphotreename.Data(),Common::disphotreename.Data());

  // Init output info
  //Skimmer::InitAndSetOutConfig();
  Skimmer::InitOutTree();
  //Skimmer::InitOutCutFlowHists();
  std::cout << "Finished setting up output skim" << std::endl;

  isGoodPho = false;
  isEleMatched = false;
  isTrackMatched = false;

  tofHist = new TH1F("tofHist","Time of Flight [ns]",10000,-5,5);
  tofHist->Sumw2(); 
  noEleMatchHist = new TH1F("noEleMatchHist","noEleMatch",400,-20,20);
  noEleMatchHist->Sumw2();
  eleMatchTrueHist = new TH1F("eleMatchTrueHist","eleMatchTrue",400,-20,20);
  eleMatchTrueHist->Sumw2();
  eleMatchFalseHist = new TH1F("eleMatchFalseHist","eleMatchFalse",400,-20,20);
  eleMatchFalseHist->Sumw2();

}

Skimmer::~Skimmer()
{

 std::cout << "Cleaning up after skim" << std::endl; 
  delete fInTree;

  delete tofHist;
  delete noEleMatchHist;
  delete eleMatchTrueHist;
  delete eleMatchFalseHist;

  delete fOutTree;
  delete fOutFile;
}

void Skimmer::EventLoop()
{
  // do loop over events, reading in branches as needed, skimming, filling output trees and hists
  //const auto nEntries = fInTree->GetEntriesFast();
  const auto nEntries = fInTree->GetEntries();
  float minRecE0 = 0.5;
  float minRecE1 = 1.f;
  float minRecE2 = 2.f;
  float minRecE5 = 5.f;
  float minRecE10 = 10.f;
  bool useTOF = true;
  //bool useTOF = false;
  //const auto nEntries = 100;
  for (Long64_t centry = 0; centry < nEntries; centry++)
  //for (auto entry = 0U; entry < 100; entry++)
  {
    // dump status check
    if (centry%Common::nEvCheck == 0 || centry == 0) std::cout << "Processing Entry: " << centry << " out of " << nEntries << std::endl;
    //if (entry%20 == 0 || entry == 0) std::cout << "Processing Entry: " << entry << " out of " << nEntries << std::endl;
    //if( entry > 100 ) break;
    
    auto entry = fInTree->LoadTree(centry);
    //fInTree->GetEntry(centry); 

    // get event weight: no scaling by BR, xsec, lumi, etc.
    const auto wgt    = 1.f; //(fIsMC ? fInEvent.genwgt : 1.f);
    const auto evtwgt = 1.f; //fSampleWeight * wgt; // sample weight for data == 1

    gZmass = 0.f;
    gdR = 0.f;

    if (fSkim == SkimType::Zee)
    {
      
      // build list of "good electrons"
      std::vector<Int_t> good_phos;
      fInEvent.b_vtxZ->GetEntry(entry);
	   fInEvent.b_vtxX->GetEntry(entry);
	   fInEvent.b_vtxY->GetEntry(entry);

     //std::cout << "Starting Zee Skim w/ nPhotons " << Common::nPhotons << endl;   
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
      {
         	auto & inpho = fInPhos[ipho];
         	
         	// 	inpho.b_pt->GetEntry(entry);
         	// 	if (inpho.pt < 40.f) continue;
         
         	inpho.b_hasPixSeed->GetEntry(entry);
         	//cout << "has Pix Seed? " << inpho.hasPixSeed << endl;
         	if (not inpho.hasPixSeed) continue;   //   <<<<<<<<<<<<<<<<<<<<<<<<<<<<< uncomment  temp fix to run 2018?
         
         	inpho.b_gedID->GetEntry(entry);
            //cout << "gedID " << inpho.gedID << endl;
         	if (inpho.gedID < 3) continue; //  <<<<<<<<<<<<<<<<<<<<<<<<<<  change back to inpho.gedID < 3    temp fix ro run 2018
         
         	inpho.b_isOOT->GetEntry(entry);
            //cout << "isOOT " << inpho.isOOT << endl;
         	if (inpho.isOOT) continue;
            //std::cout << "Photon found." << std::endl;  
				inpho.b_elMatched->GetEntry(entry);
            if (not inpho.elMatched) continue; //isEleMatched = true;
				//std::cout << "Photon has electron Match" << std::endl;
				//if( isEleMatched ) {
            //inpho.b_elTrackX->GetEntry(entry);
            //inpho.b_elTrackY->GetEntry(entry);
            inpho.b_elTrackZ->GetEntry(entry);
				//std::cout << inpho.elTrackZ << " " << fInEvent.vtxZ << " " << abs( inpho.elTrackZ - fInEvent.vtxZ ) << std::endl;
				if( abs( inpho.elTrackZ - fInEvent.vtxZ ) > 0.1 ) continue; //isTrackMatched = true;
				//std::cout << "Z Vertex match found" << std::endl;
				//}
         	good_phos.emplace_back(ipho);
      }
      
      // make sure have at least 1 good photon
      if (good_phos.size() < 1) continue;
      // make sure have at least 2 good photons
      if (good_phos.size() < 2) continue;
      // object for containing mass pairs
      std::vector<MassStruct> phopairs;

      // double loop over photons, make masse
      //cout << "good pho loop " << endl;
      for (auto i = 0U; i < good_phos.size(); i++)
      {
        	auto & pho1 = fInPhos[good_phos[i]];
        	pho1.b_pt ->GetEntry(entry);
        	pho1.b_eta->GetEntry(entry);
        	pho1.b_phi->GetEntry(entry);
        	pho1.b_E  ->GetEntry(entry);
        	TLorentzVector pho1vec; 
		   pho1vec.SetPtEtaPhiE(pho1.pt, pho1.eta, pho1.phi, pho1.E);
        
        	for (auto j = i+1; j < good_phos.size(); j++)
        	{
        	  auto & pho2 = fInPhos[good_phos[j]];
        	  pho2.b_pt ->GetEntry(entry);
        	  pho2.b_eta->GetEntry(entry);
        	  pho2.b_phi->GetEntry(entry);
        	  pho2.b_E  ->GetEntry(entry);
        	  TLorentzVector pho2vec; pho2vec.SetPtEtaPhiE(pho2.pt, pho2.eta, pho2.phi, pho2.E);
        	  // get invariant mass
        	  const auto dr12 = pho1vec.DeltaR(pho2vec);
        	  pho1vec += pho2vec;  
        	  phopairs.emplace_back(good_phos[i],good_phos[j],pho1vec.M(),dr12);
        	}
      }
      //cout << "sort by mass " << endl;
      // sort the mass structs
      std::sort(phopairs.begin(),phopairs.end(),
    		[=](const auto & phopair1, const auto & phopair2)
    		{
    		  const auto diff1 = std::abs(phopair1.mass-Common::Zmass);
    		  const auto diff2 = std::abs(phopair2.mass-Common::Zmass);
    		  return diff1 < diff2;
    		});
          
      // get best pair
      const auto & phopair = phopairs.front();
      
      // make sure within 30 GeV
      if ((phopair.mass < 60.f) || (phopair.mass > 150.f)) continue;
      isGoodPho = true;
      gZmass = phopair.mass;
      gdR = phopair.dR12;

      // re-order photons based on pairs
      auto & pho1 = fInPhos[phopair.ipho1];
      auto & pho2 = fInPhos[phopair.ipho2];

      pho1.b_seed->GetEntry(entry);
      pho2.b_seed->GetEntry(entry);
      fInRecHits.b_ID->GetEntry(entry);

      auto seed1 = pho1.seed;
      auto id1 = (*fInRecHits.ID)[seed1];
      //auto t1 = (*fInRecHits.time)[seed1];
      auto seed2 = pho2.seed;
      auto id2 = (*fInRecHits.ID)[seed2];
      //auto t2 = (*fInRecHits.time)[seed2];

  //    nxtal_sep =  0;
      nxtal_sep =  Common::Xtal_Seperation(id1,id2);
  // //  //std::cout << " nxtal_sep : " << nxtal_sep << std::endl;

      pho1.b_pt->GetEntry(entry);
      pho2.b_pt->GetEntry(entry);

      // now start to save them
      ////cout << "save photon " << endl;
      fPhoList.clear();
      fPhoList.emplace_back((pho1.pt > pho2.pt) ? phopair.ipho1 : phopair.ipho2);
      fPhoList.emplace_back((pho1.pt > pho2.pt) ? phopair.ipho2 : phopair.ipho1);
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
      {
			if      (phopair.ipho1 == ipho) continue;
			else if (phopair.ipho2 == ipho) continue;
	
			fPhoList.emplace_back(ipho);
      }
    } // end of ZeeSkim
    else if (fSkim == SkimType::DiXtal) // this is a hack selection, which mixes up seeds and photons --> do NOT use this for analysis
    {
     //std::cout << "Start DiXtal "<< std::endl;
      gZmass = 0.f;     
      gdR = 0.f; 

      // get rechits
      fInRecHits.b_E->GetEntry(entry);
      fInRecHits.b_ID->GetEntry(entry);

      // loop over photons, getting pairs of rec hits that are most energetic and match!
     //std::cout << "Looping over Photons "<< std::endl;
      std::vector<DiXtalInfo> good_pairs;
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
      {	
        	auto & inpho = fInPhos[ipho];
        
        	// skip OOT for now
        	inpho.b_isOOT->GetEntry(entry);
        	if (inpho.isOOT) continue;
        	
        	inpho.b_smin->GetEntry(entry);
        	inpho.b_smaj->GetEntry(entry);
        
        	if (inpho.smin > 0.3) continue;
        	if (inpho.smaj > 0.5) continue;
        		
        	// get pair of rechits that are good candidates : double loop, yo
        	inpho.b_recHits->GetEntry(entry);
        
        	const auto n = inpho.recHits->size();
                //std::cout << "Looping over recHits n = " << n << std::endl;
        	for (auto i = 0U; i < n; i++)
        	{
        	  Bool_t isGoodPair = false;
        
        	  const auto rh_i = (*inpho.recHits)[i]; // position within event rec hits vector
        	  const auto E_i  = (*fInRecHits.E) [rh_i];
        	  const auto id_i = (*fInRecHits.ID)[rh_i];
        
        	  for (auto j = i+1; j < n; j++)
        	  {
        	    const auto rh_j = (*inpho.recHits)[j]; // position within event rec hits vector
        	    const auto E_j  = (*fInRecHits.E) [rh_j];
        	    const auto id_j = (*fInRecHits.ID)[rh_j];
        
        		if (E_i > (1.2f * E_j)) break; // need to be within 20% of energy
                    	if (Common::IsCrossNeighbor(id_i,id_j)) // neighboring crystals
                    	{
                      		good_pairs.emplace_back(rh_i,rh_j,ipho);
                      		isGoodPair = true;
                      		break;
                    	}
        	  } // end inner double loop over rechit
        	  if (isGoodPair) break;
        	} // end outer double loop over rechits
       		//std::cout << "RecHits Loop done "<< std::endl;
      } // end loop over photons
     //std::cout << "Photon Loop done "<< std::endl;

      // skip if no pairs found
      if (good_pairs.size() == 0) continue;
      // sort pairs by highest energy for E1
      std::sort(good_pairs.begin(),good_pairs.end(),
     		[&](const auto & pair1, const auto & pair2)
     		{
     		  return ((*fInRecHits.E)[pair1.rh1] > (*fInRecHits.E)[pair2.rh2]);
     		});

      // now do the unholiest of exercises... set seed ids of first and second photon to pair ids
      const auto & pair = good_pairs.front();
      Skimmer::FillPhoListStandard();
      fOutPhos[0].seed = pair.rh1;
      fOutPhos[1].seed = pair.rh2;

      nxtal_sep = 1;
      fPhoList.clear();
      fPhoList.emplace_back(pair.iph);
      fPhoList.emplace_back(pair.iph);
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++) fPhoList.emplace_back(ipho);
      isGoodPho = true;
      isEleMatched = true;
      isTrackMatched = true;
    }
    else if (fSkim == SkimType::AlwaysTrue) // no skim, just set photon list
    {
      Skimmer::FillPhoListStandard();
    }
    else if (fSkim == SkimType::AlwaysFalse) // just skip all events! testing purposes only...
    {
      continue;
    }
    else
    {
      std::cerr << "How did this happen?? Somehow SkimType Enum is not one that is specified... Exiting..."  << std::endl;
      exit(1);
    }
    //std::cout << "Finished proccessing skim." << std::endl;

    Skimmer::FillOutEvent(entry,evtwgt);
    Skimmer::FillOutPhos(entry);
    // fill the tree
    fOutTree->Fill();
  } // end loop over events
  std::cout << "Finished proccessing skim." << std::endl;

  std::cout << "write hist output!"<< std::endl;
  fOutFile->cd();
  tofHist->Write();
  noEleMatchHist->Write();
  eleMatchTrueHist->Write();
  eleMatchFalseHist->Write();

  std::cout << "write tree output!"<< std::endl;
  //fOutConfigTree->Write();
  fOutTree->Write();
}

void Skimmer::FillOutEvent(const UInt_t entry, const Float_t evtwgt)
{
 //std::cout << "Starting FillOutEvent" << std::endl;
 // get input branches
  fInEvent.b_run->GetEntry(entry);
  fInEvent.b_lumi->GetEntry(entry);
  fInEvent.b_event->GetEntry(entry);
  fInEvent.b_hltSignal->GetEntry(entry);
  fInEvent.b_hltRefPhoID->GetEntry(entry);
  fInEvent.b_hltRefDispID->GetEntry(entry);
  fInEvent.b_hltRefHT->GetEntry(entry);
  fInEvent.b_hltPho50->GetEntry(entry);
  fInEvent.b_hltPho200->GetEntry(entry);
  fInEvent.b_hltDiPho70->GetEntry(entry);
  fInEvent.b_hltDiPho3022M90->GetEntry(entry);
  fInEvent.b_hltDiPho30PV18PV->GetEntry(entry);
  fInEvent.b_hltEle32WPT->GetEntry(entry);
  fInEvent.b_hltDiEle33MW->GetEntry(entry);
  fInEvent.b_hltJet500->GetEntry(entry);
  fInEvent.b_nvtx->GetEntry(entry);
  fInEvent.b_vtxX->GetEntry(entry);
  fInEvent.b_vtxY->GetEntry(entry);
  fInEvent.b_vtxZ->GetEntry(entry);
  fInEvent.b_rho->GetEntry(entry);
  // fInEvent.b_nmuHighT->GetEntry(entry);
  fInEvent.b_nrechits->GetEntry(entry);
  fInEvent.b_nkurechits->GetEntry(entry);
  //if( hasMultiKURecHit ){
  //b_nkuStcrechits->GetEntry(entry);
  //b_nkuNotrechits->GetEntry(entry);
  //b_nkuNotStcrechits->GetEntry(entry);
 // }
  fInEvent.b_nphotons->GetEntry(entry);

 //std::cout << "clearing UncalDigi " << std::endl;

  nurechits = 0;
  ndigis = 0;

   bunch_crossing = 0;
   num_bunch = 0;
   subtrain_position=0;
   train_position=0;
   subtrain_number=0;
   train_number=0;
   
   if( isLHCInfo ) {
   b_bunch_crossing->GetEntry(entry);   //!
   b_num_bunch->GetEntry(entry);   //!

   b_subtrain_position->GetEntry(entry);   //!
   b_train_position->GetEntry(entry);   //!
   b_subtrain_number->GetEntry(entry);   //!
   b_train_number->GetEntry(entry);   //!
   }

 ////std::cout << "lhcinfo done" << std::endl;
  // isMC only conditions
  fOutEvent.run = fInEvent.run;
  fOutEvent.lumi = fInEvent.lumi;
  fOutEvent.event = fInEvent.event;
//  fOutEvent.hltSignal = fInEvent.hltSignal;
//  fOutEvent.hltRefPhoID = fInEvent.hltRefPhoID;
//  fOutEvent.hltRefDispID = fInEvent.hltRefDispID;
//  fOutEvent.hltRefHT = fInEvent.hltRefHT;
//  fOutEvent.hltPho50 = fInEvent.hltPho50;
//  fOutEvent.hltPho200 = fInEvent.hltPho200;
//  fOutEvent.hltDiPho70 = fInEvent.hltDiPho70;
//  fOutEvent.hltDiPho3022M90 = fInEvent.hltDiPho3022M90;
//  fOutEvent.hltDiPho30PV18PV = fInEvent.hltDiPho30PV18PV;
//  fOutEvent.hltEle32WPT = fInEvent.hltEle32WPT;
//  fOutEvent.hltDiEle33MW = fInEvent.hltDiEle33MW;
//  fOutEvent.hltJet500 = fInEvent.hltJet500;
  fOutEvent.nvtx = fInEvent.nvtx;
  fOutEvent.vtxX = fInEvent.vtxX;
  fOutEvent.vtxY = fInEvent.vtxY;
  fOutEvent.vtxZ = fInEvent.vtxZ;
  fOutEvent.rho = fInEvent.rho;
  
  // fOutEvent.nmuHighT = fInEvent.nmuHighT;
  fOutEvent.nrechits = fInEvent.nrechits;
  fOutEvent.nkurechits = fInEvent.nkurechits;
  //if( hasMultiKURecHit ){
  //fOutEvent.nkuStcrechits = fInEvent.nkuStcrechits;
  //fOutEvent.nkuNotrechits = fInEvent.nkuNotrechits;
  //fOutEvent.nkuNotStcrechits = fInEvent.nkuNotStcrechits;
  //}
  fOutEvent.nphotons = fInEvent.nphotons;
  fOutEvent.evtwgt   = evtwgt;


 //std::cout << "event info done" << std::endl;

  // isMC only branches
}

void Skimmer::FillOutPhos(const UInt_t entry)
{  
  // get input photon branches
 //std::cout << "Starting get entry" << std::endl;
  for (auto ipho : fPhoList)
  {
    auto & inpho = fInPhos[ipho];
    
    inpho.b_E->GetEntry(entry);
    inpho.b_pt->GetEntry(entry);
    inpho.b_eta->GetEntry(entry);
    inpho.b_phi->GetEntry(entry);
    inpho.b_scE->GetEntry(entry);
    inpho.b_sceta->GetEntry(entry);
    inpho.b_scphi->GetEntry(entry);
    inpho.b_HoE->GetEntry(entry);
    inpho.b_r9->GetEntry(entry);
    if( hasUrecDigi ) inpho.b_tdz->GetEntry(entry);
    inpho.b_ChgHadIso->GetEntry(entry);
    inpho.b_NeuHadIso->GetEntry(entry);
    inpho.b_PhoIso->GetEntry(entry);
    inpho.b_EcalPFClIso->GetEntry(entry);
    inpho.b_HcalPFClIso->GetEntry(entry);
    inpho.b_TrkIso->GetEntry(entry);
    // inpho.b_ChgHadIsoC->GetEntry(entry);
    // inpho.b_NeuHadIsoC->GetEntry(entry);
    // inpho.b_PhoIsoC->GetEntry(entry);
    // inpho.b_EcalPFClIsoC->GetEntry(entry);
    // inpho.b_HcalPFClIsoC->GetEntry(entry);
    // inpho.b_TrkIsoC->GetEntry(entry);
    inpho.b_sieie->GetEntry(entry);
    // inpho.b_sipip->GetEntry(entry);
    // inpho.b_sieip->GetEntry(entry);
    // inpho.b_e2x2->GetEntry(entry);
    // inpho.b_e3x3->GetEntry(entry);
    // inpho.b_e5x5->GetEntry(entry);
    inpho.b_smaj->GetEntry(entry);
    inpho.b_smin->GetEntry(entry);
    // inpho.b_alpha->GetEntry(entry);
    inpho.b_suisseX->GetEntry(entry);
    inpho.b_isOOT->GetEntry(entry);
    inpho.b_isEB->GetEntry(entry);
    inpho.b_isHLT->GetEntry(entry);
    inpho.b_isTrk->GetEntry(entry);
    inpho.b_passEleVeto->GetEntry(entry);
    inpho.b_hasPixSeed->GetEntry(entry);
    inpho.b_gedID->GetEntry(entry);
    inpho.b_ootID->GetEntry(entry);

   //std::cout << "Finished Base Pho list" << std::endl;
    //if (fInConfig.storeRecHits)
    if( true )
    {
      inpho.b_seed->GetEntry(entry);
      inpho.b_recHits->GetEntry(entry);
    }
    else
    {
      // inpho.b_seedX->GetEntry(entry);
      // inpho.b_seedY->GetEntry(entry);
      // inpho.b_seedZ->GetEntry(entry);
      inpho.b_seedE->GetEntry(entry);
      inpho.b_seedtime->GetEntry(entry);
      inpho.b_seedtimeErr->GetEntry(entry);
      inpho.b_seedTOF->GetEntry(entry);
      inpho.b_seedID->GetEntry(entry);
      // inpho.b_seedisOOT->GetEntry(entry);
      inpho.b_seedisGS6->GetEntry(entry);
      inpho.b_seedisGS1->GetEntry(entry);
      inpho.b_seedped12->GetEntry(entry);
      inpho.b_seedped6->GetEntry(entry);
      inpho.b_seedped1->GetEntry(entry);
      inpho.b_seedpedrms12->GetEntry(entry);
      inpho.b_seedpedrms6->GetEntry(entry);
      inpho.b_seedpedrms1->GetEntry(entry);
    }
  }  
 //std::cout << "Finished Pho list" << std::endl;
  // get input recHits if needed
  //if (fInConfig.storeRecHits)
  if( true )
  {
    // fInRecHits.b_X->GetEntry(entry);
    // fInRecHits.b_Y->GetEntry(entry);
    // fInRecHits.b_Z->GetEntry(entry);
    fInRecHits.b_E->GetEntry(entry);
    fInRecHits.b_time->GetEntry(entry);
    fInRecHits.b_timeErr->GetEntry(entry);
    fInRecHits.b_TOF->GetEntry(entry);
    fInRecHits.b_ID->GetEntry(entry);
    // fInRecHits.b_isOOT->GetEntry(entry);
    fInRecHits.b_isGS6->GetEntry(entry);
    fInRecHits.b_isGS1->GetEntry(entry);
    fInRecHits.b_adcToGeV->GetEntry(entry);
    fInRecHits.b_ped12->GetEntry(entry);
    fInRecHits.b_ped6->GetEntry(entry);
    fInRecHits.b_ped1->GetEntry(entry);
    fInRecHits.b_pedrms12->GetEntry(entry);
    fInRecHits.b_pedrms6->GetEntry(entry);
    fInRecHits.b_pedrms1->GetEntry(entry);

  }

  b_kurhtime->GetEntry(entry);
  b_kurhtimeErr->GetEntry(entry);
  b_kurhID->GetEntry(entry);

  if( hasMultiKURecHit ){
  b_kuStcrhtime->GetEntry(entry);
  b_kuStcrhtimeErr->GetEntry(entry);
  b_kuStcrhID->GetEntry(entry);
  b_kuNotStcrhtime->GetEntry(entry);
  b_kuNotStcrhtimeErr->GetEntry(entry);
  b_kuNotStcrhID->GetEntry(entry);
  b_kuWtStcrhtime->GetEntry(entry);
  b_kuNotStcrhtimeErr->GetEntry(entry);
  b_kuWtStcrhID->GetEntry(entry);
  b_kuWootStcrhtime->GetEntry(entry);
  b_kuNotStcrhtimeErr->GetEntry(entry);
  b_kuWootStcrhID->GetEntry(entry);
  b_kuMfootStcrhtime->GetEntry(entry);
  b_kuNotStcrhtimeErr->GetEntry(entry);
  b_kuMfootStcrhID->GetEntry(entry);
  b_kuMfootCCStcrhtime->GetEntry(entry);
  b_kuMfootCCStcrhtimeErr->GetEntry(entry);
  b_kuMfootCCStcrhID->GetEntry(entry);
  }
        if( hasUrecDigi ){
                //std::cout << "Getting UrecDigi Info" << std::endl;
                b_uRhId->GetEntry(entry);
                b_ootA0->GetEntry(entry);
                b_ootA1->GetEntry(entry);
                b_ootA2->GetEntry(entry);
                b_ootA3->GetEntry(entry);
                b_ootA4->GetEntry(entry);
                b_ootA5->GetEntry(entry);
                b_ootA6->GetEntry(entry);
                b_ootA7->GetEntry(entry);
                b_ootA8->GetEntry(entry);
                b_ootA9->GetEntry(entry);
                b_ndigis->GetEntry(entry);
                b_nurechits->GetEntry(entry);
 //              //std::cout << "Filling ootAs" << std::endl;
        }
 
    out_npho_recHits_0 = (fInPhos[0]).recHits;
    out_npho_recHits_1 = (fInPhos[1]).recHits;
    out_npho_recHits_2 = (fInPhos[2]).recHits;
    out_npho_recHits_3 = (fInPhos[3]).recHits;
  //  out_fInRecHits_E = fInRecHits.E;
  //  out_fInRecHits_ID = fInRecHits.ID;
  //  out_fInRecHits_time = fInRecHits.time;
  //  out_fInRecHits_TOF = fInRecHits.TOF;
  //  out_kurhtime = kurhtime;
  //  out_kurhID = kurhID;
  //  out_kuStcrhtime = kuStcrhtime;
    //out_kuNotrhtime = kuNotrhtime;
  //  out_kuNotStcrhtime = kuNotStcrhtime;
  //  out_kuWootStcrhtime = kuWootStcrhtime;

 //std::cout << "Finished get entry" << std::endl;
  // set output photon branches
  for (auto ipho = 0; ipho < fNOutPhos; ipho++) 
  {
    const auto & inpho = fInPhos[fPhoList[ipho]];
    auto & outpho = fOutPhos[ipho];

    outpho.E = inpho.E;
    outpho.pt = inpho.pt;
    outpho.eta = inpho.eta;
    outpho.phi = inpho.phi;
    outpho.scE = inpho.scE;
    outpho.sceta = inpho.sceta;
    outpho.scphi = inpho.scphi;
    //outpho.HoE = inpho.HoE;
    //outpho.r9 = inpho.r9;
    if( hasUrecDigi ) outpho.tdz = inpho.tdz; 
    else outpho.tdz = 0.0;
    //outpho.ChgHadIso = inpho.ChgHadIso;
    //outpho.NeuHadIso = inpho.NeuHadIso;
    //outpho.PhoIso = inpho.PhoIso;
    //outpho.EcalPFClIso = inpho.EcalPFClIso;
    //outpho.HcalPFClIso = inpho.HcalPFClIso;
    //outpho.TrkIso = inpho.TrkIso;
    // outpho.ChgHadIsoC = inpho.ChgHadIsoC;
    // outpho.NeuHadIsoC = inpho.NeuHadIsoC;
    // outpho.PhoIsoC = inpho.PhoIsoC;
    // outpho.EcalPFClIsoC = inpho.EcalPFClIsoC;
    // outpho.HcalPFClIsoC = inpho.HcalPFClIsoC;
    // outpho.TrkIsoC = inpho.TrkIsoC;
    outpho.sieie = inpho.sieie;
    // outpho.sipip = inpho.sipip;
    // outpho.sieip = inpho.sieip;
    // outpho.e2x2 = inpho.e2x2;
    // outpho.e3x3 = inpho.e3x3;
    // outpho.e5x5 = inpho.e5x5;
    outpho.smaj = inpho.smaj;
    outpho.smin = inpho.smin;
    // outpho.alpha = inpho.alpha;
    outpho.suisseX = inpho.suisseX;
    outpho.isOOT = inpho.isOOT;
    outpho.isEB = inpho.isEB;
    //outpho.isHLT = inpho.isHLT;
    //outpho.isTrk = inpho.isTrk;
    //outpho.passEleVeto = inpho.passEleVeto;
    outpho.hasPixSeed = inpho.hasPixSeed;
    //outpho.gedID = inpho.gedID;
    outpho.ootID = inpho.ootID;

    //if (fInConfig.storeRecHits)
    if ( true )
    {
      // something unholy and utterly disgusting

      auto seed = inpho.seed;
      if( fSkim == SkimType::DiXtal and ipho < 2 ) seed = outpho.seed;
      //const auto seed = (fSkim != SkimType::DiXtal) ? inpho.seed : outpho.seed;

      // store seed info + derived types if seed exists
      if (seed >= 0)
      {
	// outpho.seedX = (*fInRecHits.X)[seed];
	// outpho.seedY = (*fInRecHits.Y)[seed];
	// outpho.seedZ = (*fInRecHits.Z)[seed];
	outpho.seedE = (*fInRecHits.E)[seed];

	outpho.seedtime    = (*fInRecHits.time)   [seed];
	outpho.seedtimeErr = (*fInRecHits.timeErr)[seed];
	outpho.seedTOF     = (*fInRecHits.TOF)    [seed];
   tofHist->Fill(outpho.seedTOF);

   if( ipho < 3 ){
   	inpho.b_elMatched->GetEntry(entry);
   	noEleMatchHist->Fill(outpho.seedtime);
   	if ( inpho.elMatched ) { 
         fInEvent.b_vtxZ->GetEntry(entry);
      	if ( abs( inpho.elTrackZ - fInEvent.vtxZ ) > 0.1 ) eleMatchFalseHist->Fill(outpho.seedtime);
      	else eleMatchTrueHist->Fill(outpho.seedtime);
		}
   }

	// get trigger tower
	outpho.seedTT = Common::GetTriggerTower((*fInRecHits.ID)[seed]);
	
	outpho.seedID    = (*fInRecHits.ID)[seed];
   const auto & sidinfo = Common::DetIDMap[(*fInRecHits.ID)[seed]];
   outpho.seedI1    = sidinfo.i1;
	outpho.seedI2    = sidinfo.i2;
	outpho.seedEcal  = sidinfo.ecal;
	// outpho.seedisOOT = (*fInRecHits.isOOT)[seed];

	outpho.seedootA0 = 0.0;
        outpho.seedootA1 = 0.0;
        outpho.seedootA2 = 0.0;
        outpho.seedootA3 = 0.0;
        outpho.seedootA4 = 0.0;
        outpho.seedootA5 = 0.0;
        outpho.seedootA6 = 0.0;
        outpho.seedootA7 = 0.0;
        outpho.seedootA8 = 0.0;
        outpho.seedootA9 = 0.0;
        outpho.seedootMax = 0.0;
        outpho.seedootMbefore = 0.0;
        outpho.seedootMafter = 0.0;
        outpho.seedootSign = 1;
        outpho.seedootVsum = 0.0;

	outpho.seedisGS6 = (*fInRecHits.isGS6)[seed];
	outpho.seedisGS1 = (*fInRecHits.isGS1)[seed];
	outpho.seedadcToGeV = (*fInRecHits.adcToGeV)[seed];

	outpho.seedped12 = (*fInRecHits.ped12)[seed];
	outpho.seedped6  = (*fInRecHits.ped6) [seed];
	outpho.seedped1  = (*fInRecHits.ped1) [seed];
	outpho.seedpedrms12 = (*fInRecHits.pedrms12)[seed];
	outpho.seedpedrms6  = (*fInRecHits.pedrms6) [seed];
	outpho.seedpedrms1  = (*fInRecHits.pedrms1) [seed];

        for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                if( (*kurhID)[kuseed] == (*fInRecHits.ID)[seed] ){
        		outpho.seedkutime = (*kurhtime)[kuseed];
            outpho.seedkutimeErr = (*kurhtimeErr)[kuseed];
        		outpho.seedkuID = (*kurhID)[kuseed];			
                }
        }

  	     if( hasMultiKURecHit ){
        for(UInt_t kuStcseed = 0; kuStcseed < (*kuStcrhID).size(); kuStcseed++ ){
                if( (*kuStcrhID)[kuStcseed] == (*fInRecHits.ID)[seed] ){
                        outpho.seedkuStctime = (*kuStcrhtime)[kuStcseed];
                        outpho.seedkuStctimeErr = (*kuStcrhtimeErr)[kuStcseed];
                        outpho.seedkuStcID = (*kuStcrhID)[kuStcseed];
                }
        }

        for(UInt_t kuNotStcseed = 0; kuNotStcseed < (*kuNotStcrhID).size(); kuNotStcseed++ ){
                if( (*kuNotStcrhID)[kuNotStcseed] == (*fInRecHits.ID)[seed] ){
                        outpho.seedkuNotStctime = (*kuNotStcrhtime)[kuNotStcseed];
                        outpho.seedkuNotStctimeErr = (*kuNotStcrhtimeErr)[kuNotStcseed];
                        outpho.seedkuNotStcID = (*kuNotStcrhID)[kuNotStcseed];
                }
        }
        for(UInt_t kuWtStcseed = 0; kuWtStcseed < (*kuWtStcrhID).size(); kuWtStcseed++ ){
                if( (*kuWtStcrhID)[kuWtStcseed] == (*fInRecHits.ID)[seed] ){
                        outpho.seedkuWtStctime = (*kuWtStcrhtime)[kuWtStcseed];
                        outpho.seedkuWtStctimeErr = (*kuWtStcrhtimeErr)[kuWtStcseed];
                        outpho.seedkuWtStcID = (*kuWtStcrhID)[kuWtStcseed];
                }
        }
        for(UInt_t kuWootStcseed = 0; kuWootStcseed < (*kuWootStcrhID).size(); kuWootStcseed++ ){
                if( (*kuWootStcrhID)[kuWootStcseed] == (*fInRecHits.ID)[seed] ){
                        outpho.seedkuWootStctime = (*kuWootStcrhtime)[kuWootStcseed];
                        outpho.seedkuWootStctimeErr = (*kuWootStcrhtimeErr)[kuWootStcseed];
                        outpho.seedkuWootStcID = (*kuWootStcrhID)[kuWootStcseed];
                }
        }
        for(UInt_t kuMfootStcseed = 0; kuMfootStcseed < (*kuMfootStcrhID).size(); kuMfootStcseed++ ){
                if( (*kuMfootStcrhID)[kuMfootStcseed] == (*fInRecHits.ID)[seed] ){
                        outpho.seedkuMfootStctime = (*kuMfootStcrhtime)[kuMfootStcseed];
                        outpho.seedkuMfootStcID = (*kuMfootStcrhID)[kuMfootStcseed];
                }
        }
        for(UInt_t kuMfootCCStcseed = 0; kuMfootCCStcseed < (*kuMfootCCStcrhID).size(); kuMfootCCStcseed++ ){
                if( (*kuMfootCCStcrhID)[kuMfootCCStcseed] == (*fInRecHits.ID)[seed] ){
                        outpho.seedkuMfootCCStctime = (*kuMfootCCStcrhtime)[kuMfootCCStcseed];
                        outpho.seedkuMfootCCStctimeErr = (*kuMfootCCStcrhtimeErr)[kuMfootCCStcseed];
                        outpho.seedkuMfootCCStcID = (*kuMfootCCStcrhID)[kuMfootCCStcseed];
                }
        }

        }

        if( hasUrecDigi ){
		   for(UInt_t urseed = 0; urseed < (*uRhId).size(); urseed++ ){
			  if( (*uRhId)[urseed] == (*fInRecHits.ID)[seed] ){
				//std::cout << "Found urec match to inrec" << std::endl;
	        		outpho.seedootA0 = (*ootA0)[urseed];
	        		outpho.seedootA1 = (*ootA1)[urseed];
	        		outpho.seedootA2 = (*ootA2)[urseed];
	        		outpho.seedootA3 = (*ootA3)[urseed];
	        		outpho.seedootA4 = (*ootA4)[urseed];
	        		outpho.seedootA5 = (*ootA5)[urseed];
	        		outpho.seedootA6 = (*ootA6)[urseed];
	        		outpho.seedootA7 = (*ootA7)[urseed];
	        		outpho.seedootA8 = (*ootA8)[urseed];
               outpho.seedootA9 = (*ootA9)[urseed];
				   outpho.seedootMbefore = std::max( outpho.seedootA0, 
								std::max(outpho.seedootA1, 
								std::max(outpho.seedootA2, 
								std::max(outpho.seedootA3, outpho.seedootA4 ))));
               outpho.seedootMafter = std::max( outpho.seedootA5,
                        std::max(outpho.seedootA6,
                        std::max(outpho.seedootA7,
                        std::max(outpho.seedootA8, outpho.seedootA9 )))); 
               outpho.seedootMax = std::max(outpho.seedootMbefore,outpho.seedootMafter);
				   outpho.seedootSign = (outpho.seedootMbefore < outpho.seedootMafter )?1:-1;
				   auto sum1 = outpho.seedootA0 * outpho.seedootA0 + outpho.seedootA1 * outpho.seedootA1;
			 	   auto sum2 = outpho.seedootA2 * outpho.seedootA2 + outpho.seedootA3 * outpho.seedootA3;
				   auto sum3 = outpho.seedootA4 * outpho.seedootA4 + outpho.seedootA5 * outpho.seedootA5;
				   auto sum4 = outpho.seedootA6 * outpho.seedootA6 + outpho.seedootA7 * outpho.seedootA7;
				   auto sum5 = outpho.seedootA8 * outpho.seedootA8 + outpho.seedootA9 * outpho.seedootA9;
				   outpho.seedootVsum = sum1 + sum2 + sum3 + sum4 + sum5;
				   break;
			 }
		  }
      }

	// compute mean time, weighted time, AND
	// weighted time "TOF": really compute weighted time with TOF, then subtract this from weighted time to get "TOF"
	outpho.nrechits = 0;
	outpho.nrechitsLT120 = 0;
	outpho.meantime = 0.f;
	outpho.meantimeLT120 = 0.f;
	outpho.weightedtime = 0.f;
	outpho.weightedtimeLT120 = 0.f;
	outpho.weightedtimeTOF = 0.f;
	outpho.weightedtimeLT120TOF = 0.f;
	Float_t sumweights      = 0.f;
	Float_t sumweightsLT120 = 0.f;
	for (const auto irh : (*inpho.recHits))
	{
	  const Float_t rh_E = (*fInRecHits.E)   [irh];
	  const Float_t rh_T = (*fInRecHits.time)[irh];
	  const Float_t rh_A = (rh_E/(*fInRecHits.adcToGeV)[irh])/(*fInRecHits.pedrms12)[irh]; // amplitude normalized by pedestal noise
	  const Float_t inv_weight_2 = 1.f/(std::pow(Common::timefitN/rh_A,2)+2.f*std::pow(Common::timefitC,2));
	  const Float_t rh_TOF = (*fInRecHits.TOF)[irh];

	  outpho.nrechits++;
	  outpho.meantime += rh_T;

	  outpho.weightedtime    += rh_T*inv_weight_2;
	  outpho.weightedtimeTOF += (rh_T+rh_TOF)*inv_weight_2;
	  sumweights             += inv_weight_2;
	  
	  if (rh_E > 120.f) continue;

	  outpho.nrechitsLT120++;
	  outpho.meantimeLT120 += rh_T;

	  outpho.weightedtimeLT120    += rh_T*inv_weight_2;
	  outpho.weightedtimeLT120TOF += (rh_T+rh_TOF)*inv_weight_2;
	  sumweightsLT120             += inv_weight_2;
	}

	// set the derived types
	if   (outpho.nrechits > 0)
	{
	  outpho.meantime        /= outpho.nrechits;
	  outpho.weightedtime    /= sumweights;
	  outpho.weightedtimeTOF /= sumweights;

	  // hack for weighted time "TOF"
	  outpho.weightedtimeTOF -= outpho.weightedtime;
	}
	else 
	{
	  outpho.meantime        = -9999.f;
	  outpho.weightedtime    = -9999.f;
	  outpho.weightedtimeTOF = -9999.f*2.f;
	}

	if   (outpho.nrechitsLT120 > 0)
	{
	  outpho.meantimeLT120        /= outpho.nrechitsLT120;
	  outpho.weightedtimeLT120    /= sumweightsLT120;
	  outpho.weightedtimeLT120TOF /= sumweightsLT120;

	  // hack for weighted time "TOF"
	  outpho.weightedtimeLT120TOF -= outpho.weightedtimeLT120;
	}
	else
	{
	  outpho.meantimeLT120        = -9999.f;
	  outpho.weightedtimeLT120    = -9999.f;
	  outpho.weightedtimeLT120TOF = -9999.f*2.f;
	}
      } // end check that seed exists
      else
      {
	// outpho.seedX = -9999.f;
	// outpho.seedY = -9999.f;
	// outpho.seedZ = -9999.f;
	outpho.seedE = -9999.f;

	outpho.seedtime    = -9999.f;
	// outpho.seedtimeErr = -9999.f;
	outpho.seedTOF     = -9999.f;	

	// outpho.seedID    = 0;
	// outpho.seedisOOT = -1;
	outpho.seedTT    = -9999;

	outpho.seedisGS6 = -1;
	outpho.seedisGS1 = -1;
	outpho.seedadcToGeV = -9999.f;
	outpho.seedped12 = -9999.f;
	outpho.seedped6  = -9999.f;
	outpho.seedped1  = -9999.f;
	outpho.seedpedrms12 = -9999.f;
	outpho.seedpedrms6 = -9999.f;
	outpho.seedpedrms1 = -9999.f;

        outpho.seedkuE = -9999.f;
        outpho.seedkutime    = -9999.f;
        outpho.seedkutimeErr = -9999.f;
        outpho.seedkuTOF     = -9999.f;
        outpho.seedkuID    = 0;

  	if( hasMultiKURecHit ){
        outpho.seedkuStcE = -9999.f;
        outpho.seedkuStctime    = -9999.f;
        outpho.seedkuStctimeErr = -9999.f;
        outpho.seedkuStcTOF     = -9999.f;
        outpho.seedkuStcID    = 0;

        outpho.seedkuNotStcE = -9999.f;
        outpho.seedkuNotStctime    = -9999.f;
        outpho.seedkuNotStctimeErr = -9999.f;
        outpho.seedkuNotStcTOF     = -9999.f;
        outpho.seedkuNotStcID    = 0;

        outpho.seedkuWtStcE = -9999.f;
        outpho.seedkuWtStctime    = -9999.f;
        outpho.seedkuWtStctimeErr = -9999.f;
        outpho.seedkuWtStcTOF     = -9999.f;
        outpho.seedkuWtStcID    = 0;

        outpho.seedkuWootStcE = -9999.f;
        outpho.seedkuWootStctime    = -9999.f;
        outpho.seedkuWootStctimeErr = -9999.f;
        outpho.seedkuWootStcTOF     = -9999.f;
        outpho.seedkuWootStcID    = 0;

        outpho.seedkuMfootStcE = -9999.f;
        outpho.seedkuMfootStctime    = -9999.f;
        outpho.seedkuMfootStctimeErr = -9999.f;
        outpho.seedkuMfootStcTOF     = -9999.f;
        outpho.seedkuMfootStcID    = 0;

        outpho.seedkuMfootCCStcE = -9999.f;
        outpho.seedkuMfootCCStctime    = -9999.f;
        outpho.seedkuMfootCCStctimeErr = -9999.f;
        outpho.seedkuMfootCCStcTOF     = -9999.f;
        outpho.seedkuMfootCCStcID    = 0;

        }

	outpho.nrechits             = -1;
	outpho.nrechitsLT120        = -1;
	outpho.meantime             = -9999.f;
	outpho.meantimeLT120        = -9999.f;
	outpho.weightedtime         = -9999.f;
	outpho.weightedtimeLT120    = -9999.f;
	outpho.weightedtimeTOF      = -9999.f*2.f;
	outpho.weightedtimeLT120TOF = -9999.f*2.f;
      }
    } // end check over store rechits
    else
    {
      // outpho.seedX = inpho.seedX;
      // outpho.seedY = inpho.seedY;
      // outpho.seedZ = inpho.seedZ;
      outpho.seedE = inpho.seedE;
      outpho.seedtime = inpho.seedtime;
      // outpho.seedtimeErr = inpho.seedtimeErr;
      outpho.seedTOF = inpho.seedTOF;
      // outpho.seedID = inpho.seedID;
      // outpho.seedisOOT = inpho.seedisOOT;
      outpho.seedTT = Common::GetTriggerTower(inpho.seedID);
      outpho.seedisGS6 = inpho.seedisGS1;
      outpho.seedisGS1 = inpho.seedisGS6;
      outpho.seedadcToGeV = inpho.seedadcToGeV;
      outpho.seedped12 = inpho.seedped12;
      outpho.seedped6 = inpho.seedped6;
      outpho.seedped1 = inpho.seedped1;
      outpho.seedpedrms12 = inpho.seedpedrms12;
      outpho.seedpedrms6 = inpho.seedpedrms6;
      outpho.seedpedrms1 = inpho.seedpedrms1;

    }
    
  }
}

void Skimmer::InitInTree() 
{
  Skimmer::InitInStructs();
  Skimmer::InitInBranchVecs();
  Skimmer::InitInBranches();
}

void Skimmer::InitInStructs()
{

  fInPhos.clear();
  fInPhos.resize(Common::nPhotons);
}

void Skimmer::InitInBranchVecs()
{
  fInJets.E = 0;
  fInJets.pt = 0;
  fInJets.phi = 0;
  fInJets.eta = 0;
  fInJets.ID = 0;

  // fInJets.NHF = 0;
  // fInJets.NEMF = 0;
  // fInJets.CHF = 0;
  // fInJets.CEMF = 0;
  // fInJets.MUF = 0;
  // fInJets.NHM = 0;
  // fInJets.CHM = 0;

  kurhE = 0;
  kurhtime = 0;
  kurhtimeErr = 0;
  kurhTOF = 0;
  kurhID = 0;

  if( hasMultiKURecHit ){
  kuStcrhE = 0;
  kuStcrhtime = 0;
  kuStcrhtimeErr = 0;
  kuStcrhTOF = 0;
  kuStcrhID = 0;

  kuNotStcrhE = 0;
  kuNotStcrhtime = 0;
  kuNotStcrhtimeErr = 0;
  kuNotStcrhTOF = 0;
  kuNotStcrhID = 0;

  kuWootStcrhE = 0;
  kuWootStcrhtime = 0;
  kuWootStcrhtimeErr = 0;
  kuWootStcrhTOF = 0;
  kuWootStcrhID = 0;

  kuWtStcrhE = 0;
  kuWtStcrhtime = 0;
  kuWtStcrhtimeErr = 0;
  kuWtStcrhTOF = 0;
  kuWtStcrhID = 0;

  kuMfootStcrhE = 0;
  kuMfootStcrhtime = 0;
  kuMfootStcrhtimeErr = 0;
  kuMfootStcrhTOF = 0;
  kuMfootStcrhID = 0;

  kuMfootCCStcrhtime = 0;
  kuMfootCCStcrhtime = 0;
  kuMfootCCStcrhtimeErr = 0;
  kuMfootCCStcrhTOF = 0;
  kuMfootCCStcrhID = 0;

  }

  if( hasUrecDigi ){
   ootA0 = 0;
   ootA1 = 0;
   ootA2 = 0;
   ootA3 = 0;
   ootA4 = 0;
   ootA5 = 0;
   ootA6 = 0;
   ootA7 = 0;
   ootA8 = 0;
   ootA9 = 0;
   ootMax = 0;
   ootVsum = 0;
   uRhId = 0;
  }

  //if (fInConfig.storeRecHits) 
  if ( true )
  {
    // fInRecHits.X = 0;
    // fInRecHits.Y = 0;
    // fInRecHits.Z = 0;
    fInRecHits.E = 0;
    fInRecHits.time = 0;
    fInRecHits.timeErr = 0;
    fInRecHits.TOF = 0;
    fInRecHits.ID = 0;
    // fInRecHits.isOOT = 0;
    fInRecHits.isGS6 = 0;
    fInRecHits.isGS1 = 0;
    fInRecHits.adcToGeV = 0;
    fInRecHits.ped12 = 0;
    fInRecHits.ped6 = 0;
    fInRecHits.ped1 = 0;
    fInRecHits.pedrms12 = 0;
    fInRecHits.pedrms6 = 0;
    fInRecHits.pedrms1 = 0;

    for (auto ipho = 0; ipho < Common::nPhotons; ipho++) 
    {
      fInPhos[ipho].recHits = 0;
    }  
  }
}

void Skimmer::InitInBranches()
{

  fInTree->SetBranchAddress(fInEvent.s_run.c_str(), &fInEvent.run, &fInEvent.b_run);
  fInTree->SetBranchAddress(fInEvent.s_lumi.c_str(), &fInEvent.lumi, &fInEvent.b_lumi);
  fInTree->SetBranchAddress(fInEvent.s_event.c_str(), &fInEvent.event, &fInEvent.b_event);

   if( isLHCInfo ){
   fInTree->SetBranchAddress("bunch_crossing", &bunch_crossing, &b_bunch_crossing);
   fInTree->SetBranchAddress("num_bunch", &num_bunch, &b_num_bunch);
   fInTree->SetBranchAddress("subtrain_position", &subtrain_position, &b_subtrain_position);
   fInTree->SetBranchAddress("train_position", &train_position, &b_train_position);
   fInTree->SetBranchAddress("subtrain_number", &subtrain_number, &b_subtrain_number);
   fInTree->SetBranchAddress("train_number", &train_number, &b_train_number);
   fInTree->SetBranchAddress("beam1_VC", beam1_VC, &b_beam1_VC);
   fInTree->SetBranchAddress("beam2_VC", beam2_VC, &b_beam2_VC);
   fInTree->SetBranchAddress("beam1_RF", beam1_RF, &b_beam1_RF);
   fInTree->SetBranchAddress("beam2_RF", beam2_RF, &b_beam2_RF);
   }

   fInTree->SetBranchAddress("kurhtime", &kurhtime, &b_kurhtime);
   fInTree->SetBranchAddress("kurhtimeErr", &kurhtimeErr, &b_kurhtimeErr);
   fInTree->SetBranchAddress("kurhID", &kurhID, &b_kurhID);

   if( hasMultiKURecHit ){
   fInTree->SetBranchAddress("kuStcrhtime", &kuStcrhtime, &b_kuStcrhtime);
   fInTree->SetBranchAddress("kuStcrhtimeErr", &kuStcrhtimeErr, &b_kuStcrhtimeErr);
   fInTree->SetBranchAddress("kuStcrhID", &kuStcrhID, &b_kuStcrhID);

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

   }

  if( hasUrecDigi ){
     fInTree->SetBranchAddress("nurechits", &nurechits, &b_nurechits);
     fInTree->SetBranchAddress("ndigis", &ndigis, &b_ndigis);
     fInTree->SetBranchAddress("uRhId", &uRhId, &b_uRhId);
     fInTree->SetBranchAddress("ootA0", &ootA0, &b_ootA0);
     fInTree->SetBranchAddress("ootA1", &ootA1, &b_ootA1);
     fInTree->SetBranchAddress("ootA2", &ootA2, &b_ootA2);
     fInTree->SetBranchAddress("ootA3", &ootA3, &b_ootA3);
     fInTree->SetBranchAddress("ootA4", &ootA4, &b_ootA4);
     fInTree->SetBranchAddress("ootA5", &ootA5, &b_ootA5);
     fInTree->SetBranchAddress("ootA6", &ootA6, &b_ootA6);
     fInTree->SetBranchAddress("ootA7", &ootA7, &b_ootA7);
     fInTree->SetBranchAddress("ootA8", &ootA8, &b_ootA8);
     fInTree->SetBranchAddress("ootA9", &ootA9, &b_ootA9);
  }

  fInTree->SetBranchAddress(fInEvent.s_hltSignal.c_str(), &fInEvent.hltSignal, &fInEvent.b_hltSignal);
  fInTree->SetBranchAddress(fInEvent.s_hltRefPhoID.c_str(), &fInEvent.hltRefPhoID, &fInEvent.b_hltRefPhoID);
  fInTree->SetBranchAddress(fInEvent.s_hltRefDispID.c_str(), &fInEvent.hltRefDispID, &fInEvent.b_hltRefDispID);
  fInTree->SetBranchAddress(fInEvent.s_hltRefHT.c_str(), &fInEvent.hltRefHT, &fInEvent.b_hltRefHT);
  fInTree->SetBranchAddress(fInEvent.s_hltPho50.c_str(), &fInEvent.hltPho50, &fInEvent.b_hltPho50);
  fInTree->SetBranchAddress(fInEvent.s_hltPho200.c_str(), &fInEvent.hltPho200, &fInEvent.b_hltPho200);
  fInTree->SetBranchAddress(fInEvent.s_hltDiPho70.c_str(), &fInEvent.hltDiPho70, &fInEvent.b_hltDiPho70);
  fInTree->SetBranchAddress(fInEvent.s_hltDiPho3022M90.c_str(), &fInEvent.hltDiPho3022M90, &fInEvent.b_hltDiPho3022M90);
  fInTree->SetBranchAddress(fInEvent.s_hltDiPho30PV18PV.c_str(), &fInEvent.hltDiPho30PV18PV, &fInEvent.b_hltDiPho30PV18PV);
  fInTree->SetBranchAddress(fInEvent.s_hltEle32WPT.c_str(), &fInEvent.hltEle32WPT, &fInEvent.b_hltEle32WPT);
  fInTree->SetBranchAddress(fInEvent.s_hltDiEle33MW.c_str(), &fInEvent.hltDiEle33MW, &fInEvent.b_hltDiEle33MW);
  fInTree->SetBranchAddress(fInEvent.s_hltJet500.c_str(), &fInEvent.hltJet500, &fInEvent.b_hltJet500);
  
  fInTree->SetBranchAddress(fInEvent.s_metPV.c_str(), &fInEvent.metPV, &fInEvent.b_metPV);
  fInTree->SetBranchAddress(fInEvent.s_metBeamHalo.c_str(), &fInEvent.metBeamHalo, &fInEvent.b_metBeamHalo);
  fInTree->SetBranchAddress(fInEvent.s_metHBHENoise.c_str(), &fInEvent.metHBHENoise, &fInEvent.b_metHBHENoise);
  fInTree->SetBranchAddress(fInEvent.s_metHBHEisoNoise.c_str(), &fInEvent.metHBHEisoNoise, &fInEvent.b_metHBHEisoNoise);
  fInTree->SetBranchAddress(fInEvent.s_metECALTP.c_str(), &fInEvent.metECALTP, &fInEvent.b_metECALTP);
  fInTree->SetBranchAddress(fInEvent.s_metPFMuon.c_str(), &fInEvent.metPFMuon, &fInEvent.b_metPFMuon);
  fInTree->SetBranchAddress(fInEvent.s_metPFChgHad.c_str(), &fInEvent.metPFChgHad, &fInEvent.b_metPFChgHad);
  fInTree->SetBranchAddress(fInEvent.s_metEESC.c_str(), &fInEvent.metEESC, &fInEvent.b_metEESC);
  // fInTree->SetBranchAddress(fInEvent.s_metECALCalib.c_str(), &fInEvent.metECALCalib, &fInEvent.b_metECALCalib);
  fInTree->SetBranchAddress(fInEvent.s_metECALBadCalib.c_str(), &fInEvent.metECALBadCalib, &fInEvent.b_metECALBadCalib);

  fInTree->SetBranchAddress(fInEvent.s_nvtx.c_str(), &fInEvent.nvtx, &fInEvent.b_nvtx);
  fInTree->SetBranchAddress(fInEvent.s_vtxX.c_str(), &fInEvent.vtxX, &fInEvent.b_vtxX);
  fInTree->SetBranchAddress(fInEvent.s_vtxY.c_str(), &fInEvent.vtxY, &fInEvent.b_vtxY);
  fInTree->SetBranchAddress(fInEvent.s_vtxZ.c_str(), &fInEvent.vtxZ, &fInEvent.b_vtxZ);
  fInTree->SetBranchAddress(fInEvent.s_rho.c_str(), &fInEvent.rho, &fInEvent.b_rho);


  fInTree->SetBranchAddress(fInEvent.s_nrechits.c_str(), &fInEvent.nrechits, &fInEvent.b_nrechits);
  fInTree->SetBranchAddress(fInEvent.s_nkurechits.c_str(), &fInEvent.nkurechits, &fInEvent.b_nkurechits);
  //if( hasMultiKURecHit ){
  //fInTree->SetBranchAddress("nkuStcrechits", &nkuStcrechits, &b_nkuStcrechits);
  //fInTree->SetBranchAddress("nkuNotrechits", &nkuNotrechits, &b_nkuNotrechits);
  //fInTree->SetBranchAddress("nkuNotStcrechits", &nkuNotStcrechits, &b_nkuNotStcrechits);
 // }

  //if (fInConfig.storeRecHits)
  if ( true )
  {
    // fInTree->SetBranchAddress(fInRecHits.s_X.c_str(), &fInRecHits.X, &fInRecHits.b_X);
    // fInTree->SetBranchAddress(fInRecHits.s_Y.c_str(), &fInRecHits.Y, &fInRecHits.b_Y);
    // fInTree->SetBranchAddress(fInRecHits.s_Z.c_str(), &fInRecHits.Z, &fInRecHits.b_Z);
    fInTree->SetBranchAddress(fInRecHits.s_E.c_str(), &fInRecHits.E, &fInRecHits.b_E);
    fInTree->SetBranchAddress(fInRecHits.s_time.c_str(), &fInRecHits.time, &fInRecHits.b_time);
    fInTree->SetBranchAddress(fInRecHits.s_timeErr.c_str(), &fInRecHits.timeErr, &fInRecHits.b_timeErr);
    fInTree->SetBranchAddress(fInRecHits.s_TOF.c_str(), &fInRecHits.TOF, &fInRecHits.b_TOF);
    fInTree->SetBranchAddress(fInRecHits.s_ID.c_str(), &fInRecHits.ID, &fInRecHits.b_ID);
    //fInTree->SetBranchAddress(fInRecHits.s_isOOT.c_str(), &fInRecHits.isOOT, &fInRecHits.b_isOOT);
    fInTree->SetBranchAddress(fInRecHits.s_isGS6.c_str(), &fInRecHits.isGS6, &fInRecHits.b_isGS6);
    fInTree->SetBranchAddress(fInRecHits.s_isGS1.c_str(), &fInRecHits.isGS1, &fInRecHits.b_isGS1);
    fInTree->SetBranchAddress(fInRecHits.s_adcToGeV.c_str(), &fInRecHits.adcToGeV, &fInRecHits.b_adcToGeV);
    fInTree->SetBranchAddress(fInRecHits.s_ped12.c_str(), &fInRecHits.ped12, &fInRecHits.b_ped12);
    fInTree->SetBranchAddress(fInRecHits.s_ped6.c_str(), &fInRecHits.ped6, &fInRecHits.b_ped6);
    fInTree->SetBranchAddress(fInRecHits.s_ped1.c_str(), &fInRecHits.ped1, &fInRecHits.b_ped1);
    fInTree->SetBranchAddress(fInRecHits.s_pedrms12.c_str(), &fInRecHits.pedrms12, &fInRecHits.b_pedrms12);
    fInTree->SetBranchAddress(fInRecHits.s_pedrms6.c_str(), &fInRecHits.pedrms6, &fInRecHits.b_pedrms6);
    fInTree->SetBranchAddress(fInRecHits.s_pedrms1.c_str(), &fInRecHits.pedrms1, &fInRecHits.b_pedrms1);
  

  }

  fInTree->SetBranchAddress(fInEvent.s_nphotons.c_str(), &fInEvent.nphotons, &fInEvent.b_nphotons);
  for (auto ipho = 0; ipho < Common::nPhotons; ipho++) 
  {
    auto & pho = fInPhos[ipho];
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_E.c_str(),ipho), &pho.E, &pho.b_E);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_pt.c_str(),ipho), &pho.pt, &pho.b_pt);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_eta.c_str(),ipho), &pho.eta, &pho.b_eta);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_phi.c_str(),ipho), &pho.phi, &pho.b_phi);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_scE.c_str(),ipho), &pho.scE, &pho.b_scE);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_sceta.c_str(),ipho), &pho.sceta, &pho.b_sceta);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_scphi.c_str(),ipho), &pho.scphi, &pho.b_scphi);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_HoE.c_str(),ipho), &pho.HoE, &pho.b_HoE);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_r9.c_str(),ipho), &pho.r9, &pho.b_r9);
    if( hasUrecDigi ) fInTree->SetBranchAddress(Form("%s_%i",pho.s_tdz.c_str(),ipho), &pho.tdz, &pho.b_tdz);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_ChgHadIso.c_str(),ipho), &pho.ChgHadIso, &pho.b_ChgHadIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_NeuHadIso.c_str(),ipho), &pho.NeuHadIso, &pho.b_NeuHadIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_PhoIso.c_str(),ipho), &pho.PhoIso, &pho.b_PhoIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_EcalPFClIso.c_str(),ipho), &pho.EcalPFClIso, &pho.b_EcalPFClIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_HcalPFClIso.c_str(),ipho), &pho.HcalPFClIso, &pho.b_HcalPFClIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_TrkIso.c_str(),ipho), &pho.TrkIso, &pho.b_TrkIso);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_ChgHadIsoC.c_str(),ipho), &pho.ChgHadIsoC, &pho.b_ChgHadIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_NeuHadIsoC.c_str(),ipho), &pho.NeuHadIsoC, &pho.b_NeuHadIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_PhoIsoC.c_str(),ipho), &pho.PhoIsoC, &pho.b_PhoIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_EcalPFClIsoC.c_str(),ipho), &pho.EcalPFClIsoC, &pho.b_EcalPFClIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_HcalPFClIsoC.c_str(),ipho), &pho.HcalPFClIsoC, &pho.b_HcalPFClIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_TrkIsoC.c_str(),ipho), &pho.TrkIsoC, &pho.b_TrkIsoC);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_sieie.c_str(),ipho), &pho.sieie, &pho.b_sieie);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_sipip.c_str(),ipho), &pho.sipip, &pho.b_sipip);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_sieip.c_str(),ipho), &pho.sieip, &pho.b_sieip);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_e2x2.c_str(),ipho), &pho.e2x2, &pho.b_e2x2);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_e3x3.c_str(),ipho), &pho.e3x3, &pho.b_e3x3);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_e5x5.c_str(),ipho), &pho.e5x5, &pho.b_e5x5);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_smaj.c_str(),ipho), &pho.smaj, &pho.b_smaj);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_smin.c_str(),ipho), &pho.smin, &pho.b_smin);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_alpha.c_str(),ipho), &pho.alpha, &pho.b_alpha);
    //if (fInConfig.storeRecHits)
    if ( true )
    {
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seed.c_str(),ipho), &pho.seed, &pho.b_seed);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_recHits.c_str(),ipho), &pho.recHits, &pho.b_recHits);
      //fInTree->SetBranchAddress(Form("%s_%i",pho.s_kurecHits.c_str(),ipho), &pho.kurecHits, &pho.b_kurecHits);
    }
    else
    {
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedX.c_str(),ipho), &pho.seedX, &pho.b_seedX);
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedY.c_str(),ipho), &pho.seedY, &pho.b_seedY);
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedZ.c_str(),ipho), &pho.seedZ, &pho.b_seedZ);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedE.c_str(),ipho), &pho.seedE, &pho.b_seedE);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedtime.c_str(),ipho), &pho.seedtime, &pho.b_seedtime);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedtimeErr.c_str(),ipho), &pho.seedtimeErr, &pho.b_seedtimeErr);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedTOF.c_str(),ipho), &pho.seedTOF, &pho.b_seedTOF);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedID.c_str(),ipho), &pho.seedID, &pho.b_seedID);
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedisOOT.c_str(),ipho), &pho.seedisOOT, &pho.b_seedisOOT);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedisGS6.c_str(),ipho), &pho.seedisGS6, &pho.b_seedisGS6);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedisGS1.c_str(),ipho), &pho.seedisGS1, &pho.b_seedisGS1);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedadcToGeV.c_str(),ipho), &pho.seedadcToGeV, &pho.b_seedadcToGeV);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedped12.c_str(),ipho), &pho.seedped12, &pho.b_seedped12);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedped6.c_str(),ipho), &pho.seedped6, &pho.b_seedped6);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedped1.c_str(),ipho), &pho.seedped1, &pho.b_seedped1);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedpedrms12.c_str(),ipho), &pho.seedpedrms12, &pho.b_seedpedrms12);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedpedrms6.c_str(),ipho), &pho.seedpedrms6, &pho.b_seedpedrms6);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedpedrms1.c_str(),ipho), &pho.seedpedrms1, &pho.b_seedpedrms1);

    }
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_suisseX.c_str(),ipho), &pho.suisseX, &pho.b_suisseX);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isOOT.c_str(),ipho), &pho.isOOT, &pho.b_isOOT);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isEB.c_str(),ipho), &pho.isEB, &pho.b_isEB);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isHLT.c_str(),ipho), &pho.isHLT, &pho.b_isHLT);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isTrk.c_str(),ipho), &pho.isTrk, &pho.b_isTrk);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_passEleVeto.c_str(),ipho), &pho.passEleVeto, &pho.b_passEleVeto);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_hasPixSeed.c_str(),ipho), &pho.hasPixSeed, &pho.b_hasPixSeed);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_gedID.c_str(),ipho), &pho.gedID, &pho.b_gedID);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_ootID.c_str(),ipho), &pho.ootID, &pho.b_ootID);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_elMatched.c_str(),ipho), &pho.elMatched, &pho.b_elMatched);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_elTrackX.c_str(),ipho), &pho.elTrackX, &pho.b_elTrackX);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_elTrackY.c_str(),ipho), &pho.elTrackY, &pho.b_elTrackY);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_elTrackZ.c_str(),ipho), &pho.elTrackZ, &pho.b_elTrackZ);  
  }
}

void Skimmer::InitOutTree()
{
  Skimmer::InitOutStructs();
  Skimmer::InitOutBranches();
}

void Skimmer::InitOutStructs()
{

  fOutPhos.clear();
  fOutPhos.resize(Common::nPhotons);
//  fOutPhos.resize(Common::nPhotons+2);

}

void Skimmer::InitOutBranches()
{

  fOutTree->Branch(fOutEvent.s_run.c_str(), &fOutEvent.run);
  fOutTree->Branch(fOutEvent.s_lumi.c_str(), &fOutEvent.lumi);
  fOutTree->Branch(fOutEvent.s_event.c_str(), &fOutEvent.event);

  fOutTree->Branch("gZmass",&gZmass);
  fOutTree->Branch("gdR",&gdR);
  fOutTree->Branch("bunch_crossing",&bunch_crossing);
  fOutTree->Branch("num_bunch",&num_bunch);
  fOutTree->Branch("subtrain_position",&subtrain_position);
  fOutTree->Branch("train_position",&train_position);
  fOutTree->Branch("subtrain_number",&subtrain_number);
  fOutTree->Branch("train_number",&train_number);
  fOutTree->Branch("nxtal_sep",&nxtal_sep);

  //fOutTree->Branch(fOutEvent.s_hltSignal.c_str(), &fOutEvent.hltSignal);
  //fOutTree->Branch(fOutEvent.s_hltRefPhoID.c_str(), &fOutEvent.hltRefPhoID);
  //fOutTree->Branch(fOutEvent.s_hltRefDispID.c_str(), &fOutEvent.hltRefDispID);
  //fOutTree->Branch(fOutEvent.s_hltRefHT.c_str(), &fOutEvent.hltRefHT);
  //fOutTree->Branch(fOutEvent.s_hltPho50.c_str(), &fOutEvent.hltPho50);
  //fOutTree->Branch(fOutEvent.s_hltPho200.c_str(), &fOutEvent.hltPho200);
  //fOutTree->Branch(fOutEvent.s_hltDiPho70.c_str(), &fOutEvent.hltDiPho70);
  //fOutTree->Branch(fOutEvent.s_hltDiPho3022M90.c_str(), &fOutEvent.hltDiPho3022M90);
  //fOutTree->Branch(fOutEvent.s_hltDiPho30PV18PV.c_str(), &fOutEvent.hltDiPho30PV18PV);
  //fOutTree->Branch(fOutEvent.s_hltEle32WPT.c_str(), &fOutEvent.hltEle32WPT);
  //fOutTree->Branch(fOutEvent.s_hltDiEle33MW.c_str(), &fOutEvent.hltDiEle33MW);
  //fOutTree->Branch(fOutEvent.s_hltJet500.c_str(), &fOutEvent.hltJet500);

  fOutTree->Branch(fOutEvent.s_nvtx.c_str(), &fOutEvent.nvtx);
  fOutTree->Branch(fOutEvent.s_vtxX.c_str(), &fOutEvent.vtxX);
  fOutTree->Branch(fOutEvent.s_vtxY.c_str(), &fOutEvent.vtxY);
  fOutTree->Branch(fOutEvent.s_vtxZ.c_str(), &fOutEvent.vtxZ);
  fOutTree->Branch(fOutEvent.s_rho.c_str(), &fOutEvent.rho);

  //fOutTree->Branch(fOutEvent.s_t1pfMETpt.c_str(), &fOutEvent.t1pfMETpt);
  //fOutTree->Branch(fOutEvent.s_t1pfMETphi.c_str(), &fOutEvent.t1pfMETphi);
  //fOutTree->Branch(fOutEvent.s_t1pfMETsumEt.c_str(), &fOutEvent.t1pfMETsumEt);

  //fOutTree->Branch(fOutEvent.s_njets.c_str(), &fOutEvent.njets);
  //if (fSkim != SkimType::DiXtal)
  //{
  //  fOutTree->Branch(fOutJets.s_E.c_str(), &fOutJets.E_f);
  //  fOutTree->Branch(fOutJets.s_pt.c_str(), &fOutJets.pt_f);
  //  fOutTree->Branch(fOutJets.s_phi.c_str(), &fOutJets.phi_f);
  //  fOutTree->Branch(fOutJets.s_eta.c_str(), &fOutJets.eta_f);
  //  fOutTree->Branch(fOutJets.s_ID.c_str(), &fOutJets.ID_i);
 // }

  
  fOutTree->Branch(fOutEvent.s_nrechits.c_str(), &fOutEvent.nrechits);
  fOutTree->Branch(fOutEvent.s_nkurechits.c_str(), &fOutEvent.nkurechits);
  //if( hasMultiKURecHit ){
  //fOutTree->Branch("nkuStcrechits", &nkuStcrechits);
  //fOutTree->Branch("nkuNotrechits", &nkuNotrechits);
  //fOutTree->Branch("nkuNotStcrechits", &nkuNotStcrechits);
  fOutTree->Branch("out_npho_recHits_0", &out_npho_recHits_0);
  fOutTree->Branch("out_npho_recHits_1", &out_npho_recHits_1);
  fOutTree->Branch("out_npho_recHits_2", &out_npho_recHits_2);
  fOutTree->Branch("out_npho_recHits_3", &out_npho_recHits_3);
  //fOutTree->Branch("out_fInRecHits_E", &out_fInRecHits_E);
  //fOutTree->Branch("out_fInRecHits_ID", &out_fInRecHits_ID);
  //fOutTree->Branch("out_fInRecHits_time", &out_fInRecHits_time);
  //fOutTree->Branch("out_fInRecHits_TOF", &out_fInRecHits_TOF);
  //fOutTree->Branch("out_kurhtime", &out_kurhtime);
  //fOutTree->Branch("out_kurhID", &out_kurhID);
  //fOutTree->Branch("out_kuStcrhtime", &out_kuStcrhtime);
  //fOutTree->Branch("out_kuNotrhtime", &out_kuNotrhtime);
  //fOutTree->Branch("out_kuNotStcrhtime", &out_kuNotStcrhtime);
  //fOutTree->Branch("out_kuWootStcrhtime", &out_kuWootStcrhtime);
  //}
  fOutTree->Branch("nurechits", &nurechits);
  fOutTree->Branch("ndigis", &ndigis);

  fOutTree->Branch(fOutEvent.s_nphotons.c_str(), &fOutEvent.nphotons);
  for (auto ipho = 0; ipho < fNOutPhos; ipho++) 
  {
    auto & pho = fOutPhos[ipho];
    fOutTree->Branch(Form("%s_%i",pho.s_E.c_str(),ipho), &pho.E);
    fOutTree->Branch(Form("%s_%i",pho.s_pt.c_str(),ipho), &pho.pt);
    fOutTree->Branch(Form("%s_%i",pho.s_eta.c_str(),ipho), &pho.eta);
    fOutTree->Branch(Form("%s_%i",pho.s_phi.c_str(),ipho), &pho.phi);
    fOutTree->Branch(Form("%s_%i",pho.s_scE.c_str(),ipho), &pho.scE);
    fOutTree->Branch(Form("%s_%i",pho.s_sceta.c_str(),ipho), &pho.sceta);
    fOutTree->Branch(Form("%s_%i",pho.s_scphi.c_str(),ipho), &pho.scphi);
    //fOutTree->Branch(Form("%s_%i",pho.s_HoE.c_str(),ipho), &pho.HoE);
    //fOutTree->Branch(Form("%s_%i",pho.s_r9.c_str(),ipho), &pho.r9);
    fOutTree->Branch(Form("%s_%i",pho.s_tdz.c_str(),ipho), &pho.tdz);
    //fOutTree->Branch(Form("%s_%i",pho.s_ChgHadIso.c_str(),ipho), &pho.ChgHadIso);
    //fOutTree->Branch(Form("%s_%i",pho.s_NeuHadIso.c_str(),ipho), &pho.NeuHadIso);
    //fOutTree->Branch(Form("%s_%i",pho.s_PhoIso.c_str(),ipho), &pho.PhoIso);
    //fOutTree->Branch(Form("%s_%i",pho.s_EcalPFClIso.c_str(),ipho), &pho.EcalPFClIso);
    //fOutTree->Branch(Form("%s_%i",pho.s_HcalPFClIso.c_str(),ipho), &pho.HcalPFClIso);
    //fOutTree->Branch(Form("%s_%i",pho.s_TrkIso.c_str(),ipho), &pho.TrkIso);
    // fOutTree->Branch(Form("%s_%i",pho.s_ChgHadIsoC.c_str(),ipho), &pho.ChgHadIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_NeuHadIsoC.c_str(),ipho), &pho.NeuHadIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_PhoIsoC.c_str(),ipho), &pho.PhoIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_EcalPFClIsoC.c_str(),ipho), &pho.EcalPFClIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_HcalPFClIsoC.c_str(),ipho), &pho.HcalPFClIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_TrkIsoC.c_str(),ipho), &pho.TrkIsoC);
    fOutTree->Branch(Form("%s_%i",pho.s_sieie.c_str(),ipho), &pho.sieie);
    // fOutTree->Branch(Form("%s_%i",pho.s_sipip.c_str(),ipho), &pho.sipip);
    // fOutTree->Branch(Form("%s_%i",pho.s_sieip.c_str(),ipho), &pho.sieip);
    // fOutTree->Branch(Form("%s_%i",pho.s_e2x2.c_str(),ipho), &pho.e2x2);
    // fOutTree->Branch(Form("%s_%i",pho.s_e3x3.c_str(),ipho), &pho.e3x3);
    // fOutTree->Branch(Form("%s_%i",pho.s_e5x5.c_str(),ipho), &pho.e5x5);
    fOutTree->Branch(Form("%s_%i",pho.s_smaj.c_str(),ipho), &pho.smaj);
    fOutTree->Branch(Form("%s_%i",pho.s_smin.c_str(),ipho), &pho.smin);
    // fOutTree->Branch(Form("%s_%i",pho.s_alpha.c_str(),ipho), &pho.alpha);
    fOutTree->Branch(Form("%s_%i",pho.s_suisseX.c_str(),ipho), &pho.suisseX);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedX.c_str(),ipho), &pho.seedX);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedY.c_str(),ipho), &pho.seedY);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedZ.c_str(),ipho), &pho.seedZ);
    fOutTree->Branch(Form("%s_%i",pho.s_seedE.c_str(),ipho), &pho.seedE);
    fOutTree->Branch(Form("%s_%i",pho.s_seedtime.c_str(),ipho), &pho.seedtime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedtimeErr.c_str(),ipho), &pho.seedtimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedTOF.c_str(),ipho), &pho.seedTOF);
    fOutTree->Branch(Form("%s_%i",pho.s_seedID.c_str(),ipho), &pho.seedID);
    fOutTree->Branch(Form("%s_%i",pho.s_seedI1.c_str(),ipho), &pho.seedI1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedI2.c_str(),ipho), &pho.seedI2);
    fOutTree->Branch(Form("%s_%i",pho.s_seedEcal.c_str(),ipho), &pho.seedEcal);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedisOOT.c_str(),ipho), &pho.seedisOOT);
    //fOutTree->Branch(Form("%s_%i",pho.s_seedisGS6.c_str(),ipho), &pho.seedisGS6);
    //fOutTree->Branch(Form("%s_%i",pho.s_seedisGS1.c_str(),ipho), &pho.seedisGS1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedadcToGeV.c_str(),ipho), &pho.seedadcToGeV);
    fOutTree->Branch(Form("%s_%i",pho.s_seedped12.c_str(),ipho), &pho.seedped12);
    fOutTree->Branch(Form("%s_%i",pho.s_seedped6.c_str(),ipho), &pho.seedped6);
    fOutTree->Branch(Form("%s_%i",pho.s_seedped1.c_str(),ipho), &pho.seedped1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedpedrms12.c_str(),ipho), &pho.seedpedrms12);
    fOutTree->Branch(Form("%s_%i",pho.s_seedpedrms6.c_str(),ipho), &pho.seedpedrms6);
    fOutTree->Branch(Form("%s_%i",pho.s_seedpedrms1.c_str(),ipho), &pho.seedpedrms1);

    fOutTree->Branch(Form("%s_%i",pho.s_seedkutime.c_str(),ipho), &pho.seedkutime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkutimeErr.c_str(),ipho), &pho.seedkutimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuID.c_str(),ipho), &pho.seedkuID);

    if( hasMultiKURecHit ){
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuStctime.c_str(),ipho), &pho.seedkuStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuStctimeErr.c_str(),ipho), &pho.seedkuStctimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuStcID.c_str(),ipho), &pho.seedkuStcID);

    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStctime.c_str(),ipho), &pho.seedkuNotStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStctimeErr.c_str(),ipho), &pho.seedkuNotStctimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStcID.c_str(),ipho), &pho.seedkuNotStcID);

    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWtStctime.c_str(),ipho), &pho.seedkuWtStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWtStctimeErr.c_str(),ipho), &pho.seedkuWtStctimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWtStcID.c_str(),ipho), &pho.seedkuWtStcID);

    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStctime.c_str(),ipho), &pho.seedkuWootStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStctimeErr.c_str(),ipho), &pho.seedkuWootStctimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStcID.c_str(),ipho), &pho.seedkuWootStcID);

    fOutTree->Branch(Form("%s_%i",pho.s_seedkuMfootStctime.c_str(),ipho), &pho.seedkuMfootStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuMfootStctimeErr.c_str(),ipho), &pho.seedkuMfootStctimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuMfootStcID.c_str(),ipho), &pho.seedkuMfootStcID);

    fOutTree->Branch(Form("%s_%i",pho.s_seedkuMfootCCStctime.c_str(),ipho), &pho.seedkuMfootCCStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuMfootCCStctimeErr.c_str(),ipho), &pho.seedkuMfootCCStctimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuMfootCCStcID.c_str(),ipho), &pho.seedkuMfootCCStcID);

    }

    fOutTree->Branch(Form("%s_%i",pho.s_seedootA0.c_str(),ipho), &pho.seedootA0);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA1.c_str(),ipho), &pho.seedootA1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA2.c_str(),ipho), &pho.seedootA2);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA3.c_str(),ipho), &pho.seedootA3);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA4.c_str(),ipho), &pho.seedootA4);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA5.c_str(),ipho), &pho.seedootA5);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA6.c_str(),ipho), &pho.seedootA6);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA7.c_str(),ipho), &pho.seedootA7);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA8.c_str(),ipho), &pho.seedootA8);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA9.c_str(),ipho), &pho.seedootA9);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootMax.c_str(),ipho), &pho.seedootMax);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootMbefore.c_str(),ipho), &pho.seedootMbefore);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootMafter.c_str(),ipho), &pho.seedootMafter);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootSign.c_str(),ipho), &pho.seedootSign);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootVsum.c_str(),ipho), &pho.seedootVsum);
    fOutTree->Branch(Form("%s_%i",pho.s_isOOT.c_str(),ipho), &pho.isOOT);
    fOutTree->Branch(Form("%s_%i",pho.s_isEB.c_str(),ipho), &pho.isEB);
    //fOutTree->Branch(Form("%s_%i",pho.s_isHLT.c_str(),ipho), &pho.isHLT);
    //fOutTree->Branch(Form("%s_%i",pho.s_isTrk.c_str(),ipho), &pho.isTrk);
    //fOutTree->Branch(Form("%s_%i",pho.s_passEleVeto.c_str(),ipho), &pho.passEleVeto);
    fOutTree->Branch(Form("%s_%i",pho.s_hasPixSeed.c_str(),ipho), &pho.hasPixSeed);
    //fOutTree->Branch(Form("%s_%i",pho.s_gedID.c_str(),ipho), &pho.gedID);
    fOutTree->Branch(Form("%s_%i",pho.s_ootID.c_str(),ipho), &pho.ootID);

    // Derived types
    fOutTree->Branch(Form("%s_%i",pho.s_seedTT.c_str(),ipho), &pho.seedTT);

    //if (fInConfig.storeRecHits)
    if ( true )
    {
      fOutTree->Branch(Form("%s_%i",pho.s_nrechits.c_str(),ipho), &pho.nrechits);
      //fOutTree->Branch(Form("%s_%i",pho.s_nrechitsLT120.c_str(),ipho), &pho.nrechitsLT120);
      //fOutTree->Branch(Form("%s_%i",pho.s_meantime.c_str(),ipho), &pho.meantime);
      //fOutTree->Branch(Form("%s_%i",pho.s_meantimeLT120.c_str(),ipho), &pho.meantimeLT120);
      //fOutTree->Branch(Form("%s_%i",pho.s_weightedtime.c_str(),ipho), &pho.weightedtime);
      //fOutTree->Branch(Form("%s_%i",pho.s_weightedtimeLT120.c_str(),ipho), &pho.weightedtimeLT120);
      //fOutTree->Branch(Form("%s_%i",pho.s_weightedtimeTOF.c_str(),ipho), &pho.weightedtimeTOF);
      //fOutTree->Branch(Form("%s_%i",pho.s_weightedtimeLT120TOF.c_str(),ipho), &pho.weightedtimeLT120TOF);
    }
  } // end loop over nPhotons

  // add event weight
  //fOutTree->Branch(fOutEvent.s_evtwgt.c_str(), &fOutEvent.evtwgt);
} 

void Skimmer::FillPhoListStandard()
{      
  fPhoList.clear();
  for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
  {
    fPhoList.emplace_back(ipho);
  }
}

///////////////////////////
// Configure the skimmer //
///////////////////////////

void Skimmer::SetupDefaults()
{
  fSkim = SkimType::Standard;
  fSumWgts = 1.f;
  isLHCInfo = false;
  hasUrecDigi = false;
  hasMultiKURecHit = false;
  fJEC = ECorr::Nominal;
  fJER = ECorr::Nominal;
  fPhoSc = ECorr::Nominal;
  fPhoSm = ECorr::Nominal;
}

void Skimmer::SetupSkimConfig()
{
 //std::cout << "Reading skim config..." << std::endl;

  std::ifstream infile(Form("%s",fSkimConfig.Data()),std::ios::in);
  std::string str;
  while (std::getline(infile,str))
  {
    if (str == "") continue;
    else if (str.find("skim_type=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"skim_type=");
      Skimmer::SetupSkimType(str);
    }
    else if (str.find("sum_wgts=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"sum_wgts=");
      fSumWgts = Common::Atof(str);
    }
    else if (str.find("puwgt_filename=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"puwgt_filename=");
      fPUWgtFileName = str;
    }
    else if (str.find("jet_scale=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"jet_scale=");
      Skimmer::SetupEnergyCorrection(str,fJEC,"jet_scale");
    }
    else if (str.find("jet_resol=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"jet_resol=");
      Skimmer::SetupEnergyCorrection(str,fJER,"jet_resol");
    }
    else if (str.find("pho_scale=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"pho_scale=");
      Skimmer::SetupEnergyCorrection(str,fPhoSc,"pho_scale");
    }
    else if (str.find("pho_smear=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"pho_smear=");
      Skimmer::SetupEnergyCorrection(str,fPhoSm,"pho_smear");
    }
    else if (str.find("isLHCInfo=") != std::string::npos)
    { 
      str = Common::RemoveDelim(str,"isLHCInfo=");
      if( str == "true" ) isLHCInfo = true;
      if( str == "false" ) isLHCInfo = false;
      std::cout << " Config set isLHCInfo to " << isLHCInfo << std::endl;
    }
    else if (str.find("hasUrecDigi=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"hasUrecDigi=");
      if( str == "true" ) hasUrecDigi = true;
      if( str == "false" ) hasUrecDigi = false;
      std::cout << " Config set hasUrecDigi to " << hasUrecDigi << std::endl;
    }
    else if (str.find("hasMultiKURecHit=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"hasMultiKURecHit=");
      if( str == "true" ) hasMultiKURecHit = true;
      if( str == "false" ) hasMultiKURecHit = false;
      std::cout << " Config set hasMultiKURecHit to " << hasMultiKURecHit << std::endl;
    }
    else
    {
      std::cerr << "Specified a non-known option: " << str.c_str() << " ...Exiting..." << std::endl;
      exit(1);
    }
  }
 //std::cout << "hasMultiKURecHit = " << hasMultiKURecHit << std::endl;
  // reduce output of DiXtal
  fNOutPhos = (fSkim == SkimType::DiXtal ? 4 : Common::nPhotons);
}

void Skimmer::SetupSkimType(const TString & skim_type)
{
  if      (skim_type.EqualTo("Standard"   ,TString::kExact)) fSkim = SkimType::Standard;
  else if (skim_type.EqualTo("Zee"        ,TString::kExact)) fSkim = SkimType::Zee;
  else if (skim_type.EqualTo("DiXtal"     ,TString::kExact)) fSkim = SkimType::DiXtal;
 // else if (skim_type.EqualTo("DiXtal"     ,TString::kExact)) fSkim = SkimType::DiXtal;
  else if (skim_type.EqualTo("AlwaysTrue" ,TString::kExact)) fSkim = SkimType::AlwaysTrue;
  else if (skim_type.EqualTo("AlwaysFalse",TString::kExact)) fSkim = SkimType::AlwaysFalse;
  else
  {
    std::cerr << skim_type.Data() << " is not a valid skim selection! Exiting..." << std::endl;
    exit(1);
  }
}

void Skimmer::SetupEnergyCorrection(const TString & str, ECorr & ecorr, const TString & text)
{
  if      (str.EqualTo("Nominal",TString::kExact)) ecorr = ECorr::Nominal;
  else if (str.EqualTo("Down"   ,TString::kExact)) ecorr = ECorr::Down;
  else if (str.EqualTo("Up"     ,TString::kExact)) ecorr = ECorr::Up;
  else
  {
    std::cerr << str.Data() << " is not a valid " << text.Data() << " selection! Exiting..." << std::endl;
    exit(1);
  }
}
