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
//Pendo di fare il fit della forma d'onda che ci deve usccire
//con quella che abiamo preso con la pennetta

double func(double *x, double *par)
{

    double a = par[0];
    double c = par[1];
    double ex = a * (x[0]) * exp(-(x[0]) / c);
    return ex;
}

void circ_2_1()
{
    DataContainerGen circ_2_1;
    circ_2_1.read("../Dati/2_1.txt", 4);
    vector<double> &t = circ_2_1.tabella[0];
    vector<double> &fs_t = circ_2_1.tabella[1];
    vector<double> &v_out = circ_2_1.tabella[2];
    vector<double> &fs_v_out = circ_2_1.tabella[3];

    vector<double> err_v;
    circ_2_1.err_oscilloscopio(3, 2, err_v);
    vector<double> err_t;
    circ_2_1.err_oscilloscopio(1, 0, err_t, true);

    TCanvas *c1 = new TCanvas("c1", "Circuito 2_1", 468, 206, 1332, 851);
    c1->Range(0, 0, 1, 1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);

    TGraphErrors *fileInput = new TGraphErrors(into_root(t), into_root(v_out), into_root(err_t), into_root(err_v));
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
    TF1 *expon = new TF1("expon", func, 0, 150, 2);
    expon->SetLineColor(kRed);
    expon->SetLineStyle(2);
    expon->SetLineWidth(2);
    expon->SetParameter(0, 0.0724);
    expon->SetParameter(1, 14.3);
    //expon->Draw("Lsame");
    //expon->SetParLimits(0, 0.01, .1);
    //expon->SetParLimits(1, 14, 15);
    fit(expon, 2, fileInput, t, v_out, Exp);

    //Simulazione
    DataContainerGen circ_2_1_simul;
    circ_2_1_simul.read("../Dati/2_1_simul.txt", 3);
    vector<double> &t_sim = circ_2_1_simul.tabella[0];
    vector<double> &v_out_s = circ_2_1_simul.tabella[2];

    vector<double> t_sim_sec;
    for (int i = 0; i < t_sim.size(); i++)
    {
        t_sim_sec.push_back(t_sim[i] * 1e6);
    }

    TGraph *fileInput_simul = new TGraph(into_root(t_sim_sec), into_root(v_out_s));
    fileInput_simul->SetMarkerColor(kAzure - 4);
    fileInput_simul->SetMarkerStyle(24);
    fileInput_simul->SetMarkerSize(0.7);
    fileInput_simul->Draw("Psame");
}