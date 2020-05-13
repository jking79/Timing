//
//  Histogram definitions and loading
//  Jack W King III 2019
//

#include "jwk_hist_maker.h"

//---------------------------------------------------------------------
// Utility functions
// -------------------------------------------------------------------
TLorentzVector * get4vec(double pt, double eta, double phi, double m){
	double px = pt*cos(phi);
	double py = pt*sin(phi);
	double pz = pt*sinh(eta);
	TLorentzVector *v = new TLorentzVector();
	v->SetXYZM( px,py,pz,m );
	return v;	
}
//---------------------------------------------------------------------
TLorentzVector * add4vecs( vector<double> pt, vector<double> eta, vector<double> phi, vector<double> m){

	TLorentzVector * p = new TLorentzVector();
	for(unsigned int i=0; i<pt.size(); i++){
		TLorentzVector *c = new TLorentzVector();
		c = get4vec(pt.at(i), eta.at(i), phi.at(i), m.at(i) );
		*p += *c;
	}
	return p;

}
//-----------------------------------------------------------------------
////---------------------------------------------------------------------
//
//	<--------------   create new histograms as in example below
//
//
//class otherHistClass : public parentHistClass{
// 
//  public:
//  void init_hist( string treeSubDir );
//  void fill_hist( Base* base );
// 
//}
//
//void otherHistClass::initi_hist(){
//    
//  setTDRStyle();
//  hist1d = new TH1D("parentHistClass","baseHistClass", 2, -0.5, 1.5 );
//
//}
//
//  note:  parentHistClass has pointers:  
//  		hist1d 
//  		hist2d 
//  		hist1f 
//  		hist2f
//
//void otherHistClass::fill_hist( Base* base ){
//
//  hist1d->Fill(1.0);
//  //----  or:  hist1d->Fill(base->RISR->at(2), base->weight);
//  //----  or:  hist2d->Fill(base->RISR->at(2), base->PTISR->at(2) , base->weight);
//
//}

//----------------------------------------------------------------------------
//----Example of new class follows-------------------------------------------
//----------------------------------------------------------------------------
class testHistTheFirst : public parentHistClass{

  public: 
  void init_hist( string treeSubDir );
  void fill_hist( Base* base );
 
};

void testHistTheFirst::init_hist( string treeSubDir ){
  
  set_subdir( treeSubDir );   
  hist1d = new TH1D("testHistTheFirst","FirstTestHist", 2, -1.5, 1.5 );
 // std::cout << "In Init from testHistTheFirst !!" << std::endl;

}

void testHistTheFirst::fill_hist( Base* base ){

  hist1d->Fill(1.0);

}
//-------------------------------------------------------------------------------------------------------
//----------------------------make new hist classes below------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class thisHistMaker::histMaker{

        public:
        vector< parentHistClass * > hist_vector_loader( string treeSubDir );
        bool global_cuts( Base * base ){ return false; };

};
//-------------------------------------------------------------------------------------------------------
//  make any global cuts for all histograms here.  Should return true to skip event.
//--------------------------------------------------------------------------------------------------------
bool thisHistMaker::global_cuts( Base * base ){

  bool cut = true;
  
  return !cut;

}
//---------------------------------------------------------------------------------------------------------
//  loads histograms to be filled, add to new histogram to be run to the hist class vector as shown below.
//--------------------------------------------------------------------------------------------------------
vector< parentHistClass * > thisHistMaker::hist_vector_loader( string treeSubDir ){
 
  vector< parentHistClass *  > vhistclasses;
  vhistclasses.push_back( new testHistTheFirst );
  vhistclasses.push_back( new testHistTheSecond );
  //   <--------------------------------------   add new hist classes here

  for( auto histclass : vhistclasses ){ histclass->init_hist( treeSubDir ); }

  return vhistclasses;
 
}
//----------------------------------------------------------------------------

