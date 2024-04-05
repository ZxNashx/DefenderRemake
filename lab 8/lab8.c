#include <stdio.h>
#include <osbind.h>

#define VBL_VECTOR 28

typedef void (*Vector)();
extern void vbl_isr();

Vector install_vector(int num, Vector vector);

int seconds;
int counter;

int main(){
    Vector orig_vector = install_vector(VBL_VECTOR, vbl_isr);
    long i;
    counter = 0;
    seconds = 0;

    for(i = 0; i < 10000000; i++){
        if(counter >= 70){
            counter = 0;
            seconds += 1;
            if(seconds == 10){
                i = 10000000;
            }
        }
    }

    install_vector(VBL_VECTOR, orig_vector);
    return 0;
}

Vector install_vector(int num, Vector vector){
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;

    Super(old_ssp);
    return orig;
}

void do_VBL_ISR(){
    counter += 1;
}