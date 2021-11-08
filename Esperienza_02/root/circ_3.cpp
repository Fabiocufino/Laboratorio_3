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

    double val = 0.5 * sin(2 * M_PI * 1000 * (x[0] - a)) + 0.5 * sin(2 * M_PI * 2000 * (x[0] - a) + b) + c;
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

    cout << "Resistenze usate:" << endl
         << "R1:\t" << r1 << "+-" << err_r1 << endl
         << "R1b:\t" << r1b << "+-" << err_r1b << endl
         << "Rf_sum:\t" << rf_sum << "+-" << err_rf_sum << endl
         << "R50:\t" << r50b << "+-" << err_r50 << endl
         << "R50B:\t" << r50b << "+-" << err_r50b << endl
         << endl;

    DataContainerGen tre;
    tre.read("../Dati/circuito_3.txt", 4);
    vector<double> &t = tre.tabella[(int)Colonna::t];
    vector<double> t_sec;
    for (auto c : t)
    {
        t_sec.push_back(c * pow(10, -6));
    }
    vector<double> &v_out = tre.tabella[(int)Colonna::v_out];
    vector<double> v_volt;
    for (auto c : v_out)
    {
        v_volt.push_back(c * pow(10, -3));
    }
    vector<double> &fs_vout = tre.tabella[(int)Colonna::fs_vout];

    vector<double> err_volt;
    tre.err_oscilloscopio((int)Colonna::fs_vout, (int)Colonna::v_out, err_volt);
    vector<double> err_tempo(err_volt.size(), 0);

    vector<double> err_v_volt;
    for (auto c : err_volt)
    {
        err_v_volt.push_back(c * pow(10, -3));
    }

    for (int i = 0; i < v_volt.size(); i++)
    {
        cout << t_sec[i] * 1e6 << "\t" << v_volt[i] * 1e3 << "+-" << err_v_volt[i] * 1e3 << endl;
    }
    cout << endl;

    // ------------------------------------------INIZIO GRAFCIO E CALCOLO PARAMETRI-- -------------
    auto canvas1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    canvas1->SetGrid();
    canvas1->SetFillColor(0);

    TGraphErrors *fileInput = new TGraphErrors(into_root(t_sec), into_root(v_volt), into_root(err_tempo), into_root(err_v_volt));

    fileInput->SetMarkerColor(4);
    fileInput->SetMarkerColor(kAzure - 2);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("t [s]");
    fileInput->GetYaxis()->SetTitle("V_{out} [V]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    TF1 *fit_sin = new TF1("f2", somma_seni, -0.002, 0.002, 3);
    fit_sin->SetLineColor(kRed);
    fit_sin->SetLineStyle(2);
    fit_sin->SetLineWidth(1);

    fit_sin->SetParameter(0, -1.43562);
    fit_sin->SetParameter(1, -8 + 4 * M_PI);
    fit_sin->SetParameter(2, 0.953194);

    fit_sin->SetParName(0, "t_{0}");
    fit_sin->SetParName(1, "#phi_{1} - #phi_{2}");
    fit_sin->SetParName(2, "c");

    fit_results fitres;
    fit(fit_sin, 3, fileInput, t_sec, v_volt, fitres, -0.002, 0.002);

    TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend->AddEntry(fileInput, "Dati con errore", "P");
    legend->AddEntry(fit_sin, "A_{1}sin(#omega_{1} (t-t_{0}) + #phi_{1})+A_{2}sin(#omega_{2} (t-t_{0}) + #phi_{2}) + c", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();
}