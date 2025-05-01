#ifndef QESCHEME_H
#define QESCHEME_H

#include <random>

/**
* Implements the Quadratic-Exponential (QE) scheme for the variance process in the Heston model.
* Model parameters (kappa, theta, epsilon) are provided externally by the Broadie Kaya Scheme
**/

class QEScheme {
public:
	/*
	* @param psi_c Threshold for siwtching between quadratic and exponential branches (default 1.5)
	*/

	explicit QEScheme(const double& psi_c = 1.5);

	/**
	* Copy constructor
	*/
	QEScheme(const QEScheme& other);

	/**
	* Copy assignement operator
	*/

	QEScheme& operator=(const QEScheme& other);

	/**
	* Destructor
	*/
	~QEScheme();

	/**
	* Advance the variance process V from Vt by one time step
	* @param Vt Current variance
	* @param dt Time step
	* @param kappa Mean reversion speed (\kappa)
	* @param theta Long term mean (\theta)
	* @param epsilon Volatility of variance process (\epsilon)
	* @param rng Random number generator
	* @return Next-step variance V_{t+dt}
	*/

	double step(
		const double& Vt,
		const double& dt,
		const double& kappa,
		const double& theta,
		const double& epsilon,
		std::mt19937 &rng
	) const;

private:
	double psi_c; // Threshold for switching between quadratic and exponential branches

};
#endif //QESCHEME_H

