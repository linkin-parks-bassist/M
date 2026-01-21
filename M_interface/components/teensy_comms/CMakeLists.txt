idf_component_register(SRCS "m_comms.c"
							"m_int_comms.c"
							"m_int_profile_send.c"
					REQUIRES
							driver
							drivers
					INCLUDE_DIRS "." "../../../shared" "../../include" "../" "../core")


