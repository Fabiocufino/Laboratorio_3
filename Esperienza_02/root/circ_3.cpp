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

double err_res_cap(double resistenza, double perc, double digit, double lsd)
{
    double gain = perc / 100. * resistenza * 1. / sqrt(3);
    double read = digit * lsd * 1. / sqrt(3);
    return sqrt(pow(gain, 2) + pow(read, 2));
}

enum class Colonna : int
{
    t = 0,
    fst = 1,
    v_out = 2,
    fs_vout = 3
};

double somma_seni(double *x, double *par)
{
    double a = par[0];
    double b = par[1];
    double c = par[2];

    double val = 1 * sin(2 * M_PI * 1000 * x[0] + a) + 1 * sin(2 * M_PI * 2000 * x[0] + b) + c;
    return val;
}

void circ_3()
{
    double r1 = 9.993e3;     //ohm
    double r1b = 10.003e3;   //ohm
    double rf_sum = 9.978e3; //ohm
    double r50 = 46.51;      //ohm
    double r50b = 46.74;     //ohm

    double err_r1 = err_res_cap(r1, 0.07, 8, 1);         //ohm
    double err_r1b = err_res_cap(r1b, 0.07, 8, 1);       //ohm
    double err_rf_sum = err_res_cap(rf_sum, 0.07, 8, 1); //ohm
    double err_r50 = err_res_cap(r50, 0.1, 8, 0.01);     //ohm
    double err_r50b = err_res_cap(r50b, 0.1, 8, 0.01);   //ohm

    DataContainerGen tre;
    tre.read("../Dati/circuito_3.txt", 4);
    vector<double> &t = tre.tabella[(int)Colonna::t];
    vector<double> &v_out = tre.tabella[(int)Colonna::v_out];
    vector<double> &fs_vout = tre.tabella[(int)Colonna::fs_vout];

    vector<double> err_vout;
    tre.err_oscilloscopio((int)Colonna::fs_vout, (int)Colonna::v_out, err_vout);
    vector<double> err_tempo(err_vout.size(), 0);

    // ------------------------------------------INIZIO GRAFCIO E CALCOLO PARAMETRI-- -------------
    auto canvas1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    canvas1->SetGrid();
    canvas1->SetFillColor(0);

    TGraphErrors *fileInput = new TGraphErrors(into_root(t), into_root(v_out), into_root(err_tempo), into_root(err_vout));

    fileInput->SetMarkerColor(4);
    fileInput->SetMarkerColor(kAzure - 2);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("t [us]");
    fileInput->GetYaxis()->SetTitle("V_{out} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    TF1 *fit_sin = new TF1("f2", somma_seni, 0, 1000, 3);
    fit_sin->SetLineColor(kRed);
    fit_sin->SetLineStyle(2);
    fit_sin->SetLineWidth(1);


    fit_sin->SetParameter(0, 1);
    fit_sin->SetParameter(1, 1);
    fit_sin->SetParameter(2, 1);

    fit_results fitres;
    fit(fit_sin, 3, fileInput, t, v_out, fitres, -10, 1000);
}