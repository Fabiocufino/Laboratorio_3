#ifndef DATACONTAINER
#define DATACONTAINER
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class DataContainer
{
public:
    void read(string filename);
    vector<double> vd;
    vector<double> id;
    vector<double> fs_vd;
    vector<double> fs_id;
    vector<double> err_vd;
    vector<double> err_id;

private:
    string fileread;
};

void DataContainer::read(string filename)
{

    fileread = filename;
    ifstream fin(fileread);
    if (!fin)
    {
        cout << "Errore lettura file: " + fileread + " Linea funzione: " + __LINE__ << endl;
    }

    string temp_line;
    while (getline(fin, temp_line))
    {
        if (temp_line.rfind("#", 0) == 0 || temp_line.size() < 2)
        {
            continue;
        }
        else
        {
            istringstream iss(temp_line);
            double temp_vd, temp_id, temp_fsvd, temp_fsid;
            iss >> temp_vd >> temp_id >> temp_fsvd >> temp_fsid;
            vd.push_back(temp_vd);
            id.push_back(temp_id);
            fs_vd.push_back(temp_fsvd);
            fs_id.push_back(temp_fsid);
        }
    }
}
///////////////////////////////////////////////Funzioni che servono//////////////////////////
double err_tensione(double x)
{
    double err;
    if (x <= 600)
    {
        double perc = 0.5;
        double digit = 2;
        double lsd = 0.1;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        err = sqrt(pow(gain, 2) + pow(read, 2));
    }
    else if (x >= 600)
    {
        double perc = 0.5;
        double digit = 2;
        double lsd = 1;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        err = sqrt(pow(gain, 2) + pow(read, 2));
    }
    return err;
}

double err_corrente(double x)
{
    double err;
    if (x <= 1000)
    {
        double perc = 0.1;
        double digit = 15;
        double lsd = 0.01;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        err = sqrt(pow(gain, 2) + pow(read, 2));
    }
    else if (x >= 1000 && x <= 10000)
    {
        double perc = 0.08;
        double digit = 8;
        double lsd = 0.0001;
        double gain = perc / 100. * x * 1. / sqrt(3);
        double read = digit * lsd * 1. / sqrt(3);
        err = sqrt(pow(gain, 2) + pow(read, 2));
    }
    return err;
}

//Funzione per calcolo errore log corrente, prende come argomenti x ed err_x
double err_log(double x, double err_x)
{
    return err_x / x;
}

//fa il cout degli elementi di un vettore
void print_vector(vector<double> x)
{
    for (int i = 0; i < x.size(); i++)
    {
        cout << x[i] << endl;
    }
}

//-----------------------------------------------------------------------------
class DataContainer_due
{
public:
    void read(string filename);
    vector<double> t;
    vector<double> fst;
    vector<double> v_in;
    vector<double> v_d;
    vector<double> fsv;
private:
    string fileread;
};

void DataContainer_due::read(string filename)
{

    fileread = filename;
    ifstream fin(fileread);
    if (!fin)
    {
        cout << "Errore lettura file: " + fileread + " Linea funzione: " + __LINE__ << endl;
    }

    string temp_line;
    while (getline(fin, temp_line))
    {
        if (temp_line.rfind("#", 0) == 0 || temp_line.size() < 2)
        {
            continue;
        }
        else
        {
            istringstream iss(temp_line);
            double temp_vd, temp_id, temp_fsvd, temp_fsid, temp5;
            iss >> temp_vd >> temp_id >> temp_fsvd >> temp_fsid >> temp5;
            t.push_back(temp_vd);
            fst.push_back(temp_id);
            v_in.push_back(temp_fsvd);
            v_d.push_back(temp_fsid);
            fsv.push_back(temp5);
        }
    }
}

#endif