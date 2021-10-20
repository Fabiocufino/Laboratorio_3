#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "reader.h"
#include "root.h"
#include <cmath>
#include "fstream"

using namespace std;

double err_tensione(double x)
{
    if (x <= 600)
    {
        double perc = 0.5;
        double digit = 2;
        double lsd = 0.1;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
    else if (x >= 600 )
    {
        double perc = 0.5;
        double digit = 2;
        double lsd = 1;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
};

double err_corrente(double x)
{
    if (x <= 1000)
    {
        double perc = 0.1;
        double digit = 15;
        double lsd = 0.01;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
    else if (x >= 1000 && x <= 10000)
    {
        double perc = 0.08;
        double digit = 8;
        double lsd = 0.0001;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
}

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
    vdid->NewCol(log, 1); //genera colonna con log(is)

    vdid->NewColPar(err_tensione, 0, 0.05, 3 * 0.001);
    vector<double> &vd = vdid->colonne[0];
    vector<double> &id = vdid->colonne[4];

    //Fare fit lineare su graifco

    //Stampare i valori di interpolazione con le grandezze fisiche associate n e Is con errori

    auto c1 = new TCanvas("c1", "Circuito 1", 1100, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput0 = new TGraph(into_root(vd), into_root(id));

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
    fit(retta, 2, fileInput0, vd, id, fit1);
}