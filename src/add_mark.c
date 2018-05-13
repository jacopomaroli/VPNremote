/*
 * add_mark.c
 *
 *  Created on: Apr 15, 2018
 *      Author: user
 */

#include "add_mark.h"

int add_mark(const char* ip, __u16 port)
{
	struct ipt_entry *e = NULL;
	struct xtc_handle *h;
	int result = 0;
	int err = 0;
	unsigned char *mask;
	int errno_clone = 0;

	e = generate_mark_entry(ip, port);

	mask = (unsigned char *)calloc(1, e->next_offset);
	memset(mask, 0xFF, e->next_offset);

	h = iptc_init("mangle");
	if(!h)
	{
		printf( "error condition  %s\n", iptc_strerror(errno));
		result = -1;
		goto end;
	}

	// in case of no duplicate entries are found iptc_check_entry will return 0 and errno = ENOENT
	// in case of duplicate entries are found iptc_check_entry will return 1 and errno = ENOENT
	// in case of errors iptc_check_entry will return 0 and the corresponding error
	// iptc_check_entry cannot reliably be used to assess if a rule already exists
	//err = iptc_check_entry("PREROUTING", e, (unsigned char*) mask, h);
	//errno_clone = errno;
	/*if (err && errno_clone == ENOENT)
	{
		printf("iptc_check_entry::Error check entry: already existing\n");
		result = -1;
		goto end;
	}
	if (err && errno_clone != ENOENT)
	{
		printf("iptc_check_entry::Error check entry: %s\n", iptc_strerror(errno_clone));
		result = -1;
		goto end;
	if(!err)
	{
		printf("iptc_check_entry::Error check entry: %s\n", iptc_strerror(errno_clone));
		result = -1;
		goto end;
	}
	}*/

	err = iptc_append_entry("PREROUTING", e, h);
	errno_clone = errno;
	if (!err)
	{
		printf("iptc_append_entry::Error insert/append entry: %s\n", iptc_strerror(errno_clone));
		result = -1;
		goto end;
	}

	err = iptc_commit(h);
	errno_clone = errno;
	if (!err)
	{
		printf("iptc_commit::Error commit: %s\n", iptc_strerror(errno_clone));
		result = -1;
		goto end;
	}

	end:
		free(e);
		iptc_free(h);
		return result;
}
