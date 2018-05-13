/*
 * main.h
 *
 *  Created on: Apr 22, 2018
 *      Author: user
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <ulfius.h>

#include "utils/utils.h"
#include "serverManager/serverManager.h"
#include "daemonize.h"
#include "ini_parser/ini_parser.h"
#include "logger.h"
#include "configuration.h"

#endif /* MAIN_H_ */
