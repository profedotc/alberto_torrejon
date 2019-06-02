#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "GoL.h"

void gol_init(int world[][X][Y]){
	// Poner el mundo a false
	for (int k=0;k<2;k++){
		for (int i=0; i<=X; i++) 
			for (int j=0; j<=Y; j++) 
				world[k][i][j] = 0;
	// Inicializar con un patrón
	world[k][5][5]=1;
	world[k][5][6]=1;
	world[k][5][7]=1;
	}
}


void gol_print(int world[][X][Y],int s){
	for (int i=0;i<=X;i++){
		for (int j=0; j<=Y; j++){
			printf("%c",world[s][i][j]?'x':' ');
		}
		printf("\n");
	}
}

void gol_step(int world[][X][Y],int s){
	gol_print(world,s);
	for (int i=0; i<X; i++)
		for (int j=0; j<Y; j++)
			world[!s][i][j] = gol_rule(world,i,j,s);
}

bool gol_rule(int world[][X][Y],int i,int j,int s){
	switch (gol_count_neighbors(world, i, j, s)){
	case 2: return world[s][i][j];
	case 3: return 1;
	default: return 0;
	}
}

int gol_count_neighbors(int world[][X][Y],int i,int j,int s){
	// Devuelve el número de vecinos
	int contador = -world[s][i][j];
	for (int k = i-1; k <= i+1; k++){
		for (int l = j-1; l <= j+1; l++){
			contador += gol_get_cell(world,k,l,s); 
		}	
	}
	return contador;
}

bool gol_get_cell(int world[][X][Y],int i,int j,int s){
	//Validación del mundo
	if (i >= 0 && j >= 0 && i < X && j < Y){
		return world[s][i][j];
	}else{
		return 0;
	}
}