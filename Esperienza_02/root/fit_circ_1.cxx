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

void fit_circ_1()
{

    auto c1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput = new TGraph("../Dati/circuito_1_lab_3.txt");

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kAzure - 4);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("Vpp_{IN} [mV]");
    fileInput->GetYaxis()->SetTitle("Vpp_{OUT} [?]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");
}