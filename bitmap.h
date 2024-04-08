#ifndef BITMAP_H
#define BITMAP_H

extern unsigned int spaceship_bitmap[8];
extern unsigned int alien_bitmap[8];
extern unsigned int spaceship_bitmap_alive[8];
extern unsigned int spaceship_bitmap_dead[8];

unsigned int reverseBits(unsigned int num);
void mirrorBitmap(const unsigned int *bitmap, unsigned int *mirroredBitmap, unsigned int size);
void copyBitmap(const unsigned int source[], unsigned int destination[], int size);

#endif /* BITMAP_H */
