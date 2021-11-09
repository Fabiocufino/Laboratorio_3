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
    DataContainerGen quattro_th;
    quattro_diff.read("../Dati/circuito_4_diff.txt", 8);

    quattro_th.read("../Dati/circ_4_th.txt", 4);

    vector<double> &t = quattro_diff.tabella[(int)Colonna::t];
    vector<double> &t_th = quattro_th.tabella[(int)Colonna::t];
    vector<double> t_trans;
    vector<double> t_trans_th;
    for (int i = 0; i < t.size(); i++)
    {
        t_trans.push_back(t[i] + 1.2198469);
        t_trans_th.push_back(t_th[i] + 1.2198469);
    }

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

    vector<double> &vout_th = quattro_th.tabella[2];
    vector<double> &err_vout_th = quattro_th.tabella[3];

    quattro_diff.err_oscilloscopio((int)Colonna::fs_vout, (int)Colonna::vout, err_vout);
    quattro_diff.err_oscilloscopio((int)Colonna::fs_v1, (int)Colonna::v1, err_v1);
    quattro_diff.err_oscilloscopio((int)Colonna::fs_v2, (int)Colonna::v2, err_v2);

    vector<double> err_t(err_vout.size(), 0);

    // ------------------------------------------INIZIO GRAFCIO E CALCOLO PARAMETRI-- -------------
    auto canvas1 = new TCanvas("c1", "Circuito 4", 1000, 600);
    canvas1->SetGrid();
    canvas1->SetFillColor(0);

    TGraphErrors *fileInput = new TGraphErrors(into_root(t_trans), into_root(vout), into_root(err_t), into_root(err_vout));
    TGraphErrors *fileInput_2 = new TGraphErrors(into_root(t_trans), into_root(vout_th), into_root(err_t), into_root(err_vout_th));

    fileInput->SetMarkerColor(kRed);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("t [ms]");
    fileInput->GetYaxis()->SetTitle("V_{out} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    fileInput_2->SetMarkerColor(kOrange);
    fileInput_2->SetMarkerStyle(20);
    fileInput_2->SetMarkerSize(0.7);
    fileInput_2->SetTitle("");
    fileInput_2->GetXaxis()->SetTitle("t [ms]");
    fileInput_2->GetYaxis()->SetTitle("V_{out} [mV]");
    fileInput_2->GetXaxis()->SetAxisColor(14);
    fileInput_2->GetYaxis()->SetAxisColor(14);

    fileInput_2->Draw("Psame");

    TGraph *simul = new TGraph("../Circuiti/Circuito4_diff.txt");

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

    TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend->AddEntry(fileInput, "Dati sperimentali con errore", "P");
    legend->AddEntry(simul, "Dati simulati", "P");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();

    for (int i = 0; i < vout.size(); i++)
    {
        cout << t[i] << " " << v1[i] << " +/- " << err_v1[i] << " " << v2[i] << "+/-" << err_v2[i] << " " << vout[i] << "+/-" << err_vout[i] << endl;
    }
}