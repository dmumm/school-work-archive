

package cpsc2150.labs.lab2;

import java.util.Scanner;


/**
 * Created by kplis on 1/23/2018.
 * Modified by dmumm on 2/9/2018
 */
public class MortgageApp {

    public static void main(String [] args)
    {
        Scanner sc = new Scanner(System.in);
        String name = null;
        double debt = -1;
        double income = -1;
        int creditScore = -1;
        double downPayment = -1;
        double houseCost = -1;
        int years = -1;


        while(name == null) {
            System.out.println("Name?");
            name = sc.nextLine();
            if(name == null){
                System.out.println("Error: Please enter a name");
                System.out.println();
            }
        }

        while(!(income >= 0)) {
            System.out.println("Income?");
            income = sc.nextDouble();
            if(!(income >= 0)){
                System.out.println("Error: Please enter a positive income");
                System.out.println();
            }
        }

        while(!(creditScore >= 0 && creditScore <= 850)) {
            System.out.println("Credit Score?");
            creditScore = sc.nextInt();
            if(!(creditScore >= 0 && creditScore <= 850)){
                System.out.println("Error: Please enter a credit score between 0 and 850");
                System.out.println();
            }
        }


        while(!(debt >= 0)) {
            System.out.println("Debt?");
            debt = sc.nextDouble();
            if(!(debt >= 0)){
                System.out.println("Error: Please enter a positive debt");
                System.out.println();
            }
        }

        Customer cust = new Customer(debt, income, creditScore, name);

        while(!(houseCost >= 0)) {
            System.out.println("House cost?");
            houseCost = sc.nextDouble();
            if(!(houseCost >= 0)){
                System.out.println("Error: Please enter a positive house cost");
                System.out.println();
            }
        }

        while(!(downPayment >= 0 && downPayment <= houseCost)) {
            System.out.println("Down payment?");
            downPayment = sc.nextDouble();
            if(!(downPayment >= 0 && downPayment <= houseCost)){
                System.out.println("Error: Please enter a positive down payment lesser or equal to the house cost");
                System.out.println();
            }
        }

        while(!(years == 15 || years == 20 || years == 25 || years == 30)) {
            System.out.println("Years?");
            years = sc.nextInt();
            if(!(years != 15 || years != 20 || years != 25 || years != 30)){
                System.out.println("Error: Please enter a year amount of 15, 20, 25, or 30");
                System.out.println();
            }
        }

        cust.applyForLoan(downPayment, houseCost, years);
        System.out.println(cust.toString());


    }
}
