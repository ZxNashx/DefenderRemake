#include "defs.h"
#include <osbind.h>
/* Function to get the current time from the system clock */
uint32_t get_time() {
    uint32_t *pointerToTimer = (volatile uint32_t *)0x462;
    uint32_t timenow;
    uint32_t old_ssp;

    old_ssp = Super(0);      
    timenow = *pointerToTimer;  
    Super(old_ssp);       

    return timenow;    
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
