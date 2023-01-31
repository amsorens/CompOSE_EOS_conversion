#include <iostream>   // input, output
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>

#include "./include/config.h"
#include "./include/constants.h"
#include "./include/conversion_functions_copy.h"

#include "./include/reading_functions.h"


void make_sure_that_the_file_exists (std::ifstream& CompOSE_EOS_input_file) {
  bool file_exists;
  if(!CompOSE_EOS_input_file) { 
    file_exists = false;        // The file was not found.
    std::cout << "There is no file at this address to read the data from!!!"
	      << "\n\n" << std::endl;
    std::cin.get();
  } else {                      // If the file was found, then file is non-0.
    file_exists = true;         // The file was found.
    std::cout << "The file to read the data from exists" << "\n\n" << std::endl;
  }
}


void read_EOS_parameters (// these are passed as a reference so that their
			  // values can be changed
			  double& n0_CompOSE,   // in fm^{-3}
			  double& E0_CompOSE,   // in MeV
			  double& K0_CompOSE,   // in MeV
			  double& Esym_CompOSE, // in MeV
			  double& Lsym_CompOSE, // in MeV
			  double& Ksym_CompOSE, // in MeV
			  double& Jsym_CompOSE, // in MeV
			  double& mN_CompOSE,   // in MeV
			  double& mP_CompOSE){  // in MeV
  //////////////////////////////////////////////////////////////////////////////
  // Set up variables for reading in the data
  //////////////////////////////////////////////////////////////////////////////  
  // a variable to read in a line from the file
  std::string line_from_the_file;
  // a variable to read in the first character from a line
  char first_character_from_the_line;
  
  
  //////////////////////////////////////////////////////////////////////////////
  // Open the file and check whether it exists
  //////////////////////////////////////////////////////////////////////////////
  std::string input_data_file_address = basic_data_file_address + ".txt";
  std::ifstream CompOSE_EOS_input_file( input_data_file_address.c_str() );
  make_sure_that_the_file_exists (CompOSE_EOS_input_file);

  ////////////////////////////////////////////////////////////////////////////
  // Get the CompOSE EOS parameters from lines that begin with "#".
  ////////////////////////////////////////////////////////////////////////////
    
  while ( !CompOSE_EOS_input_file.eof() ) {
    // get a line from the file
    getline(CompOSE_EOS_input_file, line_from_the_file);

    // discard an empty line (sometimes spurious empty lines are read in)
    if ( line_from_the_file.empty() ) {    
      continue;   // this is a throw-away line, we just continue!
    }

    // get the first character from the read-in line
    first_character_from_the_line = line_from_the_file.at(0);

    // get values from the line if it starts with "#"
    if ( first_character_from_the_line == '#' ) {
      // declare variables for reading in the values
      char character_from_the_line;    
      int value_recording_index = 0;
      char value_from_the_line[64];
      for (int g = 0; g < 64; g++){
	value_from_the_line[g] = '\0';  // reset all values to empty
      }

      // The EOS files are constructed in such a way that the values of the EOS
      // parameters occupy positions 9, 10, 11, 12, 13, 14, 15, 16, 17, 18
      // in the line.

      // DON'T PROCEED if the line is not a line with an EOS parameter
      // (we know how they are at least 18 characters long)
      if ( line_from_the_file.size() < 18 ) {
	continue;
      }
      
      // populate the value_from_the_line char array
      for (int i = 9; i < 19; i++) {
	// get the character from the i-th position
	character_from_the_line = line_from_the_file.at( i );

	// if the character is not empty, record the value
	if ( (character_from_the_line != ' ') ) {
	  value_from_the_line[value_recording_index] = character_from_the_line;
	  value_recording_index++;
	}   

      }

      // after reading in, we convert the read-in value to a double
      double readout_value = atof(value_from_the_line);

      // Now we're populating the correct variable by checking what is the name
      // of the EOS parameter that the current line holds; again, we can do this
      // because we know all the possible options:
      if ( (line_from_the_file.at(2) == 'n') && (line_from_the_file.at(3) == '0') ) {
	n0_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'E') && (line_from_the_file.at(3) == '0') ) {
	E0_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'K') && (line_from_the_file.at(3) == '0') ) {
	K0_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'E') && (line_from_the_file.at(3) == 's') ) {
	Esym_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'L') && (line_from_the_file.at(3) == 's') ) {
	Lsym_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'K') && (line_from_the_file.at(3) == 's') ) {
	Ksym_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'J') && (line_from_the_file.at(3) == 's') ) {
	Jsym_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'm') && (line_from_the_file.at(3) == 'N') ) {
	mN_CompOSE = readout_value;
      }
      if ( (line_from_the_file.at(2) == 'm') && (line_from_the_file.at(3) == 'P') ) {
	mP_CompOSE = readout_value;
      }

      continue;
    }

  } // while ( !CompOSE_EOS_input_file.eof() )
  
}



void read_and_convert_the_EOS_table (double n0_CompOSE,   // in fm^{-3}
				     double E0_CompOSE,   // in MeV
				     double K0_CompOSE,   // in MeV
				     double Esym_CompOSE, // in MeV
				     double Lsym_CompOSE, // in MeV
				     double Ksym_CompOSE, // in MeV
				     double Jsym_CompOSE, // in MeV
				     double mN_CompOSE,   // in MeV
				     double mP_CompOSE){
  //////////////////////////////////////////////////////////////////////////////
  // Specify an output file

  // declare the data file
  FILE *CompOSE_EOS_output_file;   
  std::string CompOSE_EOS_output_file_name = basic_data_file_address + "_Esym_exp";
    
  // The file name will reflect the particular EOS parameters used in the
  // conversion    
  if (take_E_asym_0) {
    CompOSE_EOS_output_file_name += ",_Esym=";
    std::stringstream data_1;
    data_1 << Esym_CompOSE;
    CompOSE_EOS_output_file_name += data_1.str();
  }

  if (take_L_asym) {
    CompOSE_EOS_output_file_name += ",_Lsym=";
    std::stringstream data_2;
    data_2 << Lsym_CompOSE;
    CompOSE_EOS_output_file_name += data_2.str();
  }

  if (take_K_asym) {
    CompOSE_EOS_output_file_name += ",_Ksym=";
    std::stringstream data_3;
    data_3 << Ksym_CompOSE;
    CompOSE_EOS_output_file_name += data_3.str();
  }

  if (take_J_asym) {
    CompOSE_EOS_output_file_name += ",_Jsym=";
    std::stringstream data_4;
    data_4 << Jsym_CompOSE;
    CompOSE_EOS_output_file_name += data_4.str();
  }

  if (assume_pure_neutron_matter) {
    CompOSE_EOS_output_file_name += ",_Yp=0";
  }

  if (subtract_leptons) {
    CompOSE_EOS_output_file_name += ",_minus_leptons";
  }

  if (use_charge_fraction_expansion) {
    CompOSE_EOS_output_file_name += ",_YQ_expansion";
  }
      
  CompOSE_EOS_output_file_name += ".txt";

  // initialize the data file
  CompOSE_EOS_output_file = fopen( CompOSE_EOS_output_file_name.c_str(), "w");

  // give an appropriate header
  std::fprintf(CompOSE_EOS_output_file,
	       "#\n"
	       "#nB[fm^-3]                nB/n0                 "
	       "E/A NS[MeV]           E/A HIC[MeV]       \n");



  //////////////////////////////////////////////////////////////////////////////
  // Read in and produce data
  //////////////////////////////////////////////////////////////////////////////

  // these will be used to read in the EOS table:
  double T_CompOSE = 0.0;                 // in MeV
  double nB_CompOSE = 0.0;                // in fm^{-3}
  double YQ_CompOSE = 0.0;                // [1]
  double pressure_CompOSE = 0.0;          // in MeV/fm^{-3}
  double scaled_muB_CompOSE = 0.0;        // muB - mN, in MeV
  double energy_density_CompOSE = 0.0;    // in MeV/fm^{-3}
  double proton_fraction_CompOSE = 0.0;   // [1]
  double electron_fraction_CompOSE = 0.0; // [1]
  double muon_fraction_CompOSE = 0.0;     // [1]

  
  //////////////////////////////////////////////////////////////////////////////
  // Set up variables for reading in the data
  //////////////////////////////////////////////////////////////////////////////  
  // a variable to read in a line from the file
  std::string line_from_the_file;
  // a variable to read in the first character from a line
  char first_character_from_the_line;

  
  //////////////////////////////////////////////////////////////////////////////
  // Open the file and check whether it exists
  //////////////////////////////////////////////////////////////////////////////
  std::string input_data_file_address = basic_data_file_address + ".txt";
  std::ifstream CompOSE_EOS_input_file( input_data_file_address.c_str() );
  make_sure_that_the_file_exists (CompOSE_EOS_input_file);

  //////////////////////////////////////////////////////////////////////////////
  // Read in the EOS table, convert it to symmetric matter, put in the output file
    
  while ( !CompOSE_EOS_input_file.eof() ) {
      
    getline(CompOSE_EOS_input_file, line_from_the_file);

    // discard an empty line (sometimes spurious empty lines are read in)
    if ( line_from_the_file.empty() ) {    
      continue;   // this is a throw-away line, we just continue!
    }

    // get the first character from the read-in line
    first_character_from_the_line = line_from_the_file.at(0);

    // discard the line if it starts with "#"
    if ( first_character_from_the_line == '#' ) {
      continue;   // this is a throw-away line, we just continue!
    }

    ////////////////////////////////////////////////////////////////////////////
    // If we're here, the read-in line contains EOS table data

    // convert to a stringstream
    std::stringstream string_to_get_data_from( line_from_the_file );

    // Read in the line onto variables; we can do this because we always demand
    // that CompOSE gives us files that look this way; see README above for more
    // details
    string_to_get_data_from >> T_CompOSE >> nB_CompOSE >> YQ_CompOSE
			    >> pressure_CompOSE >> scaled_muB_CompOSE
			    >> energy_density_CompOSE >> proton_fraction_CompOSE
			    >> electron_fraction_CompOSE >> muon_fraction_CompOSE;


    
    const double nucleon_energy_density = subtract_lepton_energy_density
      (nB_CompOSE, electron_fraction_CompOSE, muon_fraction_CompOSE,
       energy_density_CompOSE);

    const double EperA_NS_CompOSE = nucleon_energy_density/nB_CompOSE;

    const double sym_EperA_HIC_CompOSE = convert_to_symmetric_EOS
      (EperA_NS_CompOSE, nB_CompOSE, proton_fraction_CompOSE,
       n0_CompOSE, Esym_CompOSE, Lsym_CompOSE, Ksym_CompOSE, Jsym_CompOSE);
      
    ////////////////////////////////////////////////////////////////////////////
    // Write the data into a file
    std::fprintf(CompOSE_EOS_output_file,
		 "%10.6f              %10.6f              %10.6f            "
		 "%10.6f           \n",
		 nB_CompOSE, nB_CompOSE/n0_CompOSE, EperA_NS_CompOSE,
		 sym_EperA_HIC_CompOSE);

  } // while (file)

  fclose (CompOSE_EOS_output_file);
  
}


