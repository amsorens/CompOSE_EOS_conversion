#########################
# Copyright 2023
#  Agnieszka Sorensen
#########################

cmake_minimum_required(VERSION 3.17)
project(symmetry_energy_expansion_from_CompOSE_EOS)
find_package(GSL 2.0 REQUIRED)
include_directories(SYSTEM ${GSL_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)

set(sym_energy_exp_sources

./src/basic_functions.cc
./src/reading_functions.cc

)

add_executable(symmetry_energy_expansion_from_CompOSE_EOS ./src/symmetry_energy_expansion_from_CompOSE_EOS.cc ${sym_energy_exp_sources})

target_link_libraries(symmetry_energy_expansion_from_CompOSE_EOS ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY})
