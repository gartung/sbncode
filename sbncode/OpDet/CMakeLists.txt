cet_enable_asserts()

art_make(   TOOL_LIBRARIES ### MIGRATE-ACTION-RECOMMENDED: use art_make_library(), art_dictionary(), simple_plugin() with explicit source lists
	    art::Utilities
	    ${FHICLCPP}
	    ${CETLIB}
)

install_headers()
install_source()
install_fhicl()
