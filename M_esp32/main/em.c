#include "em.h"

em_context global_cxt;

em_transformer_view_str tv;

void app_main()
{
	init_em_context(&global_cxt);
	
	lv_disp_t *disp;
	init_display(&disp);
	
	init_em_msg_queue();
	
	//queue_msg_to_teensy(create_et_msg_no_data(ET_MESSAGE_CREATE_PROFILE));
	//queue_msg_to_teensy(create_et_msg		 (ET_MESSAGE_APPEND_TRANSFORMER, "ss", 1, TRANSFORMER_DISTORTION));
	//queue_msg_to_teensy(create_et_msg		 (ET_MESSAGE_APPEND_TRANSFORMER, "ss", 1, TRANSFORMER_COMPRESSOR));
	
	begin_em_comms();
	
	if (lvgl_port_lock(-1))
	{
		make_ui(disp);
		lvgl_port_unlock();
	}
	
	
	//queue_msg_to_teensy(create_et_msg		 (ET_MESSAGE_SWITCH_PROFILE, 	 "s",  1));
}
