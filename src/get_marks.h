/*
 * get_marks.h
 *
 *  Created on: Apr 23, 2018
 *      Author: user
 */

#ifndef GET_MARKS_H_
#define GET_MARKS_H_

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

struct ip_port
{
	struct ip_port *next;
	char ip[INET_ADDRSTRLEN];
	__u16 port;
};

struct ipt_entry_list {
	struct ipt_entry_list *next;
	const struct ipt_entry *e;
};

struct ip_port *get_marks();

#endif /* GET_MARKS_H_ */
