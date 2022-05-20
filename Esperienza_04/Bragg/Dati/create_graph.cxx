#include <string>
#include <TFile.h>
void create_graph(const char *filename = "")
{
    const char * name[12]={"anabragg_bragg_1000_375mb.root",
                             "anabragg_bragg_1000_375mb.root",
                             "anabragg_bragg_1000_400mb.root",
                             "anabragg_bragg_1000_425mb.root",
                             "anabragg_bragg_2000_500mb.root",
                             "anabragg_bragg_2000_500mb.root",
                             "anabragg_bragg_2000_550mb.root",
                             "anabragg_bragg_2000_600mb.root",
                             "anabragg_bragg_2000_650mb.root",
                             "anabragg_bragg_5000_600mb.root",
                             "anabragg_bragg_500_1.root",
                             "anabragg_bragg_prova.root"};


    for (int i = 0; i < 2; i++)
    {

        TFile *f = new TFile(name[i]);
        TTree *t1 = (TTree *)f->Get("nt");
        Float_t width, integral;
        t1->SetBranchAddress("width", &width);
        t1->SetBranchAddress("integral", &integral);
//
        Int_t nentries = (Int_t)t1->GetEntries();
//
        TCanvas *c1 = new TCanvas();
        TH2F *hpxpy = new TH2F("hpxpy", "width vs integral", nentries, 10, 70, nentries, 1000, 7000);
//
        for (Int_t i = 0; i < nentries; i++)
        {
            t1->GetEntry(i);
            hpxpy->Fill(width, integral);
        }
//
        hpxpy->SetMarkerColor(kAzure - 3);
        hpxpy->SetMarkerStyle(20);
        hpxpy->SetMarkerSize(0.5);
        hpxpy->SetTitle("width:integral");
        hpxpy->GetXaxis()->SetTitle("width [1 a.u. is 80ns]");
        hpxpy->GetYaxis()->SetTitle("integral [a.u]");
        hpxpy->GetXaxis()->SetAxisColor(14);
        hpxpy->GetYaxis()->SetAxisColor(14);
        hpxpy->SetStats(false);
//
        hpxpy->Draw();
//
        //// std::string str;
        //// const char *c = str.c_str();
    }
}
