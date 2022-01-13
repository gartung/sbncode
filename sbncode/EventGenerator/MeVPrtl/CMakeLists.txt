find_package(ifdhc) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
find_package(dk2nudata) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
find_package(dk2nugenie) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking

link_directories( $ENV{ROOTSYS}/lib ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics
link_directories( $ENV{DK2NUDATA_LIB} ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics
link_directories( $ENV{DK2NUGENIE_LIB} ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics

add_subdirectory(Tools)
add_subdirectory(config)

simple_plugin( MeVPrtlGen module
              art::Framework_Core
              art::Framework_Services_Registry
              art_root_io::TFileService_service
				      art_root_io::TFileService_service
				      art_root_io::tfile_support
              art::Framework_Principal
              art::Persistency_Common
              art::Utilities canvas::canvas
              ${MF_MESSAGELOGGER}
              ${MF_UTILITIES}
              ${FHICLCPP}
              cetlib::cetlib cetlib_except::cetlib_except
              ${ROOT_EVE_LIB_LIST}
              ${ROOT_X3d}
              ${ROOT_CORE}
              ${ROOT_BASIC_LIB_LIST}
        			${ROOT_XMLIO}
        			CLHEP::CLHEP
		nusimdata::SimulationBase
              larcorealg::Geometry
        			nurandom::RandomUtils_NuRandomService_service
        			larcoreobj::SummaryData
        			sbnobj::Common_EventGen_MeVPrtl
        			sbncode::EventGenerator_MeVPrtl_Constants
)

simple_plugin( MeVPrtlTestRayTrace module
                            art::Framework_Core
                            art::Framework_Services_Registry
                            art_root_io::TFileService_service
				art_root_io::TFileService_service
				art_root_io::tfile_support
                            art::Framework_Principal
                            art::Persistency_Common
                            art::Utilities canvas::canvas
                            ${MF_MESSAGELOGGER}
                            ${MF_UTILITIES}
                            ${FHICLCPP}
                            cetlib::cetlib cetlib_except::cetlib_except
                            ${ROOT_EVE_LIB_LIST}
                            ${ROOT_X3d}
                            ${ROOT_CORE}
                            ${ROOT_BASIC_LIB_LIST}
			${ROOT_XMLIO}
			CLHEP::CLHEP
			nurandom::RandomUtils_NuRandomService_service
			larcoreobj::SummaryData
        		sbnobj::Common_EventGen_MeVPrtl
			sbncode::EventGenerator_MeVPrtl_Constants
)



install_headers()
install_fhicl()
install_source()
