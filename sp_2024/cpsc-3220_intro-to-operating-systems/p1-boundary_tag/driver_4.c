/* CPSC 3220-002 - Spring 2024 - program 1 - driver 4
 *
 * return code tests
 *
 * signature checking is used for free blocks
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* global data structures */

struct tag_block { char tag; char sig[11]; unsigned int size; };
struct free_block { struct free_block *back_link, *fwd_link; };
struct free_block *free_list;

/* signature check macro */

#define SIGCHK(w,x,y,z) {struct tag_block *scptr = (struct tag_block *)(w);\
if(strncmp((char *)(scptr)+1,(x),(y))!=0){printf("*** sigchk fail\n");\
printf("*** at %s, offset is 0x%x, sig is %s\n",\
(z),((unsigned int)(((char *)w)-region_base)),(char *)(w)+1);}}

#define TOPSIGCHK(a,b) {SIGCHK((a),"top_",4,(b))}
#define ENDSIGCHK(a,b) {SIGCHK((a),"end_",4,(b))}

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
  TOPSIGCHK(tb,"prt_free_block")
  ENDSIGCHK((char *)(tb)+(tb->size)+16,"prt_free_block")
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
  unsigned int rc;

  printf("memory allocation test 4, pointer size is %lu bytes\n",
    sizeof(void *));

  init_region();

  ptr[1] = alloc_mem(0x50);
  if( ptr[1] != NULL ){
    prt_alloc_block(1,ptr[1]);
  }else{
    printf("ptr[1] gets NULL\n");
  }
  rc = release_mem(ptr[1]);
  printf("release_mem(ptr[1]) returns %d - 0 expected\n",rc);

  ptr[2] = alloc_mem(0x800);
  if( ptr[2] != NULL ){
    prt_alloc_block(2,ptr[2]);
  }else{
    printf("ptr[2] gets NULL\n");
  }
  rc = release_mem(ptr[2]);
  printf("release_mem(ptr[2]) returns %d - 1 expected\n",rc);

  ptr[3] = alloc_mem(0x200);
  if( ptr[3] != NULL ){
    prt_alloc_block(3,ptr[3]);
  }else{
    printf("ptr[3] gets NULL\n");
  }
  rc = release_mem(ptr[3]+3);
  printf("release_mem(ptr[3]+3) returns %d - 2 expected\n",rc);
  rc = release_mem(ptr[3]);
  printf("release_mem(ptr[3]) returns %d - 0 expected\n",rc);
  rc = release_mem(ptr[3]);
  printf("repeat of release_mem(ptr[3]) returns %d - 3 expected\n",rc);

  return 0;
}
