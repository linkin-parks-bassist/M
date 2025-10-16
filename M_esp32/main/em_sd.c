#include "em.h"

#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/i2c.h"

#define MAX_PARALLEL_FILES 5

#define PIN_NUM_MOSI GPIO_NUM_11
#define PIN_NUM_MISO GPIO_NUM_13
#define PIN_NUM_SCLK GPIO_NUM_12

static const char *TAG = "sd";

const int mount_point_strlen = strlen(MOUNT_POINT);

sdmmc_card_t *card;
const char mount_point[] = MOUNT_POINT;

sdmmc_host_t host = SDSPI_HOST_DEFAULT();

IMPLEMENT_LINKED_PTR_LIST(char);

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

    // Configure SPI bus for SD card configuration
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

    // Configure SD card slot
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
                          "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
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
    
    FILE *f = fopen("/sdcard/FOO.txt", "r");
    
    DIR *root = opendir(MOUNT_POINT);
    if (root)
    {
		printf("Root succesfully opened\n");
		closedir(root);
	}
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

string_ll *list_files_in_directory(char *dir)
{
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
		
		fname = malloc(strlen(dir) + 1 + 255);
		
		if (!fname)
		{
			ESP_LOGE(TAG, "Error: couldn't allocate string to list directory entry %s/%s", dir, directory_entry->d_name);
			return list;
		}
		
		sprintf(fname, "%s/%s", dir, directory_entry->d_name);
		
		nl = char_ptr_linked_list_append(list, fname);
		
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
