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

    double c2 = 1.01; //nanofarad
    double err_c2 = err_res_cap(c2, 1, 8, 0.01);

    return 0;
}