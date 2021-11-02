#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class DataContainerGen
{
public:
    void read(string filename, int n_col);
    void dump(vector<int> cols_to_print);

private:
    vector<vector<double>> tabella;
    string fileread;
    double n_cols;
};

void DataContainerGen::read(string filename, int n_col)
{

    fileread = filename;
    ifstream fin(fileread);
    if (!fin)
    {
        cout << "Errore lettura file: " + fileread + " Linea funzione: " + __LINE__ << endl;
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

// prova.dummp({2,3});
void DataContainerGen::dump(vector<int> cols_to_print)
{
    if (cols_to_print.size() != 0)
    {
        for (int j = 0; j < tabella[0].size(); j++)
        {
            for (int i = 0; i < cols_to_print.size(); i++)
            {
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