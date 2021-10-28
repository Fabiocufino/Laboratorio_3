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
using namespace std;

void circuito_2_lab_1()
{
    DataContainer_due due;
    due.read("../Dati/circuito2_dc.txt");

    auto c1 = new TCanvas("c1", "Circuito 1", 1000, 600);
    c1->SetGrid();
    c1->SetFillColor(0);

    TGraph *fileInput = new TGraph(into_root(due.v_in), into_root(due.v_d));

    fileInput->SetMarkerColor(4);
    fileInput->SetLineColor(kAzure - 4);
    fileInput->SetMarkerStyle(20);
    fileInput->SetMarkerSize(0.7);
    fileInput->SetTitle("");
    fileInput->GetXaxis()->SetTitle("V_{in} [V]");
    fileInput->GetYaxis()->SetTitle("V_{d} [mV]");
    fileInput->GetXaxis()->SetAxisColor(14);
    fileInput->GetYaxis()->SetAxisColor(14);

    fileInput->Draw("AP");

    fit_results retta_1;
    TF1 *retta1 = new TF1("retta1", "pol1", 0, 10);
    retta1->SetLineColor(kRed);
    retta1->SetLineStyle(2);
    retta1->SetLineWidth(2);
    fit(retta1, 2, fileInput, due.v_in, due.v_d, retta_1, 0, 2.5);

    fit_results retta_2;
    TF1 *retta2 = new TF1("retta2", "pol1", 0, 10);
    retta2->SetLineColor(kRed);
    retta2->SetLineStyle(2);
    retta2->SetLineWidth(2);
    fit(retta1, 2, fileInput, due.v_in, due.v_d, retta_2, 7, 10);



    // DISEGNO PUNTI DEL CIRCUITO IDEALE
    TGraph *ideal = new TGraph("../Dati/circuito_2_dc_ideale.txt", "%lg %*lg %lg");

    ideal->SetMarkerColor(4);
    ideal->SetLineColor(kBlue);
    ideal->SetMarkerStyle(20);
    ideal->SetMarkerSize(0.1);
    ideal->SetTitle("");
    ideal->GetXaxis()->SetTitle("V_{in} [V]");
    ideal->GetYaxis()->SetTitle("V_{d} [mV]");
    ideal->GetXaxis()->SetAxisColor(14);
    ideal->GetYaxis()->SetAxisColor(14);

    ideal->Draw("Psame");



    //commeto




    // Manca propagazione errore
    double v_in = (retta_2.a[0] - retta_1.a[0]) / (retta_1.b[0] - retta_2.b[0]);
    cout << "V_ON: " << v_in << " volt" << endl;
    double a2a1 = retta_2.a[0] - retta_1.a[0];
    double b1b2 = retta_1.b[0] - retta_2.b[0];
    double f1 = pow(retta_2.err_a[0] / b1b2, 2);
    double f2 = pow(retta_1.err_a[0] / b1b2, 2);
    double f3 = pow(a2a1 * retta_1.err_b[0] / pow(b1b2, 2), 2);
    double f4 = pow(a2a1 * retta_2.err_b[0] / pow(b1b2, 2), 2);
    double f5 = 2. * a2a1 / pow(b1b2, 3) * retta_1.covariance_matrix[0][1];
    double f6 = 2. * a2a1 / pow(b1b2, 3) * retta_2.covariance_matrix[1][0];
    double err_v_in = sqrt(f1 + f2 + f3 + f4 + f5 + f6);
    cout << "Errore v_in: " << err_v_in << " volt" << endl;

    double r_1 = 11.913; // kohm
    double r_2 = 4.63;
    double r_3 = 4.67;
    double r_4 = 8.04;

    double r_a = pow(((1 / r_2) + (1 / (r_3 + r_4))), -1);
    double coeff = r_a / (r_a + r_1) * r_4 / (r_3 + r_4);
    cout << "Coeff: " << coeff << "+/-"<< 0.00012414<<endl;

    cout << "Stima di V_ON: " << coeff * v_in << endl;
    cout << retta_1.b[0] << endl;
}