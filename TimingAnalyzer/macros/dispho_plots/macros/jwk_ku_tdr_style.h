/////////////////////////////////////////////////////////////////////////////////////////
//
// Jack W King III   2017
//
// Plot Style Code
// to use add #include "ku_tdr_style.h" to top of analysis c file.
// be sure this file is in directory with your analysis c file.
//
// ****  Add: setTDRStyle(); in the same area, but before, you create canvases. *****
//
// you can use the draw functions and the getCanvas function provided or use the code 
// as shown in those functions below to draw and get a canvas.
//
// Titles are provided by you.  be sure to specify units ex: " Pt ( GeV ) " if there are
// units and specify bin size for events ex: " Events / 20 GeV " for an event axis title.
// The titles you specify in the declaration of the histogram will be used in the plot
// as the title of the plot and the title of the stats box, plan accordingly.  I recomend
// using the same title for the histogram plot and the canvas.
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TStyle.h"

void CreatePalette()
{
    //From Prof. Chris Rogan
    //Useful ROOT5 palette
    //Call with CreatePalette()
    Int_t MyPalette[32];
    Int_t alpha=1;
    
    Double_t Stops[5] = { 0.00, 0.35, 0.60, 0.80, 1.00 };
    Double_t Red[5]   = { 0.00, 0.00, 0.74, 1.00, 1.00 };
    Double_t Green[5] = { 0.00, 0.61, 0.82, 0.70, 0.31 };
    Double_t Blue[5]  = { 0.31, 0.73, 0.08, 0.00, 0.00 };
    
    Int_t test = TColor::CreateGradientColorTable(5, Stops, Red, Green, Blue, 32);
    for(int i=0; i<32; i++)
    {
        MyPalette[i] = test+i;
    }
    gStyle->SetPalette(32,MyPalette);
}

void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  
  CreatePalette();


// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(can_y_width); //Height of canvas
  tdrStyle->SetCanvasDefW(can_x_width); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);
  
// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  // tdrStyle->SetErrorMarker(20);
  //tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);
  
//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(1); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(22);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.20);
  tdrStyle->SetStatW(0.25);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  tdrStyle->SetStatX( 0.825 );
  tdrStyle->SetStatY( 0.85 );

// Margins:
  tdrStyle->SetPadTopMargin(0.1);
  tdrStyle->SetPadBottomMargin(0.15);
  tdrStyle->SetPadLeftMargin(0.14);
  tdrStyle->SetPadRightMargin(0.14);

// For the Global title:

  tdrStyle->SetOptTitle(1);
  tdrStyle->SetTitleFont(22);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.06);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  tdrStyle->SetTitleX(0.5); // Set the position of the title box
  tdrStyle->SetTitleAlign(23);
  tdrStyle->SetTitleY(0.985); // Set the position of the title box
//  tdrStyle->SetTitleStyle(1001);
  tdrStyle->SetTitleBorderSize(0);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(22, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXSize(0.06); // Another way to set the size?  0.02
  tdrStyle->SetTitleYSize(0.06);
  tdrStyle->SetTitleXOffset(1.1);
  tdrStyle->SetTitleYOffset(1.1);
//  tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(22, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.06, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);

  tdrStyle->cd();

}

