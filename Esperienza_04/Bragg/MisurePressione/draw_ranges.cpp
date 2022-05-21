void draw_ranges()
{
    TNtuple *nt = new TNtuple("nt", "nt", "pre:e_pre:r1:er1:r2:er2:r3:er3");
    nt->ReadFile("range.txt");
    nt->Draw("pre:r1");
    TGraphErrors *unoq = new TGraphErrors(nt->GetSelectedRows(), nt->GetVal(0), nt->GetVal(2), nt->GetVal(1), nt->GetVal(3));
    unoq->Draw("ap");
}