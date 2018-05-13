/*
 * delete_mark.h
 *
 *  Created on: May 2, 2018
 *      Author: user
 */

#ifndef DELETE_MARK_H_
#define DELETE_MARK_H_

#include <getopt.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <time.h>
#include <libiptc/libiptc.h>
#include <linux/netfilter/x_tables.h>
#include <xtables.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <linux/netfilter/xt_mark.h>
#include "utils/generate_mark_entry.h"

int delete_mark(const char* ip, __u16 port);

#endif /* DELETE_MARK_H_ */
