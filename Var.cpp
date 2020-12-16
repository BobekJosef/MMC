#include "Var.h"
#include <cmath>
using namespace std;

Var::Var(double R1){rT=0; pT=0; phi=0; phip=0; eta=0; y=0; R=R1;}

void Var::Sample(const double sample[]) {
    rT=sample[0]*R;          //fm (recommended: R=7 fm)
    pT=sample[1]*3;          //GeV
    phi=sample[2]*(2*M_PI);  //0-2pi
    phip=sample[3]*(2*M_PI); //0-2pi
    eta=(sample[4]*6) - 3;   //-3 - +3
    y=(sample[5]*6) - 3;     //-3 - +3
}