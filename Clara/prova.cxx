void prova()
{

    TFile *f = new TFile("prova.root");
    TTree *t1 = (TTree *)f->Get("nt");
    Float_t px, py;
    t1->SetBranchAddress("uno", &px);
    t1->SetBranchAddress("due", &py);


    // two histograms
    TH2F *hpxpy = new TH2F("hpxpy", "py vs px", 30, -3, 3, 30, -3, 3);

    // all entries and fill the histograms
    Int_t nentries = (Int_t)t1->GetEntries();
    for (Int_t i = 0; i < nentries; i++)
    {
        t1->GetEntry(i);
        std::cout << px << " " << py << "\n";
    }

}