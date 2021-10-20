#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "fstream"

#include "TFitResult.h"
#include "TMatrixD.h"
using namespace std;


void circuito_1_lab_1()
{
    auto c1 = new TCanvas("c1", "Circuito 1", 1100, 600); 
    c1->SetGrid();
    c1->SetFillColor(0);
    TGraph *fileInput0 = new TGraph("../Dati/dati_circuito_1.txt", "%lg %lg");

    fileInput0->SetMarkerColor(4);
    fileInput0->SetLineColor(4);
    fileInput0->SetMarkerStyle(20);
    fileInput0->SetMarkerSize(0.5);
    fileInput0->SetTitle("Circuito 1");
    fileInput0->GetXaxis()->SetTitle("Asse x [ ]");
    fileInput0->GetYaxis()->SetTitle("Asse y [ ]");
    fileInput0->GetXaxis()->SetAxisColor(14);
    fileInput0->GetYaxis()->SetAxisColor(14);

    fileInput0->Draw("AP");

    TF1 *retta = new TF1("f2", "pol1", 0.3,0.92); //ho definito una funzione

    TFitResultPtr r = fileInput0->Fit(retta, "SR");
    
   
}