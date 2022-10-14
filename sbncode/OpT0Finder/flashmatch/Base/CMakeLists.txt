set( ROOTLIB ROOT::Core  ROOT::RIO ROOT::Net ROOT::Hist ROOT::Graf ROOT::Graf3d ROOT::Gpad ROOT::Tree ROOT::Rint ROOT::Postscript ROOT::Matrix ROOT::Physics ROOT::MathCore ROOT::Thread ) ### MIGRATE-ACTION-RECOMMENDED: use of $ENV{... may be UPS-dependent
art_make( ### MIGRATE-ACTION-RECOMMENDED: use art_make_library(), art_dictionary(), simple_plugin() with explicit source lists
    LIB_LIBRARIES
        #sbncode::OpT0Finder_flashmatch_GeoAlgo
        larcorealg::GeoAlgo
        larcorealg::Geometry
        larcore::Geometry_Geometry_service
        lardataalg::DetectorInfo
        art::Persistency_Provenance
        art::Utilities
        canvas::canvas
        art::Utilities canvas::canvas
        art::Framework_Core
        art::Framework_IO_Sources
        art::Framework_Principal
        art::Framework_Services_Registry
        art_root_io::tfile_support ${ROOT_CORE}
        art_root_io::TFileService_service
        ${ART_PERSISTENCY_COMMON}
        ${ART_PERSISTENCY_PROVENANCE}
        ${ART_UTILITIES}
        ${MF_MESSAGELOGGER}
        ${MF_UTILITIES}
        ${CETLIB}
        CLHEP::CLHEP
        Boost::system
        ${ROOTLIB}
        ${FHICLCPP}
        cetlib::cetlib cetlib_except::cetlib_except
)

install_headers()
install_source()
