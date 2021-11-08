#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

class DataContainerGen
{
public:
    void read(string filename, int n_col);
    void dump(vector<int> cols_to_print);

    void err_oscilloscopio(int, int, vector<double> &vec);
    vector<vector<double>> tabella;

private:
    string fileread;
    double n_cols;
};

void DataContainerGen::read(string filename, int n_col)
{

    fileread = filename;
    ifstream fin(fileread);
    if (!fin)
    {
        cout << "Errore lettura file: " + fileread + " Linea funzione: " << endl;
    }

    vector<double> empty_vec;
    for (int i = 0; i < n_col; i++)
    {
        tabella.push_back(empty_vec);
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

            for (int i = 0; i < n_col; i++)
            {
                double temp_meas;
                iss >> temp_meas;
                tabella[i].push_back(temp_meas);
            }
        }
    }
}

void DataContainerGen::dump(vector<int> cols_to_print)
{
    if (cols_to_print.size() != 0)
    {
        for (int j = 0; j < tabella[0].size(); j++)
        {
            for (int i = 0; i < cols_to_print.size(); i++)
            {
                if (cols_to_print[i] >= tabella.size())
                {
                    cout << "Non c'è la colonna che cerchi" << endl;
                }
                cout << tabella[i][j] << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        for (int j = 0; j < tabella[0].size(); j++)
        {
            for (int i = 0; i < tabella.size(); i++)
            {
                cout << tabella[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

void DataContainerGen::err_oscilloscopio(int col_fondoscala, int colonna_v, vector<double> &vec)
{
    int uniforme = 6; // Da cambiare
    for (int j = 0; j < tabella[0].size(); j++)
    {
        vec.push_back(sqrt(pow(1. / 10. * 1. / sqrt(uniforme) * tabella[col_fondoscala][j], 2) +
                           pow(3. / 100. * tabella[colonna_v][j] / sqrt(uniforme), 2)));
    }
};
