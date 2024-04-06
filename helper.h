#ifndef HELPER_H
#define HELPER_H

#include "defs.h"
#include "model.h"

/* Function to get the current time from the system clock */
uint32_t get_time();
int hit_detection(int point_x, int point_y, 
                        int box_x, int box_y, 
                        int box_width, int box_height);
void deactivate_all_shots(GameModel *model);

#endif /* HELPER_H */
