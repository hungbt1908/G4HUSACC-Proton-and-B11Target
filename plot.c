# include <string> 

void plot()
{
    gROOT->Reset();
	gROOT->SetStyle("Plain");

	TFile* f = new TFile("output.root", "READ");

	// list all Tree and Historgram
	f->ls();

    TTree* tree = (TTree*)f->Get("DetResults0;1");

    tree->Print();


    double eSum;
    double eProton;
    double eAlpha;
    double eBe8;
	double eB11;
	double eB10;
	double eNeutron;
    double eGamma;
    double eOther;

    tree->SetBranchAddress("row_wise_branch.ESum", &eSum);
    tree->SetBranchAddress("row_wise_branch.EProton", &eProton);
    tree->SetBranchAddress("row_wise_branch.EAlpha", &eAlpha);
    tree->SetBranchAddress("row_wise_branch.EBe8", &eBe8);
    tree->SetBranchAddress("row_wise_branch.EGamma", &eGamma);
	tree->SetBranchAddress("row_wise_branch.EB11", &eB11);
    tree->SetBranchAddress("row_wise_branch.EB10", &eB10);
    tree->SetBranchAddress("row_wise_branch.ENeutron", &eNeutron);
    tree->SetBranchAddress("row_wise_branch.EOther", &eOther);

    int entries;
    entries = tree->GetEntries();
    cout << "Number of entries: " << entries << endl; 

    TH1D* Total_Hist = new TH1D("Total_Hist", "Total Energy Spectrum", 8000, 0., 8.);
    TH1D* Proton_Hist = new TH1D("Proton_Hist", "Proton's Energy Spectrum", 8000, 0., 8.);
    TH1D* Alpha_Hist = new TH1D("Alpha_Hist", "Alpha's Energy Spectrum", 8000, 0., 8.);
    TH1D* Be8_Hist = new TH1D("Be8_Hist", "Be8's Energy Spectrum", 8000, 0., 8.);
    TH1D* Gamma_Hits = new TH1D("Gamma_Hits", "Gamma's Energy Spectrum", 8000, 0., 8.);
    TH1D* B11_Hits = new TH1D("B11_Hits", "B11's Energy Spectrum", 8000, 0., 8.);
    TH1D* B10_Hist = new TH1D("B10_Hist", "B10's Energy Spectrum", 8000, 0., 8.);
	TH1D* Neutron_Hist = new TH1D("Neutron_Hist", "Neutron's Energy Spectrum", 8000, 0., 8.);
    TH1D* Others_Hist = new TH1D("Others_Hist", "Others Energy Spectrum", 8000, 0., 8.);

    for(int i=0; i<entries; ++i)
    {
        tree->GetEntry(i);
	
		// fill to histograms
        Total_Hist->Fill(eSum);
        Proton_Hist->Fill(eProton);
        Alpha_Hist->Fill(eAlpha);
        Be8_Hist->Fill(eBe8);
        Gamma_Hits->Fill(eGamma);
		B11_Hits->Fill(eB11);
        B10_Hist->Fill(eB10);
        Neutron_Hist->Fill(eNeutron);
        Others_Hist->Fill(eOther);
    }

   // Draw
	Double_t w = 1920;
   	Double_t h = 1080;

	// canvas 1
	TCanvas* c1 = new TCanvas("c1", "c1", w, h);
   	c1->SetWindowSize(w + (w - c1->GetWw()), h + (h - c1->GetWh()));
	// cavans 2
	TCanvas* c2 = new TCanvas("c2", "c2", w, h);
   	c2->SetWindowSize(w + (w - c2->GetWw()), h + (h - c2->GetWh()));
	// cavans 3
	TCanvas* c3 = new TCanvas("c3", "c3", w, h);
   	c3->SetWindowSize(w + (w - c3->GetWw()), h + (h - c3->GetWh()));
	// cavans 4
	TCanvas* c4 = new TCanvas("c4", "c4", w, h);
   	c4->SetWindowSize(w + (w - c4->GetWw()), h + (h - c4->GetWh()));
	// cavans 5
	TCanvas* c5 = new TCanvas("c5", "c5", w, h);
   	c5->SetWindowSize(w + (w - c5->GetWw()), h + (h - c5->GetWh()));
	// cavans 6
	TCanvas* c6 = new TCanvas("c6", "c6", w, h);
   	c6->SetWindowSize(w + (w - c6->GetWw()), h + (h - c6->GetWh()));
	// cavans 7
	TCanvas* c7 = new TCanvas("c7", "c7", w, h);
   	c7->SetWindowSize(w + (w - c7->GetWw()), h + (h - c7->GetWh()));
	// cavans 8
	TCanvas* c8 = new TCanvas("c8", "c8", w, h);
   	c8->SetWindowSize(w + (w - c8->GetWw()), h + (h - c8->GetWh()));
	// cavans 9
	TCanvas* c9 = new TCanvas("c9", "c9", w, h);
   	c9->SetWindowSize(w + (w - c9->GetWw()), h + (h - c9->GetWh()));
	
	// Total_Hist plot
	c1->cd();
	gPad->SetLogy(1);
	Total_Hist->SetTitle("Total Energy Spectrum");
	Total_Hist->GetXaxis()->CenterTitle(true);
	Total_Hist->GetYaxis()->CenterTitle(true);
	Total_Hist->GetXaxis()->SetTitle("MeV");
	Total_Hist->GetYaxis()->SetTitle("Count");
	Total_Hist->Draw();
	Total_Hist->SetLineColor(kRed);
	c1->Print("Total Energy.pdf)","Title:Total Energy Spectrum");

	// Proton_Hist
	c2->cd();
	gPad->SetLogy(1);
	Proton_Hist->SetTitle("Proton's Energy Spectrum");
	Proton_Hist->GetXaxis()->CenterTitle(true);
	Proton_Hist->GetYaxis()->CenterTitle(true);
	Proton_Hist->GetXaxis()->SetTitle("MeV");
	Proton_Hist->GetYaxis()->SetTitle("Count");
	Proton_Hist->Draw("HIST");
	c2->Print("Proton_Hist.pdf)","Title:Proton's Energy Spectrum");

	// Alpha_Hist
	c3->cd();
	gPad->SetLogy(1);
	Alpha_Hist->SetTitle("Alpha's Energy Spectrum");
	Alpha_Hist->GetXaxis()->CenterTitle(true);
	Alpha_Hist->GetYaxis()->CenterTitle(true);
	Alpha_Hist->GetXaxis()->SetTitle("MeV");
	Alpha_Hist->GetYaxis()->SetTitle("Count");
	Alpha_Hist->Draw("HIST");
	c3->Print("Alpha_Hist.pdf)","Title:Alpha's Energy Spectrum");

	// Be8_Hist
	c4->cd();
	gPad->SetLogy(1);
	Be8_Hist->SetTitle("Be8's Energy Spectrum");
	Be8_Hist->GetXaxis()->CenterTitle(true);
	Be8_Hist->GetYaxis()->CenterTitle(true);
	Be8_Hist->GetXaxis()->SetTitle("MeV");
	Be8_Hist->GetYaxis()->SetTitle("Count");
	Be8_Hist->Draw("HIST");
	c4->Print("Be8_Hist.pdf)","Title:Be8's Energy Spectrum");

	// Gamma_Hits
	c5->cd();
	gPad->SetLogy(1);
	Gamma_Hits->SetTitle("Gamma's Energy Spectrum");
	Gamma_Hits->GetXaxis()->CenterTitle(true);
	Gamma_Hits->GetYaxis()->CenterTitle(true);
	Gamma_Hits->GetXaxis()->SetTitle("MeV");
	Gamma_Hits->GetYaxis()->SetTitle("Count");
	Gamma_Hits->Draw("HIST");
	c5->Print("Gamma_Hits.pdf)","Title:Gamma's Energy Spectrum");

	// B11_Hits
	c6->cd();
	gPad->SetLogy(1);
	B11_Hits->SetTitle("B11's Energy Spectrum");
	B11_Hits->GetXaxis()->CenterTitle(true);
	B11_Hits->GetYaxis()->CenterTitle(true);
	B11_Hits->GetXaxis()->SetTitle("MeV");
	B11_Hits->GetYaxis()->SetTitle("Count");
	B11_Hits->Draw("HIST");
	c6->Print("B11_Hits.pdf)","Title:B11's Energy Spectrum");
	
	// B10_Hist
	c7->cd();
	gPad->SetLogy(1);
	B10_Hist->SetTitle("B10's Energy Spectrum");
	B10_Hist->GetXaxis()->CenterTitle(true);
	B10_Hist->GetYaxis()->CenterTitle(true);
	B10_Hist->GetXaxis()->SetTitle("MeV");
	B10_Hist->GetYaxis()->SetTitle("Count");
	B10_Hist->Draw("HIST");
	c7->Print("B10_Hist.pdf)","Title:B10's Energy Spectrum");
	
	// Neutron_Hist
	c8->cd();
	gPad->SetLogy(1);
	Neutron_Hist->SetTitle("B11's Energy Spectrum");
	Neutron_Hist->GetXaxis()->CenterTitle(true);
	Neutron_Hist->GetYaxis()->CenterTitle(true);
	Neutron_Hist->GetXaxis()->SetTitle("MeV");
	Neutron_Hist->GetYaxis()->SetTitle("Count");
	Neutron_Hist->Draw("HIST");
	c8->Print("Neutron_Hist.pdf)","Title:B11's Energy Spectrum");
	
	// Others_Hist
	c9->cd();
	gPad->SetLogy(1);
	Others_Hist->SetTitle("Others Energy Spectrum");
	Others_Hist->GetXaxis()->CenterTitle(true);
	Others_Hist->GetYaxis()->CenterTitle(true);
	Others_Hist->GetXaxis()->SetTitle("MeV");
	Others_Hist->GetYaxis()->SetTitle("Count");
	Others_Hist->Draw("HIST");
	c9->Print("Others_Hist.pdf)","Title:Others Energy Spectrum");

}