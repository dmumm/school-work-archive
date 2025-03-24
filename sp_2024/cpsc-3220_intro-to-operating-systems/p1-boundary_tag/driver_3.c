/* CPSC 3220-002 - Spring 2024 - program 1 - driver 3
 *
 * tests
 *   first fit in alloc_mem()
 *   appending to head of free list in release_mem()
 *
 * release_mem() only uses case 1
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

  printf("memory allocation test 3, pointer size is %lu bytes\n",
    sizeof(void *));

  init_region();

  ptr[1] = alloc_mem(0x50); if(ptr[1]==NULL) printf("ptr[1] gets NULL\n");
  ptr[2] = alloc_mem(0x50); if(ptr[2]==NULL) printf("ptr[2] gets NULL\n");
  ptr[3] = alloc_mem(0x50); if(ptr[3]==NULL) printf("ptr[3] gets NULL\n");
  ptr[4] = alloc_mem(0x50); if(ptr[4]==NULL) printf("ptr[4] gets NULL\n");
  ptr[5] = alloc_mem(0x40); if(ptr[5]==NULL) printf("ptr[5] gets NULL\n");
  ptr[6] = alloc_mem(0x40); if(ptr[6]==NULL) printf("ptr[6] gets NULL\n");
  ptr[7] = alloc_mem(0x40); if(ptr[7]==NULL) printf("ptr[7] gets NULL\n");
  ptr[8] = alloc_mem(0x40); if(ptr[8]==NULL) printf("ptr[8] gets NULL\n");
  ptr[9] = alloc_mem(0x30); if(ptr[9]==NULL) printf("ptr[9] gets NULL\n");
  ptr[10] = alloc_mem(0x30); if(ptr[10]==NULL) printf("ptr[10] gets NULL\n");
  ptr[11] = alloc_mem(0x30); if(ptr[11]==NULL) printf("ptr[11] gets NULL\n");
  ptr[12] = alloc_mem(0x30); if(ptr[12]==NULL) printf("ptr[12] gets NULL\n");
  ptr[13] = alloc_mem(0x20); if(ptr[13]==NULL) printf("ptr[13] gets NULL\n");
  ptr[14] = alloc_mem(0x20); if(ptr[14]==NULL) printf("ptr[14] gets NULL\n");
  ptr[15] = alloc_mem(0x20); if(ptr[15]==NULL) printf("ptr[15] gets NULL\n");
  rc=release_mem(ptr[2]); if(rc) printf("*** release_mem(ptr[2]) fails\n");
  rc=release_mem(ptr[4]); if(rc) printf("*** release_mem(ptr[4]) fails\n");
  rc=release_mem(ptr[6]); if(rc) printf("*** release_mem(ptr[6]) fails\n");
  rc=release_mem(ptr[8]); if(rc) printf("*** release_mem(ptr[8]) fails\n");
  rc=release_mem(ptr[10]); if(rc) printf("*** release_mem(ptr[10]) fails\n");
  rc=release_mem(ptr[12]); if(rc) printf("*** release_mem(ptr[12]) fails\n");
  rc=release_mem(ptr[14]); if(rc) printf("*** release_mem(ptr[14]) fails\n");
  prt_free_list();

  ptr[16] = alloc_mem(0x50);
  if(ptr[16]==NULL) printf("*** alloc_mem(ptr[16]) returns NULL\n");
  ptr[17] = alloc_mem(0x28);
  if(ptr[17]==NULL) printf("*** alloc_mem(ptr[17]) returns NULL\n");
  ptr[18] = alloc_mem(0x200);
  if(ptr[18]!=NULL) printf("*** alloc_mem(ptr[18]) returns non-NULL\n");
  prt_free_list();

  printf("allocated blocks\n");
  prt_alloc_block(16,ptr[16]);
  prt_alloc_block(17,ptr[17]);

  return 0;
}
