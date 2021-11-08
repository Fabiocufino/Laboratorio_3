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

#include "datacontainer.h"
#include "root.h"

#include "DATACLASSGEN.h"
using namespace std;

void circuito_1_lab_1()
{
    DataContainer uno;
    uno.read("../Dati/dati_circuito_1.txt");

    vector<double> log_id;
    vector<double> err_vd;
    vector<double> err_id;
    vector<double> err_logid;

    for (int i = 0; i < uno.vd.size(); i++)
    {
        log_id.push_back(log(uno.id[i]));
        err_id.push_back(err_corrente(uno.id[i]));
        err_logid.push_back(err_log(uno.id[i], err_id[i]));
        err_vd.push_back(err_tensione(uno.vd[i]));
    }

    vector<double> new_error;

    //=================================================================inizio grafico
    auto c1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);
    TGraphErrors *fileInput = new TGraphErrors(into_root(uno.vd), into_root(log_id), into_root(err_vd), into_root(err_logid));

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kAzure - 3);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("Voltaggio V_{D} [mV]");
    fileInput->GetYaxis()->SetTitle("ln(I_{D}) [uA]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    fit_results fit1;
    TF1 *retta = new TF1("retta", "pol1", 0, 10);
    retta->SetLineColor(kRed);
    retta->SetLineStyle(2);
    retta->SetLineWidth(2);
    fit(retta, 2, fileInput, uno.vd, log_id, fit1);

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

    double n;
    double is;

    is = exp(fit1.a[0]);
    double err_is = exp(fit1.a[0]) * fit1.err_a[0];
    n = 1. / (fit1.b[0] * 26.0);
    double err_n = fit1.err_b[0] / (pow(fit1.b[0], 2) * 26.0);
    cout << "is :" << is << " +- " << err_is << " uA" << endl
         << "n: " << n << " +- " << err_n << endl;

    TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend->AddEntry(fileInput, "Dati con errore", "P");
    legend->AddEntry(retta, "Retta Interpolante", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();

    //=================================================================inizio run test

    for (int i = 0; i < err_logid.size(); i++)
    {
        new_error.push_back(sqrt(pow(err_logid[i], 2) + pow(fit1.b[0] * err_vd[i], 2)));
    }

    vector<double> scarti;
    run_test_lineare(scarti, uno.vd, log_id, fit1.a[0], fit1.b[0]);

    auto c2 = new TCanvas("c2", "Scarti circuito 1", 1100, 600);
    c2->SetGrid();
    c2->SetFillColor(0);
    TGraphErrors *graph_scarti = new TGraphErrors(into_root(uno.vd), into_root(scarti), into_root(err_vd), into_root(new_error));

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
}