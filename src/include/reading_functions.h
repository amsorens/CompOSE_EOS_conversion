#ifndef READING_FUNCTIONS_H_
#define READING_FUNCTIONS_H_

void make_sure_that_the_file_exists (std::ifstream& CompOSE_EOS_input_file);

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
			  double& mP_CompOSE);



void read_and_convert_the_EOS_table (double n0_CompOSE,   // in fm^{-3}
				     double E0_CompOSE,   // in MeV
				     double K0_CompOSE,   // in MeV
				     double Esym_CompOSE, // in MeV
				     double Lsym_CompOSE, // in MeV
				     double Ksym_CompOSE, // in MeV
				     double Jsym_CompOSE, // in MeV
				     double mN_CompOSE,   // in MeV
				     double mP_CompOSE);

#endif // READING_FUNCTIONS_H_
