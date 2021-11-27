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
    fileInput->GetXaxis()->SetTitle("Q_{in} [uC]");
    fileInput->GetYaxis()->SetTitle("V_{pre}^{MAX} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    fit_results Lin;
    TF1 *retta = new TF1("retta", "pol1", 0, 10);
    retta->SetLineColor(kRed);
    retta->SetLineStyle(2);
    retta->SetLineWidth(2);
    retta->SetParameter(0, 8.23);
    retta->SetParameter(1, 4.5e12);
    fit(retta, 2, fileInput, Q_in, v_out, Lin);

    TPaveStats *info;
    TText *scri;
    informazioni_fit_lineare(info,
                             scri,
                             to_string(round(Lin.chi_square[0] * 100.0) / 100.0),
                             to_string((int)Lin.dof[0]),
                             to_string(Lin.a[0]),
                             to_string(Lin.err_a[0]),
                             "4.507e+12",
                             "1.326e+11",
                             to_string(Lin.rho[0]),
                             to_string(Lin.t_student[0]),
                             to_string(Lin.sigma_post[0]),
                             "Fit lineare sui dati");

    TLegend *legend = new TLegend(0.15, 0.65, 0.3, 0.95);
    legend->AddEntry(fileInput, "Dati con errore", "P");
    legend->AddEntry(retta, "Retta Interpolante", "L");
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
    run_test_lineare(scarti, Q_in, v_out, Lin.a[0], Lin.b[0]);
    vector<double> err_scarti;
    for (int i = 0; i < scarti.size(); i++)
    {
        err_scarti.push_back(sqrt(pow(err_v_out[i], 2) + pow(Lin.b[0] * err_Q_in[i], 2)));
    }
    vector<double> err_zero(err_scarti.size(), 0);

    TGraphErrors *graph_scarti = new TGraphErrors(into_root(Q_in), into_root(scarti), into_root(err_zero), into_root(err_scarti));

    graph_scarti->SetMarkerColor(4);
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

    TF1 *z = new TF1("z", "pol1", 0, 10);
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