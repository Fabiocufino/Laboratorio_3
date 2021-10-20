#ifndef DATACONTAINER
#define DATACONTAINER
#include <vector>
#include <fstream>
#include <iostream>
#include "generatori.h"
using namespace std;

class DataContainer
{
public:
    void read(string filename);
    vector<vector<double>> colonne;
    string Filename() { return fileread; };
    int NewCol(double (*generatore)(double), int colonna_input);
    int NewCol2(double (*generatore)(double, double), vector<double> args);

private:
    string fileread;
};

void DataContainer::read(string filename)
{
    int ncols = 0;
    fileread = filename;
    ifstream fin(fileread);
    if (!fin)
    {
        cout << "Errore lettura file: " + fileread + " Linea funzione: " + __LINE__ << endl;
    }
    vector<double> col_element;
    int i = 0;
    double dummy;
    string temp_line;
    while (getline(fin, temp_line))
    {
        if (temp_line.rfind("#", 0) == 0 || temp_line.size() < 5)
        {
            continue;
        }
        else
        {
            if (i == 0)
            {
                istringstream ioo(temp_line);
                vector<double> temp_col;
                double temporary;
                while (ioo >> temporary)
                {
                    temp_col.push_back(temporary);
                }
                ncols = temp_col.size();
                for (int i = 0; i < ncols; i++)
                {
                    colonne.push_back(col_element);
                }
            }
            istringstream iss(temp_line);
            while (iss >> dummy)
            {
                colonne[i % ncols].push_back(dummy);
                i++;
            }
        }
    }
}

//vdid->read("../Dati/dati_circuito_1.txt", 2 , vector<double> correnti);
//
//vdid->correnti

int DataContainer::NewCol(double (*generatore)(double), int colonna_input)
{
    vector<double> col_element;
    colonne.push_back(col_element);
    for (int i = 0; i < colonne[0].size(); i++)
    {
        colonne[colonne.size() - 1].push_back(generatore(colonne[colonna_input][i]));
    }
    cout << "Nuova colonna creata con elementi: " << colonne[colonne.size() - 1].size() << endl
         << "Indice nuova colonna: " << colonne.size() - 1;
    cout << "COsa ritorno:" << &colonne[colonne.size() - 1] << endl;
    return (colonne.size() - 1);
}

int DataContainer::NewCol2(double (*gen)(double, double), vector<double> args)
{
    vector<double> col_element;
    colonne.push_back(col_element);
    for (int i = 0; i < colonne[0].size(); i++)
    {
        colonne[colonne.size() - 1].push_back(gen(colonne[args[0]][i], colonne[args[1][i]]));
    }
    return (colonne.size() - 1);
}

#endif