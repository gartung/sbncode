
art_make_library( LIBRARY_NAME sbn_LArReco
  SOURCE  TrackMomentumCalculator.cxx TrajectoryMCSFitter.cxx
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
        lardataobj::RecoBase larcorealg::CoreUtils lardata::RecoObjects
        ROOT::Minuit
        ROOT::Minuit2
        ROOT::Graf3d
                )
