#ifndef _GOL_H_ 
#define _GOL_H_

#define X 10
#define Y 10

struct world {
    bool **worlds[2];
};

void gol_init(struct world *w, int size_x, int size_y);
void gol_print(struct world *w, int size_x, int size_y);
void gol_step(struct world *w, int size_x, int size_y);

void gol_alloc(struct world *w, int size_x, int size_y);
void gol_free(struct world *w, int size_y);


#endif