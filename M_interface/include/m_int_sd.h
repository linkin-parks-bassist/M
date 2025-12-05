#ifndef M_INT_SD_CARD_H_
#define M_INT_SD_CARD_H_

#define MOUNT_POINT "/sdcard"

#define SPI_CARD_READER

int init_sd_card();

DECLARE_LINKED_PTR_LIST(char);

typedef char_pll string_ll;

string_ll *list_files_in_directory(char *dir);

void erase_sd_card_void_cb(void *data);
void erase_sd_card();

#endif
