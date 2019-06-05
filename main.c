#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "GoL.h"

int main(){

	int i = 0;
	struct world w;

	gol_init(&w);
	
	do {
		printf("\033cIteration %d\n", i++);
		gol_print(&w);
		gol_step(&w);

	} while (getchar() != 'q');
	return EXIT_SUCCESS;
}


