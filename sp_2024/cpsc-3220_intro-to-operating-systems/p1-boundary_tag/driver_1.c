/* CPSC 3220-002 - Spring 2024 - program 1 - driver 1
 *
 * tests of alloc_mem()
 *   make sure block splits are correct
 *   make sure odd request sizes are rounded up to a multiple of 16
 *   make sure logic for no split is working when less than 48 bytes
 *     remain after split
 *
 * no signature checking
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* global data structures */

struct tag_block { char tag; char sig[11]; unsigned int size; };
struct free_block { struct free_block *back_link, *fwd_link; };
struct free_block *free_list;

char *region_base;

void *alloc_mem( unsigned int amount );
unsigned int release_mem( void *ptr );

void init_region(){
  struct tag_block *ptr;
  struct free_block *links1, *links2;

  /* obtain the memory region */

  region_base = (char *) malloc( 1680 );
  if( region_base == NULL ){ printf( "no memory!\n" ); exit(0); }

  /* set up end_region tag block at top of region */
  /*   to simplify the coalescing logic           */

  ptr = (struct tag_block *) region_base;
  ptr->tag = 1;
  strcpy( ptr->sig, "end_region" );
  ptr->size = 0;

  /* set up the top tag block for the initial free block */

  ptr = (struct tag_block *)(region_base + 16);
  ptr->tag = 0;
  strcpy( ptr->sig, "top_memblk" );
  ptr->size = 1600;

  /* set up the end tag block for the initial free block */

  ptr = (struct tag_block *)(region_base + 1632);
  ptr->tag = 0;
  strcpy( ptr->sig, "end_memblk" );
  ptr->size = 1600;

  /* set up top_region tag block at end of region */
  /*   to simplify the coalescing logic           */

  ptr = (struct tag_block *)(region_base + 1648);
  ptr->tag = 1;
  strcpy( ptr->sig, "top_region" );
  ptr->size = 0;

  /* set up free list */

  links1 = (struct free_block *)(region_base + 32);
  links2 = (struct free_block *)(region_base + 1664);
  links1->back_link = links2;
  links1->fwd_link = links2;
  links2->back_link = links1;
  links2->fwd_link = links1;

  free_list = links2;

  printf( "free_list header node is located at offset 0x%x\n",
    (unsigned int)(((char *)free_list) - region_base));
}

void prt_free_block( struct free_block *fb ){
  struct tag_block *tb = (struct tag_block *)((char *)(fb)-16);
  printf( "   free block at offset 0x%x of size 0x%x\n",
    (unsigned int)(((char *)fb) - region_base), tb->size );
}

void prt_alloc_block( int b, char *alloc_block ){
  struct tag_block *tb = (struct tag_block *)((char *)(alloc_block)-16);
  printf( "   alloc block %d at offset 0x%x of size 0x%x\n",
    b, (unsigned int)(alloc_block - region_base), tb->size );
}

void prt_free_list(){
  struct free_block *ptr;
  if( free_list->fwd_link == free_list ){
    printf( "   ----------free list is empty-----------\n" );
    return;
  }
  printf( "   ---------------free list---------------\n" );
  ptr = free_list->fwd_link;
  prt_free_block( ptr );
  ptr = ptr->fwd_link;
  while( ptr != free_list ){
    prt_free_block( ptr );
    ptr = ptr->fwd_link;
  }
  printf( "   --------------end of list--------------\n" );
}


int main(){
  void *ptr[20];

  printf("memory allocation test 1, pointer size is %lu bytes\n",
    sizeof(void *));

  init_region();
  prt_free_list();

  printf("alloc 2 blocks of 0xf0 each\n");
  printf("(since you need an extra 0x20 bytes of tags on a split,\n");
  printf(" each split of 0xf0 bytes will use 0x110 bytes of free space)\n");
  ptr[1] = alloc_mem(0xf0); if(ptr[1]==NULL) printf("ptr[1] gets NULL\n");
  prt_free_list();
  ptr[2] = alloc_mem(0xf0); if(ptr[2]==NULL) printf("ptr[2] gets NULL\n");
  prt_free_list();

  printf("alloc 3 blocks of odd sizes - should round up to 0xf0 each\n");
  ptr[3] = alloc_mem(0xe1); if(ptr[3]==NULL) printf("ptr[3] gets NULL\n");
  prt_free_list();
  ptr[4] = alloc_mem(0xe4); if(ptr[4]==NULL) printf("ptr[4] gets NULL\n");
  prt_free_list();
  ptr[5] = alloc_mem(0xe8); if(ptr[5]==NULL) printf("ptr[5] gets NULL\n");
  prt_free_list();

  printf("alloc block of 0xd0 - 0x30 not left so should get remaining 0xf0\n");
  ptr[6] = alloc_mem(0xd0); if(ptr[6]==NULL) printf("ptr[6] gets NULL\n");
  prt_free_list();

  printf("allocated blocks\n");
  prt_alloc_block(1,ptr[1]);
  prt_alloc_block(2,ptr[2]);
  prt_alloc_block(3,ptr[3]);
  prt_alloc_block(4,ptr[4]);
  prt_alloc_block(5,ptr[5]);
  prt_alloc_block(6,ptr[6]);

  return 0;
}
