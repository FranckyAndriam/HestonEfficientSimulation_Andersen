#include "ImpliedVolatilitySurface.h"
#include "ThomasSolver.cpp"

ImpliedVolatilitySurface::ImpliedVolatilitySurface(
	const Vector& maturities, 
	const Vector& strikes, 
	const Matrix& market_implied_vols, 
	const double& risk_free_rate)
	: _maturities(maturities), 
	_strikes(strikes), 
	_market_implied_volatilities(market_implied_vols), 
	_risk_free_rate(risk_free_rate)
{
	// sanity checks
	if (!check_ordered_vectors())
		throw "vectors of maturities and strikes are not ordered";
	// etc....
	if (!check_matrix_dimensions())
		throw "vectors of maturities and strikes are not ordered";

	if (!check_vols_positivity())
		throw "vectors of maturities and strikes are not ordered";

	evaluate_cubic_spline_coefficients();
}

void ImpliedVolatilitySurface::evaluate_cubic_spline_coefficients()
{
	// Compute _beta - Thomas Solver
	ThomasSolver solver(lower, central, upper, rhs);  // Création de l'objet avec les diagonales
	Vector beta = solver.solve();	
	// Compute _alpha
	for (size_t j)
	// Compute _gamma


}
