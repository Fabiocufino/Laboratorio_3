#ifndef GENERATORI
#define GENERATORI
#include <cmath>
#include <iostream>
#include <fstream>
double err_tensione(double x)
{
    if (x <= 600)
    {
        double perc = 0.5;
        double digit = 2;
        double lsd = 0.1;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
    else if (x >= 600)
    {
        double perc = 0.5;
        double digit = 2;
        double lsd = 1;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
};

double err_corrente(double x)
{
    if (x <= 1000)
    {
        double perc = 0.1;
        double digit = 15;
        double lsd = 0.01;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
    else if (x >= 1000 && x <= 10000)
    {
        double perc = 0.08;
        double digit = 8;
        double lsd = 0.0001;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        return sqrt(pow(gain, 2) + pow(read, 2));
    }
}

//Funzione per calcolo errore log corrente, prende come argomenti x ed err_x
double err_log(double x, double err_x)
{
    return err_x / x;
}

#endif