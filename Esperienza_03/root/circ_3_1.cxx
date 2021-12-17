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

#include "DATACLASSGEN.h"
#include "root.h"
#include "fit_results.h"

using namespace std;

void circ_3_1()
{
    // costanti da excel e logbook
    double R_in = 55.306 * 1e3;                      // Omh
    double R_f = 681.08e3;                           //ohm
    double err_R_in = err_res_cap(R_in, 0.07, 8, 1); //0.0228 * 1e3;               // Ohm
    double err_R_f = err_res_cap(R_f, 0.07, 8, 1);   //ohm
    double v_in = 1.020;                             // V
    double err_v_in = err_osc_v(v_in, 0.500);        // V
    double t_0 = 5e-6;                               //s
    double err_t_0 = err_osc_t(1e-6);                //s (cfr excel)
    double q_in = v_in / R_in * t_0;                 //V/Ohm*us Coulomb
    double err_q_in = sqrt(pow((err_v_in / R_in) * t_0, 2) +
                           pow((v_in / R_in) * err_t_0, 2) +
                           pow((v_in / pow(R_in, 2)) * t_0 * err_R_in, 2));
    double c_0 = 19e-12;                                          //farad
    double c_f = (237 - 19) * 1e-12;                              //farad
    double err_c_f = err_res_cap(c_f * 1e12, 2.5, 15, 1) * 1e-12; //farad
    double v_pre_out_max = v_in / (R_in * c_f) * t_0;             //volt
    double err_v_pre_out_max = sqrt(pow((err_v_in / (R_in * c_f)) * t_0, 2) +
                                    pow((err_t_0 * v_in) / (R_in * c_f), 2) +
                                    pow(((v_in * err_R_in) / (pow(R_in, 2) * c_f)) * t_0, 2) +
                                    pow(((v_in * err_c_f) / (pow(c_f, 2) * R_in)) * t_0, 2));
    double tau_th = R_f * c_f;
    double err_tau_th = sqrt(pow(err_R_f * c_f, 2) + pow(R_f * err_c_f, 2));

    double v_out_pre_sper = 0.428; //v
    double err_v_out_pre_sper = err_osc_v(v_out_pre_sper, 0.1);

    /////////////////////
    //Valori di output
    cout
        << "V_0_in[mV]:\t" << v_in * 1e3 << " +- " << err_v_in << endl
        << "q_in_th[Coulomb]:\t" << q_in << " +- " << err_q_in << endl
        << "v_pre_max_out[volt]:\t" << v_pre_out_max << " +- " << err_v_pre_out_max << endl
        << "tau_th[s]\t" << tau_th << " +- " << err_tau_th << endl
        << "v_out_pre_sper\t" << v_out_pre_sper << " +- " << err_v_out_pre_sper << endl;

    ///////////////////

    DataContainerGen circ_3_1;
    circ_3_1.read("../Dati/3_1_new.txt", 3);
    vector<double> &t = circ_3_1.tabella[0];
    vector<double> &v_out = circ_3_1.tabella[1];
    vector<double> &fs_v_out = circ_3_1.tabella[2];

    double err_t = (1. / 10.) * 5 * (1. / sqrt(6.)) * 1e-6;
    vector<double> err_v_out;
    circ_3_1.err_oscilloscopio(2, 1, err_v_out);
    circ_3_1.add_col(err_v_out); //per stampa per latex
    vector<int> cols_to_print = {0, 1, 3, 2};
    circ_3_1.dump(cols_to_print);

    TCanvas *c1 = new TCanvas("c1", "Circuito 3_1", 468, 206, 1332, 851);
    c1->Range(0, 0, 1, 1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);

    TPad *pad1 = new TPad("pad1", "This is pad1", 0.005, 0.02, 0.99, 0.97);
    TPad *pad2 = new TPad("pad2", "This is pad2", 0.005, 0.02, 0.99, 0.37);
    pad1->Draw();
    pad2->Draw();

    pad1->cd();
    pad1->Range(-1.933052e-11, -751.0643, 2.211768e-10, 926.1686);
    pad1->SetFillColor(0);
    pad1->SetBorderMode(0);
    pad1->SetBorderSize(2);
    pad1->SetLeftMargin(0.08037394);
    pad1->SetRightMargin(0.05596981);
    pad1->SetTopMargin(0.003203662);
    pad1->SetBottomMargin(0.4549199);
    pad1->SetFrameBorderMode(0);
    pad1->SetFrameBorderMode(0);
    vector<double> Q_in;
    vector<double> err_Q_in;

    for (int i = 0; i < t.size(); i++)
    {
        Q_in.push_back((v_in / R_in) * t[i]);
        err_Q_in.push_back(sqrt(pow(v_in * t[i] * err_R_in / pow(R_in, 2), 2) +
                                pow(err_v_in * t[i] / R_in, 2) +
                                pow(v_in * err_t / R_in, 2)));
    }

    TGraphErrors *fileInput = new TGraphErrors(into_root(Q_in), into_root(v_out), into_root(err_Q_in), into_root(err_v_out));

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kAzure - 4);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("Q_{in} [uC]");
    fileInput->GetYaxis()->SetTitle("V_{pre}^{MAX} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    fit_results Lin;
    TF1 *retta = new TF1("retta", "pol1", 0, 10);
    retta->SetLineColor(kRed);
    retta->SetLineStyle(2);
    retta->SetLineWidth(2);
    fit(retta, 2, fileInput, Q_in, v_out, Lin);

    cout << endl
         << "c_f_from_fit:\t" << 1.0 / Lin.b[0] << "\t" << Lin.err_b[0] / pow(Lin.b[0], 2) << endl;

    TPaveStats *info;
    TText *scri;
    informazioni_fit_lineare(info,
                             scri,
                             to_string(round(Lin.chi_square[0] * 100.0) / 100.0),
                             to_string((int)Lin.dof[0]),
                             to_string(Lin.a[0]),
                             to_string(Lin.err_a[0]),
                             "4.507e+12",
                             "1.326e+11",
                             to_string(Lin.rho[0]),
                             to_string(Lin.t_student[0]),
                             to_string(Lin.sigma_post[0]),
                             "Fit lineare sui dati");

    TLegend *legend = new TLegend(0.15, 0.65, 0.3, 0.95);
    legend->AddEntry(fileInput, "Dati con errore", "P");
    legend->AddEntry(retta, "Retta Interpolante", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();

    pad2->cd(); //----------------------------------------------------------SCARTI---------------------------------
    pad2->Range(-0.8931843, -0.5835317, 10.65828, 1.252791);
    pad2->SetFillColor(0);
    pad2->SetBorderMode(0);
    pad2->SetBorderSize(2);
    pad2->SetLeftMargin(0.07732215);
    pad2->SetRightMargin(0.05698707);
    pad2->SetBottomMargin(0.1664596);
    pad2->SetFrameBorderMode(0);
    pad2->SetFrameBorderMode(0);

    vector<double> scarti;
    run_test_lineare(scarti, Q_in, v_out, Lin.a[0], Lin.b[0]);
    vector<double> err_scarti;
    for (int i = 0; i < scarti.size(); i++)
    {
        err_scarti.push_back(sqrt(pow(err_v_out[i], 2) + pow(Lin.b[0] * err_Q_in[i], 2)));
    }
    vector<double> err_zero(err_scarti.size(), 0);

    TGraphErrors *graph_scarti = new TGraphErrors(into_root(Q_in), into_root(scarti), into_root(err_zero), into_root(err_scarti));

    graph_scarti->SetMarkerColor(4);
    graph_scarti->SetLineColor(kAzure - 3);
    graph_scarti->SetMarkerStyle(20);
    graph_scarti->SetMarkerSize(0.7);
    graph_scarti->SetTitle("");

    graph_scarti->GetYaxis()->SetAxisColor(14);
    graph_scarti->GetXaxis()->SetLabelFont(42);
    graph_scarti->GetXaxis()->SetLabelSize(0.09);
    graph_scarti->GetXaxis()->SetTitleOffset(1);
    graph_scarti->GetXaxis()->SetTitleFont(42);
    graph_scarti->GetYaxis()->SetTitle("Scarti");
    graph_scarti->GetYaxis()->SetAxisColor(14);
    graph_scarti->GetYaxis()->SetLabelFont(42);
    graph_scarti->GetYaxis()->SetLabelSize(0.09);
    graph_scarti->GetYaxis()->SetTitleSize(0.11);
    graph_scarti->GetYaxis()->SetTitleOffset(0.33);
    graph_scarti->GetYaxis()->SetTitleFont(42);

    graph_scarti->Draw("AP");

    TF1 *z = new TF1("z", "pol1", 0, 10);
    z->SetLineColor(kRed);
    z->SetLineStyle(2);
    z->SetLineWidth(2);
    z->Draw("lsame");

    TLegend *legend2 = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend2->AddEntry(graph_scarti, "Dati con errore", "P");
    legend2->SetTextSize(0.04);
    legend2->SetBorderSize(1);
    legend2->SetTextSize(0.08447205);
    legend2->Draw();
}