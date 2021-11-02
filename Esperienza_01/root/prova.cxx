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

#include "datacontainer.h"
#include "root.h"

#include "DATACLASSGEN.h"
using namespace std;

enum class Colonna: int
{
    vin = 0,
    vout = 1
};

void prova()
{
    DataContainerGen prova;
    prova.read("../Dati/dati_circuito_1.txt", 4);

    prova.dump({(int)Colonna::vin, (int)Colonna::vout});
}