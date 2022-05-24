// Fa il run test per una retta del tipo a+bx
void run_test_lineare(vector<double> &scarti, vector<double> &asse_x, vector<double> &asse_y, double a_int, double b_ang)
{
    for (int i = 0; i < asse_x.size(); i++)
    {
        scarti.push_back(asse_y[i] - (a_int + (b_ang * asse_x[i])));
    }
}

TVectorD into_root(vector<double> x)
{
    TVectorD root_x(x.size(), x.data());
    return root_x;
}

void bk_2()
{
    TCanvas *c1 = new TCanvas("c1", "Bragg_kleeman", 468, 206, 1332, 851);
    c1->Range(0, 0, 1, 1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);

    TPad *pad1 = new TPad("pad1", "This is pad1", 0.005, 0.02, 0.99, 0.97);
    TPad *pad2 = new TPad("pad2", "This is pad2", 0.005, 0.02, 0.99, 0.37);
    pad1->Draw();
    pad2->Draw();

    pad1->cd();
    pad1->SetFillColor(0);
    pad1->SetBorderMode(0);
    pad1->SetBorderSize(2);
    pad1->SetLeftMargin(0.08037394);
    pad1->SetRightMargin(0.05596981);
    pad1->SetTopMargin(0.003203662);
    pad1->SetBottomMargin(0.4549199);
    pad1->SetFrameBorderMode(0);
    pad1->SetFrameBorderMode(0);

    TNtuple *nt = new TNtuple("nt", "nt", "pre:e_pre:r1:er1:r2:er2:r3:er3");
    nt->ReadFile("range.txt");

    nt->Draw("pre:e_pre:r1:er1:r2:er2", "", "goff");
    Int_t nentries = (Int_t)nt->GetEntries();

    Double_t *x = nt->GetVal(0);
    Double_t *er_x = nt->GetVal(1);
    Double_t *y = nt->GetVal(4);
    Double_t *er_y = nt->GetVal(5);

    vector<double> x_v;
    vector<double> er_x_v;
    vector<double> y_v;
    vector<double> er_y_v;
    for (int i = 0; i < 5; i++)
    {
        x_v.push_back(1 / x[i]);
        er_x_v.push_back(er_x[i]);
        y_v.push_back(y[i]);
        er_y_v.push_back(er_y[i]);
    }
    TGraphErrors *unoq = new TGraphErrors(into_root(x_v), into_root(y_v), into_root(er_x_v), into_root(er_y_v));

    unoq->SetMarkerColor(kAzure - 3);
    unoq->SetMarkerStyle(20);
    unoq->SetMarkerSize(0.5);
    unoq->GetXaxis()->SetAxisColor(14);
    unoq->GetYaxis()->SetAxisColor(14);
    unoq->GetXaxis()->SetTitle("1/P [1/mb]");
    unoq->GetYaxis()->SetTitle("Ranges []");
    unoq->Draw("ap");

    // Faccio il fit Lineare
    TF1 *retta = new TF1("retta", "pol1", 0, 10);
    retta->SetLineColor(kRed);
    retta->SetLineStyle(2);
    retta->SetLineWidth(2);
    unoq->Fit(retta, "S");

    pad2->cd(); //----------------------------------------------------------SCARTI---------------------------------
    pad2->SetFillColor(0);
    pad2->SetBorderMode(0);
    pad2->SetBorderSize(2);
    pad2->SetLeftMargin(0.07732215);
    pad2->SetRightMargin(0.05698707);
    pad2->SetBottomMargin(0.1664596);
    pad2->SetFrameBorderMode(0);
    pad2->SetFrameBorderMode(0);

    vector<double> scarti;
    run_test_lineare(scarti, x_v, y_v, retta->GetParameter(0), retta->GetParameter(1));
    vector<double> err_scarti;
    for (int i = 0; i < scarti.size(); i++)
    {
        err_scarti.push_back(sqrt(pow(er_y[i], 2) + pow(retta->GetParameter(1) * er_x[i], 2)));
    }
    vector<double> err_zero(err_scarti.size(), 0);

    TGraphErrors *graph_scarti = new TGraphErrors(into_root(x_v), into_root(scarti), into_root(err_zero), into_root(err_scarti));

    graph_scarti->SetMarkerColor(4);
    graph_scarti->SetLineColor(kAzure - 3);
    graph_scarti->SetMarkerStyle(20);
    graph_scarti->SetMarkerSize(0.7);
    graph_scarti->SetTitle("");

    graph_scarti->GetYaxis()->SetAxisColor(14);
    graph_scarti->GetXaxis()->SetLabelFont(42);
    graph_scarti->GetXaxis()->SetLabelSize(0.09);
    graph_scarti->GetXaxis()->SetTitleOffset(1);
    graph_scarti->GetXaxis()->SetTitleFont(42);
    graph_scarti->GetYaxis()->SetTitle("Scarti");
    graph_scarti->GetYaxis()->SetAxisColor(14);
    graph_scarti->GetYaxis()->SetLabelFont(42);
    graph_scarti->GetYaxis()->SetLabelSize(0.09);
    graph_scarti->GetYaxis()->SetTitleSize(0.11);
    graph_scarti->GetYaxis()->SetTitleOffset(0.33);
    graph_scarti->GetYaxis()->SetTitleFont(42);

    graph_scarti->Draw("AP");

    TF1 *z = new TF1("z", "pol1", 0, 10);
    z->SetLineColor(kRed);
    z->SetLineStyle(2);
    z->SetLineWidth(2);
    z->Draw("lsame");

    TLegend *legend2 = new TLegend(0.15, 0.15, 0.5, 0.3);
    legend2->AddEntry(graph_scarti, "Dati con errore", "P");
    legend2->SetTextSize(0.04);
    legend2->SetBorderSize(1);
    legend2->SetTextSize(0.08447205);
    legend2->Draw();
}