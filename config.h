#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 60

enum cfg_init_mode {
	CFG_NOT_DEF = -1,
	CFG_DEFAULT ,
	CFG_RANDOM ,
	_CFG_MAX_,
};

#define CFG_N_INIT_MODES (_CFG_MAX_)

struct config {
	bool show_help;
	int nrows;
	int ncols;
	enum cfg_init_mode init_mode;
	int seed;
};

int config_parse_argv(struct config *config, int argc, char *argv[]);
void config_print_usage(const char *arg0);

#endif