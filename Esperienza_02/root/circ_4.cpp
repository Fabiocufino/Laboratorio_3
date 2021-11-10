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
    v_in = 0,
    fs_vin = 1,
    v_out = 2,
    fs_vout = 3
};

double err_res_cap(double resistenza, double perc, double digit, double lsd)
{
    double gain = perc / 100. * resistenza * 1. / sqrt(3);
    double read = digit * lsd * 1. / sqrt(3);
    return sqrt(pow(gain, 2) + pow(read, 2));
}
void circ_4()
{

    double r1 = 10.003e3; //ohm
    double rf = 67.674e3; //ohm
    double r3 = 9.981e3;  //ohm
    double r4 = 68.54e3;  //ohm
    double r50 = 46.51;   //ohm
    double r50b = 46.74;  //ohm

    double err_r1 = err_res_cap(r1, 0.07, 8, 1);       //ohm
    double err_rf = err_res_cap(rf, 0.07, 8, 1);       //ohm
    double err_r3 = err_res_cap(r3, 0.07, 8, 1);       //ohm
    double err_r4 = err_res_cap(r4, 0.07, 8, 1);       //ohm
    double err_r50 = err_res_cap(r50, 0.1, 8, 0.01);   //ohm
    double err_r50b = err_res_cap(r50b, 0.1, 8, 0.01); //ohm

    cout << "Resistenze:" << endl
         << "r1\t" << r1 << "+-" << err_r1 << endl
         << "rf\t" << rf << "+-" << err_rf << endl
         << "r3\t" << r3 << "+-" << err_r3 << endl
         << "r4\t" << r4 << "+-" << err_r4 << endl
         << "r50\t" << r50 << "+-" << err_r50 << endl
         << "r50b\t" << r50b << "+-" << err_r50b << endl
         << endl;

    double ampl_th = (1 + rf / r1) * (r4 / (r3 + r4));
    double err_ampl_th = sqrt((pow(err_r4, 2) * pow(r1, 2) * pow(r1 + rf, 2) * pow(r3, 2) +
                               pow(r4, 2) * (pow(err_r3 * r1 * (r1 + rf), 2) +
                                             (pow(err_rf * r1, 2) +
                                              pow(err_r1 * rf, 2) * (pow(r3 + r4, 2))))) /
                              (pow(r1, 4) * pow(r3 + r4, 4)));
    cout << "Amplificazione th: " << endl
         << ampl_th << "+-" << err_ampl_th << endl
         << endl;

    DataContainerGen quattro_n_i;
    quattro_n_i.read("../Dati/circuito_4_non_inv.txt", 4);

    vector<double> &v_in = quattro_n_i.tabella[(int)Colonna::v_in];
    vector<double> &fs_vin = quattro_n_i.tabella[(int)Colonna::fs_vin];
    vector<double> &v_out = quattro_n_i.tabella[(int)Colonna::v_out];
    vector<double> &fs_vout = quattro_n_i.tabella[(int)Colonna::fs_vout];
    vector<double> err_vout;
    quattro_n_i.err_oscilloscopio((int)Colonna::fs_vout, (int)Colonna::v_out, err_vout);
    vector<double> err_vin;
    quattro_n_i.err_oscilloscopio((int)Colonna::fs_vin, (int)Colonna::v_in, err_vin);

    // ------------------------------------------INIZIO GRAFCIO E CALCOLO PARAMETRI-- -------------
    auto canvas1 = new TCanvas("c1", "Circuito 4", 1000, 600);
    canvas1->SetGrid();
    canvas1->SetFillColor(0);

    TGraphErrors *fileInput = new TGraphErrors(into_root(v_in), into_root(v_out), into_root(err_vin), into_root(err_vout));

    fileInput->SetMarkerColor(4);
    fileInput->SetMarkerColor(kAzure - 2);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("V_{in} [mV]");
    fileInput->GetYaxis()->SetTitle("V_{out} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    TF1 *fit_sin = new TF1("f2", "pol1", -0.002, 10);
    fit_sin->SetLineColor(kRed);
    fit_sin->SetLineStyle(2);
    fit_sin->SetLineWidth(1);

    fit_results fit1;
    fit(fit_sin, 3, fileInput, v_in, v_out, fit1, -0.002, 2100);

    TPaveStats *info;
    TText *scri;
    informazioni_fit_lineare(info,
                             scri,
                             to_string(fit1.chi_square[0]),
                             to_string(fit1.dof[0]),
                             to_string(fit1.a[0]),
                             to_string(fit1.err_a[0]),
                             to_string(fit1.b[0]),
                             to_string(fit1.err_b[0]),
                             to_string(fit1.rho[0]),
                             to_string(fit1.t_student[0]),
                             to_string(fit1.sigma_post[0]),
                             "Fit lineare sui dati");

    TGraph *simul = new TGraph("../Dati/Circuito4_vtc.txt");

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
    legend->AddEntry(simul, "Dati Simulati", "P");
    legend->AddEntry(fit_sin, "a+bx interpolante dati sperimentali", "l");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();

    cout << endl;
    for (int i = 0; i < v_out.size(); i++)
    {
        cout << v_in[i] << "+-" << err_vin[i] << " " << v_out[i] << "+-" << err_vout[i] << endl;
    }

    //-------------------------------INIZIO GRAFICO SCARTI
    vector<double> err_vuoto(err_vin.size(), 0);
    vector<double> err_vd_scarti;
    for (int i = 0; i < err_vout.size(); i++)
    {
        err_vd_scarti.push_back(sqrt(pow(err_vout[i], 2) + pow(fit1.b[0] * err_vin[i], 2)));
    }

    vector<double> scarti;
    run_test_lineare(scarti, v_in, v_out, fit1.a[0], fit1.b[0]);

    auto c2 = new TCanvas("c2", "Scarti circuito 1", 1100, 600);
    c2->SetGrid();
    c2->SetFillColor(0);
    TGraphErrors *graph_scarti = new TGraphErrors(into_root(v_in), into_root(scarti), into_root(err_vuoto), into_root(err_vd_scarti));

    graph_scarti->SetMarkerColor(4);
    graph_scarti->SetLineColor(kAzure - 3);
    graph_scarti->SetMarkerStyle(20);
    graph_scarti->SetMarkerSize(0.7);
    graph_scarti->SetTitle("");
    graph_scarti->GetXaxis()->SetTitle("Voltaggio V_{D} [mV]");
    graph_scarti->GetYaxis()->SetTitle("Scarti");
    graph_scarti->GetXaxis()->SetAxisColor(14);
    graph_scarti->GetYaxis()->SetAxisColor(14);

    graph_scarti->Draw("AP");

    TLine *line = new TLine(23, 0, 2115, 0);
    line->SetLineStyle(2);
    line->SetLineColor(kRed);
    line->SetLineColor(kRed);
    line->Draw("same");

    TLegend *legends = new TLegend(0.15, 0.15, 0.5, 0.3);
    legends->AddEntry(graph_scarti, "Dati sperimentali con errore", "P");
    legends->AddEntry(fit_sin, "retta Y=0", "L");
    legends->SetTextSize(0.04);
    legends->SetBorderSize(1);
    legends->Draw();
}