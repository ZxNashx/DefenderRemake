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
