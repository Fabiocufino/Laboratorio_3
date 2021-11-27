void circ_1_4()
{
//=========Macro generated from canvas: c1/Circuito 1_3
//=========  (Sat Nov 27 17:14:36 2021) by ROOT version 6.24/02
   TCanvas *c1 = new TCanvas("c1", "Circuito 1_3",140,99,1332,851);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "This is pad1",0.005,0.02,0.99,0.97);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-20.06447,-220.2667,256.8835,409.7162);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLeftMargin(0.07965345);
   pad1->SetRightMargin(0.05625739);
   pad1->SetTopMargin(0.01174971);
   pad1->SetBottomMargin(0.4504651);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[8] = {
   24,
   46,
   66,
   86,
   118,
   142,
   176,
   218};
   Double_t Graph0_fy1001[8] = {
   368,
   320,
   280,
   240,
   192,
   164,
   128,
   96};
   Double_t Graph0_fex1001[8] = {
   2.062296,
   2.117561,
   2.195465,
   2.296969,
   2.501053,
   2.681654,
   2.968681,
   3.360843};
   Double_t Graph0_fey1001[8] = {
   6.08114,
   5.659211,
   5.331666,
   5.030573,
   4.711291,
   4.549842,
   4.37313,
   4.248419};
   TGraphErrors *gre = new TGraphErrors(8,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
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
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,1.99539,241.3032);
   Graph_Graph01001->SetMinimum(63.51862);
   Graph_Graph01001->SetMaximum(402.3141);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("t [us]");
   Graph_Graph01001->GetXaxis()->SetAxisColor(14);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("Voltaggio [mV]");
   Graph_Graph01001->GetYaxis()->SetAxisColor(14);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   
   TF1 *expon1002 = new TF1("*expon",-1.797693e+308,1.797693e+308,3);
    //The original function : expon had originally been created by:
    //TF1 *expon = new TF1("expon",expon,-1.797693e+308,1.797693e+308,3, 1, TF1::EAddToList::kNo);
   expon1002->SetRange(-1.797693e+308,1.797693e+308);
   expon1002->SetName("expon");
   expon1002->SetTitle("expon");
   expon1002->SetSavedPoint(0,nan);
   expon1002->SetSavedPoint(1,0);
   expon1002->SetSavedPoint(2,0);
   expon1002->SetSavedPoint(3,0);
   expon1002->SetSavedPoint(4,0);
   expon1002->SetSavedPoint(5,0);
   expon1002->SetSavedPoint(6,0);
   expon1002->SetSavedPoint(7,0);
   expon1002->SetSavedPoint(8,0);
   expon1002->SetSavedPoint(9,0);
   expon1002->SetSavedPoint(10,0);
   expon1002->SetSavedPoint(11,0);
   expon1002->SetSavedPoint(12,0);
   expon1002->SetSavedPoint(13,0);
   expon1002->SetSavedPoint(14,0);
   expon1002->SetSavedPoint(15,0);
   expon1002->SetSavedPoint(16,0);
   expon1002->SetSavedPoint(17,0);
   expon1002->SetSavedPoint(18,0);
   expon1002->SetSavedPoint(19,0);
   expon1002->SetSavedPoint(20,0);
   expon1002->SetSavedPoint(21,0);
   expon1002->SetSavedPoint(22,0);
   expon1002->SetSavedPoint(23,0);
   expon1002->SetSavedPoint(24,0);
   expon1002->SetSavedPoint(25,0);
   expon1002->SetSavedPoint(26,0);
   expon1002->SetSavedPoint(27,0);
   expon1002->SetSavedPoint(28,0);
   expon1002->SetSavedPoint(29,0);
   expon1002->SetSavedPoint(30,0);
   expon1002->SetSavedPoint(31,0);
   expon1002->SetSavedPoint(32,0);
   expon1002->SetSavedPoint(33,0);
   expon1002->SetSavedPoint(34,0);
   expon1002->SetSavedPoint(35,0);
   expon1002->SetSavedPoint(36,0);
   expon1002->SetSavedPoint(37,0);
   expon1002->SetSavedPoint(38,0);
   expon1002->SetSavedPoint(39,0);
   expon1002->SetSavedPoint(40,0);
   expon1002->SetSavedPoint(41,0);
   expon1002->SetSavedPoint(42,0);
   expon1002->SetSavedPoint(43,0);
   expon1002->SetSavedPoint(44,0);
   expon1002->SetSavedPoint(45,0);
   expon1002->SetSavedPoint(46,0);
   expon1002->SetSavedPoint(47,0);
   expon1002->SetSavedPoint(48,0);
   expon1002->SetSavedPoint(49,0);
   expon1002->SetSavedPoint(50,0);
   expon1002->SetSavedPoint(51,0);
   expon1002->SetSavedPoint(52,0);
   expon1002->SetSavedPoint(53,0);
   expon1002->SetSavedPoint(54,0);
   expon1002->SetSavedPoint(55,0);
   expon1002->SetSavedPoint(56,0);
   expon1002->SetSavedPoint(57,0);
   expon1002->SetSavedPoint(58,0);
   expon1002->SetSavedPoint(59,0);
   expon1002->SetSavedPoint(60,0);
   expon1002->SetSavedPoint(61,0);
   expon1002->SetSavedPoint(62,0);
   expon1002->SetSavedPoint(63,0);
   expon1002->SetSavedPoint(64,0);
   expon1002->SetSavedPoint(65,0);
   expon1002->SetSavedPoint(66,0);
   expon1002->SetSavedPoint(67,0);
   expon1002->SetSavedPoint(68,0);
   expon1002->SetSavedPoint(69,0);
   expon1002->SetSavedPoint(70,0);
   expon1002->SetSavedPoint(71,0);
   expon1002->SetSavedPoint(72,0);
   expon1002->SetSavedPoint(73,0);
   expon1002->SetSavedPoint(74,0);
   expon1002->SetSavedPoint(75,0);
   expon1002->SetSavedPoint(76,0);
   expon1002->SetSavedPoint(77,0);
   expon1002->SetSavedPoint(78,0);
   expon1002->SetSavedPoint(79,0);
   expon1002->SetSavedPoint(80,0);
   expon1002->SetSavedPoint(81,0);
   expon1002->SetSavedPoint(82,0);
   expon1002->SetSavedPoint(83,0);
   expon1002->SetSavedPoint(84,0);
   expon1002->SetSavedPoint(85,0);
   expon1002->SetSavedPoint(86,0);
   expon1002->SetSavedPoint(87,0);
   expon1002->SetSavedPoint(88,0);
   expon1002->SetSavedPoint(89,0);
   expon1002->SetSavedPoint(90,0);
   expon1002->SetSavedPoint(91,0);
   expon1002->SetSavedPoint(92,0);
   expon1002->SetSavedPoint(93,0);
   expon1002->SetSavedPoint(94,0);
   expon1002->SetSavedPoint(95,0);
   expon1002->SetSavedPoint(96,0);
   expon1002->SetSavedPoint(97,0);
   expon1002->SetSavedPoint(98,0);
   expon1002->SetSavedPoint(99,0);
   expon1002->SetSavedPoint(100,0);
   expon1002->SetSavedPoint(101,-1.797693e+308);
   expon1002->SetSavedPoint(102,1.797693e+308);
   expon1002->SetFillColor(19);
   expon1002->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   expon1002->SetLineColor(ci);
   expon1002->SetLineWidth(2);
   expon1002->SetLineStyle(2);
   expon1002->SetChisquare(0.4814163);
   expon1002->SetNDF(5);
   expon1002->GetXaxis()->SetLabelFont(42);
   expon1002->GetXaxis()->SetTitleOffset(1);
   expon1002->GetXaxis()->SetTitleFont(42);
   expon1002->GetYaxis()->SetLabelFont(42);
   expon1002->GetYaxis()->SetTitleFont(42);
   expon1002->SetParameter(0,1.235166);
   expon1002->SetParError(0,4.392148);
   expon1002->SetParLimits(0,0,0);
   expon1002->SetParameter(1,-843.3516);
   expon1002->SetParError(1,509.967);
   expon1002->SetParLimits(1,0,0);
   expon1002->SetParameter(2,143.6151);
   expon1002->SetParError(2,3.930234);
   expon1002->SetParLimits(2,0,0);
   expon1002->SetParent(gre);
   gre->GetListOfFunctions()->Add(expon1002);
   gre->Draw("ap");
   
   TPaveStats *ptstats = new TPaveStats(0.5506278,0.8021919,0.9529026,0.9984453,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(22);
   TText *ptstats_LaTex = ptstats->AddText("Fit esponenziale sui dati");
   ptstats_LaTex->SetTextSize(0.03611062);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf =0.480000/5");
   ptstats_LaTex = ptstats->AddText("a        = 1.235166#pm4.392148");
   ptstats_LaTex = ptstats->AddText("b        = -843.351570#pm509.966954");
   ptstats_LaTex = ptstats->AddText("c        = 143.615090#pm3.930234");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   
   TLegend *leg = new TLegend(0.1025533,0.4874219,0.3178123,0.621231,NULL,"brNDC");
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

   ci = TColor::GetColor("#0066ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(42);
   entry=leg->AddEntry("expon","V(t) = a e^{-(b+t)/c}","L");

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
   pad2->Range(-15.9828,-18.58728,252.7217,13.20401);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetLeftMargin(0.07660013);
   pad2->SetRightMargin(0.05702072);
   pad2->SetTopMargin(0.0401937);
   pad2->SetBottomMargin(0.1676928);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1003[8] = {
   24,
   46,
   66,
   86,
   118,
   142,
   176,
   218};
   Double_t Graph0_fy1003[8] = {
   -3.072181,
   1.631551,
   3.019191,
   -0.9735296,
   -0.8416297,
   0.8359849,
   -0.7679565,
   -0.1167522};
   Double_t Graph0_fex1003[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1003[8] = {
   8.085404,
   7.352729,
   6.808488,
   6.337259,
   5.785729,
   5.475704,
   5.119503,
   4.807121};
   gre = new TGraphErrors(8,Graph0_fx1003,Graph0_fy1003,Graph0_fex1003,Graph0_fey1003);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0066ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0066ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph01003 = new TH1F("Graph_Graph01003","",100,4.6,237.4);
   Graph_Graph01003->SetMinimum(-13.25611);
   Graph_Graph01003->SetMaximum(11.9262);
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
   
   TF1 *z1003 = new TF1("z","pol1",0,300, TF1::EAddToList::kDefault);
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
   
   leg = new TLegend(0.7582535,0.7868558,0.928476,0.9182982,NULL,"brNDC");
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

   ci = TColor::GetColor("#0066ff");
   entry->SetMarkerColor(ci);
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
