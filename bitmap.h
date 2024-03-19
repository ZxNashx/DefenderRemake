#ifndef BITMAP_H
#define BITMAP_H

extern unsigned int spaceship_bitmap[8];
extern unsigned int alien_bitmap[8];


unsigned int reverseBits(unsigned int num);
void mirrorBitmap(const unsigned int *bitmap, unsigned int *mirroredBitmap, size_t size);

#endif /* BITMAP_H */
