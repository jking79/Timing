//
//  Jack W King III 2019
//

#include "jwk_define_hists.h"

///-------------- String declarations-------------------------------------------------------------------------


//----------------------------------------------------------
//  Create TFile and TFile SubDirectories
//---------------------------------------------------------
TFile * makeTFile( string outfile_name ){

  auto outfile = new TFile( outfile_name.c_str(), "update" );
  outfile->cd();
//  make_subdir( outfile, fall17_WZ_SubDir.c_str() );
  return outfile;
}
//-------------------------------------------------------------------------------------------------------
//  Functions called to substantiate and run the hist maker class
//-------------------------------------------------------------------------------------------------------
void run_hist_maker( string treename, vector<string> g_FileVec, string outfile_name, string treeSubDir, int skip )
{ 
  std::cout << "Running over " << treename << " in: "  << std::endl;
  for( auto gfile : g_FileVec ){ std::cout << gfile << std::endl; }
  std::cout << "Writing to " << outfile_name << "/" << treeSubDir << std::endl;
  histMaker hist_maker; 
  auto tfile = makeTFile(outfile_name);
  hist_maker.make_hists( g_Path, g_FileVec, treename, tfile, treeSubDiri, skip );
  tfile->Close();
  std::cout << "Finished" << std::endl;
}
void run_hist_maker( string treename, string g_FileName, string outfile_name, string treeSubDir, int skip )
{
  vector< string > g_FileVec;
  g_FileVec.push_back( g_FileName );
  run_hist_maker( treename, g_FileVec, outfile_name, treeSubDir, skip )
}
//-------------------------------------------------------------------------------------------------------
//Root Macro to run histogram jobs   NOTE: skip = 1 runs all events, larger #s skip events by that value
//--------------------------------------------------------------------------------------------------------

void jwk_make_hists(){

	//run_hist_maker( , , , , );

}


