#ifndef M_INT_LOGGING_H_
#define M_INT_LOGGING_H_

#define M_INT_LV_LOG_BUF_LEN 4096

int m_int_log_init();

void m_int_lv_log_cb(const char *buf);

#endif
