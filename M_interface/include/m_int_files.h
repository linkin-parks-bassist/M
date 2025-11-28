#ifndef M_INT_FILES_H_
#define M_INT_FILES_H_

#define M_INT_PROFILE_MAGIC_BYTE  			0x4a
#define M_INT_PROFILE_PIPELINE_LINEAR  		0x01

#define M_INT_PROFILE_BROKEN_TRANSFORMER	0xfffd

#define M_INT_SETTINGS_MAGIC_BYTE  			0x4b

#define M_INT_SEQUENCE_MAGIC_BYTE  			0x4c

#define M_INT_WRITE_UNFINISHED_BYTE  		0xfe
#define M_INT_WRITE_FINISHED_BYTE  			0xff

#define BACKUP_FNAME "/backup.mp"

#define MAIN_SEQUENCE_FNAME "/sdcard/main_seq.ms"

#define M_PROFILES_DIR  "/sdcard/profs"
#define M_SEQUENCES_DIR "/sdcard/seqs"

int save_profile_as_file		(m_profile *profile, const char *fname);
int save_profile_as_file_safe	(m_profile *profile, const char *fname);
int read_profile_from_file		(m_profile *profile, const char *fname);

int save_sequence_as_file		(m_int_sequence *sequence, const char *fname);
int save_sequence_as_file_safe	(m_int_sequence *sequence, const char *fname);
int read_sequence_from_file		(m_int_sequence *sequence, const char *fname);

int save_settings_to_file(m_settings *settings, const char *fname);
int load_settings_from_file(m_settings *settings, const char *fname);

int init_periodic_backup_task();

int save_profile(m_profile *profile);
int load_saved_profiles(m_context *cxt);

int save_sequence(m_int_sequence *sequence);
int load_saved_sequences(m_context *cxt);

int safe_file_write(int (*write_func)(void *arg, const char *fname), void *arg, const char *fname);

#endif
