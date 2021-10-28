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
    vector<double> colonna1;
    vector<double> colonna2;
    vector<double> colonna3;
    vector<double> colonna4;

private:
    string fileread;
};

void DataContainer::read(string filename, int n_col, vector<double> v1)
{

    fileread = filename;
    ifstream fin(fileread);
    if (!fin)
    {
        cout << "Errore lettura file: " + fileread + " Linea funzione: " + __LINE__ << endl;
    }

    if (n_col == 4)
    {
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
                double temp_1, temp_1, temp_3, temp_4;
                iss >> temp_vd >> temp_id >> temp_fsvd >> temp_fsid;
                colonna1.push_back(temp_1);
                colonna2.push_back(temp_2);
                colonna3.push_back(temp_3);
                colonna4.push_back(temp_4);
            }
            vector<double> &v1 = colonna1;
        }
    }
}
#endif