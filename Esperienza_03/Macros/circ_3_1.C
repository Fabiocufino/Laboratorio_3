void circ_3_1()
{
//=========Macro generated from canvas: c1/Circuito 3_1
//=========  (Sun Dec  5 19:40:24 2021) by ROOT version 6.22/00
   TCanvas *c1 = new TCanvas("c1", "Circuito 3_1",17,43,1332,851);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "This is pad1",0.005,0.02,0.99,0.97);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-0.9050745,-2.597122,11.5999,3.179919);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLeftMargin(0.08037394);
   pad1->SetRightMargin(0.05596981);
   pad1->SetTopMargin(0.003203662);
   pad1->SetBottomMargin(0.4549199);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[10] = {
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10};
   Double_t Graph0_fy1001[10] = {
   0.296,
   0.592,
   0.888,
   1.18,
   1.46,
   1.74,
   2.02,
   2.32,
   2.6,
   2.86};
   Double_t Graph0_fex1001[10] = {
   2.041241e-07,
   2.041241e-07,
   2.041241e-07,
   2.041241e-07,
   2.041241e-07,
   2.041241e-07,
   2.041241e-07,
   2.041241e-07,
   2.041241e-07,
   2.041241e-07};
   Double_t Graph0_fey1001[10] = {
   0.004160417,
   0.008320833,
   0.01359957,
   0.016599,
   0.02713681,
   0.02950943,
   0.03207377,
   0.03498609,
   0.03782415,
   0.04054142};
   TGraphErrors *gre = new TGraphErrors(10,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#6699ff");
   gre->SetLineColor(ci);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,0.09999976,10.9);
   Graph_Graph01001->SetMinimum(0.0309694);
   Graph_Graph01001->SetMaximum(3.161412);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("Pulse Duration");
   Graph_Graph01001->GetXaxis()->SetAxisColor(14);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("V_{out}^{MAX} [mV]");
   Graph_Graph01001->GetYaxis()->SetAxisColor(14);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   
   TF1 *retta1002 = new TF1("retta","pol1",-1.797693e+308,1.797693e+308, TF1::EAddToList::kNo);
   retta1002->SetFillColor(19);
   retta1002->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   retta1002->SetLineColor(ci);
   retta1002->SetLineWidth(2);
   retta1002->SetLineStyle(2);
   retta1002->SetChisquare(3.366399);
   retta1002->SetNDF(8);
   retta1002->GetXaxis()->SetLabelFont(42);
   retta1002->GetXaxis()->SetTitleOffset(1);
   retta1002->GetXaxis()->SetTitleFont(42);
   retta1002->GetYaxis()->SetLabelFont(42);
   retta1002->GetYaxis()->SetTitleFont(42);
   retta1002->SetParameter(0,0.009390481);
   retta1002->SetParError(0,0.005056292);
   retta1002->SetParLimits(0,0,0);
   retta1002->SetParameter(1,0.2890228);
   retta1002->SetParError(1,0.002076588);
   retta1002->SetParLimits(1,0,0);
   retta1002->SetParent(gre);
   gre->GetListOfFunctions()->Add(retta1002);
   gre->Draw("ap");
   
   TPaveStats *ptstats = new TPaveStats(0.5727644,0.4778309,0.933056,0.753429,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(22);
   TText *ptstats_LaTex = ptstats->AddText("Fit lineare sui dati");
   ptstats_LaTex->SetTextSize(0.03622146);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf =3.370000/8");
   ptstats_LaTex = ptstats->AddText("a        = 0.009390#pm0.005056");
   ptstats_LaTex = ptstats->AddText("b        = 0.289023#pm0.002077");
   ptstats_LaTex = ptstats->AddText("Pearson        = 0.999921");
   ptstats_LaTex = ptstats->AddText("T_Student        = 225.281897");
   ptstats_LaTex = ptstats->AddText("#sigma_{post}        = 0.011507");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   
   TLegend *leg = new TLegend(0.1010267,0.8287081,0.3361322,0.9792663,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph0","Dati con errore","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(42);
   entry=leg->AddEntry("retta","Retta Interpolante","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   pad1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: pad2
   TPad *pad2 = new TPad("pad2", "This is pad2",0.005,0.02,0.99,0.37);
   pad2->Draw();
   pad2->cd();
   pad2->Range(-0.8646391,-0.1224449,11.61095,0.06334965);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetLeftMargin(0.07732215);
   pad2->SetRightMargin(0.05698707);
   pad2->SetBottomMargin(0.1664596);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1003[10] = {
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10};
   Double_t Graph0_fy1003[10] = {
   -0.002413323,
   0.004563835,
   0.01154099,
   0.01451815,
   0.005495308,
   -0.003527534,
   -0.01255038,
   -0.001573218,
   -0.01059606,
   -0.0396189};
   Double_t Graph0_fex1003[10] = {
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
   Double_t Graph0_fey1003[10] = {
   0.004160417,
   0.008320833,
   0.01359957,
   0.016599,
   0.02713681,
   0.02950943,
   0.03207377,
   0.03498609,
   0.03782415,
   0.04054142};
   gre = new TGraphErrors(10,Graph0_fx1003,Graph0_fy1003,Graph0_fex1003,Graph0_fey1003);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0066ff");
   gre->SetLineColor(ci);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph01003 = new TH1F("Graph_Graph01003","",100,0.1,10.9);
   Graph_Graph01003->SetMinimum(-0.09151764);
   Graph_Graph01003->SetMaximum(0.04477019);
   Graph_Graph01003->SetDirectory(0);
   Graph_Graph01003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01003->SetLineColor(ci);
   Graph_Graph01003->GetXaxis()->SetLabelFont(42);
   Graph_Graph01003->GetXaxis()->SetLabelSize(0.09);
   Graph_Graph01003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01003->GetXaxis()->SetTitleFont(42);
   Graph_Graph01003->GetYaxis()->SetTitle("Scarti");
   Graph_Graph01003->GetYaxis()->SetAxisColor(14);
   Graph_Graph01003->GetYaxis()->SetLabelFont(42);
   Graph_Graph01003->GetYaxis()->SetLabelSize(0.09);
   Graph_Graph01003->GetYaxis()->SetTitleSize(0.11);
   Graph_Graph01003->GetYaxis()->SetTitleOffset(0.33);
   Graph_Graph01003->GetYaxis()->SetTitleFont(42);
   Graph_Graph01003->GetZaxis()->SetLabelFont(42);
   Graph_Graph01003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01003);
   
   gre->Draw("ap");
   
   TF1 *z1003 = new TF1("z","pol1",0,10, TF1::EAddToList::kDefault);
   z1003->SetFillColor(19);
   z1003->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   z1003->SetLineColor(ci);
   z1003->SetLineWidth(2);
   z1003->SetLineStyle(2);
   z1003->GetXaxis()->SetLabelFont(42);
   z1003->GetXaxis()->SetTitleOffset(1);
   z1003->GetXaxis()->SetTitleFont(42);
   z1003->GetYaxis()->SetLabelFont(42);
   z1003->GetYaxis()->SetTitleFont(42);
   z1003->SetParameter(0,0);
   z1003->SetParError(0,0);
   z1003->SetParLimits(0,0,0);
   z1003->SetParameter(1,0);
   z1003->SetParError(1,0);
   z1003->SetParLimits(1,0,0);
   z1003->Draw("lsame");
   
   leg = new TLegend(0.10866,0.2510823,0.2872791,0.3861472,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.08447205);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph0","Dati con errore","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(42);
   leg->Draw();
   pad2->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
