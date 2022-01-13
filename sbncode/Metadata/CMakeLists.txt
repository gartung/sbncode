cet_enable_asserts()

set( sbn_meta_lib_list   art::Framework_Core
                         art::Framework_Principal
                         art::Framework_Services_Registry
                         ${ART_FRAMEWORK_SERVICES_SYSTEM_FILECATALOGMETADATA_SERVICE}
                         art::Framework_Services_System_TriggerNamesService_service
			 art::Persistency_Common canvas::canvas
			 art::Persistency_Provenance canvas::canvas
                         ${MF_MESSAGELOGGER}
                         ROOT::Core
                         larcoreobj::SummaryData
    )

simple_plugin( FileCatalogMetadataSBN  "service"
               ${sbn_meta_lib_list}
        )

simple_plugin( MetadataSBN "service"
               ${sbn_meta_lib_list}
               art::Framework_IO
               art::Framework_IO_detail
        )

install_headers()
install_fhicl()
install_source()
