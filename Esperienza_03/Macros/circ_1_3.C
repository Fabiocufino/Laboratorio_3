void circ_1_3()
{
//=========Macro generated from canvas: c1/Circuito 1_3
//=========  (Sat Nov 27 15:56:01 2021) by ROOT version 6.24/02
   TCanvas *c1 = new TCanvas("c1", "Circuito 1_3",326,673,1181,690);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "This is pad1",0.005,0.02,0.99,0.97);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-1.440299e-11,-633.324,2.16484e-10,879.5854);
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
   1.844285e-11,
   3.688569e-11,
   5.532854e-11,
   7.377138e-11,
   9.221423e-11,
   1.106571e-10,
   1.290999e-10,
   1.475428e-10,
   1.659856e-10,
   1.844285e-10};
   Double_t Graph0_fy1001[10] = {
   90,
   174,
   258,
   344,
   424,
   504,
   588,
   688,
   752,
   832};
   Double_t Graph0_fex1001[10] = {
   3.789425e-12,
   3.862854e-12,
   3.982228e-12,
   4.143577e-12,
   4.342226e-12,
   4.573317e-12,
   4.832196e-12,
   5.114647e-12,
   5.416984e-12,
   5.736062e-12};
   Double_t Graph0_fey1001[10] = {
   2.319842,
   2.950943,
   3.761817,
   5.866606,
   6.605533,
   7.400613,
   8.27818,
   11.73321,
   12.30822,
   13.05758};
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
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,0,2.077156e-10);
   Graph_Graph01001->SetMinimum(54.92867);
   Graph_Graph01001->SetMaximum(874.7386);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("Q_{in} [uC]");
   Graph_Graph01001->GetXaxis()->SetRange(3,98);
   Graph_Graph01001->GetXaxis()->SetAxisColor(14);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("V_{pre}^{MAX} [mV]");
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
   retta1002->SetChisquare(0.4800438);
   retta1002->SetNDF(8);
   retta1002->GetXaxis()->SetLabelFont(42);
   retta1002->GetXaxis()->SetTitleOffset(1);
   retta1002->GetXaxis()->SetTitleFont(42);
   retta1002->GetYaxis()->SetLabelFont(42);
   retta1002->GetYaxis()->SetTitleFont(42);
   retta1002->SetParameter(0,8.239461);
   retta1002->SetParError(0,12.98119);
   retta1002->SetParLimits(0,0,0);
   retta1002->SetParameter(1,4.507654e+12);
   retta1002->SetParError(1,1.326742e+11);
   retta1002->SetParLimits(1,0,0);
   retta1002->SetParent(gre);
   gre->GetListOfFunctions()->Add(retta1002);
   gre->Draw("ap");
   
   TPaveStats *ptstats = new TPaveStats(0.08964407,0.7229125,0.4547474,0.9856747,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(22);
   TText *ptstats_LaTex = ptstats->AddText("Fit lineare sui dati");
   ptstats_LaTex->SetTextSize(0.03453446);
   ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf =0.480000/8");
   ptstats_LaTex = ptstats->AddText("a        = 8.239461#pm12.981189");
   ptstats_LaTex = ptstats->AddText("b        = 4.507e+12#pm1.326e+11");
   ptstats_LaTex = ptstats->AddText("Pearson        = 0.999721");
   ptstats_LaTex = ptstats->AddText("T_Student        = 119.748945");
   ptstats_LaTex = ptstats->AddText("#sigma_{post}        = 6.291408");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   
   TLegend *leg = new TLegend(0.672421,0.4787185,0.9399611,0.606865,NULL,"brNDC");
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
   pad2->Range(-1.59464e-11,-65.25166,2.141389e-10,60.88147);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetLeftMargin(0.07732215);
   pad2->SetRightMargin(0.05698707);
   pad2->SetBottomMargin(0.1664596);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1003[10] = {
   1.844285e-11,
   3.688569e-11,
   5.532854e-11,
   7.377138e-11,
   9.221423e-11,
   1.106571e-10,
   1.290999e-10,
   1.475428e-10,
   1.659856e-10,
   1.844285e-10};
   Double_t Graph0_fy1003[10] = {
   -1.373419,
   -0.5073782,
   0.3586631,
   3.224704,
   0.0907456,
   -3.043213,
   -2.177172,
   14.68887,
   -4.445089,
   -7.579048};
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
   17.23822,
   17.66069,
   18.34044,
   19.57748,
   20.65781,
   21.90307,
   23.30189,
   25.86898,
   27.34457,
   28.96623};
   gre = new TGraphErrors(10,Graph0_fx1003,Graph0_fy1003,Graph0_fex1003,Graph0_fey1003);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0066ff");
   gre->SetLineColor(ci);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph01003 = new TH1F("Graph_Graph01003","",100,1.844285e-12,2.01027e-10);
   Graph_Graph01003->SetMinimum(-44.25559);
   Graph_Graph01003->SetMaximum(48.26816);
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
   
   leg = new TLegend(0.1094492,0.7162191,0.2506684,0.8451128,NULL,"brNDC");
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
