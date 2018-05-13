/*
 * add_mark.h
 *
 *  Created on: Apr 15, 2018
 *      Author: user
 */

#ifndef ADD_MARK_H_
#define ADD_MARK_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <linux/types.h>
#include <libiptc/libiptc.h>
#include <linux/netfilter/xt_limit.h>
#include <linux/netfilter/xt_physdev.h>
#include <linux/netfilter/xt_dscp.h>
#include <linux/netfilter/xt_mark.h>
#include <linux/netfilter/xt_RATEEST.h>
#include <linux/netfilter/xt_rateest.h>
#include <linux/netfilter/xt_DSCP.h>
#include <linux/netfilter/xt_tcpudp.h>
#include <linux/netfilter/xt_physdev.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_mark.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "utils/generate_mark_entry.h"

int add_mark(const char* ip, __u16 port);

#endif /* ADD_MARK_H_ */
