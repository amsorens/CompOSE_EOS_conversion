#ifndef CONVERSION_FUNCTIONS_H_
#define CONVERSION_FUNCTIONS_H_

#include <cmath>

#include "./config.h"
#include "./constants.h"
#include "./basic_functions.h"

inline double subtract_lepton_energy_density (double nB_CompOSE,                // in fm^-3
					      double electron_fraction_CompOSE, // [1]
					      double muon_fraction_CompOSE,     // [1]
					      double energy_density_CompOSE) {  // in MeV/fm^3
  //////////////////////////////////////////////////////////////////////////////
  // To use the symmetry energy expansion, we need to be dealing with the energy
  // density OF PROTONS AND NEUTRONS; to get that from a neutron star EOS, we
  // need to subtract the energy densities of electrons and muons

  // Get the number densities of leptons: electrons and muons
  const double n_electron = nB_CompOSE * electron_fraction_CompOSE;  // in fm^-3
  const double n_muon = nB_CompOSE * muon_fraction_CompOSE;          // in fm^-3

  // Convert the number densities of leptons to MeV^3
  const double n_electron_MeV = n_electron * hbarc * hbarc * hbarc;
  const double n_muon_MeV = n_muon * hbarc * hbarc * hbarc;

  // Calculate the energy density of leptons in MeV^4
  const double electron_energy_density_MeV4 =
    energyDensityFG_Tzero (lepton_degeneracy, electron_mass, n_electron_MeV);
  const double muon_energy_density_MeV4 =
    energyDensityFG_Tzero (lepton_degeneracy, muon_mass, n_muon_MeV);

  // Convert the energy density of leptons back to MeV/fm^3
  const double electron_energy_density_MeV_over_fm3 =
    electron_energy_density_MeV4 / ( hbarc * hbarc * hbarc );
  const double muon_energy_density_MeV_over_fm3 =
    muon_energy_density_MeV4 / ( hbarc * hbarc * hbarc );

  // Now calculate the nucleon energy density
  double nucleon_energy_density = energy_density_CompOSE;
  if ( subtract_leptons ) {
    nucleon_energy_density = nucleon_energy_density
      - electron_energy_density_MeV_over_fm3 - muon_energy_density_MeV_over_fm3;
  }

  // Print out the basic info that we get from the CompOSE EOS:
  std::cout << "\n\n"
	    << "\n               nB = " << nB_CompOSE
	    << "\n energy density E = " << energy_density_CompOSE
	    << "\n       electron E = " << electron_energy_density_MeV_over_fm3
	    << "\n           muon E = " << muon_energy_density_MeV_over_fm3
	    << "\n        nucleon E = " << nucleon_energy_density
	    << std::endl;
  //std::cin.get();

  return nucleon_energy_density;  
}



inline double convert_to_symmetric_EOS (double EperA_NS_CompOSE,        // in MeV
					double nB_CompOSE,              // in fm^{-3}
					double proton_fraction_CompOSE, // [1]
					double n0_CompOSE,              // in fm^{-3}
					double Esym_CompOSE,            // in MeV
					double Lsym_CompOSE,            // in MeV
					double Ksym_CompOSE,            // in MeV
					double Jsym_CompOSE){           // in MeV
  //////////////////////////////////////////////////////////////////////////////
  // Perform the symmetry energy expansion as appropriate
  double symmetry_energy_transformation = 0.0;
  if (take_E_asym_0) {
    symmetry_energy_transformation += Esym_CompOSE; // use only the first term
  }
      
  if (take_L_asym) {
    symmetry_energy_transformation +=(1.0/3.0) *
      Lsym_CompOSE * ( nB_CompOSE/n0_CompOSE - 1.0 ); // first two terms
  }

  if (take_K_asym) {
    symmetry_energy_transformation += (1.0/18.0) * Ksym_CompOSE *
      std::pow( (nB_CompOSE/n0_CompOSE - 1.0), 2.0 ); // first three terms
  }

  if (take_J_asym) {
    symmetry_energy_transformation += (1.0/162.0) * Jsym_CompOSE *
      std::pow( (nB_CompOSE/n0_CompOSE - 1.0), 3.0 ); // first four terms
  }

  //////////////////////////////////////////////////////////////////////////////
  // Take into account that the proton fraction can be finite
  double proton_fraction = 0.0;

  // either use the symmetry energy expansion to get the proton fraction or get
  // the value from CompOSE
  if (use_charge_fraction_expansion) {
    double x = ( nB_CompOSE - n0_CompOSE ) / ( 3.0 * n0_CompOSE );
    // Eq. (10) in the paper with Nanxi
    double bracket_fraction =
      ( Esym_CompOSE + Lsym_CompOSE * x + 0.5 * Ksym_CompOSE * x * x ) / hbarc;
    double bracket = std::pow( bracket_fraction, 3.0 );
    double numerator = 64.0 * bracket;
    double denominator = 3.0 * M_PI * M_PI * n0_CompOSE * ( 3.0 * x + 1.0 );
    proton_fraction = numerator/denominator;
  } else {
    proton_fraction = proton_fraction_CompOSE;
  }
      
  // Compute the energy per particle of symmetric matter
  double sym_EperA_HIC_CompOSE = 0.0;
  if (assume_pure_neutron_matter) {
    sym_EperA_HIC_CompOSE = EperA_NS_CompOSE - symmetry_energy_transformation;
  } else {
    sym_EperA_HIC_CompOSE = EperA_NS_CompOSE - symmetry_energy_transformation *
      std::pow( 1.0 - 2.0 * proton_fraction , 2.0 );
  }

  return sym_EperA_HIC_CompOSE;
}




#endif // CONVERSION_FUNCTIONS_H_
