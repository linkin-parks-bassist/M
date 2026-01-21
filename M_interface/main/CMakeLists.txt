idf_component_register(SRCS "m_int.c"
					REQUIRES
							esp_timer
							fatfs
							drivers
							ui
							core
							teensy_comms
					INCLUDE_DIRS "." "../../shared" "../include")

target_compile_options(${COMPONENT_LIB} PRIVATE -DM_INTERFACE)
