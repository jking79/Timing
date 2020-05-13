#include "dispho_signed_skim_v4.C"

void dotreeloop( string rootname, string outname )
{

	dispho_skim_v4 tree( rootname, outname );
	tree.Loop();
	tree.MakePlots();

}

void make_signed_oot_plots()
{

	dotreeloop("/home/t3-ku/jaking/trees/ecal/zee_skims/dispho_Zee_v4_eg2018A_raw_315322.root", "oot_signed_plots_eg2018A_raw_315322.root");

}


