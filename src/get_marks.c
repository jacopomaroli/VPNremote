/*
 * get_marks.c
 *
 *  Created on: Apr 23, 2018
 *      Author: user
 */

#include "get_marks.h"

static int rule_match(const struct ipt_entry *e,
		struct xtc_handle *h, const char *chain, int counters)
{
  struct ipt_entry_target *t;
  struct xt_mark_tginfo2 *mark_info;

  t = ipt_get_target((struct ipt_entry *)e);

  if (!t->u.user.name[0] || strcmp(t->u.user.name, "MARK")) {
	  return 1;
  }

  mark_info = (struct xt_mark_tginfo2 *)t->data;
  if(mark_info->mark != 1 || mark_info->mask != 0xffffffffU)
  {
	  return 1;
  }

  return 0;
}

struct ip_port *get_marks()
{
  struct xtc_handle *h;
  const struct ipt_entry *e = NULL;
  const char *chain = "PREROUTING";
  char *tablename = "mangle";
  int counters = 1;
  struct ip_port *ip_port_list = NULL;

  struct xtables_globals xtp;

  xtp.program_name = "VNC_remote";
  xtp.compat_rev = xtables_compatible_revision;

  int ret = xtables_init_all(&xtp, NFPROTO_IPV4);
  if (ret < 0) {
	fprintf(stderr, "%s/%s Failed to initialize xtables\n",
			xtp.program_name,
			xtp.program_version);
			return 0;
  }

  h = iptc_init(tablename);
  if ( !h )   {
	 printf("Error initializing: %s\n", iptc_strerror(errno));
	exit(errno);
  }

  char buf[INET_ADDRSTRLEN];
  struct ipt_entry_list *mark_entry_list, *prev_mark_entry, *base_mark_entry_list, *ptr;
  unsigned int marksLen = 0;

  mark_entry_list = NULL;
  prev_mark_entry = NULL;
  base_mark_entry_list = NULL;

  for (e = iptc_first_rule(chain, h); e; e = iptc_next_rule(e, h))  {
    if(!rule_match(e, h, chain, counters))
    {
    	mark_entry_list = malloc(sizeof(struct ipt_entry_list));
    	if(!mark_entry_list)
    	{
    		perror("malloc error!");
    		exit(1);
    	}
    	if(prev_mark_entry)
    	{
    		prev_mark_entry->next = mark_entry_list;
    	}
    	else
    	{
    		base_mark_entry_list = mark_entry_list;
    	}
    	prev_mark_entry = mark_entry_list;

    	mark_entry_list->e = e;
    	mark_entry_list->next = 0;

    	marksLen++;
    }
  }

  struct ip_port *prev, *base_ip_port_list;

  prev = NULL;
  base_ip_port_list = NULL;

  for (ptr = base_mark_entry_list; ptr; ptr = ptr->next) {
	  struct xt_tcp *tcpinfo;
	  struct xt_entry_match *match_proto;

	  ip_port_list = malloc(sizeof(struct ip_port));
	  if(!ip_port_list)
	  {
		perror("malloc error!");
		exit(1);
	  }
	  if(prev)
	  {
		  prev->next = ip_port_list;
	  }
	  else
	  {
		  base_ip_port_list = ip_port_list;
	  }
	  prev = ip_port_list;

	  match_proto = (struct ipt_entry_match *) ptr->e->elems;
	  tcpinfo = (struct xt_tcp *) match_proto->data;

	  printf("--> %s:%d\n", inet_ntop(AF_INET, &ptr->e->ip.src.s_addr, buf, sizeof(buf)), tcpinfo->dpts[0]);

	  inet_ntop(AF_INET, &ptr->e->ip.src.s_addr, ip_port_list->ip, sizeof(ip_port_list->ip));
	  ip_port_list->port = tcpinfo->dpts[0];
	  ip_port_list->next = 0;
  }

  return base_ip_port_list;
}
