/**
 * @brief Logging functions
 */

#ifndef _LOG_H_
#define _LOG_H_

/*
 * Disable logging at all log sites
 */
// #define LOG_DISABLE_LOG 1

/*
 * Log immediately rather than buffering
 */
#define LOG_FORCE_FLUSH_BUFFER

#define LOG_BUFFER_STR_MAX_LEN 128
#define LOG_BUFFER_SIZE 256
#define LOG_REAL_WORLD_TIME 1

#define LOG_FLUSH_INTERVAL_SEC 1
#define LOG_SLEEP_TIME_SEC 1

/*
 * In practice: flush size < .8 * BUFFER_SIZE
 */
#define LOG_BUFFER_FLUSH_SIZE (0.8 * LOG_BUFFER_SIZE)

/*
 * Public API
 */
#ifdef LOG_DISABLE_LOG

#define log_debug(format, ...)
#define log_error(format, ...)
#define log_info(format, ...)

#define log_hex(buf, len)
#define log_init(log_file)
#define log_init_file(file_hdl)
#define log_init_flush_thread
#define log_finish
#define log_flush_buffer

#else

#define log_debug(format, ...) \
	zlog_time(ZLOG_LOC, format "\n", ##__VA_ARGS__)
#define log_error(format, ...) \
	zlog_time(ZLOG_LOC, format "\n", ##__VA_ARGS__)
#define log_info(format, ...) \
	zlog_time(ZLOG_LOC, format "\n", ##__VA_ARGS__)
#define log_hex(buf, len) \
	zlog_hex(ZLOG_LOC, buf, len)

#define log_init(log_file) zlog_init(log_file)
#define log_init_file(file_hdl) zlog_init_file(file_hdl)
#define log_init_flush_thread zlog_init_flush_thread
#define log_finish zlog_finish
#define log_flush_buffer zlog_flush_buffer

#endif

/*
 * Private API
 */
#include <stdio.h>

#define ZLOG_LOC __FILE__, __LINE__

// initialize zlog: flush to a log file
void zlog_init(char const *log_file);
// initialize zlog: flush to file handle
void zlog_init_file(FILE * out);
// creating a flushing thread
void zlog_init_flush_thread();
// finish using the zlog; clean up
void zlog_finish();
// explicitely flush the buffer in memory
void zlog_flush_buffer();

// log an entry; using the printf format
void zlogf(char const *fmt, ...)
	__attribute__ ((format(printf, 1, 2)));

// log an entry with a timestamp
void zlogf_time(char const *fmt, ...)
	__attribute__ ((format(printf, 1, 2)));

void zlog_hex(char *filename, int line, const void *buf, size_t len);

// log an entry with the filename and location;
//   the first 2 arguments can be replaced by ZLOG_LOC which
//   will be filled by the compiler
void zlog(char *filename, int line, char const *fmt, ...)
	__attribute__ ((format(printf, 3, 4)));

// log an entry with the filename and location with a timestamp
void zlog_time(char *filename, int line, char const *fmt, ...)
	__attribute__ ((format(printf, 3, 4)));

#endif
