#include "mark.h"

void register_mark_handlers(struct _u_instance * instance)
{
	ulfius_add_endpoint_by_val(instance, "GET", "/v1", "/marks", 0, &callback_get_marks, NULL);
	ulfius_add_endpoint_by_val(instance, "POST", "/v1", "/mark", 0, &callback_post_mark, NULL);
	ulfius_add_endpoint_by_val(instance, "DELETE", "/v1", "/mark", 0, &callback_delete_mark, NULL);
}

// callback GET /marks
int callback_get_marks (const struct _u_request * request, struct _u_response * response, void * user_data) {
  json_t * json_nb_sheep = ulfius_get_json_body_request(request, NULL), * json_body = NULL, *json_response = NULL;
  struct ip_port *ip_port_list = NULL, *ptr = NULL;
  /*#if JSON_INTEGER_IS_LONG_LONG
    long long nb_sheep = 0;
  #else
	long nb_sheep = 0;
  #endif*/

  ip_port_list = get_marks();

  json_response = json_array();

  for (ptr = ip_port_list; ptr; ptr = ptr->next) {
	  json_body = json_object();
	  json_object_set_new(json_body, "ip", json_string(ptr->ip));
	  json_object_set_new(json_body, "port", json_integer(ptr->port));
	  json_array_append_new(json_response, json_body);
  }

  char mystr[1024];
  sprintf(mystr, "GET /marks - %s", request->http_url);
  ulfius_set_json_body_response(response, 200, json_response);
  json_decref(json_nb_sheep);
  json_decref(json_body);
  return U_CALLBACK_CONTINUE;
}

// callback /POST mark
int callback_post_mark (const struct _u_request * request, struct _u_response * response, void * user_data) {
  const char *ip = u_map_get(request->map_post_body, "ip");
  const char *port_str = u_map_get(request->map_post_body, "port");
  __u16 port = strtoul (port_str, NULL, 0);
  add_mark(ip, port);
  char mystr[1024];
  sprintf(mystr, "POST /marks - %s:%d", ip, port);
  ulfius_set_string_body_response(response, 200, mystr);
  return U_CALLBACK_CONTINUE;
}

// callback DELETE /mark
int callback_delete_mark (const struct _u_request * request, struct _u_response * response, void * user_data) {
  const char *ip = u_map_get(request->map_post_body, "ip");
  const char *port_str = u_map_get(request->map_post_body, "port");
  __u16 port = strtoul (port_str, NULL, 0);
  delete_mark(ip, port);
  char mystr[1024];
  sprintf(mystr, "DELETE /marks - %s:%d", ip, port);
  ulfius_set_string_body_response(response, 200, mystr);
  return U_CALLBACK_CONTINUE;
}
