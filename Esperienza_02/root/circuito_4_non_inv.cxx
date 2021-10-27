#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <fstream>
#include <cmath>
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TGraphErrors.h"
#include <vector>
using namespace std;

void circuito_4_non_inv()
{
    auto c1 = new TCanvas("c1", "Circuito 4 NON INV", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput = new TGraph("../Dati/circuito4_non_inv.txt");

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kRed);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.9);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("V_{in} [V]");
    fileInput->GetYaxis()->SetTitle("V_{out} [V]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");
}