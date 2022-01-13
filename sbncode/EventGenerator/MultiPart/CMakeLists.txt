# Add the subfolder containing the deconvolution tools
art_make(  ### MIGRATE-ACTION-RECOMMENDED: use art_make_library(), art_dictionary(), simple_plugin() with explicit source lists
          MODULE_LIBRARIES larcorealg::Geometry
            larcore::Geometry_Geometry_service
            lardata::Utilities
            larevt::Filters
            lardataobj::RawData
            larevt::CalibrationDBI_IOVData
            larevt::CalibrationDBI_Providers
            lardataobj::RecoBase
            lardata::ArtDataHelper
            larsim::Simulation nug4::ParticleNavigation 
            lardataobj::Simulation
            nusimdata::SimulationBase
            lardata::Utilities
            lardataobj::MCBase
            larcoreobj::SummaryData
            nusimdata::SimulationBase
            nurandom::RandomUtils_NuRandomService_service
            lardataobj::MCBase
            CLHEP::CLHEP
            art::Framework_Core
            art::Framework_Principal
            art::Framework_Services_Registry
            art_root_io::tfile_support ${ROOT_CORE}
            art_root_io::TFileService_service
            art::Persistency_Common
            art::Persistency_Provenance
            art::Utilities
            canvas::canvas
            ${MF_MESSAGELOGGER}
            ${MF_UTILITIES}
            ${FHICLCPP}
            ${CETLIB}
            ${ROOT_FFTW}
            ${ROOT_BASIC_LIB_LIST}
	    ROOT::EG
        )

install_headers()
install_fhicl()
install_source()

