#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gol.h"

#define ITER 1000

int main(){

	int i = 0;
	struct world w;
	
    //gol_alloc(&w,X,Y);
	if (!gol_alloc(&w,X,Y)){
        fprintf(stderr, "Error couldn't allocate memory\n");
        return EXIT_FAILURE;
    }

    gol_alloc(&w);
	gol_init(&w);
	
    for (int i = 0; i < ITER; i++)
        gol_step(&w);
    
    gol_free(&w);
    
	gol_free(&w);

	return EXIT_SUCCESS;
}


