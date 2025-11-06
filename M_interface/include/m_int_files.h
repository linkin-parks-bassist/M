#ifndef M_INT_FILES_H_
#define M_INT_FILES_H_

#define M_INT_PROFILE_MAGIC_BYTE  			0x4a
#define M_INT_PROFILE_PIPELINE_LINEAR  		0x01

#define M_INT_PROFILE_BROKEN_TRANSFORMER	0xfffd

#define M_INT_WRITE_UNFINISHED_BYTE  		0xfe
#define M_INT_WRITE_FINISHED_BYTE  			0xff

#define M_INT_SETTINGS_MAGIC_BYTE  			0x4b

#define BACKUP_FNAME "/backup.mp"

int save_profile_as_file(m_int_profile *profile, char *fname);
int save_profile_as_file_safe(m_int_profile *profile, char *fname);
int read_profile_from_file(m_int_profile *profile, char *fname);

int save_settings_to_file(m_int_settings *settings, const char *fname);
int load_settings_from_file(m_int_settings *settings, const char *fname);

int init_periodic_backup_task();

int save_profile(m_int_profile *profile);
int load_saved_profiles(m_int_context *cxt);

int safe_file_write(int (*write_func)(void *arg, const char *fname), void *arg, const char *fname);

#endif
