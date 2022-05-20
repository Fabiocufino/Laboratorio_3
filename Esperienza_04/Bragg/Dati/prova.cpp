
void prova(const char *filename = "")
{
    const char *name[1] = {"anabragg_bragg_1000_350mb.root"};
    TFile *f = new TFile(name[0]);
    TTree *t1 = (TTree *)f->Get("nt");
    Float_t width, integral;
    t1->SetBranchAddress("width", &width);
    t1->SetBranchAddress("integral", &integral);

    Int_t nentries = (Int_t)t1->GetEntries();

    TCanvas *c1 = new TCanvas();
    TH2F *hpxpy = new TH2F("hpxpy", "width vs integral", nentries, 10, 70, nentries, 1000, 7000);

    for (Int_t i = 0; i < nentries; i++)
    {
        t1->GetEntry(i);
        hpxpy->Fill(width, integral);
    }

    hpxpy->SetMarkerColor(kAzure - 3);
    hpxpy->SetMarkerStyle(20);
    hpxpy->SetMarkerSize(0.5);
    hpxpy->SetTitle("width:integral");
    hpxpy->GetXaxis()->SetTitle("width [1 a.u. is 80ns]");
    hpxpy->GetYaxis()->SetTitle("integral [a.u]");
    hpxpy->GetXaxis()->SetAxisColor(14);
    hpxpy->GetYaxis()->SetAxisColor(14);
    hpxpy->SetStats(false);

    hpxpy->Draw();
}
