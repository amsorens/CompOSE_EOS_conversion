#ifndef CONFIG_H_
#define CONFIG_H_

////////////////////////////////////////////////////////////////////////////
// Specify the address of the input file
// (without the extension, which, however, should be .txt !)
////////////////////////////////////////////////////////////////////////////

//std::string basic_data_file_address = "../results/DNS(CMF)_cold_neutron_stars";
std::string basic_data_file_address = "../results/DNS(CMF)_hadronic_no_electrons_Yq=0";
//std::string basic_data_file_address = "../results/SLy2_CompOSE_e,mu";
//std::string Casic_data_file_address = "../results/GMSR(H2)_CompOSE_e,mu";
//std::string basic_data_file_address = "../results/DNS(CMF)_hadronic_with_electrons";


////////////////////////////////////////////////////////////////////////////////
// Expansion properties
////////////////////////////////////////////////////////////////////////////////

// Secide which terms in the symmetry energy expansion to consider

const bool take_E_asym_0 = true;
//const bool take_E_asym_0 = false;
const bool take_L_asym = true;
//const bool take_L_asym = false;
const bool take_K_asym = true;
//const bool take_K_asym = false;
const bool take_J_asym = true;
//const bool take_J_asym = false;


//const bool assume_pure_neutron_matter = true;
const bool assume_pure_neutron_matter = false;


const bool subtract_leptons = true;
//const bool subtract_leptons = false;

// Decide whether to use YQ from an expansion using the symmetry energy;
// better to use the proton fraction provided from CompOSE
//const bool use_charge_fraction_expansion = true;
const bool use_charge_fraction_expansion = false;

#endif // CONFIG_H_
