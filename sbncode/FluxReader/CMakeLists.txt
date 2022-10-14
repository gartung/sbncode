cet_enable_asserts()
include_directories ( $ENV{GENIE}/include/GENIE ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
include_directories ( $ENV{GENIE}/include ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
include_directories ( $ENV{DK2NUDATA_INC} ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
include_directories ( $ENV{DK2NUGENIE_INC} ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
link_directories( $ENV{DK2NUDATA_LIB}) ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics

file(GLOB INTERFACEFILES *Interface* )

simple_plugin( FluxReader
               "source"
               sbncode::FluxReader
               larcore::Geometry_Geometry_service 
               nutools::EventGeneratorBase_CRY
               lardata::Utilities
               ${ART_FRAMEWORK_PERSISTENCY_COMMON}
)

simple_plugin ( FluxGeoFilter "module"
                art::Framework_Core
                art::Framework_Principal
                art::Framework_Services_Registry
                art_root_io::TFileService_service
                art_root_io::tfile_support
                art::Persistency_Common canvas::canvas
                art::Persistency_Provenance canvas::canvas
                art::Utilities canvas::canvas
                ${MF_MESSAGELOGGER}
                nusimdata::SimulationBase
                larcore::Geometry_Geometry_service
               lardata::Utilities
                larcorealg::Geometry
                ROOT::Geom
                ${ROOT_BASIC_LIB_LIST}
)

art_make_library( LIBRARY_NAME sbncode::FluxReader_FluxInterface
                  SOURCE	${INTERFACEFILES}
                  LIBRARIES
                  nusimdata::SimulationBase
               larcore::Geometry_Geometry_service 
                  # GENIE STUFF #####################################
                  xml2

                  log4cpp::log4cpp
                  GENIE::GFwEG
                  GENIE::GFwAlg
                  GENIE::GFwMsg
                  GENIE::GFwGHEP
                  GENIE::GTlFlx
                  dk2nu::Tree
                  GENIE::GFwParDat
                  #${DK2NUDATA}
                  ${DK2NUGENIE}
                  ####################################################
                  cetlib::cetlib cetlib_except::cetlib_except
               lardata::Utilities

                  ${FHICLCPP}
                  ${MF_MESSAGELOGGER}
                  CLHEP::CLHEP
                  ROOT::Core ROOT::Tree
                  ${Boost_SYSTEM_LIBRARY}
)

art_make( EXCLUDE FluxReader_source.cc ${INTERFACEFILES} FluxGeoFilter_module.cc
          LIB_LIBRARIES	nusimdata_SimulationBase
                        sbncode_FluxReader_FluxInterface
                        larcoreobj_SummaryData
                        ${ART_FRAMEWORK_CORE}
                        ${ART_FRAMEWORK_IO_SOURCES}
                        ${ART_FRAMEWORK_PRINCIPAL}
                        ${ART_FRAMEWORK_SERVICES_REGISTRY}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL}
                        art_root_io::TFileService_service
                        art_root_io::tfile_support
                        art::Persistency_Common canvas::canvas
                        art::Persistency_Provenance canvas::canvas
                        art::Utilities canvas::canvas
                        ${MF_MESSAGELOGGER}
                        ${MF_UTILITIES}
                        ${FHICLCPP}
                        ${Boost_SYSTEM_LIBRARY}
                        ROOT::Core ROOT::Tree
                        cetlib::cetlib cetlib_except::cetlib_except
               nutools::EventGeneratorBase_CRY
               lardata::Utilities

          MODULE_LIBRARIES sbncode::FluxReader
                        sbncode::FluxReader_FluxInterface
                        nusimdata::SimulationBase
                        larcoreobj::SummaryData
               larcore::Geometry_Geometry_service 
               lardata::Utilities
                        art::Framework_Core
                        art::Framework_IO_Sources
                        art::Framework_Principal
                        art::Framework_Services_Registry
                        art_root_io::TFileService_service
                        art_root_io::TFileService_service
                        art_root_io::tfile_support
                        messagefacility::MF_MessageLogger
                        fhiclcpp::fhiclcpp
                        cetlib cetlib_except
                        # GENIE STUFF #####################################
                        xml2
                        log4cpp::log4cpp
                        GENIE::GFwEG
                        GENIE::GFwAlg
                        GENIE::GFwMsg
                        GENIE::GFwGHEP
                        GENIE::GTlFlx
                        GENIE::GFwParDat
                        ${GBASE}
                        ${GEVGCORE}
                        ${GEVGDRIVERS}
                        ${GFLUXDRIVERS}
                        ${GINTERACTION}
                        ${DK2NUDATA}
                        ${DK2NUGENIE}
                        ####################################################
                        ${Boost_SYSTEM_LIBRARY}
                        ROOT::Core ROOT::Tree
)

install_headers()
install_source()
install_fhicl()

add_subdirectory(job)
