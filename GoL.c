#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "GoL.h"

static bool get_cell(struct world *w,int i,int j){
	//Validación del mundo
	if (i >= 0 && j >= 0 && i < X && j < Y){
		return w->worlds[w->s][i][j];
	}else{
		return 0;
	}
}

static int count_neighbors(struct world *w,int i,int j){
	// Devuelve el número de vecinos
	int contador = -w->worlds[w->s][i][j];
	for (int k = i-1; k <= i+1; k++){
		for (int l = j-1; l <= j+1; l++){
			contador += get_cell(w,k,l); 
		}	
	}
	return contador;
}

static bool rule(struct world *w,int i,int j){
	switch (count_neighbors(w, i, j)){
	case 2: return w->worlds[w->s][i][j];
	case 3: return 1;
	default: return 0;
	}
}

void gol_init(struct world *w){
	// Poner el mundo a false
	for (int k=0;k<2;k++){
		for (int i=0; i<X; i++) 
			for (int j=0; j<Y; j++) 
				w->worlds[k][i][j] = 0;
	// Inicializar con un patrón
	w->worlds[k][5][5]=1;
	w->worlds[k][5][6]=1;
	w->worlds[k][5][7]=1;
	}
	w->s = 0;
}


void gol_print(struct world *w){
	for (int i=0;i<X;i++){
		for (int j=0; j<Y; j++){
			printf("%c",w->worlds[w->s][i][j]?'x':' ');
		}
		printf("\n");
	}
}

void gol_step(struct world *w){
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			w->worlds[!(w->s)][i][j] = rule(w,i,j);
	w->s=!(w->s);
}

