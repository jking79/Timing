#include "TString.h"
#include "Common.cpp"
//#include "wc_ku_Skimmer_chain_v2a.cpp"
//#include "wc_ku_Skimmer_chain_v2a_cleaned.cpp"
#include "wc_ku_Skimmer_chain_v2a_cleaned_kurhs_red.cpp"

void wc_runKUSkimmer(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig)
{
  Skimmer skimmer(indir, outdir, filename, skimconfig);
  skimmer.EventLoop();
}

int main ( int argc, char *argv[] ){

        if( argc != 5 ) { std::cout << "Insufficent arguments." << std::endl; }
        else {
                TString indir(argv[1]);
                TString outdir(argv[2]);
                TString filename(argv[3]);
                TString skimconfig(argv[4]);
                wc_runKUSkimmer( indir, outdir, filename, skimconfig);
        }
        return 1;
}
