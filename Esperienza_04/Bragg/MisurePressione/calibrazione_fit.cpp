void calibrazione_fit(){

    TTree *nt = new TTree("nt", "nt");
    nt->ReadFile("calibrazione.txt");
    nt->Draw("energia:errenergia:vmedio:errvmedio", "", "goff");

    TGraphErrors *graph_1 = new TGraphErrors(nt->GetSelectedRows(), nt->GetVal(2), nt->GetVal(0), nt->GetVal(3), nt->GetVal(1));


    TCanvas *c1 = new TCanvas();
    graph_1->SetLineColor(kAzure - 3);
    graph_1->SetMarkerColor(4);
    graph_1->SetMarkerStyle(20);
    graph_1->SetMarkerSize(0.7);
    graph_1->GetXaxis()->SetAxisColor(14);
    graph_1->GetYaxis()->SetAxisColor(14);
    graph_1->GetXaxis()->SetTitle("integral [a.u.]");
    graph_1->GetYaxis()->SetTitle("Energy [KeV]");
    graph_1->Draw("ap");

    TLegend *legend_1 = new TLegend(0.6, 0.15, 0.85, 0.25);
    legend_1->AddEntry(graph_1, "Dati con errore", "P");
    legend_1->SetTextSize(0.04);
    legend_1->SetBorderSize(1);
    legend_1->Draw();

}