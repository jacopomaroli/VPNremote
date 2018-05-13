#include "serverManager.h"

int startServer(struct _u_instance * instance, configuration *config, struct _static_file_config *static_file_config)
{
	// Initialize instance with the port number
	if (ulfius_init_instance(instance, config->web_interface.port, NULL, NULL) != U_OK) {
		fprintf(stderr, "Error ulfius_init_instance, abort\n");
		return 1;
	}

	// Endpoint list declaration
	register_mark_handlers(instance);
	register_files_handler(instance, config, static_file_config);

	// Start the framework
	if (ulfius_start_framework(instance) != U_OK)
	{
		fprintf(stderr, "Error starting framework\n");
		ulfius_clean_instance(instance);
		return 1;
	}

	printf("Server listening on port %d\n", instance->port);

	return 0;
}

int stopServer(struct _u_instance * instance, configuration *config, struct _static_file_config *static_file_config)
{
	u_map_clean(static_file_config->mime_types);
	o_free(static_file_config->mime_types);
	ulfius_stop_framework(instance);
	ulfius_clean_instance(instance);
	printf("Server stopped\n");

	return 0;
}
