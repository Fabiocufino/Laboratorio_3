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

    double r1a = 68.578e3; //ohm
    double r1b = 67.670e3; //ohm
    double r1c = 68.574e3; //ohm
    double r1d = 68.425e3; //ohm
    double r2 = 32.878e3;  //ohm

    double err_r1a = err_res_cap(r1a, 0.07, 8, 1); //ohm
    double err_r1b = err_res_cap(r1b, 0.07, 8, 1); //ohm
    double err_r1c = err_res_cap(r1c, 0.07, 8, 1); //ohm
    double err_r1d = err_res_cap(r1d, 0.07, 8, 1); //ohm
    double err_r2 = err_res_cap(r2, 0.1, 8, 0.01); //ohm

    cout << "Resistenze:" << endl
         << r1a << "+-" << err_r1a << endl
         << r1b << "+-" << err_r1b << endl
         << r1c << "+-" << err_r1c << endl
         << r1d << "+-" << err_r1d << endl
         << r2 << "+-" << err_r2 << endl
         << endl;
}