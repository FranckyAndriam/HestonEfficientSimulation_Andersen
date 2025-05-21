#ifndef TGSCHEME_H
#define TGSCHEME_H

#include <cmath>
#include <vector>
#include <random>

class TGScheme {
public:
    TGScheme(double kappa, double theta, double epsilon, double dt);

    //Constructeur par recopie
    TGScheme(const TGScheme& other);

    //Operateur d'affectation
    TGScheme& operator=(const TGScheme& other);

    //Destructeur
    ~TGScheme();

    // Simule une valeur de variance à t + dt à partir de Vt
    double simulateNextV(double Vt);

private:
    double kappa, theta, epsilon, dt;
    std::mt19937 gen;
    std::normal_distribution<> norm;

    double computeMean(double Vt);
    double computeVariance(double Vt);
    double computePsi(double m, double s2);
    double lookup_r(double psi);
    double standardNormalInverse(double u);
};

#endif // TGSCHEME_H