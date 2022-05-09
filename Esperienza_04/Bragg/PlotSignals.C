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
struct bragg_signal {
  short int s[MAXSAMPLES];
};
#endif


int plotSignal(bragg_signal sig, int same, int npts, TH2F *nullo) {

  float x[npts]; for (int i=0; i<npts; i++) x[i]=i*1.0;
  float y[npts]; for (int i=0; i<npts; i++) y[i]=sig.s[i];
  TGraph *g = new TGraph(npts,x,y); // crea il grafico
  g->SetMarkerStyle(7); // imposta alcuni attributi
  g->SetLineColor(4);
  g->SetLineWidth(2);

  TCanvas *csig = (TCanvas*)gROOT->FindObject("csig"); // cerca l'oggetto "csig" (canvas)
  if (!csig) { 
    csig=new TCanvas("csig"); // se non c'e' la crea nuova
    csig->SetGridy();
    nullo->Draw();
    g->Draw("pl"); // disegna il grafico e anche il frame con gli assi
  }
  else { 
    csig->cd(); // se c'e' si posiziona sulla canvas "csig"
    if (same)
      g->Draw("pl"); // disegna nel frame esistente
    else {
      csig->Clear();
      g->Draw("apl"); // disegna in un nuovo frame
      gSystem->Sleep(200); // aspetta 200 ms
    }      
  }
  csig->Modified(); // aggiorna la canvas
  csig->Update();
  gSystem->ProcessEvents(); // aggiorna la grafica

  return 0;
}

int PlotSignals(const char *filename="", int plfrom=0, int plto=100, int same=1, int npts=256) {

  bragg_signal signal;

  if (npts>MAXSAMPLES) npts=MAXSAMPLES;
  
  TFile *fin=new TFile(filename);
  if (!fin->IsOpen()) {
    std::cout << "file not found! " << std::endl;
    return -1;
  }

  TTree *tree = (TTree*)fin->Get("bragg");
  if (!tree) {
    std::cout << "Bragg tree not found! " << std::endl;
    return -2;
  }

  TBranch *br = tree->GetBranch("signals");
  if (!br) {
    std::cout << "Signal branch not found! " << std::endl;
    return -3;
  }

  br->SetAddress(&signal);
  int nev = br->GetEntries();
  std::cout << "Number of events in file : " << nev << std::endl;

  TH2F *hnull = new TH2F("hnull","",256,0,npts,256,-1*32, 8*32);
  hnull->SetStats(0);
  
  for (int i=plfrom; i<plto; i++) {
    br->GetEntry(i);
    plotSignal(signal,same,npts,hnull);  
  }
  
  return 0;
}
