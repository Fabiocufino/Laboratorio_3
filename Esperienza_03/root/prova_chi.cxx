#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TF2.h"
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
#include "TStyle.h"

#include "DATACLASSGEN.h"
#include "root.h"
#include "fit_results.h"

using namespace std;

double min_chi_variando_a(double *x, double *par) // le x sono i tau1 e le y sono i tau2, restituisce una z. La ampiezza del segnale è fissata

{
    DataContainerGen circ_2_1;
    circ_2_1.read("../Dati/2_1.txt", 4);
    vector<double> &t = circ_2_1.tabella[0];
    vector<double> &fs_t = circ_2_1.tabella[1];
    vector<double> &v_out = circ_2_1.tabella[2];
    vector<double> &fs_v_out = circ_2_1.tabella[3];

    for (int i = 0; i < t.size(); i++)
    {
        /* code */
        cout << v_out[i] << endl;
    }

    vector<double> err_v;
    circ_2_1.err_oscilloscopio(3, 2, err_v);
    vector<double> err_t;
    circ_2_1.err_oscilloscopio(1, 0, err_t, true);

    double a = par[0];
    double tau_1 = x[0];
    double tau_2 = x[1];

    double chi = 0;
    for (int i = 0; i < t.size(); i++)
    {
        double v_out_teor = (a * (exp(-t[i] / tau_1) - exp(-t[i] / tau_2)) * tau_1) / (tau_1 - tau_2);
        double chi_i = pow(((v_out_teor - v_out[i]) / (err_v[i])), 2);
        chi = chi + chi_i;
    }
    return chi;
}

void prova_chi()
{

    Double_t a = 1.02;
    auto c3 = new TCanvas("c3", "c3", 200, 10, 1000, 600);
    c3->SetGrid();
    c3->SetLogz();

    // TF2 *chi2 = new TF2("Minimizzazione del chi fissando A", min_chi_variando_a, 4000, 15144, 310933, 335000, 1);
    TF2 *chi2 = new TF2("Minimizzazione del chi fissando A", min_chi_variando_a, 10, 28, 10, 28, 1);

    chi2->SetParNames("a");
    chi2->SetParameter(0, a);
    chi2->GetXaxis()->SetTitle("#tau_2 [Hz]");
    chi2->GetYaxis()->SetTitle("#tau_1 [Hz]");
    chi2->SetNpx(200);
    chi2->SetNpy(200);
    gStyle->SetPalette(kRainBow);
    chi2->Draw("COLZ2");
}