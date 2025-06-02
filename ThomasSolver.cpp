#include "ThomasSolver.h"

//Le thomas Solver c'est juste pour recuperer les beta

ThomasSolver::ThomasSolver(const Vector& lower_diag, const Vector& central_diag, const Vector& upper_diag, const Vector& rhs)
	: _lower_diagonal(lower_diag), _central_diagonal(central_diag), _upper_diagonal(upper_diag), _right_hand_side(rhs)
	//We have to put all the vector at the same dimension and for lower start with 0 and (for upper finish with 0(not necessary))
{
	if(!(_lower_diagonal.size() == _upper_diagonal.size() == _central_diagonal.size() == _right_hand_side.size() ))
	{
		throw "vectors are not well dimensioned" ;
	}
	// sanity checks - check dimensions consistency ...
}

Vector ThomasSolver::solve() const
{
	size_t sol_dim = _central_diagonal.size(); //sol_dim = N-2
	Vector solution(sol_dim);

	// C_j' and R_j'
	Vector c_prime(sol_dim - 1);
	Vector R_prime(sol_dim);

	//Initialisation of coeff
	c_prime[0] =  _upper_diagonal[0] / _central_diagonal[0];
	R_prime[0] =  _right_hand_side[0] / _central_diagonal[0];

	for (size_t j = 1; j < sol_dim-1; j++ ) 
	{
		c_prime[j] = _upper_diagonal[j] /( _central_diagonal[j] - _lower_diagonal[j]*c_prime[j-1] );
		R_prime[j] = _right_hand_side[j] - _lower_diagonal[j] * R_prime[j-1] /( _central_diagonal[j] - _lower_diagonal[j]*c_prime[j-1] );
	}
	R_prime[sol_dim -1] = _right_hand_side[sol_dim -1] - _lower_diagonal[sol_dim -1] * R_prime[sol_dim-2] /( _central_diagonal[sol_dim -1] - _lower_diagonal[sol_dim -1]*c_prime[sol_dim-2 );

	//solution[sol_dim - 1] = ...
	solution[sol_dim -1] = R_prime[sol_dim -1];


	//for(size_t idx = sol_dim - 2; idx > sol_dim - 2; idx--)
		//solution[idx] = ... solution[idx+1]
	for(size_t j = sol_dim - 2; j > sol_dim - 2; j--)
	{
		solution[j] = R_prime[j] - c_prime[j]*solution[j+1];
	}

	return solution;
}
