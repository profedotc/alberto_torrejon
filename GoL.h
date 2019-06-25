#ifndef _GOL_H_ 
#define _GOL_H_

#define X 10
#define Y 20

struct world {
    bool *worlds[2];
    int nrows;
    int ncols;
};

void gol_init(struct world *w);
void gol_print(struct world *w);
void gol_step(struct world *w);

bool gol_alloc(struct world *w,int size_x,int size_y);
void gol_free(struct world *w);

#endif