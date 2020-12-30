#include <iostream>
#include <chrono>
#include <random>
#include "Gen.cpp"
using namespace std;

void DisplayParams(int K, int events, double T, double tauf, double alpha, double R) {
    cout<<"####################parameters###################"<<endl;
    cout<<"# Freeze-out temperature T............"<<T*1000<<" MeV\t#"<<endl;
    cout<<"# Freeze-out proper time tau_f........"<<tauf<<" fm/c \t#"<<endl;
    cout<<"# Free model parameter alpha.........."<<alpha<<"      \t#"<<endl;
    cout<<"# Maximal radius R...................."<<R<<" fm   \t#"<<endl;
    cout<<"#-----------------------------------------------#"<<endl;
    cout<<"# Number of events proportionality...."<<events<<"  \t#"<<endl;      //1000-50000
    cout<<"# Integration & Maximum iterations K.."<<K<<" \t#"<<endl;            //100000-1000000
    cout<<"#################################################"<<endl<<endl;
}

int main() {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    double const T=0.12, tauf=8.0, alpha=1, R=7.0;   //Parameters
    int const K=100000, events=500;   //Parameters
    DisplayParams(K, events, T, tauf, alpha, R);
    Gen gen( events, R);
    double sum, sumErr;
    ofstream NEve("C:/Users/Pepa Bobek/Desktop/MMC/data/NumberOfEvents.txt");

    Dis proton(T, tauf, R, alpha, 0.93827, 2.0, "protons");
    Dis pion(T, tauf, R, alpha, 0.13957, 1.0, "pions");
    Dis kaon(T, tauf, R, alpha, 0.49368, 1.0, "kaons");
    double Mpr=proton.Max(K, sum, sumErr);
    double Ipr=proton.Integrate(K,sum, sumErr);
    double Mpi=pion.Max(K, sum, sumErr);
    double Ipi=pion.Integrate(K,sum, sumErr);
    double Mka=kaon.Max(K, sum, sumErr);
    double Ika=kaon.Integrate(K,sum, sumErr);

    NEve<<proton.Getname()<<": "<<gen.Generate(proton, 1.1*Mpr, Ipr)<<endl;
    NEve<<pion.Getname()<<": "<<gen.Generate(pion, 1.1*Mpi, Ipi)<<endl;
    NEve<<kaon.Getname()<<": "<<gen.Generate(kaon, 1.1*Mka, Ika)<<endl;
    NEve.close();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::seconds>(end - begin).count() << "s" << endl;
    return 0;
}
