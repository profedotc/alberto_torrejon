#ifndef _GOL_H_ 
#define _GOL_H_

#define X 10
#define Y 10

void gol_init(int ini[X][Y]);
void gol_print(int ini[X][Y]);
void gol_step(int ini[X][Y],int fin[X][Y],int i);
int gol_count_neighbors(int ini[X][Y],int i,int j);
bool gol_rule(int ini[X][Y],int i,int j);
bool gol_get_cell(int ini[X][Y],int i,int j);


#endif