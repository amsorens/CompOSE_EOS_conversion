#ifndef BASIC_FUNCTIONS_H_
#define BASIC_FUNCTIONS_H_

////////////////////////////////////////////////////////////////////////////
// basic functions
////////////////////////////////////////////////////////////////////////////

// Fermi momentum
double FermiMomentum (double degeneracy, double n_density);

// relativistic free particle energy
double EKinetic (double p, double mass);

// energy density of the ideal Fermi gas at T=0
double energyDensityFG_Tzero (double degeneracy, double mass, double n_density);

#endif // BASIC_FUNCTIONS_H_
