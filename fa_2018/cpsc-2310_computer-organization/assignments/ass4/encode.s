// --------------- //
// Dylan Mumm      //
// CPSC 2310 002   //
// 12.7            //
// --------------- //

input  .req r0
output .req r1
key    .req r2
switch .req r3

.file "encode.s"
.section .text
.global encode
.align 4
.type encode, %function

encode:
  push {r4-r11, lr}

  mov r4, #0 // key count
  mov r5, #0 // string count
  mov r6, input  // take input from register
  mov r7, output // take output from register
  mov r8, key    // take key from register

  cmp switch, #1 // if switch == 1
  beq decode     // branch to decode

loop:
  ldrb r9, [r6, r5] // load value in input offset by counter

  cmp r9, #0 // if r9 == NULL
  beq done   // branch to done

  cmp r9, #32 // if r9 == space
  beq spaceE  // branch to spaceE

  ldrb r10, [r8, r4] // load value in key offset by counter

  cmp r10, #0 // if r10 == NULL
  beq resetE  // reset keystring

  cmp r10, #32 // if r10 == space
  beq zeroE    // encode as zero

  sub r9, r9, #96   // convert r9 into decimal
  sub r10, r10, #96 // convert r10 into decimal
  add r11, r9, r10  // add r9 and r10 and store

  cmp r11, #26  // if r11 > 26
  bgt decrease  // branch to decrease

  add r11, r11, #96 // convert decimal to ascii
  strb r11, [r7, r5] // store new value into output offset by counter

  add r4, r4, #1 // increment counter
  add r5, r5, #1 // increment counter

  b loop // loop

decode:
  ldrb r9, [r6, r5] // load value in input offset by counter

  cmp r9, #0 // if r9 == NULL
  beq done   // branch to done

  cmp r9, #32 // if r9 == space
  beq spaceD  // branch to spaceD

  ldrb r10, [r8, r4] // load value in key offset by counter

  cmp r10, #0 // if r10 == NULL
  beq resetD  // reset keystring

  cmp r10, #32 // if r10 == space
  beq zeroD   // decode as zero

  sub r9, r9, #96   // convert r9 into decimal
  sub r10, r10, #96 // convert r10 into decimal
  sub r11, r9, r10  // subtract and store

  cmp r11, #0       // if r11 <= 0
  ble increase     // branch to increase decoded

  add r11, r11, #96 // convert r11 into ascii
  strb r11, [r7, r5] // store new value into output offset by counter

  add r4, r4, #1 // increment counter
  add r5, r5, #1 // increment counter

  b decode

// Puts space into array
spaceE:
  mov r11, #32
  strb r11, [r7, r5]
  add r4, r4, #1 // increment counter
  add r5, r5, #1 // increment counter
  b loop

// Resets key
resetE:
	mov r4, #0
	b loop

// When key is space, store letter into output
zeroE:
  strb r9, [r7, r5]
  add r4, r4, #1 // increment counter
  add r5, r5, #1 // increment counter
  b loop

// If the value is over 26, decrease
decrease:
  sub r11, r11, #26	    // Find remainder
  add r11, r11, #96     // Convert to ascii
  strb r11, [r7, r5]    // store new value into output offset by counter
  add r4, r4, #1        // increment counter
  add r5, r5, #1        // increment counter
  b loop

// Puts space into array
spaceD:
  mov r11, #32
  strb r11, [r7, r5]
  add r4, r4, #1 // increment counter
  add r5, r5, #1 // increment counter
  b decode

// Resets key
resetD:
	mov r4, #0
	b decode

// When key is space, store letter into output
zeroD:
  strb r9, [r7, r5]
  add r4, r4, #1 // increment counter
  add r5, r5, #1 // increment counter
  b decode

// If the value is 0 or below, increase
increase:
  add r11, r11, #26   // The remainder as the new value
  add r11, r11, #96
  strb r11, [r7, r5]
  add r4, r4, #1 // increment counter
  add r5, r5, #1 // increment counter
  b decode

// done
done:
  strb r9, [r7, r5]  // Stores the null character at the end of the array
  pop {r4-r11, lr}
  bx lr
