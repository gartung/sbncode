include_directories($ENV{GENIE}/include/GENIE) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics

art_make( ### MIGRATE-ACTION-RECOMMENDED: use art_make_library(), art_dictionary(), simple_plugin() with explicit source lists
  LIBRARY_NAME sbncode_SBNEventWeight_Calculators_CrossSection
  LIB_LIBRARIES
    sbncode::SBNEventWeight_Base
    nugen::EventGeneratorBase_GENIE
    nugen::NuReweight_art
    nugen::NuReweight
    nurandom::RandomUtils_NuRandomService_service
    art::Framework_Principal
    ${ART_PERSISTENCY_PROVENANCE}
    art::Framework_Services_Registry
    ${FHICLCPP}
   #GENIE_LIB_LIST is explicitly listed below:
    LOG4CPP
    GFWMSG
    GFWREG
    GFWALG
    GFWINT
    GFWGHEP
    GFWNUM
    GFWUTL
    GFWPARDAT
    GFWEG
    GFWNTP
    GPHXSIG
    GPHPDF
    GPHNUCLST
    GPHCMN
    GPHDCY
    GPHHADTRANSP
    GPHHADNZ
    GPHDEEX
    GPHAMNGXS
    GPHAMNGEG
    GPHCHMXS
    GPHCOHXS
    GPHCOHEG
    GPHDISXS
    GPHDISEG
    GPHDFRCXS
    GPHDFRCEG
    GPHGLWRESXS
    GPHGLWRESEG
    GPHIBDXS
    GPHIBDEG
    GPHMNUCXS
    GPHMNUCEG
    GPHMEL
    GPHNUELXS
    GPHNUELEG
    GPHQELXS
    GPHQELEG
    GPHRESXS
    GPHRESEG
    GPHSTRXS
    GPHSTREG
    GPHNDCY
    GTLGEO
    GTLFLX
    GRWFWK
    GRWIO
    GRWCLC
	GSL
    #GENIE libraries are above
    ${MF_MESSAGELOGGER}
    cetlib_except::cetlib_except
)

install_headers()
install_fhicl()
install_source()

