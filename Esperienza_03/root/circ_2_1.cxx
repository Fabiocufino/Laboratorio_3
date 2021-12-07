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
    double ex = (a / c) * (x[0]) * exp(-(x[0]) / c);
    return ex;
}

void circ_2_1()
{
    double v_0 = 1.02; //volt
    double v_sh = v_0 / exp(1);
    double err_v_0 = err_osc_v(v_0, 0.200); //volt
    double err_v_sh = err_v_0 / exp(1);

    cout << "v_0:\t" << v_0 << " +- " << err_v_0 << endl
         << "v_e:\t" << v_sh << " +_ " << err_v_sh << endl;

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

    //Teorica
    TF1 *teor = new TF1("teor", func, 0, 100, 2);
    teor->SetParameter(0, 1);
    teor->SetParameter(1, 14.3502);
    teor->Draw("same");

    //
    DataContainerGen circ_2_1_teor;
    circ_2_1_teor.read("../Dati/2_1_teor.txt", 2);
    vector<double> &t_teor = circ_2_1_teor.tabella[0];
    vector<double> &v_out_teor = circ_2_1_teor.tabella[1];

    vector<double> t_teor_sec;
    for (int i = 0; i < t_teor.size(); i++)
    {
        t_teor_sec.push_back(t_teor[i] * 1e6);
    }

    TGraph *fileInput_teor = new TGraph(into_root(t_teor_sec), into_root(v_out_teor));
    fileInput_teor->SetMarkerColor(kGreen - 4);
    fileInput_teor->SetMarkerStyle(24);
    fileInput_teor->SetMarkerSize(0.7);
    fileInput_teor->Draw("Psame");

    TLegend *legend = new TLegend(0.15, 0.65, 0.3, 0.95);
    legend->AddEntry(fileInput, "Dati Sperimentali con errore", "P");
    legend->AddEntry(fileInput_simul, "Dati Simulati", "P");
    legend->AddEntry(expon, "Fit Dati sperimentali", "L");
    legend->AddEntry(fileInput_teor, "Curva di aspettazione teorica", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();
}