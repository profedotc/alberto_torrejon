#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "GoL.h"


void gol_init(int ini[X][Y]){
	// Poner el mundo a false
	int	i,j;
	for (i=0; i<=X; i++) 
		for (j=0; j<=Y; j++) 
			ini[i][j] = 0;
	// Inicializar con un patrón
	ini[5][5]=1;
	ini[5][6]=1;
	ini[5][7]=1;
}


void gol_print(int ini[X][Y]){
	// Imprimir el mundo por consola
	int	i,j;
	for (i=0;i<=X;i++){
		for (j=0; j<=Y; j++){
			printf("%c",ini[i][j]?'x':' ');
		}
		printf("\n");
	}
}

void gol_step(int mundo1[X][Y],int mundo2[X][Y],int a){
	int	i,j;	
	if (a%2==1){
		gol_print(mundo1);
		for (i=0; i<=X; i++){
			for (j=0; j<=Y; j++){
				mundo2[i][j] = gol_rule(mundo1,i,j);
		}}
	}else{
		gol_print(mundo2);
		for (i=0; i<=X; i++){
			for (j=0; j<=Y; j++){
				mundo1[i][j] = gol_rule(mundo2,i,j);
		}}		
	}
}


bool gol_rule(int mundo[X][Y],int i,int j){
	switch (gol_count_neighbors(mundo, i, j))
	{
	case 2: return mundo[i][j];
	case 3: return 1;
	default: return 0;
	}
}

int gol_count_neighbors(int mundo[X][Y],int i,int j){
	// Devuelve el número de vecinos
	int contador = -mundo[i][j];
	for (int k = i-1; k <= i+1; k++){
		for (int l = j-1; l <= j+1; l++){
			contador += gol_get_cell(mundo,k,l); 
		}	
	}
	return contador;
}


bool gol_get_cell(int mundo[X][Y],int i,int j){
	//Validación del mundo
	if (i >= 0 && j >= 0 && i < X && j < Y){
		return mundo[i][j];
	}else{
		return 0;
	}
}

