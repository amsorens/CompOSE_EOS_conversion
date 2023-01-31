# CompOSE_EOS_conversion
A code that converts EOS tables from CompOSE (note: in a specific format!) to a symmetric matter EOS.

To convert an EOS obtained from CompOSE with this code, your data file with the CompOSE EOS must have exactly the following structure:

```
# DNS(CMF) hadronic no electrons EOS from CompOSE: https://compose.obspm.fr/eos/117
#
# n0   = 0.15       fm^-3  
# E0   = -16.0      MeV
# K0   = 300.0      MeV
# Esym = 30.0       MeV
# Lsym = 88.0       MeV
# Ksym = 0.0        MeV
# mN   = 939.565421 MeV
# mP   = 938.272088 MeV
#
# T        nB        YQ        P        muB - mN        E        Yp        Ye        Ymu
#
0.0000000000000000        2.9999999999999999E-002   0.0000000000000000        1.7035236000000002E-002   2.8108878955468750        28.234852834098032        4.4524600000000001E-003   4.4524600000000001E-003   0.0000000000000000     
........
```

i.e., it must 

1) At the top of the file, have information on the EOS parameters n0 (saturation density), E0 (binding energy), K0 (incompressibility), Esym (0th coefficient of the symmetry energy expansion), Lsym (1st coefficient of the symmetry energy expansion), Ksym (2nd coefficient of the symmetry energy expansion), mN (neutron mass), mP (proton mass). The information must be given EXACTLY in the format shown, up to a single space, as names of the parameters are read based on the 3rd and 4th character in the line, and the values of the variables are read based on characters from 10th to 20th.

2) Have 9 data columns, with the following quantities in this exact order: temperature (in MeV), density (in fm^-3), charge fraction, pressure (in MeV fm^-3), scaled chemical potential (in MeV), energy density (in MeV fm^-3), proton fraction, electron fraction, muon fraction.

3) Have a .txt extension.

Some example files of this format are provided in the `results` folder.

To use this code, do the following:

1) Download the repository.
2) Create a `build` directory within the repository.
3) In the `build` directory, on the terminal, execute `cmake ..`. Note that this implies that the `CMakeLists.txt` file of the repository is one folder up from the location in which you execute the `cmake` command.
4) Review the file `/src/include/config.h`. The variable `std::string basic_data_file_address` controls which EOS data file from CompOSE it should use. as should be clear from the examples, you should not include the `.txt` extension in `basic_data_file_address`. Some example files are provided in the `results` folder. Additionally, you should review options for 
a) which symmetry expansion parameters to include, 
b) whether to assume that the EOS is one for pure neutron matter, 
c) whether to subtract leptons, and 
d) whether to use the symmetry energy charge fraction expansion for YQ. 
Make sure the relevant variables have the values you want before you compile.
5) In the `build` folder, on the terminal, execute `make` to compile.
6) Run the code by executing `./symmetry_energy_expansion_from_CompOSE_EOS`
7) The data file with the converted EOS will appear in the `results` folder. Note that while there is no guard against overwriting a data file, data file names are different when using different options from the config, so that it should never be a problem as long as the primary file with the EOS from CompOSE has a distinct name.

