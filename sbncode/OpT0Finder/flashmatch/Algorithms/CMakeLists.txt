set( ROOTLIB -L$ENV{ROOTSYS}/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMinuit -pthread -lm -ldl) ### MIGRATE-ACTION-RECOMMENDED: use of $ENV{... may be UPS-dependent

link_libraries( ${LIB_NAME} -L$ENV{BOOST_LIB} -lboost_system ${ROOTLIB} ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics ### MIGRATE-ACTION-RECOMMENDED: use of $ENV{... may be UPS-dependent

art_make( ### MIGRATE-ACTION-RECOMMENDED: use art_make_library(), art_dictionary(), simple_plugin() with explicit source lists
    LIB_LIBRARIES
        larsim::PhotonPropagation
        larsim::PhotonPropagation_PhotonVisibilityService_service
        larsim::LegacyLArG4
        #sbncode::OpT0Finder_flashmatch_GeoAlgo
        sbncode::OpT0Finder_flashmatch_Base
        larcorealg::GeoAlgo
        art::Framework_Core
        art::Framework_Principal
        ${ART_FRAMEWORK_BASIC}
        art::Framework_Services_Registry
        art_root_io::TFileService_service
        ${ART_PERSISTENCY_COMMON}
        ${ART_PERSISTENCY_PROVENANCE}
        ${ART_UTILITIES}
        ${ROOT_BASIC_LIB_LIST}
        ${FHICLCPP}
        ${CETLIB}
)

install_headers()
install_source()
