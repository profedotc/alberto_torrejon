#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM_X 10
#define TAM_Y 10

int main(){
	int i,j,s=0,
	contador = 0;
	//como está programado la frontera tienen que ser 0
	int inicial[TAM_X][TAM_Y]={
					   {0,0,0,0,0,0,0,0,0,0},
					   {0,0,1,0,0,0,0,0,0,0},
					   {0,0,1,0,0,0,1,0,0,0},
					   {0,0,1,0,1,1,0,0,0,0},
					   {0,0,0,0,0,1,0,0,0,0},
					   {0,0,0,0,1,1,0,0,0,0},
					   {0,0,1,0,0,0,0,0,0,0},
					   {0,0,0,0,0,0,0,0,0,0},
					   {0,0,1,0,0,0,0,1,1,0},
					   {0,0,0,0,0,0,0,0,0,0}
					   }; 
	int final[TAM_X][TAM_Y]; 						
	do{
		printf("\033cIteration %d\n",s++);
		for (i=1; i<TAM_X-1; i++){
			for (j=1; j<TAM_Y-1;j++){
				if (inicial[i-1][j]==1) contador++;
				if (inicial[i+1][j]==1) contador++;
				if (inicial[i][j-1]==1) contador++;
				if (inicial[i][j+1]==1) contador++;
				if (inicial[i-1][j-1]==1) contador++;
				if (inicial[i+1][j-1]==1) contador++;
				if (inicial[i+1][j+1]==1) contador++;
				if (inicial[i-1][j+1]==1) contador++;
				//printf("contador=%d\n",contador);
				if (contador==2) final[i][j]=inicial[i][j];
				if (contador==3) final[i][j]=1;
				if (contador<2) final[i][j]=0;
				if (contador>3) final[i][j]=0;
				contador = 0;	
				//printf("contador=%d\n",contador);
		}}
		for (i=1;i<TAM_X-1;i++){
			for (j=1;j<TAM_Y-1;j++){
			inicial[i][j]=final[i][j];
		}}
		for (i=0;i<TAM_X;i++){
			for (j=0; j<TAM_Y; j++){
				printf("%c",inicial[i][j]?'x':' ');
				//printf("%d",inicial[i][j]);
			}
			printf("\n");
		}
	} while (getchar() != 'q');
	
	return 0;
}

