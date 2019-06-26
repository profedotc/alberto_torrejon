#ifndef _GOL_H_ 
#define _GOL_H_

#include "config.h"

struct world;

struct world *gol_alloc(struct config *cfg);
void gol_free(struct world *w);

void gol_init(struct world *w, int mode,int s);
void gol_print(struct world *w);
void gol_step(struct world *w);

bool gol_load(struct world *w,const char *file);
bool gol_save(const struct world *w,const char *file);


#endif