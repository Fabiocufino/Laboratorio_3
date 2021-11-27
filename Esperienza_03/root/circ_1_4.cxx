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

void circ_1_4()
{
    DataContainerGen circ_1_4;
    circ_1_4.read("../Dati/1_4.txt", 4);
    vector<double> &t = circ_1_4.tabella[0];
    vector<double> &fs_t = circ_1_4.tabella[1];
    vector<double> &v_out = circ_1_4.tabella[2];
    vector<double> &fs_v_out = circ_1_4.tabella[3];

    vector<double> err_v_out;
    circ_1_4.err_oscilloscopio(3, 2, err_v_out);

    vector<double> err_t;
    circ_1_4.err_oscilloscopio(1, 0, err_t);

    TCanvas *c1 = new TCanvas("c1", "Circuito 1_3", 468, 206, 1332, 851);
    c1->Range(0, 0, 1, 1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);

    TPad *pad1 = new TPad("pad1", "This is pad1", 0.005, 0.02, 0.99, 0.97);
    TPad *pad2 = new TPad("pad2", "This is pad2", 0.005, 0.02, 0.99, 0.37);
    pad1->Draw();
    pad2->Draw();

    pad1->cd();
    pad1->Range(-1.933052e-11, -751.0643, 2.211768e-10, 926.1686);
    pad1->SetFillColor(0);
    pad1->SetBorderMode(0);
    pad1->SetBorderSize(2);
    pad1->SetLeftMargin(0.08037394);
    pad1->SetRightMargin(0.05596981);
    pad1->SetTopMargin(0.003203662);
    pad1->SetBottomMargin(0.4549199);
    pad1->SetFrameBorderMode(0);
    pad1->SetFrameBorderMode(0);

    TGraphErrors *fileInput = new TGraphErrors(into_root(t), into_root(v_out), into_root(err_t), into_root(err_v_out));
    fileInput->SetMarkerColor(kAzure - 3);
    fileInput->SetLineColor(kAzure - 3);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("t [us]");
    fileInput->GetYaxis()->SetTitle("Voltaggio [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);
    fileInput->Draw("AP");

    fit_results Exp;
    TF1 *expon = new TF1("expon", func, 0, 200, 3);
    expon->SetLineColor(kRed);
    expon->SetLineStyle(2);
    expon->SetLineWidth(2);
    expon->SetParameter(0, 1.24596);
    expon->SetParameter(1, -844.6);
    expon->SetParameter(2, 144.087);
    fit(expon, 3, fileInput, t, v_out, Exp);

    TPaveStats *info;
    TText *scri;
    informazioni_fit_3_par(info,
                           scri,
                           to_string(round(Exp.chi_square[0] * 100.0) / 100.0),
                           to_string((int)Exp.dof[0]),
                           to_string(Exp.a[0]),
                           to_string(Exp.err_a[0]),
                           to_string(Exp.b[0]),
                           to_string(Exp.err_b[0]),
                           to_string(Exp.c[0]),
                           to_string(Exp.err_c[0]),
                           "Fit esponenziale sui dati");

    TLegend *legend = new TLegend(0.15, 0.65, 0.3, 0.95);
    legend->AddEntry(fileInput, "Dati con errore", "P");
    legend->AddEntry(expon, "V(t) = a e^{-(b+t)/c}", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();

    pad2->cd(); //----------------------------------------------------------SCARTI---------------------------------
    pad2->Range(-0.8931843, -0.5835317, 10.65828, 1.252791);
    pad2->SetFillColor(0);
    pad2->SetBorderMode(0);
    pad2->SetBorderSize(2);
    pad2->SetLeftMargin(0.07732215);
    pad2->SetRightMargin(0.05698707);
    pad2->SetBottomMargin(0.1664596);
    pad2->SetFrameBorderMode(0);
    pad2->SetFrameBorderMode(0);

    vector<double> scarti;
    run_test_esponenziale(scarti, t, v_out, Exp.a[0], Exp.b[0], Exp.c[0]);
    vector<double> err_scarti;
    for (int i = 0; i < scarti.size(); i++)
    {
        err_scarti.push_back(sqrt(pow(err_v_out[i], 2) + pow(Exp.a[0] * err_t[i] / Exp.c[0] * exp(-(Exp.b[0] + t[i]) / Exp.c[0]), 2)));
    }
    vector<double> err_zero(err_scarti.size(), 0);

    TGraphErrors *graph_scarti = new TGraphErrors(into_root(t), into_root(scarti), into_root(err_zero), into_root(err_scarti));

    graph_scarti->SetMarkerColor(kAzure - 3);
    graph_scarti->SetLineColor(kAzure - 3);
    graph_scarti->SetMarkerStyle(20);
    graph_scarti->SetMarkerSize(0.7);
    graph_scarti->SetTitle("");

    graph_scarti->GetYaxis()->SetAxisColor(14);
    graph_scarti->GetXaxis()->SetLabelFont(42);
    graph_scarti->GetXaxis()->SetLabelSize(0.09);
    graph_scarti->GetXaxis()->SetTitleOffset(1);
    graph_scarti->GetXaxis()->SetTitleFont(42);
    graph_scarti->GetYaxis()->SetTitle("Scarti");
    graph_scarti->GetYaxis()->SetAxisColor(14);
    graph_scarti->GetYaxis()->SetLabelFont(42);
    graph_scarti->GetYaxis()->SetLabelSize(0.09);
    graph_scarti->GetYaxis()->SetTitleSize(0.11);
    graph_scarti->GetYaxis()->SetTitleOffset(0.33);
    graph_scarti->GetYaxis()->SetTitleFont(42);

    graph_scarti->Draw("AP");

    TF1 *z = new TF1("z", "pol1", 0, 300);
    z->SetLineColor(kRed);
    z->SetLineStyle(2);
    z->SetLineWidth(2);
    z->Draw("lsame");

    TLegend *legend2 = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend2->AddEntry(graph_scarti, "Dati con errore", "P");
    legend2->SetTextSize(0.04);
    legend2->SetBorderSize(1);
    legend2->SetTextSize(0.08447205);
    legend2->Draw();
}