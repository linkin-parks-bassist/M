#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "em.h"

em_context global_cxt;

//#define ERASE_SD_CARD

void app_main()
{
	srand(time(0));
	
	init_em_context(&global_cxt);
	
	lv_disp_t *disp;
	init_display(&disp);
	
	init_em_msg_queue();
	
	begin_em_comms();
	
	init_sd_card();
	
	#ifdef ERASE_SD_CARD
	string_ll *file_list = list_files_in_directory(MOUNT_POINT);
	
	printf("Erasing sd card. File list: %p\n", file_list);
	while (file_list)
	{
		printf("Removing file %s...\n", file_list->data);
		remove(file_list->data);
		file_list = file_list->next;
	}
	
	char buf[128];
	sprintf(buf, "%s/profiles", MOUNT_POINT);
	file_list = list_files_in_directory(buf);
	
	printf("Erasing %s. File list: %p\n", buf, file_list);
	while (file_list)
	{
		printf("Removing file %s...\n", file_list->data);
		remove(file_list->data);
		file_list = file_list->next;
	}
	#endif
	
	mkdir("/sdcard/profiles", 07777);
	
	load_and_send_saved_profiles(&global_cxt);
	
	if (lvgl_port_lock(-1))
	{
		make_ui(disp);
		lvgl_port_unlock();
	}
	
	//queue_msg_to_teensy(create_et_msg		 (ET_MESSAGE_SWITCH_PROFILE, 	 "s",  1));
}
