{

	TFile *f1 = new TFile("../TP_AIR_out.root", "READ");
	TFile *f2 = new TFile("../TP_AIR_no_table_out.root", "READ");
	
	TH1D *h_Eabs1 = (TH1D *)f1->Get("EAbs");
	h_Eabs1->Scale(1/h_Eabs1->GetEntries());
	TH1D *h_Eabs_diff = (TH1D *)h_Eabs1->Clone("EAbs_diff");
	TH1D *h_Eabs2 = (TH1D *)f2->Get("EAbs");
	h_Eabs2->Scale(1/h_Eabs2->GetEntries());
	h_Eabs2->SetLineColor(kRed);
	
	TCanvas *c = new TCanvas("Comp_table", "Comp_table", 600, 600);
	h_Eabs1->Draw();
	h_Eabs2->Draw("SAME");
	
	TCanvas *c2 = new TCanvas("Comp_table_diff", "Comp_table_diff", 600, 600);
	for(int i = 1; i <= h_Eabs_diff->GetNbinsX(); i++) {
		h_Eabs_diff->SetBinContent(i, h_Eabs1->GetBinContent(i)-h_Eabs2->GetBinContent(i));
	}
	h_Eabs_diff->Draw();
	
	
}