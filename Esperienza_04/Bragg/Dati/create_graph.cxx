
void create_graph(const char *filename = "")
{
        const char *name[13] = {"anabragg_bragg_1000_350mb.root",
                                "anabragg_bragg_1000_375mb.root",
                                "anabragg_bragg_1000_400mb.root",
                                "anabragg_bragg_1000_425mb.root",
                                "anabragg_bragg_2000_450mb.root",
                                "anabragg_bragg_2000_500mb.root",
                                "anabragg_bragg_2000_500mb.root",
                                "anabragg_bragg_2000_550mb.root",
                                "anabragg_bragg_2000_600mb.root",
                                "anabragg_bragg_2000_650mb.root",
                                "anabragg_bragg_5000_600mb.root",
                                "anabragg_bragg_500_1.root",
                                "anabragg_bragg_prova.root"};

        const char *press[12] = {"350mb",
                                 "375mb",
                                 "400mb",
                                 "425mb",
                                 "450mb",
                                 "500mb",
                                 "500mb",
                                 "550mb",
                                 "600mb",
                                 "650mb",
                                 "600mb",
                                 "500_1"};

        for (int i = 0; i < 12; i++)
        {

                TFile *f = new TFile(name[i]);
                TTree *t1 = (TTree *)f->Get("nt");
                Float_t integral, vmax;
                t1->SetBranchAddress("vmax", &vmax);
                t1->SetBranchAddress("integral", &integral);

                Int_t nentries = (Int_t)t1->GetEntries();

                TCanvas *c1 = new TCanvas();
                TH2F *hpxpy = new TH2F("hpxpy", "integral vs width", nentries, 1000, 7000, nentries, 0, 240);

                for (Int_t i = 0; i < nentries; i++)
                {
                        t1->GetEntry(i);
                        hpxpy->Fill(integral, vmax);
                }

                hpxpy->SetMarkerColor(kAzure - 3);
                hpxpy->SetMarkerStyle(20);
                hpxpy->SetMarkerSize(0.5);
                hpxpy->SetTitle(press[i]);
                hpxpy->GetXaxis()->SetAxisColor(14);
                hpxpy->GetYaxis()->SetAxisColor(14);
                hpxpy->SetStats(false);

                hpxpy->Draw();

                string temp = press[i];
                string n = "vmax_integral_" + temp + ".pdf";
                c1->Print(n.c_str());
        }
}
