#include "BroadieKayaScheme.h"
#include <cmath>

BroadieKayaScheme::BroadieKayaScheme(double kappa,
    double theta,
    double epsilon,
    double rho,
    double r,
    double gamma1,
    double gamma2,
    double psi_c)
    : kappa(kappa),
    theta(theta),
    epsilon(epsilon),
    rho(rho),
    r(r),
    gamma1(gamma1),
    gamma2(gamma2),
    qe_scheme(psi_c)
{
    // Ensure weights sum to one 
    const double sum = gamma1 + gamma2;
    if (std::abs(sum - 1.0) > 1e-12) {
        gamma1 /= sum;
        gamma2 /= sum;
    }
}

std::pair<double, double> BroadieKayaScheme::step(double St,
    double Vt,
    double dt,
    std::mt19937& rng) const
{
    // 1) Simulate variance at t+dt via QE
    double V_next = qe_scheme.step(Vt, dt, kappa, theta, epsilon, rng);

    // 2) Approximate the time‑integrated variance by weighted average
    double V_bar = gamma1 * Vt + gamma2 * V_next;

    double mu_X = std::log(St)
        + r * dt
        + rho / epsilon * (V_next - Vt - kappa * theta * dt)
        + (kappa * rho / epsilon - 0.5) * dt * V_bar;

    double sigma_X = std::sqrt((1.0 - rho * rho) * dt * V_bar);

    std::normal_distribution<double> norm(0.0, 1.0);
    double Zx = norm(rng);

    double X_next = mu_X + sigma_X * Zx;
    double S_next = std::exp(X_next);

    return { S_next, V_next };
}