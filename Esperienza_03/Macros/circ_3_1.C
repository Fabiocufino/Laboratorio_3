void circ_3_1()
{
//=========Macro generated from canvas: c1/Circuito 3_1
<<<<<<< HEAD
//=========  (Fri Dec 17 17:29:16 2021) by ROOT version 6.24/02
   TCanvas *c1 = new TCanvas("c1", "Circuito 3_1",230,165,1332,851);
=======
//=========  (Sun Dec  5 19:40:24 2021) by ROOT version 6.22/00
   TCanvas *c1 = new TCanvas("c1", "Circuito 3_1",17,43,1332,851);
>>>>>>> main
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "This is pad1",0.005,0.02,0.99,0.97);
   pad1->Draw();
   pad1->cd();
<<<<<<< HEAD
   pad1->Range(-1.719963e-05,-1.623714,0.0002197899,2.246528);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLeftMargin(0.07660013);
   pad1->SetRightMargin(0.05931071);
   pad1->SetTopMargin(0.007926596);
   pad1->SetBottomMargin(0.4504651);
=======
   pad1->Range(-0.9050745,-2.597122,11.5999,3.179919);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLeftMargin(0.08037394);
   pad1->SetRightMargin(0.05596981);
   pad1->SetTopMargin(0.003203662);
   pad1->SetBottomMargin(0.4549199);
>>>>>>> main
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[10] = {
<<<<<<< HEAD
   1.844285e-05,
   3.688569e-05,
   5.532854e-05,
   7.377138e-05,
   9.221423e-05,
   0.0001106571,
   0.0001290999,
   0.0001475428,
   0.0001659856,
   0.0001844285};
   Double_t Graph0_fy1001[10] = {
   0.222,
   0.44,
   0.664,
   0.88,
   1.1,
   1.31,
   1.52,
   1.72,
   1.92,
   2.14};
   Double_t Graph0_fex1001[10] = {
   4.240402e-07,
   8.480804e-07,
   1.272121e-06,
   1.696161e-06,
   2.120201e-06,
   2.544241e-06,
   2.968281e-06,
   3.392322e-06,
   3.816362e-06,
   4.240402e-06};
   Double_t Graph0_fey1001[10] = {
   0.003399892,
   0.006760671,
   0.01152393,
   0.01352134,
   0.01575331,
   0.01800227,
   0.02762656,
   0.02933303,
   0.03113883,
   0.03322058};
=======
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
>>>>>>> main
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
   
<<<<<<< HEAD
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,9.538001e-07,0.0002057339);
   Graph_Graph01001->SetMinimum(0.1196954);
   Graph_Graph01001->SetMaximum(2.21585);
=======
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,0.09999976,10.9);
   Graph_Graph01001->SetMinimum(0.0309694);
   Graph_Graph01001->SetMaximum(3.161412);
>>>>>>> main
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
<<<<<<< HEAD
   Graph_Graph01001->GetXaxis()->SetTitle("Q_{in} [uC]");
=======
   Graph_Graph01001->GetXaxis()->SetTitle("Pulse Duration");
>>>>>>> main
   Graph_Graph01001->GetXaxis()->SetAxisColor(14);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
<<<<<<< HEAD
   Graph_Graph01001->GetYaxis()->SetTitle("V_{pre}^{MAX} [mV]");
=======
   Graph_Graph01001->GetYaxis()->SetTitle("V_{out}^{MAX} [mV]");
>>>>>>> main
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
<<<<<<< HEAD
   retta1002->SetChisquare(1.251883);
=======
   retta1002->SetChisquare(3.366399);
>>>>>>> main
   retta1002->SetNDF(8);
   retta1002->GetXaxis()->SetLabelFont(42);
   retta1002->GetXaxis()->SetTitleOffset(1);
   retta1002->GetXaxis()->SetTitleFont(42);
   retta1002->GetYaxis()->SetLabelFont(42);
   retta1002->GetYaxis()->SetTitleFont(42);
<<<<<<< HEAD
   retta1002->SetParameter(0,0.007558783);
   retta1002->SetParError(0,0.007242723);
   retta1002->SetParLimits(0,0,0);
   retta1002->SetParameter(1,11707.6);
   retta1002->SetParError(1,155.0133);
=======
   retta1002->SetParameter(0,0.009390481);
   retta1002->SetParError(0,0.005056292);
   retta1002->SetParLimits(0,0,0);
   retta1002->SetParameter(1,0.2890228);
   retta1002->SetParError(1,0.002076588);
>>>>>>> main
   retta1002->SetParLimits(1,0,0);
   retta1002->SetParent(gre);
   gre->GetListOfFunctions()->Add(retta1002);
   gre->Draw("ap");
   
<<<<<<< HEAD
   TPaveStats *ptstats = new TPaveStats(0.09034006,0.727004,0.4811648,0.9857015,"brNDC");
=======
   TPaveStats *ptstats = new TPaveStats(0.5727644,0.4778309,0.933056,0.753429,"brNDC");
>>>>>>> main
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(22);
   TText *ptstats_LaTex = ptstats->AddText("Fit lineare sui dati");
<<<<<<< HEAD
   ptstats_LaTex->SetTextSize(0.03400026);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf =1.250000/8");
   ptstats_LaTex = ptstats->AddText("a        = 0.007559#pm0.007243");
   ptstats_LaTex = ptstats->AddText("b        = 4.507e+12#pm1.326e+11");
   ptstats_LaTex = ptstats->AddText("Pearson        = 0.999857");
   ptstats_LaTex = ptstats->AddText("T_Student        = 167.358806");
   ptstats_LaTex = ptstats->AddText("#sigma_{post}        = 0.011523");
=======
   ptstats_LaTex->SetTextSize(0.03622146);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf =3.370000/8");
   ptstats_LaTex = ptstats->AddText("a        = 0.009390#pm0.005056");
   ptstats_LaTex = ptstats->AddText("b        = 0.289023#pm0.002077");
   ptstats_LaTex = ptstats->AddText("Pearson        = 0.999921");
   ptstats_LaTex = ptstats->AddText("T_Student        = 225.281897");
   ptstats_LaTex = ptstats->AddText("#sigma_{post}        = 0.011507");
>>>>>>> main
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   
<<<<<<< HEAD
   TLegend *leg = new TLegend(0.6666539,0.4912451,0.9139727,0.631426,NULL,"brNDC");
=======
   TLegend *leg = new TLegend(0.1010267,0.8287081,0.3361322,0.9792663,NULL,"brNDC");
>>>>>>> main
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
<<<<<<< HEAD
   pad2->Range(-1.59464e-05,-0.1356141,0.0002141389,0.08015134);
=======
   pad2->Range(-0.8646391,-0.1224449,11.61095,0.06334965);
>>>>>>> main
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetLeftMargin(0.07732215);
   pad2->SetRightMargin(0.05698707);
   pad2->SetBottomMargin(0.1664596);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1003[10] = {
<<<<<<< HEAD
   1.844285e-05,
   3.688569e-05,
   5.532854e-05,
   7.377138e-05,
   9.221423e-05,
   0.0001106571,
   0.0001290999,
   0.0001475428,
   0.0001659856,
   0.0001844285};
   Double_t Graph0_fy1003[10] = {
   -0.001480286,
   0.0005982107,
   0.008676708,
   0.008755205,
   0.0128337,
   0.006912199,
   0.000990696,
   -0.01493081,
   -0.03085231,
   -0.02677381};
=======
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
>>>>>>> main
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
<<<<<<< HEAD
   0.006017098,
   0.01201214,
   0.01883127,
   0.02402428,
   0.02939935,
   0.03480438,
   0.04439471,
   0.04937392,
   0.05446071,
   0.05973464};
=======
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
>>>>>>> main
   gre = new TGraphErrors(10,Graph0_fx1003,Graph0_fy1003,Graph0_fex1003,Graph0_fey1003);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0066ff");
   gre->SetLineColor(ci);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   
<<<<<<< HEAD
   TH1F *Graph_Graph01003 = new TH1F("Graph_Graph01003","",100,1.844285e-06,0.000201027);
   Graph_Graph01003->SetMinimum(-0.09969784);
   Graph_Graph01003->SetMaximum(0.0585748);
=======
   TH1F *Graph_Graph01003 = new TH1F("Graph_Graph01003","",100,0.1,10.9);
   Graph_Graph01003->SetMinimum(-0.09151764);
   Graph_Graph01003->SetMaximum(0.04477019);
>>>>>>> main
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
   
<<<<<<< HEAD
   leg = new TLegend(0.10408,0.209201,0.2720125,0.3268073,NULL,"brNDC");
=======
   leg = new TLegend(0.10866,0.2510823,0.2872791,0.3861472,NULL,"brNDC");
>>>>>>> main
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
