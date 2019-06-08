#ifndef _GOL_H_ 
#define _GOL_H_

#define X 10
#define Y 10

struct world {
    int worlds[2][X][Y];
    int s; //current world
};

void gol_init(struct world *w);
void gol_print(struct world *w);
void gol_step(struct world *w);
//int gol_count_neighbors(struct world *w,int i,int j);
//bool gol_rule(struct world *w,int i,int j);
//bool gol_get_cell(struct world *w,int i,int j);

#endif