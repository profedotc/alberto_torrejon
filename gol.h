#ifndef _GOL_H_ 
#define _GOL_H_

#define X 10
#define Y 20

struct world;

void gol_init(struct world *w);
void gol_print(struct world *w);
void gol_step(struct world *w);

struct world *gol_alloc(int size_x, int size_y);
void gol_free(struct world *w);

#endif