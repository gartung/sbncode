#======================================================================
#  larsoft main build file
#
#  cd .../path/to/build/directory
#  source .../path/to/larsoft/ups/setup_for_development <-d|-p>
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path]
#        -DCMAKE_BUILD_TYPE=$CETPKG_TYPE
#        $CETPKG_SOURCE
#  make
#  make test
#  make install
#  make package (builds distribution tarfile)
# ======================================================================
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)



find_package(cetmodules 2.29.07 REQUIRED)
project(sbncode VERSION 09.35.00 LANGUAGES CXX)

message(STATUS "\n\n  ==========================   ${PROJECT_NAME}   ==========================")


include(CetCMakeEnv)
cet_cmake_env()

# The specification of the C++ standard is required because CET macros
# set it to C++98 by default, and then override it depending on the
# compiler version, as determined by the compiler qualifier.
# Removing that qualifier, we need to supply that information manually,
# and maintain it too.
cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  ALLOW_DEPRECATIONS
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs -Wno-undefined-var-template
)
set(fcl_dir caf)
cet_report_compiler_flags(REPORT_THRESHOLD VERBOSE)

# these are minimum required versions, not the actual product versions
find_package(art) 
find_package(messagefacility) 
find_package(art_root_io) 
find_package(nusimdata) 
find_package(nug4) 
find_package(nugen) 
find_package(nurandom) 
find_package(nutools) 
find_package(GENIE) 
find_package(lardataobj) 
find_package(larcoreobj) 
find_package(larcorealg) 
find_package(lardataalg) 
find_package(larcore) 
find_package(lardata) 
find_package(larevt) 
find_package(larsim) 
find_package(larreco) 
find_package(larpandora) 
find_package(larpandoracontent) 
find_package(artdaq_core ) 
find_package(sbnobj ) 
find_package(sbnanaobj )
find_package(sbndaq_artdaq_core )
find_package(sbndata) 
find_package(ifdhc) 
find_package(ifdh_art) 
find_package(ifbeam)
find_package(ifbeam_art)
find_package( trace )
find_package( libwda )

find_package(CLHEP COMPONENTS ALL)
find_package(ROOT REQUIRED)
find_package(Geant4 REQUIRED)
find_package(Boost COMPONENTS system)
find_library( GSL NAMES gsl )
find_library( LOG4CPP NAMES log4cpp )
find_library( XML2 NAMES xml2 )

# macros for dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

add_subdirectory(sbncode)
add_subdirectory(fcl)

# packaging utility
cet_cmake_config()
