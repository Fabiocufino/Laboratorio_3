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
#include "root.h"

#include "DATACLASSGEN.h"
using namespace std;

enum class Colonna : int
{
    t = 0,
    fst = 1,
    v1 = 2,
    fs_v1 = 3,
    v2 = 4,
    fs_v2 = 5,
    vout = 6,
    fs_vout = 7
};

double err_res_cap(double resistenza, double perc, double digit, double lsd)
{
    double gain = perc / 100. * resistenza * 1. / sqrt(3);
    double read = digit * lsd * 1. / sqrt(3);
    return sqrt(pow(gain, 2) + pow(read, 2));
}

double seno(double *x, double *par)
{
    double a = par[0];
    double b = par[1];
    double c = par[2];

    double val = a * sin(2 * M_PI * 200 * (x[0] * pow(10, -3) + b)) + c;
    return val;
}

void circ_4_1()
{

    double r1 = 10.003e3; // ohm
    double rf = 67.674e3; // ohm
    double r3 = 9.981e3;  // ohm
    double r4 = 68.54e3;  // ohm
    double r50 = 46.51;   // ohm
    double r50b = 46.74;  // ohm

    double err_r1 = err_res_cap(r1, 0.07, 8, 1);       // ohm
    double err_rf = err_res_cap(rf, 0.07, 8, 1);       // ohm
    double err_r3 = err_res_cap(r3, 0.07, 8, 1);       // ohm
    double err_r4 = err_res_cap(r4, 0.07, 8, 1);       // ohm
    double err_r50 = err_res_cap(r50, 0.1, 8, 0.01);   // ohm
    double err_r50b = err_res_cap(r50b, 0.1, 8, 0.01); // ohm

    DataContainerGen quattro_diff;
    quattro_diff.read("../Dati/circuito_4_diff.txt", 8);

    vector<double> &t = quattro_diff.tabella[(int)Colonna::t];
    vector<double> &fs_t = quattro_diff.tabella[(int)Colonna::fst];
    vector<double> &v1 = quattro_diff.tabella[(int)Colonna::v1];
    vector<double> &fs_v1 = quattro_diff.tabella[(int)Colonna::fs_v1];
    vector<double> &v2 = quattro_diff.tabella[(int)Colonna::v2];
    vector<double> &fs_v2 = quattro_diff.tabella[(int)Colonna::fs_v2];
    vector<double> &vout = quattro_diff.tabella[(int)Colonna::vout];
    vector<double> &fs_vout = quattro_diff.tabella[(int)Colonna::fs_vout];
    vector<double> err_vout;
    vector<double> err_v1;
    vector<double> err_v2;

    quattro_diff.err_oscilloscopio((int)Colonna::fs_vout, (int)Colonna::vout, err_vout);
    quattro_diff.err_oscilloscopio((int)Colonna::fs_v1, (int)Colonna::v1, err_v1);
    quattro_diff.err_oscilloscopio((int)Colonna::fs_v2, (int)Colonna::v2, err_v2);

    vector<double> err_t(err_vout.size(), 0);

    // ------------------------------------------INIZIO GRAFCIO E CALCOLO PARAMETRI-- -------------
    auto canvas1 = new TCanvas("c1", "Circuito 4", 1000, 600);
    canvas1->SetGrid();
    canvas1->SetFillColor(0);

    TGraphErrors *fileInput = new TGraphErrors(into_root(t), into_root(vout), into_root(err_t), into_root(err_vout));

    fileInput->SetMarkerColor(4);
    fileInput->SetMarkerColor(kAzure - 2);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("t [ms]");
    fileInput->GetYaxis()->SetTitle("V_{out} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    TF1 *fit_sin = new TF1("f2", seno, -0.002, 10, 3);
    fit_sin->SetLineColor(kRed);
    fit_sin->SetLineStyle(2);
    fit_sin->SetLineWidth(1);

    fit_sin->SetParameter(0, 3.11599);
    fit_sin->SetParameter(1, 1.20542e-03);
    fit_sin->SetParameter(3, 6.16184e+00);

    fit_sin->SetParLimits(0, 3.01599, 3.31599);

    fit_results fit1;
    fit(fit_sin, 3, fileInput, t, vout, fit1, -0.2, 8.7);

    TF1 *fit_sin2 = new TF1("f2", seno, -0.002, 10, 3);
    fit_sin2->SetLineColor(kRed);
    fit_sin2->SetLineStyle(2);
    fit_sin2->SetLineWidth(1);

    fit_sin2->SetParameter(0, 3.11599);
    // fit_sin2->SetParameter(1, 1.20542e-03);
    // fit_sin2->SetParameter(3, 6.16184e+00);

    fit_sin2->SetParLimits(0, 3.01599, 3.31599);

    fit_results fit2;
    fit(fit_sin2, 3, fileInput, t, vout, fit1, 8.7, 18);

    // TPaveStats *info;
    // TText *scri;
    // informazioni_fit_3_par(info,
    //                        scri,
    //                        to_string(fit1.chi_square[0]),
    //                        to_string(fit1.dof[0]),
    //                        to_string(fit1.a[0]),
    //                        to_string(fit1.err_a[0]),
    //                        to_string(fit1.b[0]),
    //                        to_string(fit1.err_b[0]),
    //                        to_string(fit1.c[0]),
    //                        to_string(fit1.err_c[0]),
    //                        "Fit 1 sui dati");
    //
    // TPaveStats *info2;
    // TText *scri2;
    // informazioni_fit_3_par(info2,
    //                       scri2,
    //                       to_string(fit2.chi_square[0]),
    //                       to_string(fit2.dof[0]),
    //                       to_string(fit2.a[0]),
    //                       to_string(fit2.err_a[0]),
    //                       to_string(fit2.b[0]),
    //                       to_string(fit2.err_b[0]),
    //                       to_string(fit2.c[0]),
    //                       to_string(fit2.err_c[0]),
    //                       "Fit 2 sui dati");
    //
<<<<<<< HEAD
    TGraph *simul = new TGraph("../Circuiti/Circuito4_diff_vout.txt");
    
    simul->SetMarkerColor(4);
    simul->SetMarkerColor(kAzure - 4);
    simul->SetMarkerStyle(20);
    simul->SetMarkerSize(0.5);
    simul->SetTitle("");
    simul->GetXaxis()->SetTitle("V_{in} [mV]");
    simul->GetYaxis()->SetTitle("V_{out} [mV]");
    simul->GetXaxis()->SetAxisColor(14);
    simul->GetYaxis()->SetAxisColor(14);
    
    simul->Draw("Psame");
    //TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
    //legend->AddEntry(fileInput, "Dati sperimentali con errore", "P");
    //legend->AddEntry(simul, "Dati Simulati", "P");
    //legend->AddEntry(fit_sin, "a+bx interpolante dati sperimentali", "l");
    //legend->SetTextSize(0.04);
    //legend->SetBorderSize(1);
    //legend->Draw();
=======
    // TGraph *simul = new TGraph("../Circuiti/Circuito4_diff_vout.txt");
    //
    // simul->SetMarkerColor(4);
    // simul->SetMarkerColor(kAzure - 4);
    // simul->SetMarkerStyle(20);
    // simul->SetMarkerSize(0.5);
    // simul->SetTitle("");
    // simul->GetXaxis()->SetTitle("V_{in} [mV]");
    // simul->GetYaxis()->SetTitle("V_{out} [mV]");
    // simul->GetXaxis()->SetAxisColor(14);
    // simul->GetYaxis()->SetAxisColor(14);
    //
    // simul->Draw("Psame");

    TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend->AddEntry(fileInput, "Dati sperimentali con errore", "P");
    legend->AddEntry(fit_sin2, "Funzioni interpolanti", "l");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();

    for (int i = 0; i < vout.size(); i++)
    {
        cout << t[i] << " " << v1[i] << " +/- " << err_v1[i] << " " << v2[i] << "+/-" << err_v2[i] << " " << vout[i] << "+/-" << err_vout[i] << endl;
    }
>>>>>>> main
}