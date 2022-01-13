link_directories( ### MIGRATE-ACTION-RECOMMENDED: use target_link_libraries() with target semantics
 $ENV{ROOTSYS}/lib
)

simple_plugin( TrackCaloSkimmer module
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
	art_root_io::tfile_support
	art_root_io::art_root_io
	art_root_io::dict
        lardataobj::AnalysisBase
        lardataobj::RecoBase
        larcorealg::Geometry
        larcore::Geometry_Geometry_service
        larcorealg::GeoAlgo
	sbnobj::Common_Reco
	larcorealg::GeoAlgo
	lardata::DetectorInfoServices_DetectorPropertiesServiceStandard_service
	lardataalg::DetectorInfo
	ROOT::Minuit
	sbncode::CAFMaker
        sbnobj::Common_Calibration_dict
        larevt::SpaceCharge
)

simple_plugin(TrackCaloSkimmerSelectStoppingTrack tool
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
        larcorealg::Geometry
	larcorealg::GeoAlgo
	lardata::DetectorInfoServices_DetectorPropertiesServiceStandard_service
	lardataalg::DetectorInfo
        larevt::SpaceCharge
        sbnobj::Common_Calibration_dict
)

simple_plugin(TrackCaloSkimmerSelectAnode2CathodeTrack tool
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
        sbnobj::Common_Calibration_dict
        larevt::SpaceCharge
)

link_directories( $ENV{IFDHC_DIR}/lib )
simple_plugin ( DataSelect module
               ifdh_art::IFDH_service
               art::Framework_Core
               art::Framework_Principal
               art::Framework_Services_Registry
               art::Utilities canvas::canvas
               ${MF_MESSAGELOGGER}
               ${MF_UTILITIES}
               ${FHICLCPP}
               cetlib::cetlib cetlib_except::cetlib_except
        ${ROOT_EVE_LIB_LIST}
        ROOT::X3d
        ${ROOT_BASIC_LIB_LIST}
        sbnobj::Common_Calibration_dict
	larevt::SpaceCharge
        lardataobj::RecoBase
)


add_subdirectory(fcl)

install_headers()
install_fhicl()
install_source()

