#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "m_int.h"

static const char *TAG = "m_int_files.c";

#define IO_BUFFER_SIZE 128

#define write_byte(x) 			  fputc(x, file);
#define write_short(x) do {arg16 = x; fwrite(&arg16, sizeof(uint16_t), 1, file);} while(0);
#define write_float(x) 			  fwrite(&x, sizeof(float), 1, file);
#define write_string(x) 		  fputs(x, file); fputc(0, file);

#define read_byte(x)  x = fgetc(file);
#define read_short(x) fread(&x, sizeof(uint16_t), 1, file);
#define read_float(x) fread(&x, sizeof(float), 1, file);
#define read_string() \
	do {\
		for (int i = 0; i < IO_BUFFER_SIZE; i++)\
		{\
			string_read_buffer[i] = fgetc(file);\
			if (!string_read_buffer[i])\
				break;\
		}\
	} while (0);
#define read_and_strndup_string(x) \
	do {\
		for (int i = 0; i < IO_BUFFER_SIZE; i++)\
		{\
			string_read_buffer[i] = fgetc(file);\
			if (!string_read_buffer[i])\
				break;\
		}\
		x = m_strndup(string_read_buffer, IO_BUFFER_SIZE);\
	} while (0);

void dump_file_contents(char *fname)
{
	printf("FILE HEX DUMP: %s\n", fname);
	FILE *file = fopen(fname, "rb");
	
	if (!file)
	{
		printf("Failed to open file %s\n", fname);
		return;
	}
	
	uint8_t byte;
	
	int i = 1;
	while (fread(&byte, 1, 1, file))
	{
		printf("0x%x%s", byte, (i % 32 == 0) ? "\n" : " ");
		i++;
	}
	
	printf((i % 32 == 1) ? "" : "\n");
	fclose(file);
}

int file_validity_check(FILE *file, uint8_t magic_byte, uint8_t *byte_out)
{
	uint8_t byte;
	
	read_byte(byte);
	
	if (byte_out)
		*byte_out = byte;
	
	if (byte != magic_byte)
		return 1;
	
	read_byte(byte);
	
	if (byte_out)
		*byte_out = byte;
	
	if (byte != M_INT_WRITE_FINISHED_BYTE)
		return 2;
	
	return 0;
}

int save_profile_as_file(m_profile *profile, const char *fname)
{
	printf("save_profile_as_file\n");
	
	if (!fname || !profile)
	{
		printf("NULL pointer lol\n");
		return ERR_NULL_PTR;
	}
	
	FILE *file = fopen(fname, "wb");
	
	uint8_t len;
	
	if (!file)
	{
		printf("Could not open file %s\n", fname);
		return ERR_FOPEN_FAIL;
	}
	
	// Declare that this is a profile file
	write_byte(M_INT_PROFILE_MAGIC_BYTE);
	
	// Write status byte; overwritten at the end
	write_byte(M_INT_WRITE_UNFINISHED_BYTE);
	
	// Might implement other types later
	write_byte(M_INT_PROFILE_PIPELINE_LINEAR);
	
	uint8_t buffer[IO_BUFFER_SIZE];
	uint16_t arg16;
	int ret_val;
	int n;
	
	char *units;
	char *name = profile->name ? profile->name : "Unnamed Profile";
	
	write_string(name);
	
	m_transformer_pll *current_transformer = profile->pipeline.transformers;
	m_parameter_pll *current_param;
	
	n = 0;
	
	while (current_transformer)
	{
		current_transformer = current_transformer->next;
		n++;
	}
	
	write_short(n);
	
	current_transformer = profile->pipeline.transformers;
	
	while (current_transformer)
	{
		if (!current_transformer->data)
		{
			write_short(M_INT_PROFILE_BROKEN_TRANSFORMER);
			current_transformer = current_transformer->next;
			continue;
		}
		
		write_short(current_transformer->data->type);
		write_short(current_transformer->data->id);
		
		current_param = current_transformer->data->parameters;
		
		while (current_param)
		{
			if (current_param->data)
				write_float(current_param->data->value);
			
			current_param = current_param->next;
		}
		
		// Add handling for settings when I implement them at all lol
		
		current_transformer = current_transformer->next;
	}
	
	// Add stuff for other profile settings when I implement those too
	
	// Go back and overwrite the unfinished byte with the finished byte
	fseek(file, 1, SEEK_SET);
	write_byte(M_INT_WRITE_FINISHED_BYTE);
	
	fclose(file);
	
	printf("save_profile_as_file done\n");
	
	return NO_ERROR;
}

int save_sequence_as_file(m_int_sequence *sequence, const char *fname)
{
	if (!sequence || !fname)
		return ERR_NULL_PTR;
	
	printf("Saving sequence %s to sd card!\n", sequence->name ? "(unnamed)" : sequence->name);
	FILE *file = fopen(fname, "wb");
	
	if (!file)
	{
		printf("Failed to open file %s\n", fname);
		return ERR_FOPEN_FAIL;
	}
	
	write_byte(M_INT_SEQUENCE_MAGIC_BYTE);
	
	write_byte(M_INT_WRITE_UNFINISHED_BYTE);
	
	char *name = sequence->name ? sequence->name : "Unnamed Sequence";
	
	write_string(name);
	
	seq_profile_ll *current = sequence->profiles;
	
	uint16_t n_profiles = 0;
	uint16_t arg16;
	
	while (current)
	{
		n_profiles++;
		current = current->next;
	}
	
	printf("Sequence has %d profiles...\n", n_profiles);
	write_short(n_profiles);
	
	current = sequence->profiles;
	while (current)
	{
		if (current->data)
		{
			if (!current->data->fname || current->data->unsaved_changes)
			{
				save_profile(current->data);
			}
			
			printf("Profile %s...\n", current->data->fname);
			write_string(current->data->fname);
		}
		
		current = current->next;
	}
	
	fseek(file, 1, SEEK_SET);
	write_byte(M_INT_WRITE_FINISHED_BYTE);
	
	fclose(file);
	
	printf("Success\n");
	
	dump_file_contents(fname);
	return NO_ERROR;
}

int save_settings_to_file(m_settings *settings, const char *fname)
{
	if (!settings || !fname)
		return ERR_NULL_PTR;
	
	printf("Saving settings to sd card!\n");
	FILE *file = fopen(fname, "wb");
	
	if (!file)
	{
		printf("Failed to open file %s\n", fname);
		return ERR_FOPEN_FAIL;
	}
	
	write_byte(M_INT_SETTINGS_MAGIC_BYTE);
	
	write_byte(M_INT_WRITE_UNFINISHED_BYTE);
	
	write_float(settings->input_gain.value);
	write_float(settings->output_gain.value);
	
	fseek(file, 1, SEEK_SET);
	write_byte(M_INT_WRITE_FINISHED_BYTE);
	
	fclose(file);
	
	printf("Success\n");
	
	dump_file_contents(fname);
	return NO_ERROR;
}

int load_settings_from_file(m_settings *settings, const char *fname)
{
	if (!settings || !fname)
		return ERR_NULL_PTR;
	
	printf("load settings from file %s...\n", fname);
	
	dump_file_contents(fname);
	
	FILE *file = fopen(fname, "rb");
	
	if (!file)
	{
		printf("Failed to open file %s\n", fname);
		settings->input_gain.value = 0.0;
		settings->output_gain.value = -60.0;
		return ERR_FOPEN_FAIL;
	}
	
	char string_read_buffer[IO_BUFFER_SIZE];
	int ret_val = NO_ERROR;
	uint16_t byte;
	
	read_byte(byte);
	
	if (byte != M_INT_SETTINGS_MAGIC_BYTE)
	{
		ret_val = ERR_MANGLED_FILE;
		goto read_settings_exit;
	}
	
	read_byte(byte);
	
	if (byte != M_INT_WRITE_FINISHED_BYTE)
	{
		ret_val = ERR_MANGLED_FILE;
		goto read_settings_exit;
	}
	
	read_float(settings->input_gain.value);
	read_float(settings->output_gain.value);

	printf("read input gain: %f\n", settings->input_gain.value);
	printf("read output gain: %f\n", settings->output_gain.value);
	
read_settings_exit:
	fclose(file);
	
	return ret_val;
}

int read_profile_from_file(m_profile *profile, const char *fname)
{
	//printf("read_profile_from_file\n");
	if (!fname || !profile)
	{
		//printf("NULL pointer lol\n");
		return ERR_NULL_PTR;
	}
	
	dump_file_contents(fname);
	
	FILE *file = fopen(fname, "r");
	
	if (!file)
	{
		//printf("Could not open file %s\n", fname);
		return ERR_FOPEN_FAIL;
	}
	
	
	ESP_LOGI(TAG, "Reading profile from %s", fname);
	
	uint8_t byte;
	uint16_t arg16;
	uint16_t n_transformers;
	char string_read_buffer[IO_BUFFER_SIZE];
	char *name = NULL;
	int ret_val = NO_ERROR;
	m_transformer *trans = NULL;
	m_parameter_pll *current_param = NULL;
	
	// Check that this is a profile file
	byte = fgetc(file);
	
	if (byte != M_INT_PROFILE_MAGIC_BYTE)
	{
		ESP_LOGE(TAG, "Attempted load of profile from file \"%s\", whose first byte 0x%02x is not the profile magic byte 0x%02x",
			fname, byte, M_INT_PROFILE_MAGIC_BYTE);
		ret_val = ERR_BAD_ARGS;
		goto profile_read_bail;
	}
	
	// Check that the write was finished
	byte = fgetc(file);
	
	if (byte != M_INT_WRITE_FINISHED_BYTE)
	{
		ESP_LOGE(TAG, "Attempted load of profile from file \"%s\", whose second byte 0x%02x indicates that its write was unfinishedn",
			fname, byte);
		ret_val = ERR_UNFINISHED_WRITE;
		goto profile_read_bail;
	}
	
	// Check that the profile is linear
	byte = fgetc(file);
	
	if (byte != M_INT_PROFILE_PIPELINE_LINEAR)
	{
		ESP_LOGE(TAG, "Attempted load of a non-linear profile from file \"%s\"; this is unimplemented", fname);
		goto profile_read_bail;
	}
	
	read_and_strndup_string(name);
	
	if (!name)
	{
		
		ESP_LOGE(TAG, "Allocation fail allocating string of length %d for profile name from file %s", (int)byte, fname);
		goto profile_read_bail;
	}
	
	profile->name = name;
	
	ESP_LOGI(TAG, "Loaded name: %s", profile->name);
	
	read_short(n_transformers);
	
	m_effect_desc *eff;
	
	for (int i = 0; i < n_transformers; i++)
	{
		//printf("Reading transformer %d...\n", i);
		//Get transformer type
		read_short(arg16);
		
		eff = get_effect_desc(arg16);
		if (!eff)
		{
			ESP_LOGE(TAG, "Profile references non-existent effect. Aborting.\n");
			ret_val = ERR_MANGLED_FILE;
			goto profile_read_bail;
		}
		
		ESP_LOGI(TAG, "Encountered %s in position %d", eff->name, (int)i);
		
		trans = m_profile_append_transformer_eff(profile, eff);
		
		if (!trans)
		{
			ESP_LOGE(TAG, "Failed to append effect \"%s\"", eff->name);
			ret_val = ERR_MANGLED_FILE;
			goto profile_read_bail;
		}
		
		// Get transformer ID
		read_short(arg16);
		
		
		ESP_LOGI(TAG, "Transformer ID: %d\n", (int)arg16);
		trans->id = arg16;
		
		current_param = trans->parameters;
		while (current_param)
		{
			if (current_param->data)
				read_float(current_param->data->value);
			
			current_param = current_param->next;
		}
	}
	
	//printf("File done! closing...\n");
	fclose(file);
	//printf("Closed. Returning\n");
	
	profile->fname = m_strndup(fname, 128);
	profile->unsaved_changes = 0;
	
	return ret_val;
	
profile_read_bail:
	//printf("BAILING\n");
	fclose(file);
	
	//printf("BAILED\n");
	return ret_val;
}

int read_sequence_from_file(m_int_sequence *sequence, const char *fname)
{
	printf("read_sequence_from_file\n");
	if (!fname || !sequence)
	{
		return ERR_NULL_PTR;
	}
	
	dump_file_contents(fname);
	
	FILE *file = fopen(fname, "r");
	
	if (!file)
	{
		//printf("Could not open file %s\n", fname);
		return ERR_FOPEN_FAIL;
	}
	
	ESP_LOGI(TAG, "Reading sequence from %s", fname);
	
	uint8_t byte;
	uint16_t arg16;
	uint16_t n_profiles;
	char string_read_buffer[IO_BUFFER_SIZE];
	char *name = NULL;
	char *profile_fname = NULL;
	
	int ret_val = NO_ERROR;
	
	switch (file_validity_check(file, M_INT_SEQUENCE_MAGIC_BYTE, &byte))
	{
		case 0:
			break;
		
		case 1:
			ESP_LOGE(TAG, "Attempted load of sequence from file \"%s\", whose first byte 0x%02x is not the sequence magic byte 0x%02x",
				fname, byte, M_INT_PROFILE_MAGIC_BYTE);
			ret_val = ERR_BAD_ARGS;
			goto sequence_read_bail;
		
		case 2:
			ESP_LOGE(TAG, "Attempted load of sequence from file \"%s\", whose second byte 0x%02x indicates that its write was unfinishedn",
				fname, byte);
			ret_val = ERR_UNFINISHED_WRITE;
			goto sequence_read_bail;
	}
	
	read_and_strndup_string(name);
	
	if (!name)
	{
		
		ESP_LOGE(TAG, "Allocation fail allocating string of length %d for sequence name from file %s", (int)byte, fname);
		goto sequence_read_bail;
	}
	
	sequence->name = name;
	
	ESP_LOGI(TAG, "Loaded name: %s", sequence->name);
	
	read_short(n_profiles);
	
	m_profile *profile;
	
	for (int i = 0; i < n_profiles; i++)
	{
		read_string();
		
		printf("Sequence contains profile %s...\n", string_read_buffer);
		profile = cxt_find_profile(&global_cxt, string_read_buffer);
		
		if (profile)
		{
			sequence_append_profile(sequence, profile);
		}
		else
		{
			ESP_LOGE(TAG, "Error: sequence %s contains profile %s, but no such profile found!\n", fname, string_read_buffer);
		}
	}
	
	printf("File done! closing...\n");
	fclose(file);
	printf("Closed. Returning\n");
	
	sequence->fname = m_strndup(fname, 128);
	sequence->unsaved_changes = 0;
	
	return ret_val;
	
sequence_read_bail:
	//printf("BAILING\n");
	fclose(file);
	
	//printf("BAILED\n");
	return ret_val;
}

int m_init_directories()
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

int safe_file_write(int (*write_func)(void *arg, const char *fname), void *arg, const char *fname)
{
	if (!write_func)
		return ERR_NULL_PTR;
	
	// Check if the file exists
	FILE *target = fopen(fname, "r");
	char buf[strlen(fname) + 5];
	int backup = 0;
	
	if (target)
	{
		backup = 1;
		
		// Append ".bak" to the filename
		sprintf(buf, "%s.bak", fname);
		
		// Check if a file with that name exists
		FILE *bakfile = fopen(buf, "r");
		if (bakfile)
		{
			// If so, delete it
			remove(buf);
			fclose(bakfile);
		}
		
		// Rename the current version
		rename(fname, buf);
		
		fclose(target);
	}
	
	int ret_val = write_func(arg, fname);
	
	// If we backed up but the write failed,
	// replace the newly written file with
	// the old backup
	if (backup && ret_val != NO_ERROR)
	{
		// Remove any busted file we wrote
		remove(fname);
		// Move the backup back in place
		rename(buf, fname);
	}
	
	return ret_val;
}

int save_profile_as_file_safe(m_profile *profile, const char *fname)
{
	// Check if the file exists
	FILE *target = fopen(fname, "r");
	char buf[strlen(fname) + 5];
	int backup = 0;
	
	if (target)
	{
		backup = 1;
		
		// Append ".bak" to the filename
		sprintf(buf, "%s.bak", fname);
		
		// Check if a file with that name exists
		FILE *bakfile = fopen(buf, "r");
		if (bakfile)
		{
			// If so, delete it
			remove(buf);
			fclose(bakfile);
		}
		
		// Rename the current version
		rename(fname, buf);
		
		fclose(target);
	}
	
	int ret_val = save_profile_as_file(profile, fname);
	
	// If we backed up but the write failed,
	// replace the newly written file with
	// the old backup
	if (backup && ret_val != NO_ERROR)
	{
		// Remove any busted file we wrote
		remove(fname);
		// Move the backup back in place
		rename(buf, fname);
	}
	
	return ret_val;
}

#define FNAME_DIGITS 4

char *generate_filename(char *prefix, char *suffix)
{
	int plen = 0, slen = 0;
	
	if (prefix)
		plen = strlen(prefix);
	if (suffix)
		slen = strlen(suffix);
	
	char *fname = m_alloc(plen + slen + FNAME_DIGITS + 1);
	
	if (!fname)
		return NULL;
	
	int index = 0;
	
	for (int i = 0; i < plen; i++)
		fname[index++] = prefix[i];
	
	char c;
	int x;
	
	for (int i = 0; i < FNAME_DIGITS; i++)
	{
		x = rand() % 36;

		fname[index++] = (x < 10) ? '0' + x : 'A' + (x - 10);
	}
	
	for (int i = 0; i < slen; i++)
		fname[index++] = (suffix[i] == '%') ? '_' : suffix[i];
	
	fname[index] = 0;
	
	printf("Generated filename %s\n", fname);
	
	return fname;
}

int save_profile(m_profile *profile)
{
	if (!profile->fname)
	{
		FILE *test = NULL;
		
		do {
			profile->fname = generate_filename(M_PROFILES_DIR, PROFILE_EXTENSION);
			
			if (!profile)
				return ERR_ALLOC_FAIL;
			
			test = fopen(profile->fname, "r");
			
			if (test)
			{
				m_free(profile->fname);
				fclose(test);
			}
		} while (test);
	}
	
	int ret_val = save_profile_as_file(profile, profile->fname);
	
	if (ret_val == NO_ERROR)
	{
		printf("Sucessfully saved profile as %s. Dumping file...\n", profile->fname);
		dump_file_contents(profile->fname);
	}
	else
	{
		printf("Profile save error: %s\n", m_error_code_to_string(ret_val));
	}
	
	return ret_val;
}

int save_sequence(m_int_sequence *sequence)
{
	if (!sequence->fname)
	{
		FILE *test = NULL;
		
		do {
			sequence->fname = generate_filename(M_SEQUENCES_DIR, SEQUENCE_EXTENSION);
			
			if (!sequence)
				return ERR_ALLOC_FAIL;
			
			test = fopen(sequence->fname, "r");
			
			if (test)
			{
				m_free(sequence->fname);
				fclose(test);
			}
		} while (test);
	}
	
	int ret_val = save_sequence_as_file(sequence, sequence->fname);
	
	if (ret_val == NO_ERROR)
	{
		printf("Sucessfully saved sequence as %s. Dumping file...\n", sequence->fname);
		dump_file_contents(sequence->fname);
	}
	else
	{
		printf("Sequence save error: %s\n", m_error_code_to_string(ret_val));
	}
	
	return ret_val;
}

int load_saved_profiles(m_context *cxt)
{
	printf("load_saved_profiles...\n");
	string_ll *current_file = list_files_in_directory(M_PROFILES_DIR);
	
	string_ll *cf = current_file;
	
	printf("Profile files fonund:\n");
	if (!cf)
	{
		printf("none!!!\n");
	}
	else
	{
		while (cf)
		{
			printf("%s\n", cf->data);
			cf = cf->next;
		}
	}
	
	m_profile *profile;
	
	m_profile_pll *nl;
	
	int ret_val;
	
	while (current_file)
	{
		printf("Loading profile %s...\n", current_file->data);
		profile = m_alloc(sizeof(m_profile));
		
		if (!profile)
			return ERR_ALLOC_FAIL;
		
		init_m_profile(profile);
		ret_val = read_profile_from_file(profile, current_file->data);
		
		if (ret_val == NO_ERROR)
		{	
			nl = m_profile_pll_append(cxt->profiles, profile);
		
			if (!nl)
			{
				free_profile(profile);
				return ERR_ALLOC_FAIL;
			}
			cxt->profiles = nl;
			
			create_profile_view_for(profile);
		}
		else
		{
			free_profile(profile);
		}
		
		current_file = current_file->next;
	}
	
	global_cxt.saved_profiles_loaded = 1;
	
	return NO_ERROR;
}

int load_saved_sequences(m_context *cxt)
{
	int ret_val;
	
	read_sequence_from_file(&cxt->main_sequence, MAIN_SEQUENCE_FNAME);
	
	string_ll *current_file = list_files_in_directory(M_SEQUENCES_DIR);
	
	m_int_sequence *sequence;
	
	m_int_sequence_pll *nl;
	
	while (current_file)
	{
		sequence = m_alloc(sizeof(m_int_sequence));
		
		if (!sequence)
			return ERR_ALLOC_FAIL;
		
		init_m_int_sequence(sequence);
		ret_val = read_sequence_from_file(sequence, current_file->data);
		
		if (ret_val == NO_ERROR)
		{	
			nl = m_int_sequence_pll_append(cxt->sequences, sequence);
		
			if (!nl)
			{
				free_sequence(sequence);
				return ERR_ALLOC_FAIL;
			}
			cxt->sequences = nl;
			
			create_sequence_view_for(sequence);
		}
		else
		{
			free_sequence(sequence);
		}
		
		current_file = current_file->next;
	}
	
	global_cxt.saved_sequences_loaded = 1;
	
	return NO_ERROR;
}

int load_effects_from_disk(m_context *cxt)
{
	if (!cxt)
		return ERR_NULL_PTR;
	
	return NO_ERROR;
}
