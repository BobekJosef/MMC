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
    cout<<"# Number of events...................."<<events<<"     \t#"<<endl;
    cout<<"# Integration & Maximum iterations K.."<<K<<" \t#"<<endl;
    cout<<"#################################################"<<endl<<endl;
}

int main() {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    double const T=0.12, tauf=8.0, alpha=0.1, R=7.0;         //Parameters
    int const K=1000000, events=1;                       //Parameters
    DisplayParams(K, events, T, tauf, alpha, R);
    Gen gen( events, R);
    double sum;
    Dis proton(T, tauf, R, alpha, 0.93827, 2.0, "protons");
    Dis pion(T, tauf, R, alpha, 0.13957, 1.0, "pions");
    Dis kaon(T, tauf, R, alpha, 0.49368, 1.0, "kaons");
    double Mpr=proton.Max(K, sum);
    double Ipr=proton.Integrate(K,sum);
    double Mpi=pion.Max(K, sum);
    double Ipi=pion.Integrate(K,sum);
    double Mka=kaon.Max(K, sum);
    double Ika=kaon.Integrate(K,sum);

    gen.Generate(proton, Mpr, Ipr);
    gen.Generate(pion, Mpi, Ipi);
    gen.Generate(kaon, Mka, Ika);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::seconds>(end - begin).count() << "s" << endl;
    return 0;
}
