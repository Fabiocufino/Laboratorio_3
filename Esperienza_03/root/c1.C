void c1()
{
//=========Macro generated from canvas: c1/Circuito 1_3
//=========  (Fri Nov 26 17:39:13 2021) by ROOT version 6.22/00
   TCanvas *c1 = new TCanvas("c1", "Circuito 1_3",34,57,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "This is pad1",0.005,0.12,0.99,0.97);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-2.023287e-11,-532.5323,2.110137e-10,926.1169);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLeftMargin(0.08749478);
   pad1->SetRightMargin(0.01426203);
   pad1->SetTopMargin(0.003648289);
   pad1->SetBottomMargin(0.3732732);
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
   Graph_Graph01001->SetMinimum(11.94242);
   Graph_Graph01001->SetMaximum(920.7953);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("Quantità di carica [uC (?)]");
   Graph_Graph01001->GetXaxis()->SetAxisColor(14);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("V_{pre}^{MAX} [V]");
   Graph_Graph01001->GetYaxis()->SetAxisColor(14);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("ap");
   pad1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: pad2
   TPad *pad2 = new TPad("pad2", "This is pad2",0.005,0.02,0.99,0.37);
   pad2->Draw();
   pad2->cd();
   pad2->Range(-1.25,-0.4455224,11.25,1.23112);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
   
   TF1 *fa11 = new TF1("fa1","sin(x)/x",0,10, TF1::EAddToList::kDefault);
   fa11->SetFillColor(19);
   fa11->SetFillStyle(0);
   fa11->SetLineColor(2);
   fa11->SetLineWidth(2);
   fa11->GetXaxis()->SetLabelFont(42);
   fa11->GetXaxis()->SetTitleOffset(1);
   fa11->GetXaxis()->SetTitleFont(42);
   fa11->GetYaxis()->SetLabelFont(42);
   fa11->GetYaxis()->SetTitleFont(42);
   fa11->Draw("");
   
   TPaveText *pt = new TPaveText(0.4721979,0.9352688,0.5278021,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("sin(x)/x");
   pt->Draw();
   pad2->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
