#include "Gen.h"
#include <random>
#include <fstream>
#include <iomanip>

Gen::Gen(int N1, double R1) {
    R=R1;
    N=N1;
}

int Gen::Generate(Dis particle, double max, double integral) {
    string path="C:/Users/Pepa Bobek/Desktop/MMC/data/";
    path.append(particle.Getname());
    path.append(".txt");
    ofstream output(path.c_str());
    Var var(R);
    unsigned long int pThisto[100];
    int acceptance;
    int NTot=static_cast<int>(N*160/integral);
    cout<<"Generating "<<particle.Getname()<<" ### Number of events: "<<NTot<<endl;
    double rT, pT, phi, phip, eta, y;
    int accepted=0, rejected=0, acceptedTot=0, rejectedTot=0;
    double U, X;
    random_device rd;
    mt19937 mt(rd());
    double sample[6];
    uniform_real_distribution<double> dist(0, 1);
    for(unsigned long int & i : pThisto)
        i=0;
    for(int Ni=0; Ni<NTot; Ni++)
    {
    acceptance=Multiplicity(integral, Ni, acceptedTot, rejectedTot);
    while(accepted<acceptance)
    {
        for(double & j : sample)
            j=dist(mt);
        var.Sample(sample);
        var.Get(rT, pT, phi, phip, eta, y);
        U=dist(mt);
        X=1.1*max*dist(mt);
        if(particle.Accepted(var,U,X))
        {
            for(int i=0;i<100;i++)
                if(pT>(i*0.03) && pT<=((i+1)*0.03))
                    pThisto[i]++;
            accepted++;
        }
        else
            rejected++;
        if(((acceptedTot+rejectedTot+accepted+rejected)%1000000)==0)
            cout<<"Accepted: "<<acceptedTot<<"    \t Rejected: "<<rejectedTot<<endl;
    }
    acceptedTot+=accepted;
    rejectedTot+=rejected;
    if(((Ni+1)%10000)==0)
        cout<<"### "<<Ni+1<<" events done out of "<<NTot<<" ###"<<endl;
    accepted=0;
    rejected=0;
    }
    cout<<"All "<<NTot<<" events done"<<endl;
    for(unsigned long int & i : pThisto)
        output<< setw(9) <<i;
    output.close();
    return NTot;
}

int Gen::Multiplicity(double lambda, int a, int b, int c) {
    seed_seq seed{static_cast<int>(lambda), a, b, c, static_cast<int>(time(nullptr))};
    default_random_engine eng{seed};
    poisson_distribution<int> dist(lambda);
    int mult=dist(eng);
    return mult;
}