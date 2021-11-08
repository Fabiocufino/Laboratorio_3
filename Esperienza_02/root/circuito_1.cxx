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
     vin = 0,
     fs_vin = 1,
     vout = 2,
     fs_vout = 3
};

void circuito_1()
{
     // Analisi capacità
     double c1 = 99.5;                           //nanofarad
     double c2 = 111.0;                          //nanofarad
     double err_c1 = err_res_cap(c1, 1, 8, 0.1); //nanofarad
     double err_c2 = err_res_cap(c2, 1, 10, 1);  //nanofarad
     cout << "Capacità [nanofarad]:" << endl
          << c1 << " +- " << err_c1 << endl
          << c2 << " +- " << err_c2 << endl
          << endl;

     // Analisi delle resistenze
     double r1 = 9.993e3;                             //ohm
     double rf = 67.759e3;                            //ohm
     double r50 = 46.51;                              //ohm
     double err_r1 = err_res_cap(r1, 0.07, 8, 1);     //ohm
     double err_rf = err_res_cap(rf, 0.07, 8, 1);     //ohm
     double err_r50 = err_res_cap(r50, 0.1, 8, 0.01); //ohm
     double ampl_th = -rf / r1;
     double err_ampl_th = sqrt(pow(err_rf / r1, 2) + pow((err_r1 * rf / pow(r1, 2)), 2));
     cout << "Resistenze [ohm]:" << endl
          << r1 << " +- " << err_r1 << endl
          << rf << " +- " << err_rf << endl
          << r50 << " +- " << err_r50 << endl
          << endl;

     cout << "Amplificazione prevista:" << endl
          << ampl_th << "+-" << err_ampl_th << endl
          << endl;

     //Letura e grafici dati
     DataContainerGen uno;
     uno.read("../Dati/circuito_1.txt", 4);
     vector<double> &vin = uno.tabella[(int)Colonna::vin];
     vector<double> &vout = uno.tabella[(int)Colonna::vout];

     vector<double> &fs_vin = uno.tabella[(int)Colonna::fs_vin];
     vector<double> &fs_vout = uno.tabella[(int)Colonna::fs_vout];

     vector<double> err_vin;
     vector<double> err_vout;
     uno.err_oscilloscopio((int)Colonna::fs_vout, (int)Colonna::vout, err_vout);
     uno.err_oscilloscopio((int)Colonna::fs_vin, (int)Colonna::vin, err_vin);

     //------------------------------------------INIZIO GRAFCIO E CALCOLO PARAMETRI---------------
     auto canvas1 = new TCanvas("c1", "Circuito 1", 1000, 600);
     canvas1->SetGrid();
     canvas1->SetFillColor(0);

     TGraphErrors *fileInput = new TGraphErrors(into_root(vin), into_root(vout), into_root(err_vin), into_root(err_vout));

     fileInput->SetMarkerColor(4);
     fileInput->SetLineColor(kAzure - 4);
     fileInput->SetMarkerStyle(20);
     fileInput->SetMarkerSize(0.7);
     fileInput->SetTitle("");
     fileInput->GetXaxis()->SetTitle("Vpp_{IN} [mV]");
     fileInput->GetYaxis()->SetTitle("Vpp_{OUT} [V]");
     fileInput->GetXaxis()->SetAxisColor(14);
     fileInput->GetYaxis()->SetAxisColor(14);

     fileInput->Draw("AP");

     fit_results fit1;
     TF1 *retta = new TF1("retta", "pol1", 0, 10);
     retta->SetLineColor(kRed);
     retta->SetLineStyle(2);
     retta->SetLineWidth(2);
     fit(retta, 2, fileInput, vin, vout, fit1, 0, 3800);

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

     TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
     legend->AddEntry(fileInput, "Dati con errore", "P");
     legend->AddEntry(retta, "Retta Interpolante", "L");
     legend->SetTextSize(0.04);
     legend->SetBorderSize(1);
     legend->Draw();

     //Inizio residui
     vector<double> scarti;
     run_test_lineare(scarti, vin, vout, fit1.a[0], fit1.b[0]);

     auto canvas2 = new TCanvas("c2", "Scarti circuito 1", 1100, 600);
     canvas2->SetGrid();
     canvas2->SetFillColor(0);
     TGraphErrors *graph_scarti = new TGraphErrors(into_root(vin), into_root(scarti), into_root(err_vin), into_root(err_vout));

     graph_scarti->SetMarkerColor(4);
     graph_scarti->SetLineColor(kAzure - 3);
     graph_scarti->SetMarkerStyle(20);
     graph_scarti->SetMarkerSize(0.7);
     graph_scarti->SetTitle("");
     graph_scarti->GetXaxis()->SetTitle("Vpp_{IN} [mV]");
     graph_scarti->GetYaxis()->SetTitle("Scarti");
     graph_scarti->GetXaxis()->SetAxisColor(14);
     graph_scarti->GetYaxis()->SetAxisColor(14);

     graph_scarti->Draw("AP");

     TLegend *legend2 = new TLegend(0.15, 0.15, 0.5, 0.3);
     legend2->AddEntry(fileInput, "Dati con errore", "P");
     legend2->SetTextSize(0.04);
     legend2->SetBorderSize(1);
     legend2->Draw();

     //------------------------------------------FINE GRAFCIO E CALCOLO PARAMETRI---------------

     double ampl_sper = -1. * fit1.b[0] * 1e3;
     double err_ampl_sper = fit1.err_b[0] * 1e3;
     cout << "Amplificazione calcolata:" << endl
          << ampl_sper << "+-" << err_ampl_sper << endl
          << endl;

     cout << "Compatibilità ampli th e calcolata: " << comp(ampl_th, ampl_sper, err_ampl_sper, err_ampl_th) << endl
          << endl;

     for (int i = 0; i < err_vin.size(); i++)
     {
          cout << vin[i] << "\t" << err_vin[i] << "\t" << fs_vin[i] << "\t" << vout[i] << "\t" << err_vout[i] << "\t" << fs_vin[i] << endl;
     }
}
