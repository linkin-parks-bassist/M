#ifndef EM_FILES_H_
#define EM_FILES_H_

#define EM_PROFILE_MAGIC_BYTE  			0x4a
#define EM_PROFILE_PIPELINE_LINEAR  	0x01

#define EM_PROFILE_BROKEN_TRANSFORMER	0xfffd

#define EM_WRITE_UNFINISHED_BYTE  		0xfe
#define EM_WRITE_FINISHED_BYTE  		0xff

#define BACKUP_FNAME "/backup.mp"

int save_profile_as_file(em_profile *profile, char *fname);
int save_profile_as_file_safe(em_profile *profile, char *fname);
int read_profile_from_file(em_profile *profile, char *fname);

int init_periodic_backup_task();

int save_profile(em_profile *profile);
int load_and_send_saved_profiles(em_context *cxt);

#endif
