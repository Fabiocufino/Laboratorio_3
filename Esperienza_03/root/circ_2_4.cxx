#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <fstream>
#include <cmath>
//#include "TFitresult.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TGraphErrors.h"
#include <vector>
#include <fstream>
#include "TLine.h"

#include "DATACLASSGEN.h"
#include "root.h"
#include "fit_results.h"

using namespace std;

void circ_2_4()
{

    double r_sh_1 = 3.24 * 1e3;                            // Omh
    double err_r_sh_1 = err_res_cap(r_sh_1, 0.07, 8, 0.1); // 0.0228 * 1e3;               // Ohm
    double r_sh_2 = 3.25e3;                                // ohm
    double err_r_sh_2 = err_res_cap(r_sh_2, 0.07, 8, 0.1); // ohm

    double c_0 = 19e-12;                                                // farad
    double c_f = (237 - 19) * 1e-12;                                    // farad
    double err_c_f = err_res_cap(c_f * 1e12, 2.5, 15, 1) * 1e-12;       // farad
    double c_sh_1 = (116 - 19) * 1e-12;                                 // far
    double err_c_sh_1 = err_res_cap(c_sh_1 * 1e12, 2.5, 15, 1) * 1e-12; // far
    double c_sh_2 = (119 - 19) * 1e-12;                                 // far
    double err_c_sh_2 = err_res_cap(c_sh_2 * 1e12, 2.5, 15, 1) * 1e-12; // far

    double tau_sh_1 = r_sh_1 * c_sh_1;
    double err_tau_sh_1 = sqrt(pow(err_r_sh_1 * c_sh_1, 2) + pow(err_c_sh_1 * r_sh_1, 2));
    double tau_sh_2 = r_sh_2 * c_sh_2;
    double err_tau_sh_2 = sqrt(pow(err_r_sh_2 * c_sh_2, 2) + pow(err_c_sh_2 * r_sh_2, 2));

    cout << "r_sh_1:\t" << r_sh_1 << "+-" << err_r_sh_1 << endl
         << "r_sh_2:\t" << r_sh_2 << "+-" << err_r_sh_2 << endl
         << "tau_sh_1:\t" << tau_sh_1 << "+-" << err_tau_sh_1 << endl
         << "tau_sh_2:\t" << tau_sh_2 << "+-" << err_tau_sh_2 << endl;
}