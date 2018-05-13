/*
 * logger.h
 *
 *  Created on: May 13, 2018
 *      Author: user
 */

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct logger logger, *pno;

void init(logger *self, const char *log_file_name);
int append(logger *self, const char *entry);
void terminate(logger *self);

struct logger
{
	const char *log_file_name;
	FILE *log_stream;

    void (*init)();
    int (*append)();
    void (*terminate)();
};

void init_logger(logger *logger_to_init);

#endif /* SRC_LOGGER_H_ */
