
include_directories( $ENV{IFBEAM_DIR}/include )
include_directories( $ENV{LIBWDA_DIR}/include )
include_directories( $ENV{IFDHC_DIR}/inc )
include_directories( $ENV{IFDH_ART_DIR}/include )
include_directories( $ENV{TRACE_INC} )

simple_plugin(EXTRetriever module
	${ART_FRAMEWORK_CORE}
	${ART_FRAMEWORK_SERVICES_REGISTRY}
	${ART_FRAMEWORK_SERVICES}
	${ART_FRAMEWORK_PRINCIPAL}
	art::Persistency_Common
	art::Utilities canvas::canvas
	${FHICLCPP}
	cetlib::cetlib cetlib_except::cetlib_except
	messagefacility::MF_MessageLogger
       	sbnobj::Common_POTAccounting
	sbndaq_artdaq_core::sbndaq-artdaq-core_Overlays_Common
  	sbndaq_artdaq_core::sbndaq-artdaq-core_Overlays
	sbndaq_artdaq_core::sbndaq-artdaq-core_Overlays_ICARUS	
        artdaq_core::artdaq-core_Utilities
        lardata::Utilities
        larcore::Geometry_AuxDetGeometry_service
)

install_headers()
install_fhicl()
install_source()

