idf_component_register(SRCS "m_alloc.c"
							"m_error_codes.c"
							"m_transformer_enum.c"
							"m_int_context.c"
							"m_int_files.c"
							"m_int_lv_log.c"
							"m_int_parameter.c"
							"m_int_pipeline.c"
							"m_int_profile.c"
							"m_int_representation.c"
							"m_int_sequence.c"
							"m_int_settings.c"
							"m_int_transformer.c"
							"m_int_transformer_init.c"
							"m_int_transformer_table.c"
							"m_int_hfunc.c"
							"m_effect.c"
					REQUIRES
							driver
							drivers
							ui
							teensy_comms
					INCLUDE_DIRS "." "../../../shared" "../../main" "../" "../ui" "../drivers")
