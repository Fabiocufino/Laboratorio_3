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

#include "datacontainer.h"
#include "root.h"
using namespace std;

void circuito_3_lab_1()
{
    DataContainer_tre tre;
    tre.read("../Dati/circuito3.txt");

    auto c1 = new TCanvas("c1", "Circuito 3", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput = new TGraph(into_root(tre.v_a), into_root(tre.v_out));

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kRed);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.9);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("V_{a} [V]");
    fileInput->GetYaxis()->SetTitle("V_{out} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    //--------------------SIMULAZIONE
    TGraph *simul = new TGraph("../Diodo/circuito_3_lab_1_va_vb_vout.txt","%*lg %lg %*lg %lg");

    simul->SetMarkerColor(4);
    simul->SetLineColor(kAzure - 4);
    simul->SetMarkerStyle(20);
    simul->SetMarkerSize(0.2);
    simul->SetTitle("");
    simul->GetXaxis()->SetTitle("V_{a} [V]");
    simul->GetYaxis()->SetTitle("V_{out} [mV]");
    simul->GetXaxis()->SetAxisColor(14);
    simul->GetYaxis()->SetAxisColor(14);

    simul->Draw("Psame");
}