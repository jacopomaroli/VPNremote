/*
 * configuration.h
 *
 *  Created on: May 13, 2018
 *      Author: user
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

#include <linux/types.h>

typedef struct
{
    const char* logFile;
    struct
    {
    	__u16 port;
        const char* web_assets;
    } web_interface;
} configuration;

#endif /* SRC_CONFIGURATION_H_ */
