void circ_1_5()
{
//=========Macro generated from canvas: c1/Circuito 1_5
//=========  (Thu Dec  2 21:31:23 2021) by ROOT version 6.24/02
   TCanvas *c1 = new TCanvas("c1", "Circuito 1_5",200,152,1577,779);
   c1->Range(1.084938,-51.70751,6.446446,31.57844);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogx();
   c1->SetLeftMargin(0.06984127);
   c1->SetRightMargin(0.02793651);
   c1->SetTopMargin(0.04111406);
   c1->SetBottomMargin(0.08222812);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[12] = {
   32,
   100,
   316,
   1000,
   3162,
   10000,
   31623,
   100000,
   316228,
   1000000,
   1500000,
   1800000};
   Double_t Graph0_fy1001[12] = {
   21.80353,
   21.63808,
   21.36232,
   18.54004,
   11.87575,
   2.354179,
   -7.224344,
   -16.76677,
   -25.93668,
   -32.73644,
   -36.25827,
   -38.19647};
   Double_t Graph0_fex1001[12] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[12] = {
   0.2662399,
   0.2641917,
   0.2665616,
   0.1826876,
   0.2370094,
   0.1723745,
   0.1839732,
   0.2044973,
   0.3789843,
   0.7569908,
   1.120368,
   0.5781598};
   TGraphErrors *gre = new TGraphErrors(12,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0066ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0066ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,28.8,1979997);
   Graph_Graph01001->SetMinimum(-44.85907);
   Graph_Graph01001->SetMaximum(28.15421);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("f [kHz]");
   Graph_Graph01001->GetXaxis()->SetAxisColor(14);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("A [dB]");
   Graph_Graph01001->GetYaxis()->SetAxisColor(14);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("ap");
   
   Double_t Graph1_fx1[49] = {
   32,
   40.28561,
   50.71658,
   63.84839,
   80.38037,
   101.1929,
   127.3943,
   160.3799,
   201.9064,
   254.185,
   320,
   402.8561,
   507.1658,
   638.4839,
   803.8037,
   1011.929,
   1273.943,
   1603.799,
   2019.064,
   2541.85,
   3200,
   4028.561,
   5071.658,
   6384.839,
   8038.037,
   10119.29,
   12739.43,
   16037.99,
   20190.64,
   25418.5,
   32000,
   40285.61,
   50716.58,
   63848.39,
   80380.37,
   101192.9,
   127394.3,
   160379.9,
   201906.4,
   254185,
   320000,
   402856.1,
   507165.8,
   638483.9,
   803803.7,
   1011929,
   1273943,
   1603799,
   2000000};
   Double_t Graph1_fy1[49] = {
   21.80415,
   21.80188,
   21.79829,
   21.79261,
   21.78361,
   21.76939,
   21.74695,
   21.71163,
   21.65622,
   21.56982,
   21.43632,
   21.23281,
   20.9286,
   20.48627,
   19.8662,
   19.03521,
   17.97667,
   16.69648,
   15.22088,
   13.58761,
   11.83603,
   10.00041,
   8.107426,
   6.176331,
   4.220377,
   2.248402,
   0.2661804,
   -1.72256,
   -3.715433,
   -5.710919,
   -7.708051,
   -9.706212,
   -11.70501,
   -13.70417,
   -15.70353,
   -17.70295,
   -19.7023,
   -21.70144,
   -23.70018,
   -25.69825,
   -27.69523,
   -29.69049,
   -31.68298,
   -33.67111,
   -35.65231,
   -37.62256,
   -39.57551,
   -41.50125,
   -43.30787};
   TGraph *graph = new TGraph(49,Graph1_fx1,Graph1_fy1);
   graph->SetName("Graph1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#6699ff");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(24);
   graph->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph11 = new TH1F("Graph_Graph11","",100,28.8,2199997);
   Graph_Graph11->SetMinimum(-49.81908);
   Graph_Graph11->SetMaximum(28.31535);
   Graph_Graph11->SetDirectory(0);
   Graph_Graph11->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11->SetLineColor(ci);
   Graph_Graph11->GetXaxis()->SetTitle("f [kHz]");
   Graph_Graph11->GetXaxis()->SetAxisColor(14);
   Graph_Graph11->GetXaxis()->SetLabelFont(42);
   Graph_Graph11->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11->GetXaxis()->SetTitleFont(42);
   Graph_Graph11->GetYaxis()->SetTitle("A [dB]");
   Graph_Graph11->GetYaxis()->SetAxisColor(14);
   Graph_Graph11->GetYaxis()->SetLabelFont(42);
   Graph_Graph11->GetYaxis()->SetTitleFont(42);
   Graph_Graph11->GetZaxis()->SetLabelFont(42);
   Graph_Graph11->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph11);
   
   graph->Draw("p");
   
   Double_t Graph2_fx2[12] = {
   32,
   100,
   316,
   1000,
   3162,
   10000,
   31623,
   100000,
   316228,
   1000000,
   1500000,
   1800000};
   Double_t Graph2_fy2[12] = {
   21.80326,
   21.77172,
   21.46803,
   19.22383,
   12.2047,
   2.654931,
   -7.297353,
   -17.29248,
   -27.29201,
   -37.29196,
   -40.81378,
   -42.3974};
   graph = new TGraph(12,Graph2_fx2,Graph2_fy2);
   graph->SetName("Graph2");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph22 = new TH1F("Graph_Graph22","Graph",100,28.8,1979997);
   Graph_Graph22->SetMinimum(-48.81747);
   Graph_Graph22->SetMaximum(28.22332);
   Graph_Graph22->SetDirectory(0);
   Graph_Graph22->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph22->SetLineColor(ci);
   Graph_Graph22->GetXaxis()->SetLabelFont(42);
   Graph_Graph22->GetXaxis()->SetTitleOffset(1);
   Graph_Graph22->GetXaxis()->SetTitleFont(42);
   Graph_Graph22->GetYaxis()->SetLabelFont(42);
   Graph_Graph22->GetYaxis()->SetTitleFont(42);
   Graph_Graph22->GetZaxis()->SetLabelFont(42);
   Graph_Graph22->GetZaxis()->SetTitleOffset(1);
   Graph_Graph22->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph22);
   
   graph->Draw("l");
   TLine *line = new TLine(1109.326,-44,1109.326,28);
   line->SetLineColor(38);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(261.448,-31.42321,"#it{f_{t}}#approx 1109.3");
   tex->SetTextAlign(13);
   tex->SetTextSize(0.04564315);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.6189968,0.746888,0.9519744,0.9377593,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph0","Dati Sperimentali con errore","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0066ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","Dati Simulati","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#6699ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2","Previsione Teorica","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
