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
#include "root.h"
#include "fit_results.h"

using namespace std;

void circ_1_3()
{
    // costanti da excel e logbook
    double R_in = 55.306;          // KOmh
    double err_R_in = 0.0228;      // KOhm
    double v_in = 1020;            // mV
    double err_v_in = 23.93170839; // mV

    DataContainerGen circ_1_3;
    circ_1_3.read("../Dati/1_3.txt", 3);
    vector<double> &t = circ_1_3.tabella[0];
    vector<double> &v_out = circ_1_3.tabella[1];
    vector<double> &fs_v_out = circ_1_3.tabella[2];
    double err_t = (1. / 10.) * 5 * (1. / sqrt(6.));

    auto c1 = new TCanvas("c1", "Circuito 1_3", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    vector<double> Q_in;
    vector<double> err_Q_in;

    for (int i = 0; i < t.size(); i++)
    {
        Q_in.push_back((v_in / R_in) * t[i]);
        err_Q_in.push_back(sqrt(pow(v_in * t[i] * err_R_in / pow(R_in, 2), 2) + pow(err_v_in * t[i] / R_in, 2) + pow(v_in * err_t / R_in, 2)));
    }

    vector<double> err_v_out;
    circ_1_3.err_oscilloscopio(2, 1, err_v_out);

    TGraphErrors *fileInput = new TGraphErrors(into_root(Q_in), into_root(v_out), into_root(err_Q_in), into_root(err_v_out));

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