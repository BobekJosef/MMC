#ifndef MMC_GEN_H
#define MMC_GEN_H
#include "Dis.cpp"

class Gen {
private:
    int N;
    double R;
public:
    Gen(int N1, double R1);
    int Generate(Dis particle, double max, double integral);
    int Multiplicity(double lambda, int a, int b, int c);
};


#endif //MMC_GEN_H
