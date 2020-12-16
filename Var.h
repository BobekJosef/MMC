#ifndef MMC_VAR_H
#define MMC_VAR_H
using namespace std;

class Var
        {
private:
    double rT, pT, phi, phip, eta, y, R;
public:
    explicit Var(double R1);
    void Sample(const double sample[]);

    inline void Get(double &_rT, double &_pT, double &_phi,
                    double &_phip, double &_eta, double &_y) {
        _rT=rT; _pT=pT; _phi=phi; _phip=phip; _eta=eta; _y=y;
    }
};
#endif //MMC_VAR_H
