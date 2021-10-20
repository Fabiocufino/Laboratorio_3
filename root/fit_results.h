#define ROOTDATACLASS
#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>
#include "statistica.h"
#include <iomanip>

using namespace std;
class fit_results
{
public:
    vector<double> a;
    vector<double> err_a;
    vector<double> b;
    vector<double> err_b;
    vector<double> c;
    vector<double> err_c;
    vector<double> d;
    vector<double> err_d;
    vector<double> e;
    vector<double> err_e;
    vector<double> chi_square;
    vector<double> rho;
    vector<double> t_student;
    vector<double> sigma_post;
    vector<double> dof;

    double covariance_matrix[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    fit_results(){};

    //usando statistica.h calcola Perason Student e Chi Squared
    fit_results(vector<double> &asse_x, vector<double> &asse_y)
    {
        rho.push_back(pearson(asse_x, asse_y));
        t_student.push_back(student(asse_x, asse_y));
        sigma_post.push_back(sigma_y_posteriori(asse_x, asse_y));
    }
};