cet_make_exec( extractCAFMetadata
               SOURCE extractCAFMetadata.cc
               LIBRARIES ROOT::Core ROOT::RIO
               )

cet_script(diff_cafs)

install_headers()
install_source()
