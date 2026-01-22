idf_component_register(SRCS "m_int_button.c"
							"m_int_home_view.c"
							"m_int_menu.c"
							"m_int_parameter_widget.c"
							"m_int_profile_view.c"
							"m_int_profile_settings.c"
							"m_int_sequence_list.c"
							"m_int_sequence_view.c"
							"m_int_transformer_select.c"
							"m_int_transformer_settings.c"
							"m_int_transformer_view.c"
							"m_int_ui.c"
					REQUIRES
							driver
							drivers
							teensy_comms
					INCLUDE_DIRS "." "../../../shared" "../../main" "../" "../core")

