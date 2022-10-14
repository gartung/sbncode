#link_directories( ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics
# $ENV{ROOTSYS}/lib
#)

add_subdirectory(LArReco)
art_make( 
  LIB_LIBRARIES
		fhiclcpp::fhiclcpp
		art::Persistency_Provenance canvas
		${ROOT_BASIC_LIB_LIST}
		sbncode_GeoWrappers

  MODULE_LIBRARIES
	art::Framework_Core
	art::Framework_Services_Registry
	art_root_io::TFileService_service 
	art::Framework_Principal
	art::Persistency_Common
	art::Utilities canvas::canvas
	${MF_MESSAGELOGGER}
	${MF_UTILITIES}
	${FHICLCPP}
	cetlib::cetlib cetlib_except::cetlib_except
	${ROOT_EVE_LIB_LIST}
	ROOT::X3d
	ROOT::Core
	messagefacility::MF_MessageLogger
        ROOT::EG
	sbn_LArReco	    
        sbncode_LArRecoProducer
	sbnobj::Common_CRT
	sbnobj::Common_Reco
	lardataobj::RecoBase_AssnsDicts_dict
	lardataobj::RecoBase_dict	
	lardataobj::RecoBase
)

install_headers()
install_fhicl()
install_source()

