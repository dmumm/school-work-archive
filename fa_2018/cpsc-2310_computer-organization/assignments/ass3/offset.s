/*
  Dylan Mumm
   CPSC 2310
   11.9
*/

        .text
        .global offset
        .type offset, %function




offset:

  push {r4, lr}

  mov r4, #4

  mul r3, r0, r2  //   row# * elements per row
  add r3, r3, r1 // + column#
  mul r2, r4, r3  // * sizeof(int)

  pop {r4, pc}

  .align	2
