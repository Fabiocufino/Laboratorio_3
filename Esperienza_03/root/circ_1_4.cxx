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

#include "DATACLASSGEN.h"
using namespace std;

void circ_1_3()
{
    DataContainerGen circ_1_3;
    circ_1_3.read("../Dati/1_3.txt", 4);
    vector<double> t = circ_1_3.tabella[0];
    vector<double> fs_t = circ_1_3.tabella[1];
    vector<double> v_out = circ_1_3.tabella[2];
    vector<double> fs_v_out = circ_1_3.tabella[3];

    vector<double> ln_v_out;
    for (int i = 0; i < v_out.size(); i++)
    {
        ln_v_out[i] = log(v_out[i]);
    }

    auto c1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput = new TGraph("1_3.txt");

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kAzure - 4);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("Quantità di carica [uC (?)]");
    fileInput->GetYaxis()->SetTitle("V_{pre}^{MAX} [V]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");
}