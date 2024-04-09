#ifndef BITMAP_H
#define BITMAP_H

extern unsigned int spaceship_bitmap[8];
extern unsigned int alien_bitmap[8];
extern unsigned int spaceship_bitmap_alive[8];
extern unsigned int spaceship_bitmap_dead[8];
extern unsigned int mouse_bitmap[8];
extern unsigned int mouse_bitmap_old[8];

/*
Function: reverseBits
Arguments:
    unsigned int num: The number whose bits are to be reversed.
Returns:
    unsigned int: The result after reversing the bits of the input number.
Description:
    Reverses the bit order of a given number. This can be used in operations where bit manipulation or reflection is required, such as graphics processing.
*/
unsigned int reverseBits(unsigned int num);

/*
Function: mirrorBitmap
Arguments:
    const unsigned int *bitmap: Pointer to the original bitmap data.
    unsigned int *mirroredBitmap: Pointer to the storage for the mirrored bitmap.
    unsigned int size: Size of the bitmap (assumed to be square for simplicity).
Description:
    Creates a horizontally mirrored version of the provided bitmap. Useful in graphical operations where an inverted image is needed, like sprite animations.
*/
void mirrorBitmap(const unsigned int *bitmap, unsigned int *mirroredBitmap, unsigned int size);

/*
Function: copyBitmap
Arguments:
    const unsigned int source[]: Array representing the source bitmap.
    unsigned int destination[]: Array where the copied bitmap will be stored.
    int size: The size of the bitmap arrays.
Description:
    Copies the contents of one bitmap array to another. This function is essential for operations that require duplication of bitmap data.
*/
void copyBitmap(const unsigned int source[], unsigned int destination[], int size);

#endif /* BITMAP_H */
