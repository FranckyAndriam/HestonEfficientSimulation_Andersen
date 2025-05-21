#include "TGScheme.h"

//Constructeur par recopie
TGScheme::TGScheme(double kappa_, double theta_, double epsilon_, double dt_)
    : kappa(kappa_), theta(theta_), epsilon(epsilon_), dt(dt_), gen(std::random_device{}()), norm(0.0, 1.0) {}

//Operateur d'affectation
TGScheme& TGScheme::operator=(const TGScheme& other){
    if (this != &other){
        kappa = other.kappa;
        theta = other.theta;
        epsilon = other.epsilon;
        dt = other.dt;
        gen = other.gen;
        norm = other.norm;
    }
    return *this;
}

//Destructeur
TGScheme::~TGScheme(){
}

double TGScheme::simulateNextV(double Vt) {
    double m = computeMean(Vt);
    double s2 = computeVariance(Vt);
    double psi = computePsi(m, s2);
    double r = lookup_r(psi);  // Do interpolation from precomputed grid in real-case

    // Compute fμ and fσ as in the paper
    double phi_r = std::exp(-0.5 * r * r) / std::sqrt(2.0 * M_PI);
    double Phi_r = 0.5 * (1.0 + std::erf(r / std::sqrt(2.0)));

    double f_mu = r / (phi_r + r * Phi_r);
    double f_sigma = std::sqrt(psi) * f_mu;

    double mu = f_mu * m;
    double sigma = f_sigma * std::sqrt(s2);

    double Z = norm(gen);
    return std::max(0.0, mu + sigma * Z);
}

double TGScheme::computeMean(double Vt) {
    return theta + (Vt - theta) * std::exp(-kappa * dt);
}

double TGScheme::computeVariance(double Vt) {
    double ekt = std::exp(-kappa * dt);
    double term1 = Vt * epsilon * epsilon * ekt * (1.0 - ekt) / kappa;
    double term2 = theta * epsilon * epsilon * std::pow(1.0 - ekt, 2) / (2.0 * kappa);
    return term1 + term2;
}

double TGScheme::computePsi(double m, double s2) {
    return s2 / (m * m);
}

double TGScheme::lookup_r(double psi) {
    // Approximate or interpolate precomputed r(ψ) function
    // For simplicity, return a linear approx valid around psi=1
    return std::sqrt(2.0 * std::log(1.0 + psi));  // Rough approximation
}

"""double TGScheme::standardNormalInverse(double u) {
    // Approximation from Moro or similar algorithms (here we just use inverse erf for simplicity)
    return std::sqrt(2.0) * std::erfinv(2.0 * u - 1.0);
}"""