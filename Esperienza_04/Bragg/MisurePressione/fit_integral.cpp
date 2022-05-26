void fit_integral()
{

    TTree *nt = new TTree("nt", "nt");
    nt->ReadFile("fit_integral.txt");
    nt->Draw("err_press:press:mean1:errmean1:mean2:errmean2:mean3:errmean3", "", "goff");

    TGraphErrors *graph_1 = new TGraphErrors(nt->GetSelectedRows(), nt->GetVal(1), nt->GetVal(2), nt->GetVal(0), nt->GetVal(3));
    TGraphErrors *graph_2 = new TGraphErrors(nt->GetSelectedRows(), nt->GetVal(1), nt->GetVal(4), nt->GetVal(0), nt->GetVal(5));
    TGraphErrors *graph_3 = new TGraphErrors(nt->GetSelectedRows(), nt->GetVal(1), nt->GetVal(6), nt->GetVal(0), nt->GetVal(7));

    graph_1->SetTitle("Np-237");
    graph_2->SetTitle("Am-241");
    graph_3->SetTitle("Cm-244");

    TCanvas *c1 = new TCanvas();
    graph_1->SetLineColor(kAzure - 3);
    graph_1->SetMarkerColor(4);
    graph_1->SetMarkerStyle(20);
    graph_1->SetMarkerSize(0.7);
    graph_1->GetXaxis()->SetAxisColor(14);
    graph_1->GetYaxis()->SetAxisColor(14);
    graph_1->GetXaxis()->SetTitle("P [mb]");
    graph_1->GetYaxis()->SetTitle("integral [a.u.]");
    graph_1->Draw("ap");
    c1->Print("Np-237.pdf");

    TLegend *legend_1 = new TLegend(0.6, 0.15, 0.85, 0.25);
    legend_1->AddEntry(graph_1, "Dati con errore", "P");
    legend_1->SetTextSize(0.04);
    legend_1->SetBorderSize(1);
    legend_1->Draw();

    TCanvas *c2 = new TCanvas();
    graph_2->SetLineColor(kAzure - 3);
    graph_2->SetMarkerColor(4);
    graph_2->SetMarkerStyle(20);
    graph_2->SetMarkerSize(0.7);
    graph_2->GetXaxis()->SetAxisColor(14);
    graph_2->GetYaxis()->SetAxisColor(14);
    graph_2->GetXaxis()->SetTitle("P [mb]");
    graph_2->GetYaxis()->SetTitle("integral [a.u.]");
    graph_2->Draw("ap");
    c2->Print("Am-241.pdf");

    TLegend *legend_2 = new TLegend(0.6, 0.15, 0.85, 0.25);
    legend_2->AddEntry(graph_2, "Dati con errore", "P");
    legend_2->SetTextSize(0.04);
    legend_2->SetBorderSize(1);
    legend_2->Draw();

    TCanvas *c3 = new TCanvas();
    graph_3->SetLineColor(kAzure - 3);
    graph_3->SetMarkerColor(4);
    graph_3->SetMarkerStyle(20);
    graph_3->SetMarkerSize(0.7);
    graph_3->GetXaxis()->SetAxisColor(14);
    graph_3->GetYaxis()->SetAxisColor(14);
    graph_3->GetXaxis()->SetTitle("P [mb]");
    graph_3->GetYaxis()->SetTitle("integral [a.u.]");
    graph_3->Draw("ap");
    c3->Print("Cm-244.pdf");

    TLegend *legend_3 = new TLegend(0.6, 0.15, 0.85, 0.25);
    legend_3->AddEntry(graph_3, "Dati con errore", "P");
    legend_3->SetTextSize(0.04);
    legend_3->SetBorderSize(1);
    legend_3->Draw();
}