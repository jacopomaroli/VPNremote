/*
 * utils.h
 *
 *  Created on: Apr 22, 2018
 *      Author: user
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>

int check_root();
void log_cwd();
void register_interrupt_handlers(void *term);

volatile sig_atomic_t done;

#endif /* UTILS_UTILS_H_ */
