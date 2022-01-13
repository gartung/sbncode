art_make( ### MIGRATE-ACTION-RECOMMENDED: use art_make_library(), art_dictionary(), simple_plugin() with explicit source lists
  LIBRARY_NAME sbncode::SBNEventWeight_Base
  LIB_LIBRARIES
    sbnobj::Common_SBNEventWeight
    nurandom::RandomUtils_NuRandomService_service
    art::Framework_Services_Registry
    ${ART_FRAMEWORK_SERVICES_OPTIONAL_RANDOMNUMBERGENERATOR_SERVICE}
    ${ART_UTILITIES}
    ${ROOT_BASIC_LIB_LIST}
    CLHEP::CLHEP
    canvas::canvas
    cetlib_except::cetlib_except
)

install_headers()
install_fhicl()
install_source()

