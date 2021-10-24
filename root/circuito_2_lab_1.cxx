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

void circuito_2_lab_1()
{
    DataContainer_due due;
    due.read("../Dati/circuito2_dc.txt");

    auto c1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);
    TGraph *fileInput = new TGraph(into_root(due.v_in), into_root(due.v_d));

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kAzure - 3);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("V_{in} [V]");
    fileInput->GetYaxis()->SetTitle("V_{d} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    fit_results retta_1;
    TF1 *retta1 = new TF1("retta1", "pol1", 0, 10);
    retta1->SetLineColor(kRed);
    retta1->SetLineStyle(2);
    retta1->SetLineWidth(2);
    fit(retta1, 2, fileInput, due.v_in, due.v_d, retta_1, 0, 2);

    fit_results retta_2;
    TF1 *retta2 = new TF1("retta2", "pol1", 0, 10);
    retta2->SetLineColor(kRed);
    retta2->SetLineStyle(2);
    retta2->SetLineWidth(2);
    fit(retta1, 2, fileInput, due.v_in, due.v_d, retta_2, 7, 10);

    cout << (retta_2.a[0] - retta_1.a[0]) / (retta_1.b[0] - retta_2.b[0]) << endl;
    //Manca propagazione errore
}