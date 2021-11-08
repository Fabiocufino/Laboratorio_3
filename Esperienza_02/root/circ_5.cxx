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
#include "root.h"

#include "DATACLASSGEN.h"
using namespace std;

enum class Colonna : int
{
    v_in = 0,
    fs_vin = 1,
    v_out = 2,
    fs_vout = 3
};

double err_res_cap(double resistenza, double perc, double digit, double lsd)
{
    double gain = perc / 100. * resistenza * 1. / sqrt(3);
    double read = digit * lsd * 1. / sqrt(3);
    return sqrt(pow(gain, 2) + pow(read, 2));
}
void circ_5()
{

    double ra = 68.578e3; //ohm
    double rb = 67.670e3; //ohm
    double rc = 68.574e3; //ohm
    double rd = 68.425e3; //ohm
    double r2 = 32.878e3; //ohm

    double err_ra = err_res_cap(ra, 0.07, 8, 1);   //ohm
    double err_rb = err_res_cap(rb, 0.07, 8, 1);   //ohm
    double err_rc = err_res_cap(rc, 0.07, 8, 1);   //ohm
    double err_rd = err_res_cap(rd, 0.07, 8, 1);   //ohm
    double err_r2 = err_res_cap(r2, 0.1, 8, 0.01); //ohm

    cout << "Resistenze:" << endl
         << ra << "+-" << err_ra << endl
         << rb << "+-" << err_rb << endl
         << rc << "+-" << err_rc << endl
         << rd << "+-" << err_rd << endl
         << r2 << "+-" << err_r2 << endl
         << endl;

    double vin = 10.5;
    double err_vin = sqrt(2.) * sqrt(pow(1. / 10. * 1. / sqrt(6) * 5, 2) +
                                     pow(3. / 100. * vin / sqrt(6), 2));
    double von = 0.51;
    double err_von = 0.04;
    
    double vout_p = vin * (-1.0 * rd / rc + (rd * rb) / (r2 * ra));
    double voutp_p = -1.0 * rb / ra * vin - von;
    double v2_p = -1.0 * (rb / ra) * vin;

    double err_vout_p = sqrt(pow(err_vin, 2) * pow(((rb * rd) / (r2 * ra) - rd / rc), 2) +
                             (pow(err_rb, 2) * pow(rd, 2) * pow(vin, 2)) / (pow(r2, 2) * pow(ra, 2)) +
                             (pow(err_ra, 2) * pow(rb, 2) * pow(rd, 2) * pow(vin, 2)) / (pow(r2, 2) * pow(ra, 4)) +
                             (pow(err_r2, 2) * pow(rb, 2) * pow(rd, 2) * pow(vin, 2)) / (pow(r2, 4) * pow(ra, 2)) +
                             (pow(err_rc, 2) * pow(rd, 2) * pow(vin, 2)) / pow(rc, 4) +
                             pow(err_rd, 2) * pow(((rb * vin) / (r2 * ra) - vin / rc), 2));
    double err_voutp_p = sqrt(pow(err_von, 2) +
                              (pow(err_vin, 2) * pow(rb, 2)) / pow(ra, 2) +
                              (pow(err_rb, 2) * pow(vin, 2)) / pow(ra, 2) +
                              (pow(err_ra, 2) * pow(rb, 2) * pow(vin, 2)) / pow(ra, 4));
    double err_v2_p = sqrt((pow(err_vin, 2) * pow(rb, 2)) / pow(ra, 2) +
                           (pow(err_rb, 2) * pow(vin, 2)) / pow(ra, 2) +
                           (pow(err_ra, 2) * pow(rb, 2) * pow(vin, 2)) / pow(ra, 4));

    double vout_n = -1.0 * vin;
    double voutp_n = 1.0 * von;
    double v2_n = 0;

    double err_vout_n = err_vin;
    double err_voutp_n = err_von;
    double err_v2_n = 0;

    cout << "vin:\t" << vin << "+-" << err_vin << endl
         << "von:\t" << von << "+-" << err_von << endl
         << "vo_p:\t" << vout_p << "+-" << err_vout_p << endl
         << "v2_p:\t" << v2_p << "+-" << err_v2_p << endl
         << "vop_p:\t" << voutp_p << "+-" << err_voutp_p << endl
         << "vo_n:\t" << vout_n << "+-" << err_vout_n << endl
         << "v2_n:\t" << v2_n << "+-" << err_v2_n << endl
         << "vop_n:\t" << voutp_n << "+-" << err_voutp_n << endl;
}