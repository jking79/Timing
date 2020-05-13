#include <fstream>
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

Scrap pad
————————————————————————————————————————


string itostr( int num ) // convert int to a string
{
        stringstream ss;
        ss << num;
        string result(ss.str());
        return result;
}

string rpsb(string temp)  // replace space with underline
{
   int position = temp.find( " " ); // find first space
   while ( position != int(string::npos) )
   {
      temp.replace( position, 1, "_" );
      position = temp.find( " ", position + 1 );
   }
   return temp;
}

string revrpsb(string temp)  //  replace underline with space
{
   int position = temp.find( "_" ); // find first space
   while ( position != int(string::npos) )
   {
      temp.replace( position, 1, " " );
      position = temp.find( "_", position + 1 );
   }
   return temp;
}


// draws a histogram when TH1F, canvas, and x,y titles provided.
void tdrHistDraw( TH1D* &hist, TCanvas* &can, string xtit, string ytit )
{
    can->cd();
    hist->UseCurrentStyle();
    hist->GetXaxis()->CenterTitle(true);
    hist->GetXaxis()->SetTitle(xtit.c_str());
    hist->GetYaxis()->CenterTitle(true);
    hist->GetYaxis()->SetTitle(ytit.c_str());
    hist->Draw();
    gPad->Update();
    return;

}

// draws a histogram when TH1F, canvas, and x,y titles provided.
void tdrHistDrawLogX( TH1D* &hist, TCanvas* &can, string xtit, string ytit )
{
    can->cd();
    hist->UseCurrentStyle();
    gPad->SetLogx();
    hist->GetXaxis()->CenterTitle(true);
    hist->GetXaxis()->SetTitle(xtit.c_str());
    hist->GetYaxis()->CenterTitle(true);
    hist->GetYaxis()->SetTitle(ytit.c_str());
    hist->Draw();
    gPad->Update();
    return;

}


// draws a 2d histogram when TH2F, canvas, and x,y titles provided.
void tdrHist2DDraw( TH2D* &hist, TCanvas* &can, string xtit, string ytit )
{
    can->cd();
    hist->UseCurrentStyle();
    hist->GetXaxis()->CenterTitle(true);
    hist->GetXaxis()->SetTitle(xtit.c_str());
    hist->GetYaxis()->CenterTitle(true);
    hist->GetYaxis()->SetTitle(ytit.c_str());
    hist->Draw("colz");
    gPad->Update();
    return;

}

// draws a histogram when TH1F, canvas, and x,y titles provided.
void tdrHistDrawMulti( vector<TH1D*> &hist, TCanvas* &can, string xtit, string ytit, double miny, double maxy, vector<string> label )
{
    can->cd();
    TLegend* myleg = new TLegend( 0.6, 0.6, 0.8, 0.8 );
    myleg->SetFillColor(0);
    myleg->SetBorderSize(0);
    myleg->SetTextSize(0.025);
    myleg->SetHeader( (label[0]).c_str() );
    for( int i = 0 ; i < int(hist.size()); i++)
    {
      hist[i]->UseCurrentStyle();
      hist[i]->SetStats(false);
      hist[i]->GetXaxis()->CenterTitle(true);
      hist[i]->GetXaxis()->SetTitle(xtit.c_str());
      hist[i]->GetYaxis()->CenterTitle(true);
      hist[i]->GetYaxis()->SetTitle(ytit.c_str());
      hist[i]->GetYaxis()->SetRangeUser( miny, maxy );
      if( i == 0 ){
         hist[i]->SetLineColor(i+2);
         hist[i]->Draw();
         myleg->AddEntry( hist[i], (label[i+1]).c_str(), "L" );
         gPad->Update();
      }else{
         hist[i]->SetLineColor(i+2);
         hist[i]->Draw("same");
         myleg->AddEntry( hist[i], (label[i+1]).c_str(), "L" );
         gPad->Update();
      }
    }
    myleg->Draw();
    gPad->Update();
    return;

}


void tdrHistDrawMulti( vector<TH1D*> &hists, TCanvas* &can, string xtit, string ytit )
{
        vector<string> bob;
        bob.push_back( "Legend" );
        bob.push_back( "DeltaR of Tmax" );
        bob.push_back( "DeltaR of Tmin" );
        bob.push_back( "DeltaR of Wb" );

        tdrHistDrawMulti( hists, can, xtit, ytit, 0, 2500, bob );
        return;

}

// returns a canvas if title is specified.


int can_x_width = 1000;
int can_y_width = 600;


TCanvas* getEwkinoCanvas(){

  TCanvas* can = (TCanvas*) new TCanvas("can","can",700.,600);

  can->SetLeftMargin(0.15);
  can->SetRightMargin(0.18);
  can->SetBottomMargin(0.15);
  can->SetGridx();
  can->SetGridy();
  can->SetLogz();
  can->Draw();
  can->cd();

  return can;

}

TCanvas* getTDRCanvas( string title )
{
    TCanvas *can = new TCanvas( title.c_str(), title.c_str(), can_x_width, can_y_width );
    return can;
}

TCanvas* getTDRCanvas( string title, string mod )
{
    TCanvas *can = new TCanvas( title.c_str(), title.c_str(), can_x_width*2, can_y_width*3 );
    return can;
}

void fixOverlay() {
  gPad->RedrawAxis();
}


TCanvas* drawPrint( TH1D* hist, string type, string title, string xtitle, string ytitle, string rfname)
{
        TCanvas *c = getTDRCanvas( title + rfname );
        tdrHistDraw( hist, c, xtitle, ytitle );
        string savetitle( rfname + "_" + rpsb(title) + type );
        c->SaveAs( savetitle.c_str() );
        return c;
}

TCanvas* drawPrint( TH1D* hist, string title, string xtitle, string ytitle, string rfname)
{
        return drawPrint( hist, ".pdf", title, xtitle, ytitle, rfname );
}

TCanvas* drawPrintLogX( TH1D* hist, string type, string title, string xtitle, string ytitle, string rfname)
{
        TCanvas *c = getTDRCanvas( title + rfname );
        tdrHistDrawLogX( hist, c, xtitle, ytitle );
        string savetitle( rfname + "_" + rpsb(title) + type );
        c->SaveAs( savetitle.c_str() );

        return c;
}

TCanvas* drawPrintLogX( TH1D* hist, string title, string xtitle, string ytitle, string rfname )
{
        return drawPrintLogX( hist, ".pdf", title, xtitle, ytitle, rfname );
}


TCanvas* drawPrintMulti( vector<TH1D*> histlist, string type, string title, string xtitle, string ytitle, string rfname, double ymin, double ymax, vector<string> label )
{

        double biggest = 0;
        for( int i = 0; i < int(histlist.size()); i++ ){ if( biggest < histlist[i]->GetMaximum() ) biggest = histlist[i]->GetMaximum();}
        ymax = biggest*1.25;
        TCanvas *c = getTDRCanvas( title + rfname );
        tdrHistDrawMulti( histlist, c, xtitle, ytitle, ymin, ymax, label );
        string savetitle( rfname + "_" + rpsb(title) + type );
        c->SaveAs( savetitle.c_str() );
        return c;
}

TCanvas* drawPrintMulti( vector<TH1D*> histlist, string title, string xtitle, string ytitle, string rfname, double ymin, double ymax, vector<string> label )
{
        return drawPrintMulti( histlist, ".pdf", title, xtitle, ytitle, rfname, ymin, ymax, label );
}

TCanvas* drawPrintMulti( vector<TH1D*> histlist, string title, string xtitle, string ytitle, string rfname, vector<string> label )
{
        return drawPrintMulti( histlist, ".pdf", title, xtitle, ytitle, rfname, 0, 0, label );
}

TCanvas* drawPrint2D( TH2D* hist, string type, string title, string xtitle, string ytitle, string rfname )
{
        TCanvas *c = getTDRCanvas( title + rfname );
        tdrHist2DDraw( hist, c, xtitle, ytitle );
        string savetitle( rfname + "_" + rpsb(title) + type );
        c->SaveAs( savetitle.c_str() );

        return c;
}

TCanvas* drawPrint2D( TH2D* hist, string title, string xtitle, string ytitle, string rfname)
{
        return drawPrint2D( hist, ".pdf", title, xtitle, ytitle , rfname );
}


