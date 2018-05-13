/*
 * delete_mark.c
 *
 *  Created on: May 2, 2018
 *      Author: user
 */

#include "delete_mark.h"

/*static unsigned char *
make_delete_mask(struct xtables_rule_match *matches,
		 const struct xtables_target *target)
{
	// Establish mask for comparison
	unsigned int size;
	struct xtables_rule_match *matchp;
	unsigned char *mask, *mptr;

	size = sizeof(struct ipt_entry);
	for (matchp = matches; matchp; matchp = matchp->next)
		size += XT_ALIGN(sizeof(struct ipt_entry_match)) + matchp->match->size;

	mask = xtables_calloc(1, size
			 + XT_ALIGN(sizeof(struct ipt_entry_target))
			 + target->size);

	memset(mask, 0xFF, sizeof(struct ipt_entry));
	mptr = mask + sizeof(struct ipt_entry);

	for (matchp = matches; matchp; matchp = matchp->next) {
		memset(mptr, 0xFF,
		       XT_ALIGN(sizeof(struct ipt_entry_match))
		       + matchp->match->userspacesize);
		mptr += XT_ALIGN(sizeof(struct ipt_entry_match)) + matchp->match->size;
	}

	memset(mptr, 0xFF,
	       XT_ALIGN(sizeof(struct ipt_entry_target))
	       + target->userspacesize);

	return mask;
}*/

int delete_mark(const char* ip, __u16 port)
{
	struct ipt_entry *e = NULL;
	struct xtc_handle *h;

	/*const xt_chainlabel chain;
	struct xtables_rule_match *matches = NULL;
	struct xtables_target *target_module = NULL;*/
	unsigned char *mask;

	int result = 0;

	/*strcpy((char *)chain,"PREROUTING");

	struct xtables_globals xtp;

	xtp.program_name = "VNC_remote";
	xtp.compat_rev = xtables_compatible_revision;

	int ret = xtables_init_all(&xtp, NFPROTO_IPV4);
	if (ret < 0) {
		fprintf(stderr, "%s/%s Failed to initialize xtables\n",
				xtp.program_name,
				xtp.program_version);
		result = -1;
		goto end;
	}

	xtables_find_match("tcp", XTF_TRY_LOAD, &matches);

	target_module = xtables_find_target("MARK", XTF_TRY_LOAD);

	if (!target_module)
	{
		printf("error\n");
		result = -1;
		goto end;
	}*/

	e = generate_mark_entry(ip, port);

	//target_module->t = ipt_get_target(e);

	//mask = make_delete_mask(matches, target_module);
	mask = (unsigned char *)calloc(1, e->next_offset);
	memset(mask, 0xFF, e->next_offset);
	h = iptc_init("mangle");
	if(!h)
	{
		printf( "error condition  %s\n", iptc_strerror(errno));
		result = -1;
		goto end;
	}

	int x = iptc_delete_entry("PREROUTING", e, mask, h);
	if (!x)
	{
		printf("iptc_append_entry::Error insert/append entry: %s\n", iptc_strerror(errno));
		result = -1;
		goto end;
	}

	int y = iptc_commit(h);
	if (!y)
	{
		printf("iptc_commit::Error commit: %s\n", iptc_strerror(errno));
		result = -1;
		goto end;
	}

	end:
		free(e);
		iptc_free(h);
		return result;
}
