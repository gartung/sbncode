add_subdirectory(TrackHit)
add_subdirectory(TrackSplit)
add_subdirectory(VertexStub)
add_subdirectory(CalorimetryAnalysis)

link_directories( ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics
 $ENV{ROOTSYS}/lib
)

simple_plugin(NuVertexChargeTree module
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
	${ROOT_BASIC_LIB_LIST}
	messagefacility::MF_MessageLogger
        lardata::DetectorInfoServices_DetectorClocksServiceStandard_service
	sbnobj::Common_Reco
	lardataobj::AnalysisBase
        lardataalg::DetectorInfo        
        art_root_io::tfile_support
        art_root_io::art_root_io
        art_root_io::dict
        caf_RecoUtils
        larsim::MCCheater_BackTrackerService_service
        nusimdata::SimulationBase
        larcorealg::Geometry
        larcore::Geometry_Geometry_service
	larpandora::LArPandoraInterface
        larsim::MCCheater_ParticleInventoryService_service
	sbn_LArReco	    
	sbncode::TPCReco_VertexStub
)

link_directories( $ENV{IFDHC_DIR}/lib )

simple_plugin ( EventSelect module
               ifdh_art::IFDH_service
               art::Framework_Core
               art::Framework_Principal
               art::Framework_Services_Registry
               art::Utilities canvas::canvas
               ${MF_MESSAGELOGGER}
               ${MF_UTILITIES}
               ${FHICLCPP}
               cetlib::cetlib cetlib_except::cetlib_except
               lardataalg::DetectorInfo        
	${ROOT_EVE_LIB_LIST}
	ROOT::X3d
	${ROOT_BASIC_LIB_LIST}
)


install_headers()
install_fhicl()
install_source()

