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

void circ_3_2()
{
    DataContainerGen circ_3_2;
    circ_3_2.read("../Dati/3_2.txt", 5);
    vector<double> &f = circ_3_2.tabella[0];
    vector<double> &v_in = circ_3_2.tabella[1];
    vector<double> &fs_v_in = circ_3_2.tabella[2];
    vector<double> &v_out = circ_3_2.tabella[3];
    vector<double> &fs_v_out = circ_3_2.tabella[4];

    vector<double> err_vin;
    circ_3_2.err_oscilloscopio(2, 1, err_vin);
    circ_3_2.add_col(err_vin);

    vector<double> err_v_out;
    circ_3_2.err_oscilloscopio(4, 3, err_v_out);
    circ_3_2.add_col(err_v_out);
    vector<int> cols_to_print = {
        0,
        1,
    };
    circ_3_2.dump(cols_to_print);

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



    // Simulazione
    DataContainerGen circ_3_2_simul;
    circ_3_2_simul.read("../Dati/3_2_b_simul.txt", 3);
    vector<double> &f_sim = circ_3_2_simul.tabella[0];
    vector<double> &v_in_s = circ_3_2_simul.tabella[1];
    vector<double> &v_out_s = circ_3_2_simul.tabella[2];

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

}