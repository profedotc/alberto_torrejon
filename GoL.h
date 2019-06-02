#ifndef _GOL_H_ 
#define _GOL_H_

#define X 10
#define Y 10

void gol_init(int world[][X][Y]);
void gol_print(int world[][X][Y],int s);
void gol_step(int world[][X][Y],int s);
int gol_count_neighbors(int world[][X][Y],int i,int j,int s);
bool gol_rule(int world[][X][Y],int i,int j,int s);
bool gol_get_cell(int world[][X][Y],int i,int j,int s);


#endif