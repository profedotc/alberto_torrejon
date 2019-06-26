#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "config.h"

static const char *init_mode_str[] = {
	[CFG_DEFAULT] = "default",
	[CFG_RANDOM]  = "random"
};

static const struct option long_options[] =
{
	{"usage",  no_argument,       0, 'u'},
	{"width",  required_argument, 0, 'w'}, 
	{"height", required_argument, 0, 'h'}, 
	{"init",   required_argument, 0, 'i'},
	{"seed",   optional_argument, 0, 's'},
	{0, 0, 0, 0}
};

static bool check_config(const struct config *config);
static enum cfg_init_mode str2init_mode(const char *opt);

//args getopt_long
int config_parse_argv(struct config *config, int argc, char *argv[])
{
	int option_index = 0;
	int c;

	// Default values
	config->show_help = false;
	config->nrows     = 10;
	config->ncols     = 10;
	config->init_mode = CFG_DEFAULT;
	config->seed = -1;

	while ((c = getopt_long(argc, argv, "uw:h:i:s:", long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'u':
			config->show_help = true;
			break;
		case 'w':
			config->nrows = strtol(optarg, NULL, 0);
			break;
		case 'h':
			config->ncols = strtol(optarg, NULL, 0);
			break;
		case 'i':
			config->init_mode = str2init_mode(optarg);
			break;
		case 's':
			config->seed =  strtol(optarg, NULL, 0);
			break;
		case '?':
			printf("\nERROR: unknown option %s \n", optarg);
			return false;
			break;
		}
	}

	return check_config(config);
}

//Comprobar los inputs
static bool check_config(const struct config *config)
{
	bool correct = true;

	if (config->show_help)
		return true;

	correct &= config->nrows > 0;
	correct &= config->ncols > 0;
	correct &= config->init_mode > -1;

	return correct;
}

static enum cfg_init_mode str2init_mode(const char *opt)
{
	int i;
	for (i = 0; i < CFG_N_INIT_MODES; i++)
		if ( !strcmp(opt, init_mode_str[i]) )
			break;
	return i == CFG_N_INIT_MODES ? CFG_NOT_DEF : i;
}

//Imprimir la ayuda del usage
void config_print_usage(const char *arg0)
{
	printf("Usage: %s\n"
		"\t[-u|--usage]\n"
		"\t[-w|--width]\n"
		"\t[-h|--height]\n"
		"\t[-i|--init <see init_mode>]\n"
		"\t[-s|--seed <only in init_mode::random>]\n"
		, arg0);

	printf("\ninit_mode: ");
	for (int i = 0; i < CFG_N_INIT_MODES + 1; i++)
		printf(" '%s'", init_mode_str[i]);
	printf("\n\n");
}

