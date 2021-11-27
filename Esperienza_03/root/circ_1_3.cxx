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
    double R_in = 55.306 * 1e3;          // KOmh
    double err_R_in = 0.0228 * 1e3;      // KOhm
    double v_in = 1020 / 1e3;            // mV
    double err_v_in = 23.93170839 / 1e3; // mV

    DataContainerGen circ_1_3;
    circ_1_3.read("../Dati/1_3.txt", 3);
    vector<double> &t = circ_1_3.tabella[0];
    vector<double> &v_out = circ_1_3.tabella[1];
    vector<double> &fs_v_out = circ_1_3.tabella[2];
    double err_t = (1. / 10.) * 5 * (1. / sqrt(6.)) * 1e-6;

    auto c1 = new TCanvas("c1", "Circuito 1_3", 1000, 600);
    c1->SetBottomMargin(0.1);
    c1->SetTopMargin(0.1);
    c1->SetLeftMargin(0.1);
    c1->SetRightMargin(0.1);

    c1->SetBorderMode(0);

    c1->SetFillColor(0);

    TPad *pad1 = new TPad("pad1", "This is pad1", 0.005, 0.12, 0.99, 0.97);
    TPad *pad2 = new TPad("pad2", "This is pad2", 0.005, 0.02, 0.99, 0.37);
    pad1->Draw();
    pad2->Draw();

    pad1->cd();
    pad1->SetBorderMode(0);
    pad1->SetBorderSize(2);
    pad1->SetLeftMargin(0.08749478);
    pad1->SetRightMargin(0.01426203);
    pad1->SetTopMargin(0.003648289);
    pad1->SetBottomMargin(0.3732732);
    pad1->SetFrameBorderMode(0);
    pad1->SetFrameBorderMode(0);
    vector<double> Q_in;
    vector<double> err_Q_in;

    for (int i = 0; i < t.size(); i++)
    {
        Q_in.push_back((v_in / R_in) * t[i]);
        err_Q_in.push_back(sqrt(pow(v_in * t[i] * err_R_in / pow(R_in, 2), 2) +
                                pow(err_v_in * t[i] / R_in, 2) +
                                pow(v_in * err_t / R_in, 2)));
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

    pad2->cd();
    pad2->SetBorderMode(0);
    pad2->SetBorderSize(2);
    pad2->SetLeftMargin(0.08749478);
    pad2->SetRightMargin(0.01426203);
    pad2->SetTopMargin(0.003648289);
    pad2->SetBottomMargin(0.3732732);
    pad2->SetFrameBorderMode(0);
    pad2->SetFrameBorderMode(0);
    TF1 *fa1 = new TF1("fa1", "sin(x)/x", 0, 10);
    fa1->Draw();
}