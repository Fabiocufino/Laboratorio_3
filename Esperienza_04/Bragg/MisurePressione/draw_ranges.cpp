void draw_ranges()
{
    TNtuple *nt = new TNtuple("nt", "nt", "pre:e_pre:r1:er1:r2:er2:r3:er3");
    nt->ReadFile("range.txt");

    nt->Draw("pre:e_pre:r1:er1", "", "goff");
    Int_t nentries = (Int_t)nt->GetEntries();

    TCanvas *c1 = new TCanvas();

    Double_t *x = nt->GetVal(0);
    Double_t *l;

    TGraphErrors *unoq = new TGraphErrors(nt->GetSelectedRows(), nt->GetVal(0), nt->GetVal(2), nt->GetVal(1), nt->GetVal(3));

    unoq->SetMarkerColor(kAzure - 3);
    unoq->SetMarkerStyle(20);
    unoq->SetMarkerSize(0.5);
    unoq->GetXaxis()->SetAxisColor(14);
    unoq->GetYaxis()->SetAxisColor(14);
    unoq->SetStats(false);

    unoq->Draw("ap");
}