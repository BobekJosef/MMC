#ifndef MMC_DIS_H
#define MMC_DIS_H
#include "Var.cpp"
#include <string>

class Dis {
private:
    double T;       //0.12 GeV
    double tauf;    //8 fm/c
    double R;       //7 fm
    double g;       //2J+1
    double m;
    double alpha;   //??
    string name;
public:
    Dis(double T1, double _tauf, double R1, double _alpha, double _m, double _g, string _name);

    inline double mT(double pT) const;
    double Max(int K, double &sum);
    double Integrate(int K, double sum);
    double Value(double rT, double pT, double phi, double phip, double eta, double y) const;
    bool Accepted(Var avar, double U, double X) const;
    inline string Getname() {return name;};
};

#endif //MMC_DIS_H
