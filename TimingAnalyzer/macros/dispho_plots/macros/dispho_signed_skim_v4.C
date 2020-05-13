#define dispho_skim_v4_cxx
#include "dispho_skim_v4.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "jwk_ku_tdr_style.h"

void dispho_skim_v4::Loop()
{
//   In a ROOT session, you can do:
//      root> .L dispho_skim_v4.C
//      root> dispho_skim_v4 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   std::cout << "Starting Tree Loop." << std::endl;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   Long64_t report = (nentries/20 < 1) ? 1 : nentries/20;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
//     std::cout << "ientry: "<< ientry << " jentry: " << jentry << std::endl;
      if (ientry < 0) break;
  //   if (ientry > 1000) break;

//     std::cout << "Setting Branch status" << std::endl;

      fChain->SetBranchStatus("*",0);
 //     fChain->SetBranchStatus("run",1);
 //     fChain->SetBranchStatus("lumi",1);
 //     fChain->SetBranchStatus("event",1);
 //
     fChain->SetBranchStatus("phoseedootMax_0",1);//ootmax/b/a ---- 0
     fChain->SetBranchStatus("phoseedootMbefore_0",1);
     fChain->SetBranchStatus("phoseedootMafter_0",1);
     fChain->SetBranchStatus("phoseedadcToGeV_0",1);
     fChain->SetBranchStatus("phoseedE_0",1);

     fChain->SetBranchStatus("phoseedootMax_1",1);//ootmax/b/a ---- 1
     fChain->SetBranchStatus("phoseedootMbefore_1",1);
     fChain->SetBranchStatus("phoseedootMafter_1",1);
     fChain->SetBranchStatus("phoseedadcToGeV_1",1);
     fChain->SetBranchStatus("phoseedE_1",1);

     fChain->SetBranchStatus("phoseedtime_0",1);//seedtime ---- 0
     fChain->SetBranchStatus("phoseedtime_1",1);//seedtime ---- 1
     fChain->SetBranchStatus("phoseedootSign_0",1);
     fChain->SetBranchStatus("phoseedootSign_1",1);
     fChain->SetBranchStatus("phoseedTOF_0",1);
     fChain->SetBranchStatus("phoseedTOF_1",1);

// finished setting tree branches
//     std::cout << "GetEntry from Chain." << std::endl;
     nb = fChain->GetEntry(jentry);   
   //  nbytes += nb;
   if( ientry % report == 0 )  cout << "Event " << ientry << " | " << nentries << endl;
// phoseedootMafter_0*(phoseedadcToGeV_0/phoseedE_0)

  //   std::cout << "Processing Data" << std::endl;
	//Int_t xbin;
        //Int_t ybin;
        //Float_t amp_0;
	//Float_t amp_1;
	
	auto seedAmp_0 = (phoseedadcToGeV_0/phoseedE_0);
	auto seedAmp_1 = (phoseedadcToGeV_1/phoseedE_1);
        auto diff_t = phoseedtime_0 - phoseedtime_1 + (phoseedTOF_0-phoseedTOF_1);
	auto sign = phoseedootSign_0;

        auto amp_0 = phoseedootMax_0*seedAmp_0;
        auto amp_1 = phoseedootMax_1*seedAmp_1;
	auto xbin = int(amp_0/step);
        auto ybin = int(amp_1/step);
	if( xbin > maxbin ) continue;
	if( ybin > maxbin ) continue;

	if(amp_1>amp_0){
		sign = phoseedootSign_1;
		auto temp = ybin;
		ybin = xbin;
		xbin = temp;
	}
	auto max_diff_t = diff_t*sign;
//	std::cout << "max values: " << amp_0 << " : " << amp_1 << " dt: " << diff_t << std::endl;
//	std::cout << "bin values: " << xbin << " : " << ybin << " maxbin : " << maxbin << " step: " << step << std::endl;

	twodeeMax[xbin][ybin]->Fill(max_diff_t);
	onedeeMax_0[xbin]->Fill(max_diff_t);
        onedeeMaxCount_0[xbin]++;
	onedeeMax_1[ybin]->Fill(max_diff_t);
        onedeeMaxCount_1[xbin]++;

        amp_0 = phoseedootMbefore_0*seedAmp_0;
        amp_1 = phoseedootMbefore_1*seedAmp_1;
        xbin = int(amp_0/step);
        ybin = int(amp_1/step);
        if( xbin > maxbin ) continue;
        if( ybin > maxbin ) continue;

	sign = phoseedootSign_0;
        if(amp_1>amp_0){
                sign = phoseedootSign_1;
                auto temp = ybin;
                ybin = xbin;
                xbin = temp;
        }
        auto before_diff_t = diff_t*sign;

        twodeeBefore[xbin][ybin]->Fill(before_diff_t);
        onedeeBefore_0[xbin]->Fill(before_diff_t);
        onedeeBeforeCount_0[xbin]++;
        onedeeBefore_1[ybin]->Fill(before_diff_t);
        onedeeBeforeCount_1[xbin]++;

        amp_0 = phoseedootMafter_0*seedAmp_0;
        amp_1 = phoseedootMafter_1*seedAmp_1;
        xbin = int(amp_0/step);
        ybin = int(amp_1/step);
        if( xbin > maxbin ) continue;
        if( ybin > maxbin ) continue;

        sign = phoseedootSign_0;
        if(amp_1>amp_0){
                sign = phoseedootSign_1;
                auto temp = ybin;
                ybin = xbin;
                xbin = temp;
        }
       	auto after_diff_t = diff_t*sign;

        twodeeAfter[xbin][ybin]->Fill(after_diff_t);
        onedeeAfter_0[xbin]->Fill(after_diff_t);
        onedeeAfterCount_0[xbin]++;
        onedeeAfter_1[ybin]->Fill(after_diff_t);
        onedeeAfterCount_1[xbin]++;

 //    	std::cout << "Finished Bin Fill" << std::endl;
   }
   std::cout << "Tree Loop Finished." << std::endl;
}

void dispho_skim_v4::MakePlots()
{

   setTDRStyle();
   std::cout << "Filling Histograms." << std::endl;

   TH2F twodeeMaxMuHist("twodeeMaxMuHist","twodeeMaxMuHist",nbins,0.0,binmax,nbins,0.0,binmax);
   twodeeMaxMuHist.GetXaxis()->SetTitle("R_{oot}(pho max)");
   twodeeMaxMuHist.GetYaxis()->SetTitle("R_{oot}(pho min)");
   twodeeMaxMuHist.GetZaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot} ordered");
   TH2F twodeeMaxSigmaHist("twodeeMaxSigmaHist","twodeeMaxSigmaHist",nbins,0.0,binmax,nbins,0.0,binmax);
   twodeeMaxSigmaHist.GetXaxis()->SetTitle("R_{oot}(pho max)");
   twodeeMaxSigmaHist.GetYaxis()->SetTitle("R_{oot}(pho min)");
   twodeeMaxSigmaHist.GetZaxis()->SetTitle("#sigma(#delta(Pho_{t}^{seed})) [ns] R_{oot} ordered");
   TH2F onedeeMaxMuHist_0("onedeeMaxMuHist_0","onedeeMaxMuHist_0",nbins,0.0,binmax,od_nTbins,(-1*od_tBin),od_tBin);
   onedeeMaxMuHist_0.GetXaxis()->SetTitle("R_{oot}(pho max)");
   onedeeMaxMuHist_0.GetYaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot} ordered");
   //onedeeMaxMuHist_0.GetZaxis()->SetTitle("a.u.");
   TH2F onedeeMaxMuHist_1("onedeeMaxMuHist_1","onedeeMaxMuHist_1",nbins,0.0,binmax,od_nTbins,(-1*od_tBin),od_tBin);
   onedeeMaxMuHist_1.GetXaxis()->SetTitle("R_{oot}(pho min)");
   onedeeMaxMuHist_1.GetYaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot} ordered");
   //onedeeMaxMuHist_1.GetZaxis()->SetTitle("a.u.");

   TH2F twodeeBeforeMuHist("twodeeBeforeMuHist","twodeeBeforeMuHist",nbins,0.0,binmax,nbins,0.0,binmax);
   twodeeBeforeMuHist.GetXaxis()->SetTitle("R_{oot}^{preNomBX}(pho max)");
   twodeeBeforeMuHist.GetYaxis()->SetTitle("R_{oot}^{preNomBX}(pho min)");
   twodeeBeforeMuHist.GetZaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{preNomBX} ordered");
   TH2F twodeeBeforeSigmaHist("twodeeBeforeSigmaHist","twodeeBeforeSigmaHist",nbins,0.0,binmax,nbins,0.0,binmax);
   twodeeBeforeSigmaHist.GetXaxis()->SetTitle("R_{oot}^{preNomBX}(pho max)");
   twodeeBeforeSigmaHist.GetYaxis()->SetTitle("R_{oot}^{preNomBX}(pho min)");
   twodeeBeforeSigmaHist.GetZaxis()->SetTitle("#sigma(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{preNomBX} ordered");
   TH2F onedeeBeforeMuHist_0("onedeeBeforeMuHist_0","onedeeBeforeMuHist_0",nbins,0.0,binmax,od_nTbins,(-1*od_tBin),od_tBin);
   onedeeBeforeMuHist_0.GetXaxis()->SetTitle("R_{oot}^{preNomBX}(pho max)");
   onedeeBeforeMuHist_0.GetYaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{preNomBX} ordered");
   //onedeeBeforeMuHist_0.GetZaxis()->SetTitle("a.u.");
   TH2F onedeeBeforeMuHist_1("onedeeBeforeMuHist_1","onedeeBeforeMuHist_1",nbins,0.0,binmax,od_nTbins,(-1*od_tBin),od_tBin);
   onedeeBeforeMuHist_1.GetXaxis()->SetTitle("R_{oot}^{postNomBX}(pho min)");
   onedeeBeforeMuHist_1.GetYaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{preNomBX} ordered");
   //onedeeBeforeMuHist.GetZaxis()->SetTitle("a.u.");

   TH2F twodeeAfterMuHist("twodeeAfterMuHist","twodeeAfterMuHist",nbins,0.0,binmax,nbins,0.0,binmax);
   twodeeAfterMuHist.GetXaxis()->SetTitle("R_{oot}^{postNomBX}(pho max)");
   twodeeAfterMuHist.GetYaxis()->SetTitle("R_{oot}^{postNomBX}(pho min)");
   twodeeAfterMuHist.GetZaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{postNomBX} ordered");
   TH2F twodeeAfterSigmaHist("twodeeAfterSigmaHist","twodeeAfterSigmaHist",nbins,0.0,binmax,nbins,0.0,binmax);
   twodeeAfterSigmaHist.GetXaxis()->SetTitle("R_{oot}^{postNomBX}(pho max)");
   twodeeAfterSigmaHist.GetYaxis()->SetTitle("R_{oot}^{postNomBX}(pho min)");
   twodeeAfterSigmaHist.GetZaxis()->SetTitle("#sigma(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{postNomBX} ordered");
   TH2F onedeeAfterMuHist_0("onedeeAfterMuHist_0","onedeeAfterMuHist_0",nbins,0.0,binmax,od_nTbins,(-1*od_tBin),od_tBin);
   onedeeAfterMuHist_0.GetXaxis()->SetTitle("R_{oot}^{postNomBX}(pho max)");
   onedeeAfterMuHist_0.GetYaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{postNomBX} ordered");
   //onedeeAfterMuHist_0.GetZaxis()->SetTitle("a.u.");
   TH2F onedeeAfterMuHist_1("onedeeAfterMuHist_1","onedeeAfterMuHist_1",nbins,0.0,binmax,od_nTbins,(-1*od_tBin),od_tBin);
   onedeeAfterMuHist_1.GetXaxis()->SetTitle("R_{oot}^{postNomBX}(pho min)");
   onedeeAfterMuHist_1.GetYaxis()->SetTitle("#mu(#delta(Pho_{t}^{seed})) [ns] R_{oot}^{postNomBX} ordered");
   //onedeeAfterMuHist_1.GetZaxis()->SetTitle("a.u.");

   for( int i = 0; i < nbins; i++ ){

		onedeeMaxMuHist_0.Fill((i+0.5)*(binmax/nbins),onedeeMax_0[i]->GetMean(),onedeeMaxCount_0[i]);
		onedeeMaxMuHist_1.Fill((i+0.5)*(binmax/nbins),onedeeMax_1[i]->GetMean(),onedeeMaxCount_1[i]);

                onedeeBeforeMuHist_0.Fill((i+0.5)*(binmax/nbins),onedeeBefore_0[i]->GetMean(),onedeeBeforeCount_0[i]);
                onedeeBeforeMuHist_1.Fill((i+0.5)*(binmax/nbins),onedeeBefore_1[i]->GetMean(),onedeeBeforeCount_1[i]);

                onedeeAfterMuHist_0.Fill((i+0.5)*(binmax/nbins),onedeeAfter_0[i]->GetMean(),onedeeAfterCount_0[i]);
                onedeeAfterMuHist_1.Fill((i+0.5)*(binmax/nbins),onedeeAfter_1[i]->GetMean(),onedeeAfterCount_1[i]);        

	        for( int j = 0; j < nbins; j++ ){

			if( twodeeMax[i][j]->GetEntries() >  10 ){
			twodeeMaxMuHist.Fill((i+0.5)*(binmax/nbins),(j+0.5)*(binmax/nbins),twodeeMax[i][j]->GetMean());
                        twodeeMaxSigmaHist.Fill((i+0.5)*(binmax/nbins),(j+0.5)*(binmax/nbins),twodeeMax[i][j]->GetStdDev());
			}
			if( twodeeBefore[i][j]->GetEntries() > 10 ){
                        twodeeBeforeMuHist.Fill((i+0.5)*(binmax/nbins),(j+0.5)*(binmax/nbins),twodeeBefore[i][j]->GetMean());
                        twodeeBeforeSigmaHist.Fill((i+0.5)*(binmax/nbins),(j+0.5)*(binmax/nbins),twodeeBefore[i][j]->GetStdDev());
			}
                        if( twodeeAfter[i][j]->GetEntries() > 10 ){
                        twodeeAfterMuHist.Fill((i+0.5)*(binmax/nbins),(j+0.5)*(binmax/nbins),twodeeAfter[i][j]->GetMean());
                        twodeeAfterSigmaHist.Fill((i+0.5)*(binmax/nbins),(j+0.5)*(binmax/nbins),twodeeAfter[i][j]->GetStdDev());
			}
		} //(nbins, vector<vector<Float_t>>(nbins, vector<Float_t>));
   }

//  make plots

//   open tfile to save to ........
//   auto outTfile = new TFile( "ootAmp_dt_Maps.root", "update" );
	outTfile->cd();

   twodeeMaxMuHist.Write("twodeeMaxMuHist",TObject::kWriteDelete);
   twodeeMaxSigmaHist.Write("twodeeMaxSigmaHist",TObject::kWriteDelete);
   onedeeMaxMuHist_0.Write("onedeeMaxMuHist_0",TObject::kWriteDelete);
   onedeeMaxMuHist_1.Write("onedeeMaxMuHist_1",TObject::kWriteDelete);
   twodeeBeforeMuHist.Write("twodeeBeforeMuHist",TObject::kWriteDelete);
   twodeeBeforeSigmaHist.Write("twodeeBeforeSigmaHist",TObject::kWriteDelete);
   onedeeBeforeMuHist_0.Write("onedeeBeforeMuHist_0",TObject::kWriteDelete);
   onedeeBeforeMuHist_1.Write("onedeeBeforeMuHist_1",TObject::kWriteDelete);
   twodeeAfterMuHist.Write("twodeeAfterMuHist",TObject::kWriteDelete);
   twodeeAfterSigmaHist.Write("twodeeAfterSigmaHist",TObject::kWriteDelete);
   onedeeAfterMuHist_0.Write("onedeeAfterMuHist_0",TObject::kWriteDelete);
   onedeeAfterMuHist_1.Write("onedeeAfterMuHist_1",TObject::kWriteDelete);

   outTfile->Close();
   std::cout << "Filling  Finished." << std::endl;

}




