#include <cmath>

using namespace std;

double err_res_cap(double resistenza, double perc, double digit, double lsd)
{
    double gain = perc / 100. * resistenza * 1. / sqrt(3);
    double read = digit * lsd * 1. / sqrt(3);
    return sqrt(pow(gain, 2) + pow(read, 2));
}
int main()
{
    double r1 = 9.993e3;     //ohm
    double r1b = 10.003e3;   //ohm
    double rf_sum = 9.978e3; //ohm
    double r50 = 46.51;      //ohm
    double r50b = 46.74;     //ohm

    double err_r1 = err_res_cap(r1, 0.07, 8, 1);         //ohm
    double err_r1b = err_res_cap(r1b, 0.07, 8, 1);       //ohm
    double err_rf_sum = err_res_cap(rf_sum, 0.07, 8, 1); //ohm
    double err_r50 = err_res_cap(r50, 0.1, 8, 0.01);     //ohm
    double err_r50b = err_res_cap(r50b, 0.1, 8, 0.01);   //ohm

    return 0;
}