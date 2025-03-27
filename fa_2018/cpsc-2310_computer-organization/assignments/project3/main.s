/*
  Dylan Mumm
   CPSC 2310
   11.9
*/

.file "main.s"
.text
        .global main
        .type main, %function



main:

  push {r4-r7, lr}
  mov r4, r0      // saving argc
  mov r5, r1     // saving argv

store:

  ldr r0, [r5, #4]     // converting i to int
  bl atoi
  mov r1, r0

  ldr r0, [r5, #8]     // converting j to int
  bl atoi
  mov r2, r0

  ldr r0, [r5, #12]    // converting n to int
  bl atoi

  mov r2, r0           // shifting registers
  mov r1, r2
  mov r0, r1

run:

  bl offset           // running offset subroutine

  mov r3, r2  // shifting registers up
  mov r2, r1
  mov r1, r0

print:

  ldr r0, =fmt1      // loading printf into r0
  bl printf          // calling print f

done:

  mov		r0, #0       // restoring r0
  pop {r4-r7,pc}

  .align	2

fmt1:    .asciz "the offset for a[%d][%d] is %d\n"
