
art_make_library( LIBRARY_NAME caf_RecoUtils
                  SOURCE  RecoUtils.cc
                  LIBRARIES 
		    art::Framework_Core
		    art::Framework_Services_Registry
		    art::Framework_Principal
		    art::Persistency_Common
		    art::Utilities canvas::canvas
                    ${ROOT_BASIC_LIB_LIST}
		    ${MF_MESSAGELOGGER}
		    ${MF_UTILITIES}
		    ${FHICLCPP}
                    cetlib::cetlib cetlib_except::cetlib_except
		    larsim::MCCheater_BackTrackerService_service
		    larsim::MCCheater_ParticleInventoryService_service
                    larcorealg::Geometry
                    larcore::Geometry_DumpGeometry_module
                )
