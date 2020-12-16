#include "Gen.h"
#include <random>
#include <fstream>
#include <iomanip>

Gen::Gen(int N1, double R1) {
    R=R1;
    N=N1;
}

void Gen::Generate(Dis particle, double max, double integral) {
    cout<<"Generating "<<particle.Getname()<<endl;
    string path="C:/Users/Pepa Bobek/Desktop/MMC/data/";
    path.append(particle.Getname());
    path.append(".txt");
    ofstream output(path.c_str());
    Var var(R);
    int pThisto[100];
    int acceptance;
    double rT, pT, phi, phip, eta, y;
    int accepted=0, rejected=0;
    double U, X;
    random_device rd;
    mt19937 mt(rd());
    double sample[6];
    uniform_real_distribution<double> dist(0, 1);
    for(int Ni=0; Ni<N; Ni++)
    {
    cout<<"### Event "<<Ni+1<<" out of "<<N<<" ###";
    acceptance=Multiplicity(100000);
    cout<<" multiplicity in the event: "<<acceptance<<" ###"<<endl;
    for(int & i : pThisto)
        i=0;

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
        if(((accepted+rejected)%1000000)==0)
            cout<<"Accepted: "<<accepted<<"    \t Rejected: "<<rejected<<endl;
    }
    cout<<"Accepted: "<<accepted<<"    \t Rejected: "<<rejected<<"   (Event done)"<<endl;
    output<< setw(7);
    for(int & i : pThisto)
    output <<i<< setw(7);
    output<<endl;
    accepted=0;
    rejected=0;
    }
}

int Gen::Multiplicity(double lambda) {
    default_random_engine eng{static_cast<long unsigned int>(time(0))};
    poisson_distribution<int> dist(lambda);
    int mult=dist(eng);
    return mult;
}