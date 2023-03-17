#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize){
  if(newSize == 0){
    free(pointer);
    return NULL;
  }
  /* When newSize is zero, we handle the deallocation case ourselves by calling free(). Otherwise, we rely on the C standard library’s realloc() function. That function conveniently supports the other three aspects of our policy. When oldSize is zero, realloc() is equivalent to calling malloc().

The interesting cases are when both oldSize and newSize are not zero. Those tell realloc() to resize the previously allocated block. If the new size is smaller than the existing block of memory, it simply updates the size of the block and returns the same pointer you gave it. If the new size is larger, it attempts to grow the existing block of memory.

It can do that only if the memory after that block isn’t already in use. If there isn’t room to grow the block, realloc() instead allocates a new block of memory of the desired size, copies over the old bytes, frees the old block, and then returns a pointer to the new block. Remember, that’s exactly the behavior we want for our dynamic array. */
  void* result = realloc(pointer, newSize);
  if(result == NULL) exit(1);
  return result;
}
