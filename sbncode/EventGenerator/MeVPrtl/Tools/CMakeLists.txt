
find_library( IFDH NAMES ifdh PATHS $ENV{IFDHC_DIR}/lib) ### MIGRATE-ACTION-RECOMMENDED: use of ENV ... may be UPS-dependent ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
include_directories( $ENV{IFDHC_DIR}/inc ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics

find_library( DK2NUTREE NAMES dk2nuTree PATHS $ENV{DK2NUDATA_LIB})
find_library( DK2NUGENIE NAMES dk2nuGenie PATHS $ENV{DK2NUGENIE_LIB})

art_make_library( LIBRARY_NAME sbncode::EventGenerator_MeVPrtl_Constants
          SOURCE Constants.cpp
          LIBRARIES
                        ROOT::Core
                        ROOT::Eve
                        ROOT::X3d
                            fhiclcpp::fhiclcpp
                            cetlib::cetlib cetlib_except::cetlib_except
        )


simple_plugin( EmptyKaonGen tool
                            art::Framework_Core
                            art::Framework_Services_Registry
                            art_root_io::TFileService_service
                            art::Framework_Principal
                            art::Persistency_Common
                            art::Utilities canvas::canvas
                            ${MF_MESSAGELOGGER}
                            ${MF_UTILITIES}
                            fhiclcpp::fhiclcpp
                            cetlib::cetlib cetlib_except::cetlib_except
                            ROOT::Eve
                            ROOT::X3d
                            ROOT::Core
			CLHEP::CLHEP
			nurandom::RandomUtils_NuRandomService_service
			nusimdata::SimulationBase
			sbncode::EventGenerator_MeVPrtl_Constants
)


simple_plugin( NuMiKaonGen tool
                            ifdh_art::IFDH_service
                            art::Framework_Core
                            art::Framework_Services_Registry
                            art_root_io::TFileService_service 
                            art::Framework_Principal
                            art::Persistency_Common
                            art::Utilities canvas::canvas
                            ${MF_MESSAGELOGGER}
                            ${MF_UTILITIES}
                            fhiclcpp::fhiclcpp
                            cetlib::cetlib cetlib_except::cetlib_except
                            ROOT::Eve
                            ROOT::X3d
                            ROOT::Core
			CLHEP::CLHEP
			ifdh::ifdh
			${DK2NUTREE}
			nurandom::RandomUtils_NuRandomService_service
			nusimdata::SimulationBase
			sbncode::EventGenerator_MeVPrtl_Constants
)

simple_plugin( WeightedRayTraceBox tool
                            art::Framework_Core
                            art::Framework_Services_Registry
                            art_root_io::TFileService_service 
                            art::Framework_Principal
                            art::Persistency_Common
                            art::Utilities canvas::canvas
                            ${MF_MESSAGELOGGER}
                            ${MF_UTILITIES}
                            fhiclcpp::fhiclcpp
                            cetlib::cetlib cetlib_except::cetlib_except
                            ROOT::Eve
                            ROOT::X3d
                            ROOT::Core
			CLHEP::CLHEP
			larcorealg::Geometry
			nurandom::RandomUtils_NuRandomService_service
			${DK2NUGENIE}
			${DK2NUTREE}
			sbncode::EventGenerator_MeVPrtl_Constants
                        sbnobj::Common_EventGen_MeVPrtl
)

simple_plugin( MixedWeightRayTraceBox tool
                            art::Framework_Core
                            art::Framework_Services_Registry
                            art_root_io::TFileService_service
                            art::Framework_Principal
                            art::Persistency_Common
                            art::Utilities canvas::canvas
                            ${MF_MESSAGELOGGER}
                            ${MF_UTILITIES}
                            fhiclcpp::fhiclcpp
                            cetlib::cetlib cetlib_except::cetlib_except
                            ROOT::Eve
                            ROOT::X3d
                            ROOT::Core
			CLHEP::CLHEP
			larcorealg::Geometry
			nurandom::RandomUtils_NuRandomService_service
			dk2nuTree
			sbncode::EventGenerator_MeVPrtl_Constants
)




simple_plugin( ReThrowRayTraceBox tool
                            art::Framework_Core
                            art::Framework_Services_Registry
                            art_root_io::TFileService_service
                            art::Framework_Principal
                            art::Persistency_Common
                            art::Utilities canvas::canvas
                            ${MF_MESSAGELOGGER}
                            ${MF_UTILITIES}
                            fhiclcpp::fhiclcpp
                            cetlib::cetlib cetlib_except::cetlib_except
                            ROOT::Eve
                            ROOT::X3d
                            ROOT::Core
			CLHEP::CLHEP
			larcorealg::Geometry
			nurandom::RandomUtils_NuRandomService_service
			sbncode::EventGenerator_MeVPrtl_Constants
)

simple_plugin( RayTraceBox tool
                            art::Framework_Core
                            art::Framework_Services_Registry
                            art_root_io::TFileService_service
                            art::Framework_Principal
                            art::Persistency_Common
                            art::Utilities canvas::canvas
                            ${MF_MESSAGELOGGER}
                            ${MF_UTILITIES}
                            fhiclcpp::fhiclcpp
                            cetlib::cetlib cetlib_except::cetlib_except
                            ROOT::Eve
                            ROOT::X3d
                            ROOT::Core
			CLHEP::CLHEP
			larcorealg::Geometry
			nurandom::RandomUtils_NuRandomService_service
			sbncode::EventGenerator_MeVPrtl_Constants
)

add_subdirectory(Higgs)
add_subdirectory(HNL)

install_headers()
install_fhicl()
install_source()
