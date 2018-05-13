#ifndef __REST_MARK_H__
#define __REST_MARK_H__

#include <ulfius.h>
#include <jansson.h>
#include "../get_marks.h"
#include "../add_mark.h"
#include "../delete_mark.h"

void register_mark_handlers(struct _u_instance * instance);
int callback_get_marks (const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_post_mark (const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_delete_mark (const struct _u_request * request, struct _u_response * response, void * user_data);

#endif // __REST_MARK_H__
