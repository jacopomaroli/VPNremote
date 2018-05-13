/*
 * fileHandler.h
 *
 *  Created on: Apr 22, 2018
 *      Author: user
 */

#ifndef FILEHANDLER_FILEHANDLER_H_
#define FILEHANDLER_FILEHANDLER_H_

#include <stdio.h>
#include <string.h>
#include <orcania.h>
#include <yder.h>
#include <ulfius.h>
#include "../configuration.h"

#define STATIC_FILE_CHUNK 256

struct _static_file_config {
  const char    * files_path;
  const char    * url_prefix;
  struct _u_map * mime_types;
};

void register_files_handler(struct _u_instance * instance, configuration *config, struct _static_file_config *static_file_config);
int callback_static_file (const struct _u_request * request, struct _u_response * response, void * user_data);
const char * get_filename_ext(const char *path);

#endif /* FILEHANDLER_FILEHANDLER_H_ */
