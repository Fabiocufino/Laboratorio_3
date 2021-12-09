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

void circ_2_3()
{
    double v_max_sh = 131;                         // mv
    double err_v_max_sh = err_osc_v(v_max_sh, 20); // mv
    double v_under = 23.2;                         // mv
    double err_v_under = err_osc_v(v_under, 20);   // mv
    double t_max = 17;                             // us
    double err_t_max = err_osc_t(5);               // us

    double r_in = 55.306 * 1e3;                      // Omh
    double err_r_in = err_res_cap(r_in, 0.07, 8, 1); // 0.0228 * 1e3;               // Ohm
    double r_f = 681.08e3;                           // ohm
    double err_r_f = err_res_cap(r_f, 0.07, 8, 1);   // ohm
    double v_in = 1.020;                             // V
    double err_v_in = err_osc_v(v_in, 0.500);        // V

    double c_0 = 19e-12;                                                // farad
    double c_f = (237 - 19) * 1e-12;                                    // farad
    double err_c_f = err_res_cap(c_f * 1e12, 2.5, 15, 1) * 1e-12;       // farad
    double c_sh_1 = (116 - 19) * 1e-12;                                 // far
    double err_c_sh_1 = err_res_cap(c_sh_1 * 1e12, 2.5, 15, 1) * 1e-12; // far

    double r_pz = r_f * c_f / c_sh_1; // ohm
    double err_r_pz = sqrt(pow(err_r_f * c_f / c_sh_1, 2) +
                           pow(r_f * err_c_f / c_sh_1, 2) +
                           pow(r_f * c_f * err_c_sh_1 / pow(c_sh_1, 2), 2));

    double r_1 = 1.0016e6;
    double r_2 = 559e3;
    double err_r_1 = err_res_cap(r_1, 0.07, 8, 1);
    double err_r_2 = err_res_cap(r_2, 0.07, 8, 1);

    cout << "v_max_sh:\t" << v_max_sh << "+-" << err_v_max_sh << endl
         << "v_under:\t" << v_under << "+-" << err_v_under << endl
         << "t_max:\t" << t_max << "+-" << err_t_max << endl
         << "r_pz:\t" << r_pz << "+-" << err_r_pz << endl
         << "r_1:\t" << r_1 << "+-" << err_r_1 << endl
         << "r_2:\t" << r_2 << "+-" << err_r_2 << endl;
}