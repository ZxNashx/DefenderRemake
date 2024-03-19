#include "input.h"
#include <osbind.h>

int input_available() {
    return Cconis();
}

char read_input() {
    if (input_available()) {
        return (char)Cnecin();
    }
    return 0; 
}
