/*
 * daemonize.h
 *
 *  Created on: May 8, 2018
 *      Author: user
 */

#ifndef DAEMONIZE_H_
#define DAEMONIZE_H_

#include <stdio.h>    //printf(3)
#include <stdlib.h>   //exit(3)
#include <unistd.h>   //fork(3), chdir(3), sysconf(3)
#include <signal.h>   //signal(3)
#include <sys/stat.h> //umask(3)
#include <syslog.h>   //syslog(3), openlog(3), closelog(3)

int daemonize2(char* name, char* path, char* outfile, char* errfile, char* infile );

#endif /* DAEMONIZE_H_ */
