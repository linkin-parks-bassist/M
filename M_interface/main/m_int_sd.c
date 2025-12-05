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

#ifdef SPI_CARD_READER
#define PIN_NUM_MISO  27
#define PIN_NUM_MOSI  33
#define PIN_NUM_CLK   32
#define PIN_NUM_CS	46
#else
#define PIN_NUM_MOSI GPIO_NUM_11
#define PIN_NUM_MISO GPIO_NUM_13
#define PIN_NUM_SCLK GPIO_NUM_12
#endif

const int mount_point_strlen = strlen(MOUNT_POINT);

const char mount_point[] = MOUNT_POINT;

sdmmc_host_t host = SDMMC_HOST_DEFAULT();
sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

esp_vfs_fat_sdmmc_mount_config_t mount_config = {
		.format_if_mount_failed = false,
		.max_files = 5,
		.allocation_unit_size = 16 * 1024
	};
sdmmc_card_t *card = NULL;

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
	#ifdef SPI_CARD_READER
	esp_err_t ret;

	ESP_LOGI(TAG, "Initializing SD card (SPI mode)");

	// FATFS mount configuration
	esp_vfs_fat_sdmmc_mount_config_t mount_config = {
		.format_if_mount_failed = false,	// set true if you want auto-format
		.max_files = 5,
		.allocation_unit_size = 16 * 1024,
		// .disk_status_check_enable = false, // available in newer IDF; ignore if not present
	};

	// Set up SD SPI host
	sdmmc_host_t host = SDSPI_HOST_DEFAULT();
	host.slot = SPI2_HOST;  // which SPI host to use

	// Configure SPI bus pins
	spi_bus_config_t bus_cfg = {
		.mosi_io_num = PIN_NUM_MOSI,
		.miso_io_num = PIN_NUM_MISO,
		.sclk_io_num = PIN_NUM_CLK,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		.max_transfer_sz = 4000,
		// .flags = 0,   // you can leave defaults
		// .intr_flags = 0,
	};

	ESP_LOGI(TAG, "Initializing SPI bus (host=%d)", host.slot);
	ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "spi_bus_initialize failed: %s", esp_err_to_name(ret));
		return ERR_SD_INIT_FAIL;
	}

	// Configure SD-over-SPI device (CS pin etc.)
	sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
	slot_config.gpio_cs = PIN_NUM_CS;	// CS pin
	slot_config.host_id = host.slot;	 // same SPI host as above

	ESP_LOGI(TAG, "Mounting filesystem at %s", mount_point);
	ret = esp_vfs_fat_sdspi_mount(mount_point,
								  &host,
								  &slot_config,
								  &mount_config,
								  &card);
	if (ret != ESP_OK) {
		if (ret == ESP_FAIL) {
			ESP_LOGE(TAG,
					 "Failed to mount filesystem. "
					 "Set format_if_mount_failed = true to auto-format.");
		} else {
			ESP_LOGE(TAG,
					 "Failed to initialize the card (%s). "
					 "Check wiring and pull-up resistors on all SD lines.",
					 esp_err_to_name(ret));
		}
		spi_bus_free(host.slot);
		return ERR_SD_MOUNT_FAIL;
	}

	ESP_LOGI(TAG, "Filesystem mounted");

	// Optional: print card info
	sdmmc_card_print_info(stdout, card);
	init_directories();

	return NO_ERROR;
	#else
	printf("init_sd_card\n");
	esp_err_t ret;
	
	slot_config.width = 1;
	slot_config.d0 = 39;
	slot_config.d1 = -1;
	slot_config.d2 = -1;
	slot_config.d3 = -1;
	slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;
	
	gpio_reset_pin(42);
	
	gpio_config_t cfg = {
		.pin_bit_mask = 1ULL << 45,
		.mode = GPIO_MODE_OUTPUT,
		.pull_up_en = 0,
		.pull_down_en = 0,
		.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&cfg);
	gpio_set_level(45, 1);	  // TURN ON SD POWER
	vTaskDelay(pdMS_TO_TICKS(50));
	
	ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);
	
	if (ret != ESP_OK)
	{
		ESP_LOGE("SD", "Failed to mount SD card: %s\n", esp_err_to_name(ret));
		return ERR_SD_INIT_FAIL;
	}
	
	sdmmc_card_print_info(stdout, card);
	init_directories();
	
	return NO_ERROR;
	#endif
}

#else

int init_sd_card()
{
	return NO_ERROR;
}

#endif


string_ll *list_files_in_directory(char *dir)
{
	#ifndef USE_SDCARD
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
		
		sprintf(fname, "%s%s", dir, directory_entry->d_name);
		
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

int erase_folder(const char *dir)
{
	printf("Erasing directory %s...\n", dir);
	
	DIR *directory = opendir(dir);
	
	if (!directory)
	{
		printf("Failed to open directory!\n");
		return ERR_BAD_ARGS;
	}
	
	struct dirent *directory_entry = readdir(directory);
	
	int ret_val = NO_ERROR;
	int bufsize = strlen(dir) + NAME_MAX + 1;
	char *buf = m_alloc(sizeof(bufsize));
	
	if (!buf)
		return ERR_ALLOC_FAIL;
	
	while (directory_entry)
	{
		printf("Directory entry: %s\n", directory_entry->d_name);
		if (directory_entry->d_type == DT_DIR)
		{
			printf("... is itself a directory!\n");
			snprintf(buf, bufsize, "%s/%s", dir, directory_entry->d_name);
			printf("Full name: %s\n", buf);
			m_free(buf);
			ret_val = erase_folder(buf);
			rmdir(buf);
			buf = m_alloc(sizeof(bufsize));
			if (!buf)
				return ERR_ALLOC_FAIL;
		}
		else
		{
			printf("... is a file. Deleting...\n");
			snprintf(buf, bufsize, "%s/%s", dir, directory_entry->d_name);
			printf("Full name: %s\n", buf);
			remove(buf);
		}
		
		directory_entry = readdir(directory);
	}
	
	return ret_val;
}

void erase_sd_card()
{
	erase_folder(MOUNT_POINT);
}
