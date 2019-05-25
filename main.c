#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "GoL.h"

int main(){

	int i = 0;
	
	// Declara dos mundos
	int ini[X][Y];
	int fin[X][Y];

	// Inicializa el mundo
	gol_init(ini);
	
	do {
	
		printf("\033cIteration %d\n", i++);
	
		//Iterar
		gol_step(ini,fin,i);

	} while (getchar() != 'q');
	return EXIT_SUCCESS;
}
