#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TLatex.h"
#include "TPaveStats.h"

#include "fit_results.h"

TVectorD into_root(vector<double> x)
{
    TVectorD root_x(x.size(), x.data());
    return root_x;
}

//Mette nella struttura fit_resuts tutti i parametri del fit
void fit(TF1 *f, Double_t number_of_parameters, TGraph *graf, vector<double> &asse_x, vector<double> &asse_y, fit_results &fit_res_str, double asse_x_inizio = -__DBL_MAX__, double asse_x_fine = __DBL_MAX__)
{
    //TFitResultPtr fit_res = graf->Fit(f, "S");
    TFitResultPtr fit_res = graf->Fit(f, "+S", "", asse_x_inizio, asse_x_fine); //quando ci sono più fit nello stesso canvas li fa vedere tutti
    TMatrixD cov = fit_res->GetCovarianceMatrix();

    fit_res_str.a.push_back(f->GetParameter(0));
    fit_res_str.err_a.push_back(f->GetParError(0));
    fit_res_str.chi_square.push_back(f->GetChisquare());
    fit_res_str.dof.push_back(f->GetNDF());

    if (number_of_parameters == 2) //(FIT LINEARE a+bx)
    {
        fit_res_str.b.push_back(f->GetParameter(1));
        fit_res_str.err_b.push_back(f->GetParError(1));
        fit_res_str.rho.push_back(pearson(asse_x, asse_y));
        fit_res_str.t_student.push_back(student(asse_x, asse_y));
        fit_res_str.sigma_post.push_back(sigma_y_posteriori(asse_x, asse_y));
        fit_res_str.covariance_matrix[0][1] = cov[0][1];
        fit_res_str.covariance_matrix[1][0] = cov[0][1];
    }
    if (number_of_parameters == 3)
    {
        fit_res_str.b.push_back(f->GetParameter(1));
        fit_res_str.err_b.push_back(f->GetParError(1));
        fit_res_str.covariance_matrix[0][1] = cov[0][1];
        fit_res_str.rho.push_back(pearson(asse_x, asse_y));
        fit_res_str.t_student.push_back(student(asse_x, asse_y));
        fit_res_str.sigma_post.push_back(sigma_y_posteriori(asse_x, asse_y));
        fit_res_str.c.push_back(f->GetParameter(2));
        fit_res_str.err_c.push_back(f->GetParError(2));

        fit_res_str.covariance_matrix[1][2] = cov[1][2];
        fit_res_str.covariance_matrix[2][0] = cov[2][0];
    }

    if (number_of_parameters == 4) //AGGIUSTARE LA MATRICE DI COVARIANZE
    {
        fit_res_str.b.push_back(f->GetParameter(1));
        fit_res_str.err_b.push_back(f->GetParError(1));
        fit_res_str.covariance_matrix[0][1] = cov[0][1];
        fit_res_str.rho.push_back(pearson(asse_x, asse_y));
        fit_res_str.t_student.push_back(student(asse_x, asse_y));
        fit_res_str.sigma_post.push_back(sigma_y_posteriori(asse_x, asse_y));
        fit_res_str.c.push_back(f->GetParameter(2));
        fit_res_str.err_c.push_back(f->GetParError(2));
        fit_res_str.d.push_back(f->GetParameter(2));
        fit_res_str.err_d.push_back(f->GetParError(2));

        fit_res_str.covariance_matrix[1][2] = cov[1][2];
        fit_res_str.covariance_matrix[2][0] = cov[2][0];
    }
    if (number_of_parameters == 5) //AGGIUSTARE LA MATRICE DI COVARIANZE
    {
        fit_res_str.b.push_back(f->GetParameter(1));
        fit_res_str.err_b.push_back(f->GetParError(1));
        fit_res_str.covariance_matrix[0][1] = cov[0][1];
        fit_res_str.rho.push_back(pearson(asse_x, asse_y));
        fit_res_str.t_student.push_back(student(asse_x, asse_y));
        fit_res_str.sigma_post.push_back(sigma_y_posteriori(asse_x, asse_y));
        fit_res_str.c.push_back(f->GetParameter(2));
        fit_res_str.err_c.push_back(f->GetParError(2));
        fit_res_str.d.push_back(f->GetParameter(2));
        fit_res_str.err_d.push_back(f->GetParError(2));
        fit_res_str.e.push_back(f->GetParameter(2));
        fit_res_str.err_e.push_back(f->GetParError(2));

        fit_res_str.covariance_matrix[1][2] = cov[1][2];
        fit_res_str.covariance_matrix[2][0] = cov[2][0];
    }
}

//Fa il run test per una retta del tipo a+bx
void run_test_lineare(vector<double> &scarti, vector<double> &asse_x, vector<double> &asse_y, double a_int, double b_ang)
{
    for (int i = 0; i < asse_x.size(); i++)
    {
        scarti.push_back(asse_y[i] - (a_int + (b_ang * asse_x[i])));
    }
}

//========================================================Parte Grafica per i grafici=======================
void informazioni_fit_lineare(TPaveStats *ptstats1, TText *ptstats_LaTex1, string chi_s, string dof, string par_0, string err_par_0, string par_1, string err_par_1, string pear, string stu, string sigma_p, string title = "")
{
    ptstats1 = new TPaveStats(0.5, 0.65, 0.95, 0.95, "brNDC");
    ptstats1->SetName("stats");
    ptstats1->SetBorderSize(1);
    ptstats1->SetFillColor(0);
    ptstats1->SetTextAlign(12);
    ptstats1->SetTextFont(22);

    if (title.size() != 0)
    {
        const char *title_c = title.c_str();
        ptstats_LaTex1 = ptstats1->AddText(title_c);
    }

    string first = "#chi^{2} / ndf =" + chi_s + "/" + dof;
    const char *first_c = first.c_str();
    ptstats_LaTex1 = ptstats1->AddText(first_c);

    string second = "a        = " + par_0 + "#pm" + err_par_0;
    const char *second_c = second.c_str();
    ptstats_LaTex1 = ptstats1->AddText(second_c);

    string third = "b        = " + par_1 + "#pm" + err_par_1;
    const char *third_c = third.c_str();
    ptstats_LaTex1 = ptstats1->AddText(third_c);

    string fourth = "Pearson        = " + pear;
    const char *fourth_c = fourth.c_str();
    ptstats_LaTex1 = ptstats1->AddText(fourth_c);

    string fiveth = "T_Student        = " + stu;
    const char *fiveth_c = fiveth.c_str();
    ptstats_LaTex1 = ptstats1->AddText(fiveth_c);

    string sixth = "#sigma_{post}        = " + sigma_p;
    const char *sixth_c = sixth.c_str();
    ptstats_LaTex1 = ptstats1->AddText(sixth_c);

    ptstats1->SetOptStat(0);
    ptstats1->SetOptFit(111);
    ptstats1->Draw();
}