/*
Nikhil Grover
CSE 351 - Autumn 2017
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 262144 bytes
    associativity = 1
mystery1:
    block size = 8 bytes
    cache size = 16384 bytes
    associativity = 4
mystery2:
    block size = 16 bytes
    cache size = 65536 bytes
    associativity = 16
mystery3:
    block size = 2 bytes
    cache size = 131072 bytes
    associativity = 2
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  int i = 0;
  int block = 0;
  access_cache(0);
  while(access_cache(i)) {
    block++;
    i++;
  }

  return block;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  int i = 0;
  int check_size = block_size;
  flush_cache();
  access_cache(0);
  while(access_cache(0)) {
    i = block_size;
    while(i <= check_size) {
      i += block_size;
      access_cache(i);
    }
    check_size += block_size;
  }
  return i;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  int i = 0;
  int check = 1;
  int E = 0;
  flush_cache();
  access_cache(0);
  while(access_cache(0)) {
    i = cache_size;
    E = 0;
    while(i <= check) {
      i += cache_size;
      E++;
      access_cache(i);
    }
    check += cache_size;
  }
  return E;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
