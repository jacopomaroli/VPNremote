/*
 * utils.c
 *
 *  Created on: Apr 22, 2018
 *      Author: user
 */

#include "utils.h"

int check_root()
{
	uid_t uid = geteuid();

	if(uid)
	{
		struct passwd *pw = getpwuid(uid);
		if (pw)
		{
			fprintf(stderr, "running as: \"%s\". root privileges are required to interact with iptables\n", pw->pw_name);
		}
		return 1;
	}

	return 0;
}

void log_cwd()
{
	/*char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return NULL;
	}
		fprintf(stdout, "Current working dir: %s\n", cwd);
	else*/

}

void register_interrupt_handlers(void *term)
{
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigemptyset(&action.sa_mask);
	action.sa_flags=0;
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGINT, &action, NULL);
}
