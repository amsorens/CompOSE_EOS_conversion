////////////////////////////////////////////////////////////////////////////////
// basic functions
////////////////////////////////////////////////////////////////////////////////

#include <cmath>

#include "./include/basic_functions.h"

// Fermi momentum
double FermiMomentum (double degeneracy, double n_density)
{
  return cbrt( 6.0 * M_PI * M_PI * n_density / degeneracy );
}

// relativistic free particle energy
double EKinetic (double p, double mass)
{
  return sqrt( p * p + mass * mass );
}

// energy density of the ideal Fermi gas at T=0
double energyDensityFG_Tzero (double degeneracy, double mass, double n_density)
{
  double integral_multiplier = degeneracy / (16.0 * M_PI * M_PI);

  double pFermi = FermiMomentum (degeneracy, n_density);
  double eKineticFermi = EKinetic (pFermi, mass);

  double term1 = 2.0 * ( eKineticFermi * eKineticFermi * eKineticFermi ) * pFermi;
  double term2 = -( mass * mass ) * eKineticFermi * pFermi;
  double term3 = -( mass * mass * mass * mass ) * log( (eKineticFermi + pFermi)/mass );
   
  return integral_multiplier * (term1 + term2 + term3);
}


