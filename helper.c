#include "defs.h"
#include "model.h"
#include <osbind.h>
#include "isr.h"
/* Function to get the current time from the system clock */
uint32_t get_time() {

    return vbl_counter;    
}

/**
 * Function to check if a point is within a box.
 */
int hit_detection(int point_x, int point_y, 
                        int box_x, int box_y, 
                        int box_width, int box_height) {
    return (point_x >= box_x && point_x <= (box_x + box_width) &&
            point_y >= box_y && point_y <= (box_y + box_height));
}

/* Deactivate all shots */
void deactivate_all_shots(GameModel *model) {
    int i;

    /* Deactivate all alien shots */
    for (i = 0; i < SHOT_COUNT; i++) {
        model->alienShots[i].active = false;
        model->playerShots[i].active = false;
    }

}