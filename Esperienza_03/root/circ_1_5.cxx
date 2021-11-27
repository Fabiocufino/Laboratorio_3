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

double func(double *x, double *par)
{

    double a = par[0];
    double b = par[1];
    double c = par[2];
    double ex = a * exp(-(b + x[0]) / c);
    return ex;
}

void circ_1_5()
{
    DataContainerGen circ_1_4;
    circ_1_4.read("../Dati/1_5.txt", 5);
    vector<double> &f = circ_1_4.tabella[0];
    vector<double> &v_in = circ_1_4.tabella[1];
    vector<double> &fs_v_in = circ_1_4.tabella[2];
    vector<double> &v_out = circ_1_4.tabella[3];
    vector<double> &fs_v_out = circ_1_4.tabella[4];

    vector<double> err_v_out;
    circ_1_4.err_oscilloscopio(4, 3, err_v_out);

    vector<double> err_f(err_v_out.size(), 0);

    vector<double> A;
    vector<double> err_A;
    for (int i = 0; i < v_out.size(); i++)
    {
        A.push_back(20 * log10(v_out[i] / v_in[i]));
        err_A.push_back(0);
    }

    TCanvas *c1 = new TCanvas("c1", "Circuito 1_5", 468, 206, 1332, 851);
    c1->Range(0, 0, 1, 1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);

    c1->SetLogx();

    TGraphErrors *fileInput = new TGraphErrors(into_root(f), into_root(A), into_root(err_f), into_root(err_A));
    fileInput->SetMarkerColor(kAzure - 3);
    fileInput->SetLineColor(kAzure - 3);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("f [kHz]");
    fileInput->GetYaxis()->SetTitle("A [dB]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);
    fileInput->Draw("AP");


    TLegend *legend = new TLegend(0.15, 0.65, 0.3, 0.95);
    legend->AddEntry(fileInput, "Dati con errore", "P");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();
}