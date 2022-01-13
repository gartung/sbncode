link_directories( ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics
 $ENV{ROOTSYS}/lib
)

art_make_library(
	LIBRARY_NAME sbn_LArReco_PCA
	SOURCE PCA.cc
	LIBRARIES
	sbnobj::Common_Reco
	lardataobj::RecoBase_AssnsDicts_dict
	lardataobj::RecoBase_dict	
	sbndcode_OpDetSim
)

simple_plugin(PCAnglePlaneMaker module
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
	${ROOT_X3d}
	${ROOT_BASIC_LIB_LIST}
	messagefacility::MF_MessageLogger

	sbnobj::Common_Reco
	lardataobj::AnalysisBase
        larcorealg::Geometry
        larcore::Geometry_Geometry_service
	sbn_LArReco_PCA
)

simple_plugin(PCAngleKinkFinder module
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
	${ROOT_X3d}
	${ROOT_BASIC_LIB_LIST}
	messagefacility::MF_MessageLogger
	Minuit

	sbnobj::Common_Reco
	lardataobj::AnalysisBase
        larcorealg::Geometry
        larcore::Geometry_Geometry_service
)

simple_plugin(PCAngleKinkTree module
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
	${ROOT_X3d}
	${ROOT_BASIC_LIB_LIST}
	messagefacility::MF_MessageLogger

	sbnobj::Common_Reco
	lardataobj::AnalysisBase
        
        art_root_io::tfile_support
        art_root_io::art_root_io
        art_root_io::dict
        caf_RecoUtils
        larsim::MCCheater_BackTrackerService_service
        nusimdata::SimulationBase
        larcorealg::Geometry
        larcore::Geometry_Geometry_service
	sbn_LArReco_PCA
)

install_headers()
install_fhicl()
install_source()

