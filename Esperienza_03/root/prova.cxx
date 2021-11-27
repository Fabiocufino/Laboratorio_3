void prova(){
    TCanvas *c1 = new TCanvas("c1","Canvas Example",200,10,600,480);
 
   // Inside this canvas, we create two pads
   TPad *pad1 = new TPad("pad1","This is pad1",0.15,0.22,0.95,0.97);
   TPad *pad2 = new TPad("pad2","This is pad2",0.05,0.02,0.95,0.47);
   pad1->SetFillColor(11);
   pad2->SetFillColor(11);
   pad1->Draw();
   pad2->Draw();

   pad1->cd();
    
   TF1 *fa1 = new TF1("fa1","sin(x)/x",0,10);
   fa1->Draw();


}