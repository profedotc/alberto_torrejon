#ifndef _GOL_H_ 
#define _GOL_H_

#include "config.h"

struct world;

void gol_init(struct world *w, int mode,int s
);
void gol_print(struct world *w);
void gol_step(struct world *w);

//struct world *gol_alloc(int size_x, int size_y);
struct world *gol_alloc(struct config *cfg);
void gol_free(struct world *w);

#endif