/*
 * serverManager.h
 *
 *  Created on: Apr 22, 2018
 *      Author: user
 */

#ifndef SERVERMANAGER_SERVERMANAGER_H_
#define SERVERMANAGER_SERVERMANAGER_H_

#include <stdio.h>
#include <ulfius.h>
#include "../handlers.h"

int startServer(struct _u_instance * instance, configuration *config, struct _static_file_config *static_file_config);
int stopServer(struct _u_instance * instance, configuration *config, struct _static_file_config *static_file_config);

#endif /* SERVERMANAGER_SERVERMANAGER_H_ */
