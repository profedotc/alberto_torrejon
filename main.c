#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define X 10
#define Y 10

void gol_init(int ini[X][Y]);
void gol_print(int ini[X][Y]);
void gol_step(int ini[X][Y],int fin[X][Y]);
int gol_count_neighbors(int ini[X][Y],int i,int j);
bool gol_get_cell(int ini[X][Y],int i,int j);
void gol_copy(int ini[X][Y],int fin[X][Y]);

int main(){
	int i = 0;
	// Declara dos mundos
	int ini[X][Y];
	int fin[X][Y];
	
	int inicial=ini;
	int final=fin;

	// Inicializa el mundo
	gol_init(inicial);
	
	do {
		printf("\033cIteration %d\n", i++);
		// Imprime el mundo
		gol_print(inicial);
		// Itera
		gol_step(inicial,final);
		
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void gol_init(int ini[X][Y]){
	// Poner el mundo a false
	int	i,j;
	for (i=0; i<X; i++) 
		for (j=0; j<Y; j++) 
			ini[i][j] = 0;
	// Inicializar con un patrón
	ini[5][5]=1;
	ini[5][6]=1;
	ini[5][7]=1;

}

void gol_print(int ini[X][Y]){
	// Imprimir el mundo por consola
	int	i,j;
	for (i=0;i<X;i++){
		for (j=0; j<Y; j++){
			printf("%c",ini[i][j]?'x':' ');
		}
		printf("\n");
	}
}

void gol_step(int ini[X][Y],int fin[X][Y]){
	int	i,j;
	for (i=1;i<X-1;i++){
		for (j=1;j<Y-1;j++){
		fin[i][j]=gol_get_cell(ini[X][Y],i,j);
	}}
	gol_copy(ini[X][Y],fin[X][Y]);
}

int gol_count_neighbors(int ini[X][Y],int i,int j){
	// Devuelve el número de vecinos
	int contador=0;
	if (ini[i-1][j]==1) contador++;
	if (ini[i+1][j]==1) contador++;
	if (ini[i][j-1]==1) contador++;
	if (ini[i][j+1]==1) contador++;
	if (ini[i-1][j-1]==1) contador++;
	if (ini[i+1][j-1]==1) contador++;
	if (ini[i+1][j+1]==1) contador++;
	if (ini[i-1][j+1]==1) contador++;
	return contador;
}

bool gol_get_cell(int ini[X][Y],int i,int j){
	// Devuelve el estado de la célula de posición indicada
	if (gol_count_neighbors(ini[X][Y],i,j)==2) 1;
	if (gol_count_neighbors(ini[X][Y],i,j)==3) 1;
	if (gol_count_neighbors(ini[X][Y],i,j)<2) 0;
	if (gol_count_neighbors(ini[X][Y],i,j)>3) 0;
}

void gol_copy(int ini[X][Y],int fin[X][Y]){
	// Copia el mundo segundo mundo sobre el primero
	int	i,j;
	for (i=1;i<X-1;i++){
		for (j=1;j<Y-1;j++){
			ini[i][j]=fin[i][j];
	}}
}
