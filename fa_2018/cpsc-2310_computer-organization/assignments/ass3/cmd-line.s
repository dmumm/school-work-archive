
        .global main
main:
        push {r4-r5, lr}
        mov r4, r0                // save argc
        mov r5, r1                // save argv
        ldr r0, =fmt1             // put addr of fmt1 in r0 for printing
        mov r1, r4                // put argc in r1 for printint
        bl printf

loop:                             // compare this loop with the assembly
        cmp  r4, #0               // code generated for the C loop
        ble  done                 //   
                                  //   while(argc != 0) 
        ldr  r0, =fmt2            //   {
        ldr  r1, [r5]             //      printf("%s\n",*argv);
        bl printf                 //      argv++;
                                  //      argc--;
        add  r5,r5,#4             //   }
        sub r4, r4, #1 

        b loop

done:
        mov  r0, #0
        pop {r4-r5, pc}

        .section ".rodata"
fmt1:    .asciz "\nnumber of strings on command line is %d\n"
fmt2:    .asciz "%s\n"
