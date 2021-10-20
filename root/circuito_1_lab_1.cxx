#include <cmath>
#include <fstream>
#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TMatrixD.h"

#include "datacontainer.h"
#include "root.h"

using namespace std;

void circuito_1_lab_1()
{
    //Leggere i dati del file e archiviarli in vettori c++
    DataContainer *vdid = new DataContainer();
    vdid->read("../Dati/dati_circuito_1.txt");
    for (int i = 0; i < vdid->colonne[0].size(); i++)
    {
        cout << vdid->colonne[0][i] << endl;
    }

    //Calcolare gli errori associati a vd e id in c++

    //Convertire tutti  i dati precedenti in rootvettore e darli in pasto a TGraph
    vector<double> &vd = vdid->colonne[0];

    auto n_log_id = vdid->NewCol(log, 1); //genera colonna con log(is)
    vector<double> &log_id = vdid->colonne[n_log_id];

    auto n_err_vd = vdid->NewCol(err_tensione, 1);
    vector<double> &err_vd = vdid->colonne[n_err_vd];
    auto n_err_id = vdid->NewCol(err_corrente, 1);
    vector<double> &err_id = vdid->colonne[n_err_id];

    //Fare fit lineare su graifco

    //Stampare i valori di interpolazione con le grandezze fisiche associate n e Is con errori

    auto c1 = new TCanvas("c1", "Circuito 1", 1100, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput0 = new TGraph(into_root(vd), into_root(log_id));

    fileInput0->SetMarkerColor(4);
    fileInput0->SetLineColor(4);
    fileInput0->SetMarkerStyle(20);
    fileInput0->SetMarkerSize(0.7);
    fileInput0->SetTitle("");
    fileInput0->GetXaxis()->SetTitle("Voltaggio V_{D} [mV]");
    fileInput0->GetYaxis()->SetTitle("ln(I_{D})");
    fileInput0->GetXaxis()->SetAxisColor(14);
    fileInput0->GetYaxis()->SetAxisColor(14);

    fileInput0->Draw("AP");

    fit_results fit1;
    TF1 *retta = new TF1("retta", "pol1", 0, 10);
    retta->SetLineColor(kRed);
    retta->SetLineStyle(2);
    retta->SetLineWidth(2);
    fit(retta, 2, fileInput0, vd, log_id, fit1);
}