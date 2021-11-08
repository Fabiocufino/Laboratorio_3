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
     freq = 0,
     v_in = 1,
     fs_vin = 2,
     v_out = 3,
     fs_vout = 4
};

void circ_2()
{
     double r1 = 9.993e3;                         //ohm
     double rf = 67.759e3;                        //ohm
     double err_r1 = err_res_cap(r1, 0.07, 8, 1); //ohm
     double err_rf = err_res_cap(rf, 0.07, 8, 1); //ohm

     cout << "Resistenza[ohm]: " << endl
          << r1 << "+-" << err_r1 << endl
          << endl;

     double c2 = 1.01; //nanofarad
     double err_c2 = err_res_cap(c2, 1, 8, 0.01);
     cout << "Capacita[nF]: " << endl
          << c2 << "+-" << err_c2 << endl
          << endl;

     double f_th = 1.0 / (2.0 * M_PI * r1 * c2 * 1e-9);
     double err_f_th = sqrt(pow(err_r1 / (2.0 * M_PI * c2 * 1e-9 * pow(r1, 2)), 2) +
                            pow((err_c2 * 1e-9) / (2.0 * M_PI * r1 * pow(c2 * 1e-9, 2)), 2));

     cout << "F taglio th[Hz]: " << endl
          << f_th << "+-" << err_f_th << endl
          << endl;

     double ampl_th = rf / r1 * (1.0 / sqrt(2.0));
     double err_ampl_th = sqrt(pow(err_rf / (r1 * sqrt(2.0)), 2) + pow(((r1 * err_rf) / (pow(rf, 2) * sqrt(2))), 2));
     cout << "Amplificazione attesa Rf/R1/sqrt(2): " << endl
          << ampl_th << "+-" << err_ampl_th << endl
          << endl;

     double vin_sper = 1.03;
     double fs_vin_sper = 0.2;
     double err_vin_sper = sqrt(pow(0.3 * 1. / 25. * fs_vin_sper, 2) +
                                pow(3. / 100. * vin_sper / sqrt(12), 2));
     double vout_sper = 4.88;
     double fs_vout_sper = 1;
     double err_vout_sper = sqrt(pow(0.3 * 1. / 25. * fs_vout_sper, 2) +
                                 pow(3. / 100. * vout_sper / sqrt(12), 2));

     double ampl_sper = vout_sper / vin_sper;
     double err_ampl_sper = sqrt(pow(err_vout_sper / vin_sper, 2) +
                                 pow(vout_sper * err_vin_sper / pow(vin_sper, 2), 2));

     cout << "Misure puntuali: [V]" << endl
          << "v IN" << endl
          << vin_sper << "+-" << err_vin_sper << endl
          << endl
          << "v OUT" << endl
          << vout_sper << "+-" << err_vout_sper << endl
          << endl;

     cout << "Amplificaz puntuale: [V/V]" << endl
          << ampl_sper << "+-" << err_ampl_sper << endl
          << endl;

     cout << "Comp amplificazioni th e sper" << endl
          << comp(ampl_th, ampl_sper, err_ampl_th, err_ampl_sper) << endl
          << endl;

     //Letura e grafici dati
     DataContainerGen due;
     due.read("../Dati/circuito_2.txt", 5);
     vector<double> &freq = due.tabella[(int)Colonna::freq];
     vector<double> &v_in = due.tabella[(int)Colonna::v_in];
     vector<double> &fs_vin = due.tabella[(int)Colonna::fs_vin];
     vector<double> &v_out = due.tabella[(int)Colonna::v_out];
     vector<double> &fs_vout = due.tabella[(int)Colonna::fs_vout];

     vector<double> err_vin;
     vector<double> err_vout;
     due.err_oscilloscopio((int)Colonna::fs_vout, (int)Colonna::v_out, err_vout);
     due.err_oscilloscopio((int)Colonna::fs_vin, (int)Colonna::v_in, err_vin);

     cout << "Tabella dati grezzi" << endl
          << endl;
     for (int i = 0; i < v_in.size(); i++)
     {
          cout << freq[i] << "\t" << v_in[i] << "+-" << err_vin[i] << "\t" << v_out[i] << "+-" << err_vout[i] << "\t" << fs_vin[i] << "\t" << fs_vout[i] << endl;
     }
     cout << endl
          << endl;

     vector<double> ampl;
     vector<double> err_ampl;
     //vector<double> ampl_th;
     for (int i = 0; i < freq.size(); i++)
     {
          ampl.push_back(20 * log10(v_out[i] / v_in[i]));
          double err_amplitude = sqrt(pow(20 * (1 / (v_out[i] * log(10))) * err_vout[i], 2) + pow(20 * (1 / (v_in[i] * log(10))) * err_vin[i], 2));
          err_ampl.push_back(err_amplitude); //DA FARE
                                             //ampl_th.push_back(20 * log10((rf * 2 * M_PI * freq[i] * c2) / (sqrt(pow(r1 * 2 * M_PI * freq[i] * c2, 2) + 1))));
     }

     //------------------------------------------INIZIO GRAFCIO E CALCOLO PARAMETRI---------------
     auto canvas1 = new TCanvas("c1", "Circuito 1", 1000, 600);
     canvas1->SetGrid();
     canvas1->SetFillColor(0);
     canvas1->SetLogx();

     TGraphErrors *fileInput = new TGraphErrors(into_root(freq), into_root(ampl), into_root(err_ampl), into_root(err_ampl));

     fileInput->SetMarkerColor(4);
     fileInput->SetMarkerColor(kAzure - 2);
     fileInput->SetMarkerStyle(20);
     fileInput->SetMarkerSize(0.7);
     fileInput->SetTitle("");
     fileInput->GetXaxis()->SetTitle("freq [Hz]");
     fileInput->GetYaxis()->SetTitle("A_{dB} [V/V]");
     fileInput->GetXaxis()->SetAxisColor(14);
     fileInput->GetYaxis()->SetAxisColor(14);

     fileInput->Draw("AP");

     TGraph *simul = new TGraph("../Dati/circuito_2_simulato");

     simul->SetMarkerColor(4);
     simul->SetMarkerColor(kAzure - 4);
     simul->SetMarkerStyle(20);
     simul->SetMarkerSize(0.5);
     simul->SetTitle("");
     simul->GetXaxis()->SetTitle("freq [Hz]");
     simul->GetYaxis()->SetTitle("A_{dB} [V/V]");
     simul->GetXaxis()->SetAxisColor(14);
     simul->GetYaxis()->SetAxisColor(14);

     simul->Draw("Psame");

     TGraph *teor = new TGraph("../Dati/circuito_2_teorico.txt");

     teor->SetMarkerColor(4);
     teor->SetLineColor(kRed);

     teor->SetTitle("");
     teor->SetLineColor(kRed);
     teor->SetLineStyle(2);
     teor->SetLineWidth(2);
     teor->GetXaxis()->SetTitle("freq [Hz]");
     teor->GetYaxis()->SetTitle("A_{dB} [V/V]");
     teor->GetXaxis()->SetAxisColor(14);
     teor->GetYaxis()->SetAxisColor(14);

     teor->Draw("Lsame");

     TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
     legend->AddEntry(fileInput, "Dati Sperimentali con errore", "P");
     legend->AddEntry(simul, "Dati Simulati con errore", "P");
     legend->AddEntry(teor, "Previsione Teorica ", "L");
     legend->SetTextSize(0.04);
     legend->SetBorderSize(1);
     legend->Draw();
}