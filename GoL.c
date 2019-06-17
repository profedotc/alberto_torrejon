#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gol.h"

enum world_state {
	CURRENT = 0,
	NEXT = 1,
};

static bool get_cell(struct world *w, int i, int j, int size_x, int size_y);
static int count_neighbors(struct world *w, int i, int j, int size_x, int size_y);
static bool rule(struct world *w,int i,int j, int size_x, int size_y);

//Reserva de memoria
void gol_alloc(struct world *w, int size_x, int size_y){
  w->worlds[CURRENT] = (bool **)malloc(size_x * sizeof(bool *));
  w->worlds[NEXT] = (bool **)malloc(size_x * sizeof(bool *));
  for (int i = 0; i < size_y; i++){
    w->worlds[CURRENT][i] = (bool *)malloc(size_y * sizeof(bool));
    w->worlds[NEXT][i] = (bool *)malloc(size_y * sizeof(bool));
  }
}

//Liberación memoria
void gol_free(struct world *w, int size_y){
  for (int i = 0; i < size_y; i++){
    free(w->worlds[NEXT][i]);
    free(w->worlds[CURRENT][i]);
  }
  free(w->worlds[NEXT]);
  free(w->worlds[CURRENT]);
}

//Inicializar el mundo
void gol_init(struct world *w, int size_x, int size_y){
	// Poner el mundo a false
		for (int i=0; i<size_x; i++) 
			for (int j=0; j<size_y; j++) 
				w->worlds[CURRENT][i][j] = 0;
	// Inicializar con un patrón
	w->worlds[CURRENT][5][5]=1;
	w->worlds[CURRENT][5][6]=1;
	w->worlds[CURRENT][5][7]=1;
}

//Imprimir mundo
void gol_print(struct world *w,int size_x, int size_y){
	for (int i=0;i<size_x;i++){
		for (int j=0; j<size_y; j++){
			printf("%c",w->worlds[CURRENT][i][j]?'x':' ');
		}
		printf("\n");
	}
}

void gol_step(struct world *w,int size_x, int size_y){
	for (int i=0; i<size_x; i++)
		for (int j=0; j<size_y; j++)
			w->worlds[NEXT][i][j] = rule(w,i,j,size_x,size_y);
	//Cambio del mundo
	bool *aux = w->worlds[NEXT];
	w->worlds[NEXT] = w->worlds[CURRENT];
	w->worlds[CURRENT] = aux;
}

static bool rule(struct world *w,int i,int j, int size_x, int size_y){
	switch (count_neighbors(w, i, j, size_x, size_y)){
	case 2: return w->worlds[CURRENT][i][j];
	case 3: return 1;
	default: return 0;
	}
}

static bool get_cell(struct world *w,int i,int j,int size_x, int size_y){
	//Validación del mundo
	if (i >= 0 && j >= 0 && i < size_x && j < size_y){
		return w->worlds[CURRENT][i][j];
	}else{
		return 0;
	}
}

static int count_neighbors(struct world *w,int i,int j,int size_x,int size_y){
	// Devuelve el número de vecinos
	int contador = -w->worlds[CURRENT][i][j];
	for (int k = i-1; k <= i+1; k++){
		for (int l = j-1; l <= j+1; l++){
			contador += get_cell(w,k,l,size_x,size_y); 
		}	
	}
	return contador;
}

