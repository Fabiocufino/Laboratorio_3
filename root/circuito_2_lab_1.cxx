```cpp
#include "TH1.h"
#include "TMath.h"
#include <cmath>
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "fstream"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "vector"
#include "iostream"
#include "usual.h"
using namespace std;

void sferica()
{
    TCanvas *c1 = new TCanvas("c1", "Canvas", 200, 10, 1500, 900);

    c1->SetGrid();
    c1->SetFillColor(0);

    ifstream fab("../Dati/circ_2_1.txt");
    double val;
    vector<double> v_in;
    while (fab >> val)
        v_in.push_back(val);

    TVectorD root_v_in(v_in.size(),v_in.data());

    TGraph *fabio = new TGraph(asse_x_f, root_sferica_f);

    fabio->SetMarkerColor(2);
    fabio->SetMarkerStyle(20);
    fabio->SetMarkerSize(0.8);
    fabio->SetTitle("Operatore A");
    fabio->GetXaxis()->SetTitle("Numero della misurazione");
    fabio->GetYaxis()->SetTitle(" [1/m]");
    fabio->GetXaxis()->SetAxisColor(14);
    fabio->GetYaxis()->SetAxisColor(14);

    fabio->Draw("AP");

    //------------------Mark-------------
    ifstream mar("../Dati/circ_2_2.txt");
    double val1;
    vector<double> sferica_m;
    while (mar >> val1)
        sferica_m.push_back(val1);

    TVectorD root_sferica_m(sferica_m.size(), sferica_m.data());
    TVectorD asse_x_m(sferica_f.size());
    for (int i = 0; i < sferica_m.size(); i++)
        asse_x_m(i) = i + 1;

    TGraph *marco = new TGraph(asse_x_m, root_sferica_m);

    marco->SetMarkerColor(3);
    marco->SetMarkerStyle(20);
    marco->SetMarkerSize(0.8);
    marco->SetTitle("Operatore B");
    marco->GetXaxis()->SetTitle("Numero della misurazione");
    marco->GetYaxis()->SetTitle(" [1/m]");
    marco->GetXaxis()->SetAxisColor(14);
    marco->GetYaxis()->SetAxisColor(14);

    marco->Draw("Psame");


    TLegend *legend = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend->SetHeader("Aberrazione sferica", "C");
    legend->AddEntry(fabio, "Operatore A", "P");
    legend->AddEntry(marco, "Operatore B", "P");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();
}
```