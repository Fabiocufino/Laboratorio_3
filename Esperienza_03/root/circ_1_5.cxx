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
#include<string>

#include "DATACLASSGEN.h"
#include "root.h"
#include "fit_results.h"

using namespace std;

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
    vector<double> err_vin;
    circ_1_4.err_oscilloscopio(2, 1, err_vin);

    for (int i = 0; i < err_v_out.size(); i++)
    {
        cout << err_vin[i] << "\t" << err_v_out[i] << endl;
    }

    vector<double> err_f(err_v_out.size(), 0);

    vector<double> A;
    vector<double> err_A;
    for (int i = 0; i < v_out.size(); i++)
    {
        A.push_back(20 * log10(v_out[i] / v_in[i]));
        double err_amplitude = sqrt((400 * pow(err_vin[i], 2)) / (pow(v_in[i], 2) * pow(log(10), 2)) +
                                    (400 * pow(err_v_out[i], 2)) / (pow(v_out[i], 2) * pow(log(10), 2)));
        double err_amplitude_2 = sqrt(pow(20.0 / (v_out[i] * log(10)) * err_v_out[i], 2) +
                                      pow(20.0 / (v_in[i] * log(10)) * err_vin[i], 2));
        err_A.push_back(err_amplitude); //DA FARE
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

    //Simulazione
    DataContainerGen circ_1_4_simul;
    circ_1_4_simul.read("../Dati/1_5_simul.txt", 3);
    vector<double> &f_sim = circ_1_4_simul.tabella[0];
    vector<double> &v_in_s = circ_1_4_simul.tabella[1];
    vector<double> &v_out_s = circ_1_4_simul.tabella[2];

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

    //Teorico
    vector<double> amp_teor;
    vector<double> f_teor;
    double tau_sper = 143.615 * pow(10, -6);                      //us
    double err_tau_sper = 3.93e-6;                                //us da fit root
    double R = (681.) * pow(10, 3);                               //ohm
    double err_R = err_res_cap(R, 0.07, 8, 1);                    //ohm
    double c_0 = 19e-12;                                          //farad
    double c_f = (237 - 19) * 1e-12;                              //farad
    double err_c_f = err_res_cap(c_f * 1e12, 2.5, 15, 1) * 1e-12; //farad
    double R1 = 55.31 * pow(10, 3);                               //ohm

    for (int i = 0; i < f.size(); i++)
    {
        f_teor.push_back(f[i]);
        double real = (-1. / tau_sper) / ((-pow(2. * M_PI * f[i], 2.) - (1. / pow(tau_sper, 2.))));
        double imm = 2. * M_PI * f[i] / ((-pow(2. * M_PI * f[i], 2.) - (1. / pow(tau_sper, 2.))));
        amp_teor.push_back(-20. * log10(R1) + 20. * log10((R / tau_sper) * (sqrt(pow(real, 2.) + pow(imm, 2.)))));
    }

    TGraph *fileInput_teor = new TGraph(into_root(f_teor), into_root(amp_teor));
    fileInput_teor->SetLineColor(kRed);
    fileInput_teor->SetLineStyle(2);
    fileInput_teor->SetLineWidth(2);
    fileInput_teor->Draw("Lsame");

    //Plotto la freuenza relativa al tau
    double f_tau_sper = (1. / (2 * M_PI * tau_sper));
    double err_f_tau_sper = err_tau_sper / (2 * M_PI * pow(tau_sper, 2));
    double f_tau_th = (1.0 / (2.0 * M_PI * R * c_f));
    double err_f_tau_th = sqrt(pow(err_R / (2 * M_PI * pow(R, 2) * c_f), 2) +
                               pow(err_c_f / (2 * M_PI * pow(c_f, 2) * R), 2));

    cout << "f_tau_sper:\t" << f_tau_sper << " +- " << err_f_tau_sper << endl
         << "f_tau_th:\t" << f_tau_th << " +- " << err_f_tau_th << endl;

    TLine *max_sper = new TLine(f_tau_sper, -44, f_tau_sper, 28);
    max_sper->SetLineColor(kBlack);
    max_sper->SetLineStyle(2);
    max_sper->Draw("same");

    TLine *max_th = new TLine(f_tau_th, -44, f_tau_th, 28);
    max_th->SetLineColor(kRed);
    max_th->SetLineStyle(2);
    max_th->Draw("same");

    TLatex latex;
    latex.SetTextSize(0.25);
    latex.SetTextAlign(13); //align at top
    latex.DrawLatex(1000, 19, "#it{f_{t}}#approx 1.1 kHz");

    TLegend *legend = new TLegend(0.15, 0.65, 0.3, 0.95);
    legend->AddEntry(fileInput, "Dati Sperimentali con errore", "P");
    legend->AddEntry(fileInput_simul, "Dati Simulati", "P");
    legend->AddEntry(fileInput_teor, "Previsione Teorica", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();
}