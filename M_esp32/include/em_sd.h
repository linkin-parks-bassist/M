#ifndef EM_SD_CARD_H_
#define EM_SD_CARD_H_

#define MOUNT_POINT "/sdcard"

int init_sd_card();

DECLARE_LINKED_PTR_LIST(char);

typedef char_ptr_linked_list string_ll;

string_ll *list_files_in_directory(char *dir);

#endif
