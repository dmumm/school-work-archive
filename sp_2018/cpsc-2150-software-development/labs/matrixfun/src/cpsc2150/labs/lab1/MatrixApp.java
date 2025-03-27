// Dylan Mumm, 2151-004
// Lab 1
// January 26th

package cpsc2150.labs.lab1;

import java.util.*;


public class MatrixApp {

    public static void main ( String [] args)
    {
        int r = 0;
        int c = 0;


        // reads in and verifies user input
        while(r < 1 || r > 10) {
            System.out.println("How many rows should your matrix have?");
            Scanner sc = new Scanner(System.in);
            r = sc.nextInt();
            if(r < 1 || r > 10){
                System.out.println("Error: Please enter a number 1-10");
                System.out.println();
            }
        }

        // reads in and verifies user input

        while(c < 1 || c > 10) {
            System.out.println("How many columns should your matrix have?");
            Scanner sc = new Scanner(System.in);
            c = sc.nextInt();
            if(c < 1 || c > 10){
                System.out.println("Error: Please enter a number 1-10");
                System.out.println();
            }
        }

        // declaring double array
        int[][] m = new int[c][r];

        // 2d loop to read in cells
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                System.out.println("What number should go in Row: " + i + " Col: " + j);
                Scanner sc = new Scanner(System.in);
                m[j][i] = sc.nextInt();
            }
        }

        // printing matrix
        System.out.println("Your matrix is:");

        for(int i = 0; i < r; i++) {
            System.out.print("|");
            for(int j = 0; j < c; j++) {
                System.out.print(m[j][i] + "|");
            }
            System.out.println();
        }
        System.out.println();

        // declaring new transposed matrix double array and initializing it to function
        System.out.println("The transposed matrix is:");
        int t[][] = transposedMatrix(m, r, c);

        // printing matrix
        for(int i = 0; i < c; i++) {
            System.out.print("|");
            for(int j = 0; j < r; j++) {
                System.out.print(t[j][i] + "|");
            }
            System.out.println();
        }
        System.out.println();


        System.out.println("The product sum is:");
        System.out.println(productSum(m, r, c));
        System.out.println();


        System.out.println("The product average is:");
        System.out.println(average(m, r, c));
        System.out.println();


        System.out.println("The sums of each Row are:");
        System.out.print("|");
        int rs[] = rowSums(m, r, c);
        for(int i = 0; i < r; i++) {
            System.out.print(rs[i] + "|");
        }
        System.out.println();
        System.out.println();



        System.out.println("The sums of each Column are:");
        System.out.print("|");
        int cs[] = colSums(m, r, c);
        for(int i = 0; i < c; i++) {
            System.out.print(cs[i] + "|");
        }
        System.out.println();
        System.out.println();






    }

    private static int[][] transposedMatrix(int m[][], int r, int c)
    {
        // reads in transposed matrix
        int[][] t = new int[r][c];
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                t[i][j] = m[j][i];
            }
        }
        return t;
    }

    private static int productSum(int m[][], int r, int c )
    {
        // counts sum of each row before multiplying it to previous row's sum (if applicable)
        int rSum;
        int product = 1;
        for(int i = 0; i < r; i++) {
            rSum = 0;
            for(int j = 0; j < c; j++) {
                rSum += m[j][i];
            }
            product *= rSum;
        }
        return product;
    }

    private static double average(int m[][], int r, int c )
    {
        // adds up all values before dividing it by total cell count
        int sum = 0;
        double divisor = r * c;
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                sum += m[j][i];
            }
        }
        return (sum / divisor);
    }

    private static int[] rowSums(int m[][], int r, int c)
    {
        // adds up sum of each row and deposits it in array
        int[] s = new int[r];
        for(int i = 0; i < r; i++) {
            s[i] = 0;
            for(int j = 0; j < c; j++) {
                s[i] += m[j][i];
            }
        }
        return s;
    }

    private static int[] colSums(int m[][], int r, int c)
    {
        // adds up sum of each row and deposits it in column
        int[] s = new int[c];
        for(int i = 0; i < c; i++) {
            s[i] = 0;
            for(int j = 0; j < r; j++) {
                s[i] += m[i][j];
            }
        }
        return s;
    }
}



