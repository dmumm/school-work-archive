/*

Dylan Mumm
CPSC 2310 - 002
Assignment 2
October 23rd, 2018

Description: Prints steps for 8-bit by 8-bit multiplication of inputted
             variables

*/

import java.util.*;

public class multiply {

    public static void main(String args[]) {

        /* takes multiplier and multiplicand from stdin, ensures in range */
        /* if not, exits program */

        Scanner in = new Scanner(System.in);
        Variables var = new Variables();

        System.out.print("multiplicand: ");
        var.in1 = in.nextInt();

        if(var.in1 > 255 || var.in1 < 0) {
            System.out.println("Error: Integer not in range 0 to 255");
            System.exit(0);
        }


        System.out.print("multiplier: ");
        var.in2 = in.nextInt();

        if(var.in2 > 255 || var.in2 < 0) {
            System.out.println("Error: Integer not in range 0 to 255");
            System.exit(0);
        }


        System.out.println();

        /* echos initialized simulated registers in decimal and binary */

        var.c = 0; var.acc = 0;
        System.out.println("c and acc set to 0");

        var.mq = var.in2;
        System.out.println("mq set to multiplier    =  " + var.in2 +
                " decimal and " + printBinary(binary(var.in2)) + " binary");

        var.mdr = var.in1;
        System.out.println("mdr set to multiplicand =  " + var.in1 +
                " decimal and " + printBinary(binary(var.in1)) + " binary");
        printLine();

        /* loops through respective multiplication steps */
        for(int i = 0; i < 8; i++){

            step(i, var);

        }

        /* shows binary and decimal multiplication problem side by side */
        System.out.println("check:                 binary   decimal");
        System.out.print("                     " +
                printBinary(binary(var.in1)));
        System.out.format("%10d%n", var.in1);
        System.out.print("           x         " +
                printBinary(binary(var.in2)));
        System.out.format("  x%7d%n", var.in2);
        System.out.println("             ----------------    ------");

        String answer = printBinary(binary(var.acc)) +
                printBinary(binary(var.mq));

        System.out.print("             " + answer);
        System.out.format("%10d%n",  Integer.parseInt(answer, 2));


    }

    /* prints line of hyphens */
    private static void printLine() {
        System.out.println(
                "---------------------------------------------------");
    }

    /* illustrates respective multiplication step */
    private static void step(int i, Variables var){

        // First line of each step of process
        System.out.print("step " + (i + 1) + ":   ");
        System.out.println(var.c + " " + printBinary(binary(var.acc)) + " " +
                printBinary(binary(var.mq)));

        /* Determines whether addition should be done based on lsb */
        if(binary(var.mq)[7]) {
            System.out.println("        +   " + printBinary(binary(var.mdr)) +
                    "        ^ " +  "add based on lsb=1");
            System.out.println("          ----------");
            var.acc = var.acc + var.in1;

            if(var.acc > 255)
                var.c = 1;
        }
        else {
            System.out.println("        +   00000000        ^ " +
                    "no add based on lsb=0");
            System.out.println("          ----------");
        }

        /* Prints sum and right shift */
        System.out.println("          " + var.c + " " +
                printBinary(binary(var.acc)) + " " +
                printBinary(binary(var.mq)));
        System.out.println("       >>                     shift right");

        var.mq = var.mq >> 1;

        if(binary(var.acc)[7]) {
            var.mq += 128;
        }

        var.acc = var.acc >> 1;
        var.c = 0;

        System.out.println("          " + var.c + " " +
                printBinary(binary(var.acc)) + " " +
                printBinary(binary(var.mq)));

        printLine();

    }

    /* converts integer to 8 value boolean array representing binary */
    private static boolean[] binary(int number) {
        final boolean[] set = new boolean[8];
        for (int i = 0; i < 8; i++) {
            set[7 - i] = (1 << i & number) != 0;
        }
        return set;
    }

    /* converts 8 value boolean array to binary string */
    private static String printBinary(boolean[] arr) {
        String result = "";
        for(int i = 0; i < 8; i++) {
            if(arr[i])
                result += '1';
            else
                result += '0';
        }
        return result;
    }

}

/* stores variables */
class Variables {

    public int in1 = 0, in2 = 0, c = 0, acc = 0, mq = 0, mdr = 0;

}
