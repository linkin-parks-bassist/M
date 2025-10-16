#include "em.h"

static const char *TAG = "em_files.c";

#define IO_BUFFER_SIZE 128

#define write_byte(x) 			  fputc(x, file);
#define write_short(x) arg16 = x; fwrite(&arg16, sizeof(uint16_t), 1, file);
#define write_float(x) 			  fwrite(&x, sizeof(float), 1, file);
#define write_string(x) 		  fputs(x, file); fputc(0, file);

void dump_file_contents(char *fname)
{
	FILE *file = fopen(fname, "rb");
	
	if (!file)
	{
		printf("Failed to open file %s\n", fname);
	}
	
	uint8_t byte;
	
	int i = 1;
	while (fread(&byte, 1, 1, file))
	{
		printf("0x%x%s", byte, (i % 32 == 0) ? "\n" : " ");
		i++;
	}
	
	fclose(file);
}

int save_profile_as_file(em_profile *profile, char *fname)
{
	printf("save_profile_as_file\n");
	
	if (!fname || !profile)
	{
		printf("NULL pointer lol\n");
		return ERR_NULL_PTR;
	}
	
	FILE *file = fopen(fname, "w+");
	
	uint8_t len;
	
	if (!file)
	{
		printf("Could not open file %s\n", fname);
		return ERR_FOPEN_FAIL;
	}
	
	// Declare that this is a profile file
	write_byte(EM_PROFILE_MAGIC_BYTE);
	
	// Write status byte; overwritten at the end
	write_byte(EM_WRITE_UNFINISHED_BYTE);
	
	// Might implement other types later
	write_byte(EM_PROFILE_PIPELINE_LINEAR);
	
	uint8_t buffer[IO_BUFFER_SIZE];
	uint16_t arg16;
	int ret_val;
	int n;
	
	char *units;
	char *name = profile->name ? profile->name : "Unnamed Profile";
	
	write_string(name);
	
	em_transformer_ll *current = profile->pipeline.transformers;
	
	n = 0;
	
	while (current)
	{
		current = current->next;
		n++;
	}
	
	write_short(n);
	
	current = profile->pipeline.transformers;
	
	while (current)
	{
		if (!current->data)
		{
			write_short(EM_PROFILE_BROKEN_TRANSFORMER);
			current = current->next;
			continue;
		}
		
		write_short(current->data->type);
		write_short(current->data->transformer_id);
		write_short(current->data->n_parameters);
		
		for (int i = 0; i < current->data->n_parameters; i++)
		{
			write_float(current->data->parameters[i].val);
		}
		
		// Add handling for options when I implement them at all lol
		
		current = current->next;
	}
	
	// Add stuff for other profile settings when I implement those too
	
	// Go back and overwrite the unfinished byte with the finished byte
	fseek(file, 1, SEEK_SET);
	write_byte(EM_WRITE_FINISHED_BYTE);
	
	fclose(file);
	
	printf("save_profile_as_file done\n");
	
	return NO_ERROR;
}

#define read_short(x) fread(&x, sizeof(uint16_t), 1, file);
#define read_float(x) fread(&x, sizeof(float), 1, file);
#define read_string(x) \
	for (int i = 0; i < IO_BUFFER_SIZE; i++)\
	{\
		string_read_buffer[i] = fgetc(file);\
		if (!string_read_buffer[i])\
			break;\
	}\
	x = strndup(string_read_buffer, IO_BUFFER_SIZE);

int read_profile_from_file(em_profile *profile, char *fname)
{
	printf("read_profile_from_file\n");
	if (!fname || !profile)
	{
		printf("NULL pointer lol\n");
		return ERR_NULL_PTR;
	}
	
	dump_file_contents(fname);
	
	FILE *file = fopen(fname, "r");
	
	if (!file)
	{
		printf("Could not open file %s\n", fname);
		return ERR_FOPEN_FAIL;
	}
	
	ESP_LOGI(TAG, "Reading profile from %s", fname);
	
	uint8_t byte;
	uint16_t arg16;
	uint16_t n_transformers;
	char string_read_buffer[IO_BUFFER_SIZE];
	char *name = NULL;
	int ret_val = NO_ERROR;
	em_transformer *trans = NULL;
	em_parameter *param = NULL;
	
	// Check that this is a profile file
	byte = fgetc(file);
	
	if (byte != EM_PROFILE_MAGIC_BYTE)
	{
		ESP_LOGE(TAG, "Attempted load of profile from file \"%s\", whose first byte 0x%02x is not the profile magic byte 0x%02x",
			fname, byte, EM_PROFILE_MAGIC_BYTE);
		ret_val = ERR_BAD_ARGS;
		goto profile_read_bail;
	}
	
	// Check that the write was finished
	byte = fgetc(file);
	
	if (byte != EM_WRITE_FINISHED_BYTE)
	{
		ESP_LOGE(TAG, "Attempted load of profile from file \"%s\", whose second byte 0x%02x indicates that its write was unfinishedn",
			fname, byte);
		ret_val = ERR_UNFINISHED_WRITE;
		goto profile_read_bail;
	}
	
	// Check that the profile is linear
	byte = fgetc(file);
	
	if (byte != EM_PROFILE_PIPELINE_LINEAR)
	{
		ESP_LOGE(TAG, "Attempted load of a non-linear profile from file \"%s\"; this is unimplemented", fname);
		goto profile_read_bail;
	}
	
	read_string(name);
	
	if (!name)
	{
		ESP_LOGE(TAG, "Allocation fail allocating string of length %d for profile name from file %s", (int)byte, fname);
		goto profile_read_bail;
	}
	
	profile->name = name;
	
	ESP_LOGI(TAG, "Loaded name: %s", profile->name);
	
	read_short(n_transformers);
	
	for (int i = 0; i < n_transformers; i++)
	{
		printf("Reading transformer %d...\n", i);
		//Get transformer type
		read_short(arg16);
		
		ESP_LOGI(TAG, "Encountered %s in position %d", transformer_type_to_string(arg16), (int)i);
		
		if (!transformer_type_valid(arg16))
		{
			ESP_LOGE(TAG, "Invalid transformer type %d in file. Aborting", (int)arg16);
			ret_val = ERR_MANGLED_FILE;
			goto profile_read_bail;
		}
		
		trans = em_profile_append_transformer_type(profile, arg16);
		
		if (!trans)
		{
			ESP_LOGE(TAG, "Failed to append %s ", transformer_type_to_string(arg16));
			ret_val = ERR_MANGLED_FILE;
			goto profile_read_bail;
		}
		
		// Get transformer ID
		read_short(arg16);
		
		ESP_LOGI(TAG, "Transformer ID: %d\n", (int)arg16);
		trans->transformer_id = arg16;
		
		for (uint16_t j = 0; j < trans->n_parameters; j++)
		{
			printf("Reading parameter %d...\n", j);
			param = &trans->parameters[j];
			
			printf("Read value...\n");
			read_float(param->val);
			printf("Got: %f\n", param->val);
			
			printf("Parameter %s has value %f\n", param->name, param->val);
		}
		
		printf("Done reading parameters for transformer %d...\n", (int)i);
	}
	
	printf("File done! closing...\n");
	fclose(file);
	printf("Closed. Returning\n");
	
	profile->fname = strndup(fname, 128);
	profile->unsaved_changes = 0;
	
	return ret_val;
	
profile_read_bail:
	printf("BAILING\n");
	fclose(file);
	
	printf("BAILED\n");
	return ret_val;
}

int save_profile_as_file_safe(em_profile *profile, char *fname)
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
	{
		plen = strlen(prefix);
		
		// Prevent any sprintf foolishness
		for (int i = 0; i < plen; i++)
			prefix[i] = (prefix[i] == '%') ? '_' : prefix[i];
	}
	if (suffix)
	{
		slen = strlen(suffix);
		
		for (int i = 0; i < plen; i++)
			prefix[i] = (prefix[i] == '%') ? '_' : prefix[i];
	}
	
	char *fname = malloc(plen + slen + FNAME_DIGITS + 1);
	
	if (!fname)
		return NULL;
	
	if (prefix)
		sprintf(fname, prefix);
	
	int index = plen;
	
	char c;
	int x;
	
	for (int i = 0; i < FNAME_DIGITS; i++)
	{
		x = rand() % 36;

		fname[index++] = (x < 10) ? '0' + x : 'A' + (x - 10);
	}
	
	if (suffix)
		sprintf(&fname[index], suffix);
	
	return fname;
}

int save_profile(em_profile *profile)
{
	if (!profile->fname)
	{
		FILE *test = NULL;
		
		do {
			profile->fname = generate_filename("/sdcard/profiles/", ".mp");
			
			if (!profile)
				return ERR_ALLOC_FAIL;
			
			test = fopen(profile->fname, "r");
			
			if (test)
			{
				free(profile->fname);
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

int load_and_send_saved_profiles(em_context *cxt)
{
	string_ll *current_file = list_files_in_directory("/sdcard/profiles");
	
	em_profile *profile;
	
	em_profile_ptr_linked_list *nl;
	
	int ret_val;
	
	while (current_file)
	{
		profile = malloc(sizeof(em_profile));
		
		if (!profile)
			return ERR_ALLOC_FAIL;
		
		init_em_profile(profile);
		ret_val = read_profile_from_file(profile, current_file->data);
		
		if (ret_val == NO_ERROR)
		{
			send_new_profile_to_teensy(profile);
			
			nl = em_profile_ptr_linked_list_append(cxt->profiles, profile);
		
			if (!nl)
			{
				free_profile(profile);
				return ERR_ALLOC_FAIL;
			}
			cxt->profiles = nl;
			
			make_profile_view_for(profile);
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
