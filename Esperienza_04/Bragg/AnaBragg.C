#include <Riostream.h>
#include <stdlib.h>
#include <TROOT.h>
#include <TSystem.h>
#include "TNtuple.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"

#ifndef LABNUC
#define LABNUC
#endif

#ifndef BRAGGSIGNAL
#define BRAGGSIGNAL
#define MAXSAMPLES 1024
struct bragg_signal
{
  short int s[MAXSAMPLES];
};
#endif

int AnaBragg(const char *filename = "", int blto = 60, int intfrom = 100, int intto = 200, int npts = 256, int nsig = 0)
{

  bragg_signal signal;

  TFile *fin = new TFile(filename);
  if (!fin->IsOpen())
  {
    std::cout << "file not found! " << std::endl;
    return -1;
  }

  TTree *tree = (TTree *)fin->Get("bragg");
  if (!tree)
  {
    std::cout << "Bragg tree not found! " << std::endl;
    return -2;
  }

  TBranch *br = tree->GetBranch("signals");
  if (!br)
  {
    std::cout << "Signal branch not found! " << std::endl;
    return -3;
  }

  br->SetAddress(&signal);
  int nev = br->GetEntries();
  std::cout << "Number of events in file : " << nev << std::endl;

  // ANALIZZA EVENTO x EVENTO

  // altri parametri iniziali DA VERIFICARE ED EVENTUALMENTE MODIFICARE
  float thr_frac = 0.3; // soglia rispetto al vmax per il calcolo della larghezza
  // int intfrom = 300;// regione di integrazione da 0 a intto
  if (intto > MAXSAMPLES)
    intto = MAXSAMPLES;
  int blfrom = 0; // regione per il calcolo della baseline

  float bl;       // baseline evento x evento
  float integral; // integrale di carica
  float vmax;     // massimo relativo alla bl
  float width;    // larghezza temporale dei segnali

  char outfilename[200];
  strcpy(outfilename, "anabragg_");
  const char *cc = strrchr(filename, '/');
  if (cc)
  {
    cc++;
    strcat(outfilename, cc);
  }
  else
    strcat(outfilename, filename);

  TFile *fout = new TFile(outfilename, "RECREATE"); // output file

  TNtuple *nt = new TNtuple("nt", "", "ev:vmax:integral:width:baseline");

  int maxev = nev;
  if (nsig && nsig < nev)
    maxev = nsig;

  // LOOP SUGLI EVENTI
  for (int i = 0; i < maxev; i++)
  {

    // recupera l'evento
    br->GetEntry(i);

    // inizializza a zero
    bl = 0;
    integral = 0;
    vmax = 0;
    width = 0;

    // DA IMPLEMENTARE:
    // CALCOLO DELLA BASELINE
    // ...
    double sum = 0;
    for (int i = blfrom; i < blto; i++)
    {
      sum += signal.s[i];
    }
    bl = sum / (blto - blfrom);

    // calcolo integrali e vmax
    for (int j = intfrom; j < intto; j++)
    {
      integral += (signal.s[j] - bl);
      if ((signal.s[j] - bl) > vmax)
        vmax = (signal.s[j] - bl);
    }
    integral += gRandom->Rndm();

    // DA IMPLEMENTARE:
    // CALCOLO DELLA LARGHEZZA DEL SEGNALE A UNA CERTA PERCENTUALE DEL VMAX
    double posmin, posmax;
    for (int i = 0; i < npts; i++)
    {
      if (((signal.s[i] - bl) - (vmax * thr_frac)) * ((signal.s[i + 1] - bl) - (vmax * thr_frac)) < 0)
      {

        if (((signal.s[i] - bl) - (vmax * thr_frac)) < 0)
        {
          double y2 = signal.s[i + 1];
          double y1 = signal.s[i];
          posmin = i + ((vmax * thr_frac) - y1) * ((i + 1 - i) / (y2 - y1));
          cout << "MIN" << i << "  " << posmin << " \n";
        }
        else
        {
          double y2 = signal.s[i + 1];
          double y1 = signal.s[i];
          posmax = i + ((vmax * thr_frac) - y1) * ((i + 1 - i) / (y2 - y1));
          cout << "MAX" << i << "  " << posmax << " \n";
        }
      }
    }
    width = posmax - posmin;

    nt->Fill(i, vmax, integral, width, bl);
  }
  std::cout << maxev << " events analyzed..." << std::endl;

  fout->Write();
  fout->Close();

  fin->Close();

  new TFile(outfilename); // riapre il file dei risultati

  return 0;
}
