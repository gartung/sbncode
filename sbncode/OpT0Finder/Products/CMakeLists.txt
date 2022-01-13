# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
# include_directories( $ENV{NUTOOLS_INC} ) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
get_target_property(DICT_INC_DIR lardataobj::RecoBase INTERFACE_INCLUDE_DIRECTORIES)
include_directories( ${DICT_INC_DIR} )
get_target_property(DICT_INC_DIR larcorealg::Geometry INTERFACE_INCLUDE_DIRECTORIES)
include_directories( ${DICT_INC_DIR} )
get_target_property(DICT_INC_DIR larcoreobj::SimpleTypesAndConstants INTERFACE_INCLUDE_DIRECTORIES)
include_directories( ${DICT_INC_DIR} )

art_make( ### MIGRATE-ACTION-RECOMMENDED: use art_make_library(), art_dictionary(), simple_plugin() with explicit source lists
    LIB_LIBRARIES
        lardataobj::RecoBase
        ROOT::Core
        ROOT::Eg
)

install_headers()
install_fhicl()
install_source()
