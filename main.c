#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "GoL.h"

int main(){

	int i = 0;
	int world[2][X][Y];

	gol_init(world);
	
	do {
		printf("\033cIteration %d\n", i++);
		gol_step(world,i%2);

	} while (getchar() != 'q');
	return EXIT_SUCCESS;
}
