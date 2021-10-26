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

void circuito_2_lab_1_AC()
{
    DataContainer_due_ac due;
    due.read("../Dati/circuito2_ac.txt");

    auto c1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput = new TGraph(into_root(due.v_in), into_root(due.v_d));

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kAzure - 4);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("V_{in} [V]");
    fileInput->GetYaxis()->SetTitle("V_{d} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");
}