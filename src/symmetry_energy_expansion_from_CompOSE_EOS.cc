/*
 *  Copyright 2023
 *  Agnieszka Sorensen
 */


/*
 * ------------------------------------ README ---------------------------------
 * 
 * This is a simple symmetry energy expansion code to get a symmetric nuclear
 * matter EOS from a pure neutron matter or neutron star matter EOS downloaded
 * from CompOSE.
 * Note: the EOS table files need to have a specific structure, as in the example
 * below
 * (here, # is the first character in the line):
 *
 * # DNS(CMF) hadronic no electrons EOS from CompOSE: https://compose.obspm.fr/eos/117
 * #
 * # n0   = 0.15       fm^-3   
 * # E0   = -16.0      MeV
 * # K0   = 300.0      MeV
 * # Esym = 30.0       MeV
 * # Lsym = 88.0       MeV
 * # Ksym = 0.0     MeV
 * # mN   = 939.565421 MeV
 * # mP   = 938.272088 MeV
 * #
 * #             T [MeV]                     nB [fm^-3]                   YQ         pressure P [MeV fm^-3]       muB - mN [MeV]     energy density [MeV fm^-3]   proton fraction Yp       electron fraction Ye       muon fraction Ymu
 * #
 * #
 * 0.0000000000000000        2.9999999999999999E-002   0.0000000000000000        1.7035236000000002E-002   2.8108878955468750        28.234852834098032        4.4524600000000001E-003   4.4524600000000001E-003   0.0000000000000000     
 * 0.0000000000000000        4.0000000000000001E-002   0.0000000000000000        2.2371962000000002E-002   3.0917935959526246        37.658048439891623        6.0456299999999998E-003   6.0456299999999998E-003   0.0000000000000000     
 * 0.0000000000000000        5.0000000000000003E-002   0.0000000000000000        6.5354892499999998E-002   4.0387494526316248        47.082518252269956        8.3839599999999993E-003   8.3839599999999993E-003   0.0000000000000000     
 * 0.0000000000000000        5.9999999999999998E-002   0.0000000000000000       0.14543827020000000        5.4883178852989998        56.518983126767942        1.0992840000000000E-002   1.0992840000000000E-002   0.0000000000000000     
 * ........
 *
 * Note specifically that all EOS parameters, such as the saturation density n0
 * or the binding energy E0, have values specified between the 10th and 20th
 * character of the line: THIS CODE WON'T WORK unless this is the case. If a
 * given EOS doesn't provide a value for a given parameter, one should provide a
 * dummy value, such as, e.g., Ksym = 0.0 in the example above.
 * 
 * Note also that each file needs to have the same number of columns, with the
 * same order of variables.
 *
 * Reading in of the data in the file is done in two steps: first all the EOS
 * parameters, provided in lines starting with "#", are read in. Then the EOS
 * table is read-in, and relevant operations ((e.g., subtraction of leptons,
 * symmetry energy expansion, etc.) are applied. Finally, a data file containing
 * the converted EOS data is produced.
 * 
 */


#include <iostream>   // input, output
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>

#include "./include/reading_functions.h"



int main () {

  std::cout << "\nHello there!"
	    << "\nThis is a code for performing the symmetry energy expansion "
	    << "for CompOSE EOSs \n" << std::endl;

  try{

    ////////////////////////////////////////////////////////////////////////////
    // Go over a CompOSE data file
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Declare variables that will take the values of the EOS parameters from
    // the input file:
    double n0_CompOSE = 0.0;     // in fm^{-3}
    double E0_CompOSE = 0.0;     // in MeV
    double K0_CompOSE = 0.0;     // in MeV
    double Esym_CompOSE = 0.0;   // in MeV
    double Lsym_CompOSE = 0.0;   // in MeV
    double Ksym_CompOSE = 0.0;   // in MeV
    double Jsym_CompOSE = 0.0;   // in MeV
    double mN_CompOSE = 0.0;     // in MeV
    double mP_CompOSE = 0.0;     // in MeV


    ////////////////////////////////////////////////////////////////////////////
    // First, get the CompOSE EOS parameters
    ////////////////////////////////////////////////////////////////////////////

    read_EOS_parameters (n0_CompOSE, E0_CompOSE, K0_CompOSE,
			 Esym_CompOSE, Lsym_CompOSE, Ksym_CompOSE,
			 Jsym_CompOSE, mN_CompOSE, mP_CompOSE);

    // at this point we have read in all data about saturation density etc.
    
    ////////////////////////////////////////////////////////////////////////////
    // Then, read in the EOS table, convert, produce a converted EOS data file
    ////////////////////////////////////////////////////////////////////////////
   
    read_and_convert_the_EOS_table (n0_CompOSE, E0_CompOSE, K0_CompOSE,
			 Esym_CompOSE, Lsym_CompOSE, Ksym_CompOSE, Jsym_CompOSE,
			 mN_CompOSE, mP_CompOSE);

    // at this point the code finished producing the EOS table
    
    } catch (std::exception &e) {
      std::cout << "Symmetry energy expansion failed with the following error:\n"
		<< e.what() << "\n" << std::endl;
      return EXIT_FAILURE;
    }

  std::cout << "\nFinished!\n" << std::endl;
  
}


