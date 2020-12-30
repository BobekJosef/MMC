void PlotMaxInt() {
  ifstream inFile1;
  inFile1.open("protons.MaxSum.txt");
  ifstream inFile2;
  inFile2.open("pions.MaxSum.txt");
  ifstream inFile3;
  inFile3.open("kaons.MaxSum.txt");
  double alpha=1.0;


  int color[3]={622,632,1};
  if (!inFile1||!inFile2||!inFile3) {cerr << "Unable to open file"; exit(EXIT_FAILURE);}
  gStyle->SetOptStat(0);
  double Volume=4263.66910*  7; //R=7fm
  double Data[4]={0,0,0,0};
  TCanvas *c = new TCanvas("c","GraphDraw",0,0,600,500);

  int l = 0;
  int k = 0;
  
  TGraph *MaxPr = new TGraph();
  TGraph *MaxPi = new TGraph();
  TGraph *MaxKa = new TGraph();
  auto *IntPr = new TGraphErrors();
  auto *IntPi = new TGraphErrors();
  auto *IntKa = new TGraphErrors();
  TGraph *IntPr2 = new TGraph();
  TGraph *IntPi2 = new TGraph();
  TGraph *IntKa2 = new TGraph();

  

  while (!inFile1.eof())
  {
  for(int i=0;i<4;i++)
  inFile1 >> Data[i];
  Data[2]=(Data[2]*Volume)/Data[0];
  Data[3]=Volume*sqrt(Data[3]/(Data[0]*(Data[0]-1)));
  MaxPr->SetPoint(l,Data[0],Data[1]);
  IntPr->SetPoint(k,Data[0],Data[2]);
  IntPr2->SetPoint(k,Data[0],Data[2]);
  IntPr->SetPointError(k,0,Data[3]);
  l++;
  k++;
  }
  IntPr->RemovePoint(k-1);
  IntPr2->RemovePoint(k-1);
  l=0;
  k=0;
  while (!inFile2.eof())
  {
  for(int i=0;i<4;i++)
  inFile2 >> Data[i];
  Data[2]=(Data[2]*Volume)/Data[0];
  Data[3]=Volume*sqrt(Data[3]/(Data[0]*(Data[0]-1)));
  MaxPi->SetPoint(l,Data[0],Data[1]);
  IntPi->SetPoint(k,Data[0],Data[2]);
  IntPi2->SetPoint(k,Data[0],Data[2]);
  IntPi->SetPointError(k,0,Data[3]);
  l++;
  k++;
  }
  IntPi->RemovePoint(k-1);
  IntPi2->RemovePoint(k-1);
  l=0;
  k=0;
  while (!inFile3.eof())
  {
  for(int i=0;i<4;i++)
  inFile3 >> Data[i];
  Data[2]=(Data[2]*Volume)/Data[0];
  Data[3]=Volume*sqrt(Data[3]/(Data[0]*(Data[0]-1)));
  MaxKa->SetPoint(l,Data[0],Data[1]);
  IntKa->SetPoint(k,Data[0],Data[2]);
  IntKa2->SetPoint(k,Data[0],Data[2]);
  IntKa->SetPointError(k,0,Data[3]);
  l++;
  k++;
  }
  IntKa->RemovePoint(k-1);
  IntKa2->RemovePoint(k-1);

  //MaxPr->SetTitle("Maximum value of proton PDF");
  MaxPr->GetYaxis()->SetTitle("max");
  MaxPr->GetXaxis()->SetTitle("iterations");
  MaxPr->GetYaxis()->SetTitleOffset(1.5);
  MaxPr->SetLineColor(color[1]);
  MaxPr->SetLineWidth(2);
  //MaxPi->SetTitle("Maximum value of pion PDF");
  MaxPi->GetYaxis()->SetTitle("max");
  MaxPi->GetXaxis()->SetTitle("iterations");
  MaxPi->GetYaxis()->SetTitleOffset(1.5);
  MaxPi->SetLineColor(color[1]);
  MaxPi->SetLineWidth(2);
  //MaxKa->SetTitle("Maximum value of kaon PDF");
  MaxKa->GetYaxis()->SetTitle("max");
  MaxKa->GetXaxis()->SetTitle("iterations");
  MaxKa->GetYaxis()->SetTitleOffset(1.5);
  MaxKa->SetLineColor(color[1]);
  MaxKa->SetLineWidth(2);

  //IntPr->SetTitle("Integral of proton PDF");
  IntPr->GetYaxis()->SetTitle("N_{p}");
  IntPr->GetXaxis()->SetTitle("iterations");
  IntPr->GetYaxis()->SetTitleOffset(1.5);
  IntPr2->SetLineColor(color[2]);
  IntPr->SetFillColor(color[0]);
  IntPr2->SetLineWidth(1);
  //IntPi->SetTitle("Integral of pion PDF");
  IntPi->GetYaxis()->SetTitle("N_{#pi}");
  IntPi->GetXaxis()->SetTitle("iterations");
  IntPi->GetYaxis()->SetTitleOffset(1.5);
  IntPi2->SetLineColor(color[2]);
  IntPi->SetFillColor(color[0]);
  IntPi2->SetLineWidth(1);
  //IntKa->SetTitle("Integral of kaon PDF");
  IntKa->GetYaxis()->SetTitle("N_{K}");
  IntKa->GetXaxis()->SetTitle("iterations");
  IntKa->GetYaxis()->SetTitleOffset(1.5);
  IntKa2->SetLineColor(color[2]);
  IntKa->SetFillColor(color[0]);
  IntKa2->SetLineWidth(1);

  inFile1.close();
  inFile2.close();
  inFile3.close();
  
  TPaveText *pt = new TPaveText(0.75,0.15,0.85,0.25,"NDC");
  pt->SetFillColor(0);
  pt->SetBorderSize(0);
  pt->AddText(Form("#alpha= %.1f",alpha));


  MaxPr->Draw("AL");
  pt->Draw();
  c->Print("plots/MaxProtons.pdf");
  MaxPi->Draw("AL");
  pt->Draw();
  c->Print("plots/MaxPions.pdf");
  MaxKa->Draw("AL");
  pt->Draw();
  c->Print("plots/MaxKaons.pdf");
  IntPr->Draw("AL3");
  IntPr2->Draw("SAME");
  pt->Draw();
  c->Print("plots/IntegralProtons.pdf");
  IntPi->Draw("AL3");
  IntPi2->Draw("SAME");
  pt->Draw();
  c->Print("plots/IntegralPions.pdf");
  IntKa->Draw("AL3");
  IntKa2->Draw("SAME");
  pt->Draw();
  c->Print("plots/IntegralKaons.pdf");
}


////////////


void PlotPt(){
  ifstream inFile1;
  inFile1.open("protons.txt");
  ifstream inFile2;
  inFile2.open("pions.txt");
  ifstream inFile3;
  inFile3.open("kaons.txt");
  ifstream inFileN;
  inFileN.open("NumberOfEvents.txt");
  int color[3]={419,632,602};
  if (!inFile1||!inFile2||!inFile3||!inFileN) {cerr << "Unable to open file"; exit(EXIT_FAILURE);}
  gStyle->SetOptStat(0);
  double data[100];
  int events[3];
  int tmpi;
  string line;
  double norm;
  double alpha=0.5;

  TCanvas *c = new TCanvas("c","GraphDraw",0,0,800,500);
  TH1::SetDefaultSumw2(kTRUE);

  TH1* protons = new TH1D("Protons", "", 100, 0.0, 3);
  TH1* pions = new TH1D("Pions", "", 100, 0.0, 3);
  TH1* kaons = new TH1D("Kaons", "", 100, 0.0, 3);

  cout<<"Number of events"<<endl;
  for(int i=0; i<3; i++)
  {
    getline(inFileN,line); cout<<line<<endl;
    tmpi=0;
    while(line[tmpi]!=' ')
      tmpi++;
    events[i]=stoi(line.substr(tmpi));
  }

  for(int i=0;i<100;i++)
  {
    inFile1 >> data[i];
    data[i]=data[i]/events[0];
    protons->SetBinContent(i,data[i]);
  }

  for(int i=0;i<100;i++)
  {
    inFile2 >> data[i];
    data[i]=data[i]/events[1];
    pions->SetBinContent(i,data[i]);
  }
  

  for(int i=0;i<100;i++)
  {
    inFile3 >> data[i];
    data[i]=data[i]/events[2];
    kaons->SetBinContent(i,data[i]);
  }

  inFile1.close();
  inFile2.close();
  inFile3.close();
  inFileN.close();


  TF2 *f1pr=new TF2("I0pr", "ROOT::Math::cyl_bessel_i(0,(x/0.12)*sinh(1*y/7))");    //PROTONS
  //f1pr->SetParameter(0,alpha);
  TF2 *f2pr=new TF2("K1pr", "ROOT::Math::cyl_bessel_k(1,(sqrt((x*x)+(0.93827*0.93827))/0.12)*cosh(1*y/7))");
  //f2pr->SetParameter(0,alpha);
  TF2 *fpr=new TF2("fpr","130.162739*8*6*(2/3.1415926535)*x*sqrt((x*x)+(0.93827*0.93827))*y*I0pr*K1pr");
  TH1* protonsSEF = new TH1D("ProtonsSEF", "p_{T} spectra", 100, 0.0, 3);
  for(int i=0;i<100;i++)
      protonsSEF->SetBinContent(i,fpr->Integral(i*0.03, (i+1)*0.03, 0, 7)); //R=7
  protonsSEF->SetLineColor(616);
  protonsSEF->SetLineWidth(2);

  TF2 *f1pi=new TF2("I0pi", "ROOT::Math::cyl_bessel_i(0,(x/0.12)*sinh(1*y/7))");    //PIONS
  //f1pi->SetParameter(0,alpha);
  TF2 *f2pi=new TF2("K1pi", "ROOT::Math::cyl_bessel_k(1,(sqrt((x*x)+(0.13957*0.13957))/0.12)*cosh(1*y/7))");
  //f2pi->SetParameter(0,alpha);
  TF2 *fpi=new TF2("fpi","130.162739*8*6*(1/3.1415926535)*x*sqrt((x*x)+(0.13957*0.13957))*y*I0pi*K1pi");
  TH1* pionsSEF = new TH1D("PionsSEF", "p_{T} spectra", 100, 0.0, 3);
  for(int i=0;i<100;i++)
      pionsSEF->SetBinContent(i,fpi->Integral(i*0.03, (i+1)*0.03, 0, 7)); //R=7
  pionsSEF->SetLineColor(432);
  pionsSEF->SetLineWidth(2);

  TF2 *f1ka=new TF2("I0ka", "ROOT::Math::cyl_bessel_i(0,(x/0.12)*sinh(1*y/7))");    //KAONS            
  //f1ka->SetParameter(0,alpha);        
  TF2 *f2ka=new TF2("K1ka", "ROOT::Math::cyl_bessel_k(1,(sqrt((x*x)+(0.49368*0.49368))/0.12)*cosh(1*y/7))");
  //f2ka->SetParameter(0,alpha);
  TF2 *fka=new TF2("fka","130.162739*8*6*(1/3.1415926535)*x*sqrt((x*x)+(0.493687*0.49368))*y*I0ka*K1ka");
  TH1* kaonsSEF = new TH1D("KaonsSEF", "p_{T} spectra", 100, 0.0, 3);
  for(int i=0;i<100;i++)
      kaonsSEF->SetBinContent(i,fka->Integral(i*0.03, (i+1)*0.03, 0, 7)); //R=7
  kaonsSEF->SetLineColor(416);
  kaonsSEF->SetLineWidth(2);

  TPaveText *pt = new TPaveText(0.75,0.55,0.85,0.65,"NDC");
  pt->SetFillColor(0);
  pt->SetBorderSize(0);
  pt->AddText(Form("#alpha= %.1f",alpha));

  protons->SetMarkerStyle(21);
  protons->SetFillColor(color[1]);
  protons->SetMarkerColor(color[1]);
  protons->SetMarkerSize(0.5);
  pions->SetMarkerStyle(21);
  pions->SetFillColor(color[2]);
  pions->SetMarkerColor(color[2]);
  pions->SetMarkerSize(0.5);
  kaons->SetMarkerStyle(21);
  kaons->SetFillColor(color[0]);
  kaons->SetMarkerColor(color[0]);
  kaons->SetMarkerSize(0.5);
  pions->GetXaxis()->SetTitle("p_{T} [GeV]");
  pions->GetYaxis()->SetTitle("#frac{1}{N} #frac{dN}{dp_{T}}");
  pions->GetYaxis()->SetTitleOffset(1.3);
  c->cd();
  c->SetLogy();
  pions->Draw("same,pe2");
  kaons->Draw("same,pe2");
  protons->Draw("same,pe2");
  pionsSEF->Draw("SAME,c");
  protonsSEF->Draw("SAME,c");
  kaonsSEF->Draw("SAME,c");
  pt->Draw();

  auto legend = new TLegend(0.7,0.7,0.89,0.89);
  legend->AddEntry(pions, "Pions", "p");
  legend->AddEntry(kaons, "Kaons", "p");
  legend->AddEntry(protons, "Protons", "p");
  legend->SetBorderSize(0);
  legend->Draw();
  
  c->Modified();
  c->Print("plots/pT.pdf");
}

void Plot()
{
PlotMaxInt();
PlotPt();
}