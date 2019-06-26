﻿#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

#include "gol.h"
#include "config.h"

int main(int argc, char *argv[]){

	int i = 0;

	struct config cfg;
	struct world *w;

	if (!config_parse_argv(&cfg, argc, argv)) {
		printf("ERROR: Bad input\n");
		config_print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	else if (cfg.show_help) {
		config_print_usage(argv[0]);
		return EXIT_SUCCESS;
	}

	w = gol_alloc(&cfg);
	if (!w){
        fprintf(stderr, "Error couldn't allocate memory\n");
        return EXIT_FAILURE;
    }

	gol_init(w,cfg.init_mode,cfg.seed);
	
	do {
		printf("\033cIteration %d\n", i++);
		gol_print(w);
		usleep((useconds_t) 10000);
		gol_step(w);
	} while (i<=100); //iteraciones automáticas
	//} while (getchar() != 'q') //iteraciones manual

	gol_free(w);

	return EXIT_SUCCESS;
}


