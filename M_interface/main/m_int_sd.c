#include "m_int.h"

static const char *TAG = "m_int_sd.c";

IMPLEMENT_LINKED_PTR_LIST(char);

#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#ifndef M_SIMULATED
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/i2c.h"

#define MAX_PARALLEL_FILES 5

#define PIN_NUM_MOSI GPIO_NUM_11
#define PIN_NUM_MISO GPIO_NUM_13
#define PIN_NUM_SCLK GPIO_NUM_12


const int mount_point_strlen = strlen(MOUNT_POINT);

sdmmc_card_t *card;
const char mount_point[] = MOUNT_POINT;

sdmmc_host_t host = SDSPI_HOST_DEFAULT();

int init_directories()
{
	struct stat statbuf;

    if (stat(M_PROFILES_DIR, &statbuf) == 0)
    {
		ESP_LOGI(TAG, "Profiles directory %s found", M_PROFILES_DIR);
	}
	else
	{
		ESP_LOGW(TAG, "Profiles directory %s doesn't exist. Creating...", M_PROFILES_DIR);
		if (mkdir(M_PROFILES_DIR, 07777) != 0)
		{
			ESP_LOGE(TAG, "Failed to create profiles directory\n");
		}
		else
		{
			ESP_LOGI(TAG, "Directory created sucessfully");
		}
	}

    if (stat(M_SEQUENCES_DIR, &statbuf) == 0)
    {
		ESP_LOGI(TAG, "Sequences directory %s found", M_SEQUENCES_DIR);
	}
	else
	{
		ESP_LOGW(TAG, "Sequences directory %s doesn't exist. Creating...", M_SEQUENCES_DIR);
		if (mkdir(M_SEQUENCES_DIR, 07777) != 0)
		{
			ESP_LOGE(TAG, "Failed to create sequences directory");
		}
		else
		{
			ESP_LOGI(TAG, "Directory created sucessfully");
		}
	}
	
	return NO_ERROR;
}

int init_sd_card()
{
	esp_err_t ret;
    // Control CH422G to pull down the CS pin of the SD
    uint8_t write_buf = 0x01;
    i2c_transmit(0x24, &write_buf, 1);
    
    // Options for mounting the filesystem
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = MAX_PARALLEL_FILES,
        .allocation_unit_size = 16 * 1024
    };

    // Initializing SD card
	ESP_LOGW(TAG, "Initializing SD card");

    // Conpfigure SPI bus for SD card configuration
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI, // Set MOSI pin
        .miso_io_num = PIN_NUM_MISO, // Set MISO pin
        .sclk_io_num = PIN_NUM_SCLK,  // Set SCLK pin
        .quadwp_io_num = -1,         // Not used
        .quadhd_io_num = -1,         // Not used
        .max_transfer_sz = 4000,     // Maximum transfer size
    };
    
    // Initialize SPI bus
    ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK)
    {
        // Failed to initialize bus
		ESP_LOGW(TAG, "Failed to initialize bus.");
        return ESP_FAIL;
    }

    // Conpfigure SD card slot
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = -1; // CS is controlled via pin expander
    slot_config.host_id = host.slot;  // Set host ID
	
    // Mounting filesystem
    ESP_LOGW(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            // Failed to mount filesystem
            ESP_LOGW(TAG, "Failed to mount filesystem. "
                          "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig setting.");
        }
        else
        {
            // Failed to initialize the card
            ESP_LOGW(TAG, "Failed to initialize the card (%s). "
                          "Make sure SD card lines have pull-up resistors in place.",
                     esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    // Filesystem mounted
    ESP_LOGW(TAG, "Filesystem mounted");
    
    init_directories();
    
    /*struct dirent *dir_ent = readdir(root);
    
    char buf[255+9];
    while (dir_ent) {
		printf("Directory entry found, fname = %s\n", dir_ent->d_name);
		sprintf(buf, "/sdcard/%s", dir_ent->d_name);
		remove(buf);
		dir_ent = readdir(root);
	}*/
    
	return NO_ERROR;
}

#else

int init_sd_card()
{
	return NO_ERROR;
}

#endif


string_ll *list_files_in_directory(char *dir)
{
	#ifndef USE_SD_CARD
	return NULL;
	#endif
	
	if (!dir)
		return NULL;
	
	printf("Generating list of files in %s\n", dir);
	
	char *fname = NULL;
	
	DIR *directory = opendir(dir);
	
	if (!directory)
	{
		printf("Failed to open directory!\n");
		return NULL;
	}
	
	struct dirent *directory_entry = readdir(directory);
	
	string_ll *list = NULL;
	string_ll *nl;
	int is_dir;
	
	while (directory_entry)
	{
		printf("Directory entry: %s\n", directory_entry->d_name);
		if (directory_entry->d_type == DT_DIR)
		{
			printf("... is itself a directory!\n");
			directory_entry = readdir(directory);
			continue;
		}
		
		fname = m_alloc(strlen(dir) + 1 + 255);
		
		if (!fname)
		{
						ESP_LOGE(TAG, "Error: couldn't allocate string to list directory entry %s/%s", dir, directory_entry->d_name);
			return list;
		}
		
		sprintf(fname, "%s/%s", dir, directory_entry->d_name);
		
		nl = char_pll_append(list, fname);
		
		if (nl)
		{
			list = nl;
		}
		else
		{
						ESP_LOGE(TAG, "Error: couldn't append linked list to list directory entry %s/%s", dir, directory_entry->d_name);
			return list;
		}
		
		directory_entry = readdir(directory);
	}
	
	return list;
}

void erase_sd_card_void_cb(void *data)
{
	#ifdef USE_SDCARD
	erase_sd_card();
	#endif
}

void erase_sd_card()
{
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
}
