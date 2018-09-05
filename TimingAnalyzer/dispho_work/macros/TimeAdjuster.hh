#idndef __TimeAdjuster__
#define __TimeAdjuster__

// ROOT inludes
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TRandom.h"
#include "TString.h"
#include "TPaveText.h"

// STL includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

// Common include
#include "Common.hh"

struct Event
{
  // vars
  UInt_t run;
  Int_t  nphotons;

  // strings
  std::string s_run = "run";
  std::string s_photons = "nphotons";

  // branches
  TBranch * b_run;
  TBranch * b_photons;
};

struct Photon
{
  // old vars
  Float_t pt;
  Bool_t  isEB;
  // new vars
  Float_t seedtimeSHIFT;
  Float_t seedtimeSMEAR;
  
  // strings
  std::string s_pt = "phopt";
  std::string s_isEB = "phoisEB";
  std::string s_seedtimeSHIFT = "seedtimeSHIFT";
  std::string s_seedtimeSMEAR = "seedtimeSMEAR";

  // branches
  TBranch * b_pt;
  TBranch * b_isEB;
  TBranch * b_seedtimeSHIFT;
  TBranch * b_seedtimeSMEAR;
};

struct FitStruct
{
  FitStruct() {}
  FitStruct(const TString & label) : label(label) {}

  const TString label;
  std::vector<TString,TH1F*> MuHistMap;
  std::vector<TString,TH1F*> SigmaHistMap;
  std::vector<TString,TF1*>  SigmaFitMap;
};

class TimeAdjuster
{
public:
  TimeAdjuster(const TString & skimfilename, const TString & infilesconfig, const TString & outfiletext);
  ~TimeAdjuster();

  // Config
  void SetupCommon();
  void SetupInFiles();

  // Main calls
  void AdjustTime();
  void PrepAdjustments(FitStruct & FitInfo);
  void CorrectData(FitStruct & DataInfo);
  void CorrectMC(FitStruct & DataInfo, FitStruct & MCInfo);
  void SaveSigmaFits(FitStruct & DataInfo, FitStruct & MCInfo);
  
  // Getting adjustments ready
  void GetInputHists(FitStruct & FitInfo);
  void PrepSigmaFits(FitStruct & FitInfo);
  void FitSigmaHists(FitStruct & FitInfo);

  // Meta data
  void MakeCongigPave();

  // Helper functions
  template <typename T>
  void DeleteMap(T & Map);

private:
  // settings
  const TString fSkimFileName;
  const TString fInFilesConfig;
  const TString fOutFileText;

  // adjust config
  TString fHistName;

  // inputs
  std::map<TString,TString> fInFileNameMap;
  std::map<TString,TFile*> fInFileMap;

  // I/O
  TFile * fSkimFile;
  TPaveText * fPaveText;
};

#endif
