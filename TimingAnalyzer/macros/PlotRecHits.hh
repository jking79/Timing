#ifndef _plotrechits_
#define _plotrechits_

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"

#include <vector>
#include <map>
//#include <unordered_map>

typedef std::map<TString,TH1F*> TH1Map;
typedef TH1Map::iterator        TH1MapIter;

typedef std::map<TString,TH2F*> TH2Map;
typedef TH2Map::iterator        TH2MapIter;

typedef std::map<TString,TString> TStrMap;
typedef TStrMap::iterator         TStrMapIter;

typedef std::vector<TString> TStrVec;

class PlotRecHits 
{
public :
  PlotRecHits(TString filename, TString outdir = "output", 
	      Bool_t applyrhidcut = false, TString rhlistfile = "output/rhlist.txt",
	      Bool_t applyrhecut = false, Float_t rhEcut = 1.f, Bool_t applyecalacceptcut = false);
  ~PlotRecHits();
  void InitTree();
  void DoPlots();
  void SetupPlots();
  void SetupRecHits();
  TH1F * MakeTH1F(TString hname, TString htitle, Int_t nbinsx, Float_t xlow, Float_t xhigh, TString xtitle, TString ytitle, TString subdir);
  TH2F * MakeTH2F(TString hname, TString htitle, Int_t nbinsx, Float_t xlow, Float_t xhigh, TString xtitle, Int_t nbinsy, Float_t ylow, Float_t yhigh, TString ytitle, TString subdir);
  void RecHitsLoop();
  void FillRecHits();
  void MakeSubDirs();
  void OutputTH1Fs();
  void OutputTH2Fs();
  void ClearTH1Map();
  void ClearTH2Map();

private :
  // Input vars
  TFile * fInFile; //!pointer to file
  TTree * fInTree; //!pointer to the analyzed TTree

  // In routine vars
  std::map<int,std::map<int,int> > fEvRhMapMap;  
  UInt_t  fNEvCheck;
  TH1Map  fPlots;
  TH2Map  fPlots2D;
  TStrVec fTotalNames;

  // Config
  const Bool_t  fApplyrhIDCut;
  const TString fRHListFile;
  const Bool_t  fApplyrhECut;
  const Float_t frhECut;
  const Bool_t  fApplyECALAcceptCut;

  // Output vars
  TString fOutDir;
  TStrMap fSubDirs;
  TFile * fOutFile;

  Int_t event;
  Int_t run;
  Int_t lumi;
  Int_t nrhEB;
  Int_t nrhEE;
  vector<float> * rhEs;
  vector<float> * rhphis;
  vector<float> * rhetas;
  vector<float> * rhtimes;
  vector<int>   * rhIDs;
  vector<int>   * rhOOTs;

  // List of branches
  TBranch * b_event;   //!
  TBranch * b_run;   //!
  TBranch * b_lumi;   //!
  TBranch * b_nrhEB;   //!
  TBranch * b_nrhEE;   //!
  TBranch * b_rhEs;   //!
  TBranch * b_rhphis;   //!
  TBranch * b_rhetas;   //!
  TBranch * b_rhtimes;   //!
  TBranch * b_rhIDs;   //!
  TBranch * b_rhOOTs;   //!
};
#endif