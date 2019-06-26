#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gol.h"

struct world {
    bool *worlds[2];
    bool *mem; //Puntero para reserva conjunta
    int nrows;
    int ncols;
};

enum world_type {
	CURRENT = 0,
	NEXT = 1,
	NUM_WORLDS = 2
};

//MACRO para la reserva del bloque de memoria
#define CELL(w,wtype,i,j) ((w)->worlds[(wtype)][(i) * (w)->ncols + (j)]) 


static void fix_coords(const struct world *w, int *i, int *j);
static void set_cell(struct world *w, enum world_type wtype, 
						int i, int j, bool alive);
static bool get_cell(const struct world *w, enum world_type wtype, int i, int j);
static int count_neighbors(const struct world *w, int i, int j);
static bool rule(const struct world *w,int i,int j);

//Reserva memoria conjunta
struct world *gol_alloc(int size_x, int size_y){
	struct world *w;

	w = malloc(sizeof(struct world));
	if(!w) 
		return NULL;

	w->mem = (bool *)malloc(NUM_WORLDS * size_x * size_y * sizeof(bool));
	if(!w->mem){
		free(w);
		return NULL;
	}
		
	w->nrows = size_x;
	w->ncols = size_y;
	w->worlds[CURRENT]=w->mem;
	w->worlds[NEXT]=w->mem + size_x * size_y;

	return w;
}

//Liberación memoria
void gol_free(struct world *w){
		free(w->mem);
}

//Inicializar el mundo
void gol_init(struct world *w){
	// Poner el mundo a false
		for (int i = 0; i < w->nrows; i++) 
			for (int j = 0; j < w->ncols; j++) 
				set_cell(w,CURRENT,i,j,false);
	// Inicializar con un patrón
	set_cell(w,CURRENT,5,5,true);
	set_cell(w,CURRENT,5,6,true);
	set_cell(w,CURRENT,5,7,true);
	
	// //Otro patrón de prueba:
	// //¿Por qué empieza en 0 y no en 1?
	// // set_cell(w,CURRENT,0,0,true);	
	// set_cell(w,CURRENT,1,3,true);
	// set_cell(w,CURRENT,2,1,true);
	// set_cell(w,CURRENT,2,3,true);
	// set_cell(w,CURRENT,3,2,true);
	// set_cell(w,CURRENT,3,3,true);

}

//Imprimir mundo
void gol_print(struct world *w){
	for (int i = 0; i < w->nrows; i++){
		for (int j = 0; j< w->ncols; j++){
			printf("%c",get_cell(w,CURRENT,i,j)?'x':' ');
		}
		printf("\n");
	}
}

//Iterar
void gol_step(struct world *w){
	for (int i=0; i<w->nrows; i++)
		for (int j=0; j<w->ncols; j++)
			set_cell(w,NEXT,i,j,rule(w,i,j));
	//Cambio del mundo
	bool *aux = w->worlds[NEXT];
	w->worlds[NEXT] = w->worlds[CURRENT];
	w->worlds[CURRENT] = aux;
}

static bool rule(const struct world *w,int i,int j){
	switch (count_neighbors(w, i, j)){
	case 2: return get_cell(w,CURRENT,i,j);
	case 3: return 1;
	default: return 0;
	}
}

static int count_neighbors(const struct world *w,int i,int j){
	// Devuelve el número de vecinos
	int contador = -get_cell(w,CURRENT,i,j);
	for (int k = i-1; k <= i+1; k++){
		for (int l = j-1; l <= j+1; l++){
			contador += get_cell(w,CURRENT,k,l); 
		}	
	}
	return contador;
}

static void set_cell(struct world *w, enum world_type wtype, int i, int j, bool alive){
	fix_coords(w,&i,&j);
	CELL(w,wtype,i,j) = alive;
}

static bool get_cell(const struct world *w, enum world_type wtype, int i, int j){
	fix_coords(w,&i,&j);
	return CELL(w,wtype,i,j);
}

static void fix_coords(const struct world *w, int *i, int*j){
	if (*i >= w->nrows)
		*i = 0;
	else if (*i<0)
		*i = w->nrows - 1;

	if (*j >= w->ncols)
		*j = 0;
	else if (*j<0)
		*j = w->ncols - 1;
} 
