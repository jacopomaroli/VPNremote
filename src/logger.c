/*
 * logger.c
 *
 *  Created on: May 13, 2018
 *      Author: user
 */
#include "logger.h"

void init_logger(logger *logger_to_init)
{
	logger_to_init->log_file_name = NULL;
	logger_to_init->log_stream = NULL;
	logger_to_init->init = init;
	logger_to_init->append = append;
	logger_to_init->terminate = terminate;
}

void init(logger *self, const char *log_file_name) {
	/* Try to open log file to this daemon */
	if (log_file_name != NULL) {
		self->log_stream = fopen(log_file_name, "a+");
		if (self->log_stream == NULL) {
			syslog(LOG_ERR, "Can not open log file: %s, error: %s",
				log_file_name, strerror(errno));
			self->log_stream = stdout;
		}
	} else {
		self->log_stream = stdout;
	}
}

int append(logger *self, const char *entry) {
	int ret = 0;

	ret = fprintf(self->log_stream, "%s\n", entry);
	if (ret < 0) {
		syslog(LOG_ERR, "Can not write to log stream: %s, error: %s",
			(self->log_stream == stdout) ? "stdout" : self->log_file_name, strerror(errno));
		return ret;
	}

	ret = fflush(self->log_stream);
	if (ret != 0) {
		syslog(LOG_ERR, "Can not fflush() log stream: %s, error: %s",
			(self->log_stream == stdout) ? "stdout" : self->log_file_name, strerror(errno));
		return ret;
	}

	return ret;
}

void terminate(logger *self) {
	if (self->log_stream != stdout) {
		fclose(self->log_stream);
	}
}
