#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TVectorD.h"

#include "fit_results.h"

TVector into_root(vector<double> x)
{
    TVectorD root_x(x.size(), x.data());
    return root_x;
}

//Mette nella struttura fit_resuts tutti i parametri del fit
void fit(TF1 *f, Double_t number_of_parameters, TGraph *graf, vector<double> &asse_x, vector<double> &asse_y, fit_results &fit_res_str, double asse_x_inizio = -__DBL_MAX__, double asse_x_fine = __DBL_MAX__)
{
    TFitResultPtr fit_res = graf->Fit(f, "S");
    //TFitResultPtr fit_res = graf->Fit(f, "+S", "", asse_x_inizio, asse_x_fine);
    TMatrixD cov = fit_res->GetCovarianceMatrix();

    fit_res_str.a.push_back(f->GetParameter(0));
    fit_res_str.err_a.push_back(f->GetParError(0));
    fit_res_str.chi_square.push_back(f->GetChisquare());
    fit_res_str.dof.push_back(f->GetNDF());

    if (number_of_parameters == 2)
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