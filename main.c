#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <time.h>

#include "gol.h"
#include "config.h"

static bool load_world(struct world *w);
static bool save_world(struct world *w);

int main(int argc, char *argv[]){

	int i = 0;
	bool run = true;

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
	
		printf("Welcome to the Game of Life \n"
		" (a) Automatic mode \n"
		" (m) Manual mode \n"
		"Type q to exit the game \n"
		"Type a/m:");
	
	switch (getchar()){
	case 'a':
		do{
			printf("\033cIteration %d\n", i++);
			gol_print(w);
			usleep((useconds_t) 10000);
			gol_step(w);
		} while (i<=100);
		gol_free(w);
		return EXIT_SUCCESS;

	case 'm':
		
		while( run != false){
			switch (getchar()){
			case 'q':
				run = false;
				break;
			case 's':
				if(!save_world(w))
					getchar();
				break;	
			case 'l':
				if(!load_world(w))
					getchar();
				break;	
			default:
				break;
		}
		printf("\033cIteration %d\n", i++);
		gol_print(w);
		gol_step(w);
		}
		gol_free(w);
		return EXIT_SUCCESS;
	
	default:
		break;
	}	

}


static bool load_world(struct world *w){
	
	char file[255];
	int matches;

	printf("Insert file name: ");
	matches = scanf("%254s",file);
	getchar();
	if(matches != 1){
		perror("Error reading name");
		return false;
	}
	if(!gol_load(w,file)){
		return false;
	}

	return true;
}

static bool save_world(struct world *w){
	
	char file[255];
	int matches;

	printf("Insert file name: ");
	matches = scanf("%s",file);
	getchar();
	if(matches != 1){
		perror("Error reading name");
		return false;
	}
	if(!gol_save(w,file)){
		return false;
	}

	return true;
}