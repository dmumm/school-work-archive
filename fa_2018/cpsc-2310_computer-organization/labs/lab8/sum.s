/*
Dylan Mumm
CPSC 2311-004
Lab 8
*/


    .file "sum.s"
    .text
    .align  2
    .global main
    .type   main, %function

/* main() sums 10 values from stdin and prints the sum */
main:

    push {lr}    // save lr

    add sp, sp, #-40 // allows storage of 10 ints of size 4
    mov r4, sp       // stack pointer stored in r4
    mov r5, #1       // initializing counter

    loop1:

      cmp r5, #10  // if(i <= 10)...
      bgt done1    // branch -> after loop

      ldr r0, =rdfmt      // loading scanf
		  mov r1, r4		      // moving sp to r1
		  bl scanf		        // calling scanf

		  add r4, r4, #4	// move pointer up one integer
		  add r5, r5, #1	// i++
      b loop1         // loop

	  done1:

    	mov r4, sp			// r4 moved to bottom of stack
    	mov r5, #1			// counter = 1
    	mov r6, #0 			// sum = 0

  	loop2:

  		cmp r5, #10		// if(i <= 10)...
  		bgt done2     // branch -> after loop

  		ldr r0, [r4]	  // retrieve element pointed to by r4
  		add r6, r6, r0	// sum += r0

  		add r4, r4, #4	// move pointer up one integer
  		add r5, r5, #1	// i++
  		bal loop2       // loop

  	done2:

  	ldr r0, = prtfmt	// loading print
  	mov r1, r6			  // moving sum to r1
  	bl printf			    // calling printf

  	add sp, sp, #40		// clearing stack


    pop {pc}         // put lr in pc

.section    .rodata
    rdfmt:        .asciz "%d"
    prtfmt:       .asciz "sum is %d\n"
