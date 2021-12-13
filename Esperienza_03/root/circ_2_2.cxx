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
#include <fstream>
#include "TLine.h"

#include "DATACLASSGEN.h"
#include "root.h"
#include "fit_results.h"

using namespace std;

double func(double *x, double *par)
{

    double a = par[0];
    double b = par[1];
    double v_out_teor = (a + b * log10(x[0]));
    return v_out_teor;
}

void circ_2_2()
{
    DataContainerGen circ_2_2;
    circ_2_2.read("../Dati/2_2.txt", 5);
    vector<double> &f = circ_2_2.tabella[0];
    vector<double> &v_in = circ_2_2.tabella[1];
    vector<double> &fs_v_in = circ_2_2.tabella[2];
    vector<double> &v_out = circ_2_2.tabella[3];
    vector<double> &fs_v_out = circ_2_2.tabella[4];

    vector<double> err_vin;
    circ_2_2.err_oscilloscopio(2, 1, err_vin);
    circ_2_2.add_col(err_vin);

    vector<double> err_v_out;
    circ_2_2.err_oscilloscopio(4, 3, err_v_out);
    circ_2_2.add_col(err_v_out);
    vector<int> cols_to_print = {
        0,
        1,
    };
    circ_2_2.dump(cols_to_print);

    vector<double> err_f(err_v_out.size(), 0);

    vector<double> A;
    vector<double> err_A;
    for (int i = 0; i < v_out.size(); i++)
    {
        A.push_back(20 * log10(v_out[i] / v_in[i]));
        double err_amplitude = sqrt((400 * pow(err_vin[i], 2)) / (pow(v_in[i], 2) * pow(log(10), 2)) +
                                    (400 * pow(err_v_out[i], 2)) / (pow(v_out[i], 2) * pow(log(10), 2)));
        cout << "Questa è A  " << A[i] << endl;
        err_A.push_back(err_amplitude);
    }

    TCanvas *c1 = new TCanvas("c1", "Circuito 2_1", 468, 206, 1332, 851);
    c1->Range(0, 0, 1, 1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);

    TPad *pad1 = new TPad("pad1", "This is pad1", 0.005, 0.02, 0.99, 0.97);
    TPad *pad2 = new TPad("pad2", "This is pad2", 0.005, 0.02, 0.49, 0.37);
    TPad *pad3 = new TPad("pad2", "This is pad2", 0.49, 0.02, 0.99, 0.37);
    pad1->Draw();
    pad2->Draw();
    pad3->Draw();

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
    pad1->SetLogx();
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

    fit_results Lin;
    TF1 *retta = new TF1("retta", func, 0, 100000000, 2);
    retta->SetLineColor(kAzure - 4);
    retta->SetLineStyle(7);
    retta->SetLineWidth(2);
    fit(retta, 2, fileInput, f, A, Lin, 0, 8502);

    fit_results Lin2;
    TF1 *retta2 = new TF1("retta2", func, 0, 100000000, 2);
    retta2->SetLineColor(kAzure - 4);
    retta2->SetLineStyle(7);
    retta2->SetLineWidth(2);
    fit(retta2, 2, fileInput, f, A, Lin2, 10966, 1.6e+06);

    // Simulazione
    DataContainerGen circ_2_2_simul;
    circ_2_2_simul.read("../Dati/2_2_simul.txt", 3);
    vector<double> &f_sim = circ_2_2_simul.tabella[0];
    vector<double> &v_in_s = circ_2_2_simul.tabella[1];
    vector<double> &v_out_s = circ_2_2_simul.tabella[2];

    vector<double> amp_simul;
    for (int i = 0; i < v_out_s.size(); i++)
    {
        amp_simul.push_back(v_out_s[i] - v_in_s[i]);
    }

    TGraph *fileInput_simul = new TGraph(into_root(f_sim), into_root(amp_simul));
    fileInput_simul->SetMarkerColor(kAzure - 4);
    fileInput_simul->SetMarkerStyle(24);
    fileInput_simul->SetMarkerSize(0.7);
    fileInput_simul->SetTitle("");
    fileInput_simul->GetXaxis()->SetTitle("f [kHz]");
    fileInput_simul->GetYaxis()->SetTitle("A [dB]");
    fileInput_simul->GetXaxis()->SetAxisColor(14);
    fileInput_simul->GetYaxis()->SetAxisColor(14);
    fileInput_simul->Draw("Psame");
    // Va rifatta con la capacità in parallelo

    // Teorico
    TGraph *fileInput_teor = new TGraph("../Dati/2_2_teor.txt");
    fileInput_teor->SetLineColor(kRed);
    fileInput_teor->SetLineStyle(2);
    fileInput_teor->SetLineWidth(2);
    fileInput_teor->Draw("Lsame");

    // Plotto la freuenza relativa al tau

    double f_tau = 10100;
    // cout << f_tau << endl;
    TLine *max = new TLine(f_tau, -55, f_tau, -6.49);
    max->SetLineColor(kBlack);
    max->SetLineStyle(2);
    max->Draw("same");
    //
    TLatex latex;
    latex.SetTextSize(0.25);
    latex.SetTextAlign(13); // align at top
    latex.DrawLatex(1000, -30, "#it{f_{t}}#approx 10.1 kHz");
    //
    TLegend *legend = new TLegend(0.15, 0.65, 0.3, 0.95);
    legend->AddEntry(fileInput, "Dati Sperimentali con errore", "P");
    legend->AddEntry(fileInput_simul, "Dati Simulati", "P");
    legend->AddEntry(fileInput_teor, "Previsione Teorica", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();

    //----------------------------------------------------------SCARTI---------------------------------

    pad2->cd();
    pad2->SetLogx();
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
    run_test_lineare_logx(scarti, f, A, Lin.a[0], Lin.b[0]);
    vector<double> err_scarti;
    for (int i = 0; i < scarti.size(); i++)
    {
        err_scarti.push_back(sqrt(pow(err_A[i], 2) + pow(Lin.b[0] * err_f[i], 2)));
    }
    vector<double> err_zero(err_scarti.size(), 0);

    TGraphErrors *graph_scarti = new TGraphErrors(into_root(f), into_root(scarti), into_root(err_zero), into_root(err_scarti));

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

    TF1 *z = new TF1("z", "pol1", 0, 10000);
    z->SetLineColor(kRed);
    z->SetLineStyle(2);
    z->SetLineWidth(2);
    z->Draw("lsame");

    TLegend *legend2 = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend2->AddEntry(graph_scarti, "Scarti retta SX", "P");
    legend2->SetTextSize(0.04);
    legend2->SetBorderSize(1);
    legend2->SetTextSize(0.08447205);
    legend2->Draw();

    //=============================================scarti 2
    pad3->cd();
    pad3->SetLogx();
    pad3->SetFillColor(0);
    pad3->SetBorderMode(0);
    pad3->SetBorderSize(2);
    pad3->SetLeftMargin(0.07732215);
    pad3->SetRightMargin(0.05698707);
    pad3->SetBottomMargin(0.1664596);
    pad3->SetFrameBorderMode(0);
    pad3->SetFrameBorderMode(0);

    vector<double> scarti2;
    run_test_lineare_logx(scarti2, f, A, Lin2.a[0], Lin2.b[0]);
    vector<double> err_scarti2;
    for (int i = 0; i < scarti2.size(); i++)
    {
        err_scarti2.push_back(sqrt(pow(err_A[i], 2) + pow(Lin2.b[0] * err_f[i], 2)));
    }
    vector<double> err_zero2(err_scarti2.size(), 0);

    TGraphErrors *graph_scarti2 = new TGraphErrors(into_root(f), into_root(scarti2), into_root(err_zero2), into_root(err_scarti2));

    graph_scarti2->SetMarkerColor(4);
    graph_scarti2->SetLineColor(kAzure - 3);
    graph_scarti2->SetMarkerStyle(20);
    graph_scarti2->SetMarkerSize(0.7);
    graph_scarti2->SetTitle("");

    graph_scarti2->GetYaxis()->SetAxisColor(14);
    graph_scarti2->GetXaxis()->SetLabelFont(42);
    graph_scarti2->GetXaxis()->SetLabelSize(0.09);
    graph_scarti2->GetXaxis()->SetTitleOffset(1);
    graph_scarti2->GetXaxis()->SetTitleFont(42);
    graph_scarti2->GetYaxis()->SetTitle("Scarti");
    graph_scarti2->GetYaxis()->SetAxisColor(14);
    graph_scarti2->GetYaxis()->SetLabelFont(42);
    graph_scarti2->GetYaxis()->SetLabelSize(0.09);
    graph_scarti2->GetYaxis()->SetTitleSize(0.11);
    graph_scarti2->GetYaxis()->SetTitleOffset(0.33);
    graph_scarti2->GetYaxis()->SetTitleFont(42);

    graph_scarti2->Draw("AP");

    TF1 *z2 = new TF1("zz", "pol1", 10000, 10000000);
    z2->SetLineColor(kRed);
    z2->SetLineStyle(2);
    z2->SetLineWidth(2);
    z2->Draw("lsame");

    TLegend *legend4 = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend4->AddEntry(graph_scarti2, "Scarti retta DX", "P");
    legend4->SetTextSize(0.04);
    legend4->SetBorderSize(1);
    legend4->SetTextSize(0.08447205);
    legend4->Draw();
}