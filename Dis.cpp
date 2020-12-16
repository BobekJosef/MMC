#include "Dis.h"
#include <random>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;
Dis::Dis(double T1, double _tauf, double R1, double _alpha, double _m, double _g, string _name) {
    T=T1; tauf=_tauf; R=R1; alpha=_alpha; m=_m; g=_g, name=std::move(_name);
}

double Dis::mT(double pT) const {return sqrt((m*m)+(pT*pT));}

double Dis::Max(int K, double &sum) {
    cout<<"Estimating maximum for "<<name<<" distribution: ";
    string path="C:/Users/Pepa Bobek/Desktop/MMC/data/";
    path.append(name);
    path.append(".MaxSum.txt");
    ofstream output(path.c_str());
    double max=0;
    sum=0;
    Var maxvar(R);
    double rT, pT, phi, phip, eta, y;
    random_device rd;
    mt19937 mt(rd());
    double sample[6];
    uniform_real_distribution<double> dist(0, 1);
    for(int i=0; i<K; i++)
    {
        for(double & j : sample)
            j=dist(mt);
        maxvar.Sample(sample);
        maxvar.Get(rT, pT, phi, phip, eta, y);
        sum+=Value(rT, pT, phi, phip, eta, y);
        if(Value(rT, pT, phi, phip, eta, y)>max)
            max=Value(rT, pT, phi, phip, eta, y);
        if(((i+1)%100)==0)
            output <<setw(10)<<i+1<< setw(16)<<max<< setw(16)<<sum<<endl;
    }
    cout<<max<<endl;
    return max;
}

double Dis::Integrate(int K, double sum) {
    double Vol=R*3*(2*M_PI)*(2*M_PI)*6*6*5.06765;   //rT*pT*phi*phip*eta*y*1/hbarc
    double result=Vol*sum/K;
    cout<<"Calculating PDF integral for "<<name<<": "<<result<<endl;
    return result;
}

double Dis::Value(double rT, double pT, double phi, double phip, double eta, double y) const {
    double exponent=((pT/T)*sinh(alpha*(rT/R))*cos(phi-phip))-((mT(pT)/T)*cosh(eta-y)*cosh(alpha*rT/R));
    double value=130.148927*tauf*(g/(2*M_PI*2*M_PI*2*M_PI))*rT*pT*mT(pT)*cosh(eta-y)*exp(exponent);
    return value;
}

bool Dis::Accepted(Var avar, double U, double X) const {
    double rT, pT, phi, phip, eta, y;
    avar.Get(rT, pT, phi, phip, eta, y);
    if(U<(Value(rT, pT, phi, phip, eta, y)/X))
        return true;
    return false;
}


