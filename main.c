#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gol.h"

int main(){

	int i = 0;
	struct world w;
	
	gol_alloc(&w,X,Y);
	gol_init(&w,X,Y);
	
	do {
		printf("\033cIteration %d\n", i++);
		gol_print(&w,X,Y);
		gol_step(&w,X,Y);
	} while (getchar() != 'q');

	gol_free(&w,Y);
	return EXIT_SUCCESS;
}


