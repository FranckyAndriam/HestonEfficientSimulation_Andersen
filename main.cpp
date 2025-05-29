#include "FourierPricer.h"
#include <iostream>

int main() {
    // Paramètres d’un exemple réeliste
    double S0 = 100.0, V0 = 0.04, kappa = 0.5, theta = 0.04;
    double epsilon = 1.0, rho = -0.9, T = 10.0, K = 100.0;

    // Création du pricer analytique
    FourierPricer pricer(S0, V0, kappa, theta, epsilon, rho, T, K);
    double exact_price = pricer.computePrice();

    std::cout << "Prix exact (Fourier): " << exact_price << std::endl;
    return 0;
}