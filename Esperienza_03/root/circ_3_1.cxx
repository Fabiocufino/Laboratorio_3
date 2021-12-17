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

void circ_3_1()
{

    double r_1_a = 46.7 * 1e3;                          //Ohm
    double err_r_1_a = err_res_cap(r_1_a, 0.07, 8, 1);  //
    double r_2_a = 472.5 * 1e3;                         //
    double err_r_2_a = err_res_cap(r_2_a, 0.07, 8, 10); //

    double ampl = r_2_a / r_1_a;
    double err_ampl = sqrt(pow((err_r_1_a * r_2_a) / pow(r_1_a, 2), 2) +
                           pow(err_r_2_a / r_1_a, 2));

    double v_out = 2.88;                      //volt
    double err_v_out = err_osc_v(v_out, 0.5); //volt

    double r_1_a_bias = 9.82 * 1e3;
    double err_r_1_a_bias = err_res_cap(r_1_a_bias, 0.07, 8, 1);
    double r_2_a_bias = 148.93 * 1e3;
    double err_r_2_a_bias = err_res_cap(r_2_a_bias, 0.07, 8, 10);
    double r_1_b = 9.831 * 1e3;
    double err_r_1_b = err_res_cap(r_1_b, 0.07, 8, 1);
    double r_2_b_first = 817.5*1e3;
    double err_r_2_b_first = err_res_cap(r_2_b_first, 0.07, 8, 10);
    double r_2_b_second = 100.01*1e3;
    double err_r_2_b_second = err_res_cap(r_2_b_second, 0.07, 8, 10);
    double r_3_b = 9.96 * 1e3;
    double err_r_3_b = err_res_cap(r_3_b, 0.07, 8, 1);
    double r_2_b = r_2_b_first + r_2_b_second;
    double err_r_2_b = sqrt(pow(err_r_2_b_first, 2) +
                            pow(err_r_2_b_second, 2));

    cout
        << "r_1_a:\t" << r_1_a << "+-" << err_r_1_a << endl
        << "r_2_a:\t" << r_2_a << "+-" << err_r_2_a << endl
        << "ampl:\t" << ampl << "+-" << err_ampl << endl
        << "vout:\t" << v_out << "+-" << err_v_out << endl
        << endl
        << "r_1_a_b:\t" << r_1_a_bias << "+-" << err_r_1_a_bias << endl
        << "r_2_a_b:\t" << r_2_a_bias << "+-" << err_r_2_a_bias << endl
        << "r_1_b:\t" << r_1_b << "+-" << err_r_1_b << endl
        << "r_2_b:\t" << r_2_b << "+-" << err_r_2_b << endl
        << "r_2_b_fi:\t" << r_2_b_first << "+-" << err_r_2_b_first << endl
        << "r_2_b_se:\t" << r_2_b_second << "+-" << err_r_2_b_second << endl

        << "r_3_b:\t" << r_3_b << "+-" << err_r_3_b << endl;
}