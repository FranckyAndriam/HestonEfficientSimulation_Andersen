// BroadieKayaScheme.h
#ifndef BROADIE_KAYA_SCHEME_H
#define BROADIE_KAYA_SCHEME_H

#include "QEScheme.h"
#include <random>
#include <utility>

/**
 * Implements one time–step of the Broadie–Kaya scheme for the Heston model.
 * Given (S_t, V_t) it returns (S_{t+dt}, V_{t+dt}) using:
 *   – QE scheme for the variance (Andersen 2008)
 *   – Exact conditional normal law for log–spot as in Broadie & Kaya (2006)
 */
class BroadieKayaScheme {
public:

    BroadieKayaScheme(double kappa,
        double theta,
        double epsilon,
        double rho,
        double r,
        double gamma1 ,
        double gamma2 ,
        double psi_c = 1.5);


    std::pair<double, double> step(double St,
        double Vt,
        double dt,
        std::mt19937& rng) const;

private:
    double kappa, theta, epsilon, rho, r;
    double gamma1, gamma2;
    QEScheme qe_scheme;
};

#endif // BROADIE_KAYA_SCHEME_H
