/*
 * generate_mark_entry.c
 *
 *  Created on: May 3, 2018
 *      Author: user
 */

#include "generate_mark_entry.h"

//  target = xtables_find_target("MARK", XTF_TRY_LOAD);
//  t = ipt_get_target(entry);
//	size = IPT_ALIGN(sizeof(struct ipt_entry_target))
//						+ target->size;


//iptables -t mangle -A PREROUTING -p tcp --dport 80 -s 192.168.1.143 -j MARK --set-mark 1

struct ipt_entry *generate_mark_entry(const char* ip, __u16 port)
{
	struct ipt_entry *e = NULL;

	struct xt_entry_match *match_proto;
	struct xt_tcp *tcpinfo;
	struct xt_entry_target *target;
	struct xt_mark_tginfo2 *mark_info;

	unsigned int size_ipt_entry = XT_ALIGN(sizeof(struct ipt_entry));
	unsigned int size_ipt_entry_match = XT_ALIGN(sizeof(struct xt_entry_match));
	unsigned int size_ipt_tcp = XT_ALIGN(sizeof(struct xt_tcp));
	unsigned int size_ipt_entry_target = XT_ALIGN(sizeof(struct ipt_entry_target));
	unsigned int size_ipt_entry_target_data = XT_ALIGN(sizeof(struct xt_mark_tginfo2));

	unsigned int entry_length = size_ipt_entry + size_ipt_entry_match + size_ipt_tcp;
	unsigned int total_length = entry_length + size_ipt_entry_target + size_ipt_entry_target_data;

	e = (struct ipt_entry *)calloc(1, total_length);
	if(e == NULL)
	{
			printf("calloc failure :%s\n", strerror(errno));
			return 0;
	}

	//offsets to the other bits:
	//target struct begining
	e->target_offset = entry_length;
	//next "e" struct, end of the current one
	e->next_offset = total_length;

	//match structs setting:
	//set match rule for the protocol to use
	//”-p tcp” part of our desirable rule
	match_proto = (struct ipt_entry_match *) e->elems;
	match_proto->u.match_size = size_ipt_entry_match + size_ipt_tcp;
	strcpy(match_proto->u.user.name, "tcp");//set name of the module, we will use in this match

	//set up packet matching rules: "-s 192.168.1.143" part
	//of our desirable rule
	e->ip.src.s_addr = inet_addr(ip);
	e->ip.smsk.s_addr= inet_addr("255.255.255.255");
	//e->ip.dst.s_addr = inet_addr("0.0.0.0");
	//e->ip.dmsk.s_addr= inet_addr("255.255.255.255");
	e->ip.proto = IPPROTO_TCP;
	//e->nfcache = 0;
	//strcpy(e->ip.iniface, "");

	//tcp module - match extension
	//"--dport 80” part of our desirable rule
	tcpinfo = (struct xt_tcp *)match_proto->data;
	tcpinfo->spts[0] = 0x0;
	tcpinfo->spts[1] = 0xFFFF;
	tcpinfo->dpts[0] = port;
	tcpinfo->dpts[1] = port;
	tcpinfo->invflags = 0x0000;

	//target struct
	//"-j MARK --set-mark 1" part of our desirable rule
	// target = ipt_get_target(e);
	target = (struct xt_entry_target *)((void *)e + e->target_offset);
	target->u.target_size = size_ipt_entry_target + size_ipt_entry_target_data;
	strcpy(target->u.user.name,"MARK");
	target->u.user.revision = 2;
	mark_info = (struct xt_mark_tginfo2 *)target->data;
	// according to mark_tg_print implementation
	// mark == 0 -> and
	// mark == mask -> or
	// mask == 0 -> xor
	// mask == 0xffffffffU -> set
	// else -> xset
	mark_info->mark = 1;
	mark_info->mask = 0xffffffffU;

	return e;
}
