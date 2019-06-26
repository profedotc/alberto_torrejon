#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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
struct world *gol_alloc(struct config *cfg){
	struct world *w;
	int size_x = cfg->nrows;
	int size_y = cfg->ncols;

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

//Guardar como binario 
bool gol_save(const struct world *w,const char *file){
	
	FILE *f;
	f = fopen(file, "w");
	if(!f){
		perror("Couldn't open de world file");
		return false;
	}

	fwrite(w->worlds[CURRENT],sizeof(bool), w->nrows * w->ncols,f);
	if (ferror(f)){
		perror("Couldn't write the world file");
		fclose(f);
		return false;
	}

	fclose(f);
	return true;

}
 
//Cargar binario 
bool gol_load(struct world *w,const char *file){
	
	size_t read_bytes;
	size_t size;

	FILE *f;
	f = fopen(file, "r");
	if(!f){
		perror("Couldn't open de world file");
		return false;
	}

	read_bytes = fread(w->worlds[CURRENT],sizeof(bool), w->nrows * w->ncols,f);
	
	if (ferror(f)){
		perror("Couldn't read world file");
		fclose(f);
		return false;
	}

	fclose(f);
	return true;

}

//Inicializar el mundo
void gol_init(struct world *w, int mode,int s){
	for (int i = 0; i < w->nrows; i++)
		for (int j = 0; j < w->ncols; j++)
			set_cell(w, CURRENT, i, j, false);

	//default 
	if (mode == 0) {
		set_cell(w,CURRENT,5,5,true);
		set_cell(w,CURRENT,5,6,true);
		set_cell(w,CURRENT,5,7,true);
	}

	//random
	else if (mode == 1) {
		if (s!=-1){
			srand((unsigned) s);
			for (int i = 0; i < w->nrows; i++)
				for (int j = 0; j < w->ncols; j++)
					set_cell(w, 0, i, j, rand() % 2);
		} else {
			/* Intializes random number generator */
			time_t t;
			srand((unsigned) time(&t));
		
			for (int i = 0; i < w->nrows; i++)
				for (int j = 0; j < w->ncols; j++)
					set_cell(w, 0, i, j, rand() % 2);
		}
	}
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


