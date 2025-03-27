package cpsc2150.labs.lab2;

/**
 * Created by kplis on 1/23/2018.
 * Modified by dmumm on 2/9/2018
 */


/**
 * @invariant name not null
 * @invariant monthlyDebtPayments >= 0
 * @invariant income >= 0
 * @invariant 0 <= creditScore <= 850
 */
public class Customer {
    private String name;

    private double monthlyDebtPayments;
    private double income;
    private int creditScore;
    private Mortgage loan;

    /**
     * This constructor sets the monthly debt payments, income, credit score and name for a customer
     *
     * @param debt     a customer's monthly debt payments
     * @param inc      a customer's income
     * @param score    a customer's credit score
     * @param n        a customer's name
     *
     * @requires debt >= 0
     * @requires inc >= 0
     * @requires 0 <= score <= 850
     * @requires n not null
     *
     * @ensures  monthDebtPayment = debt
     * @ensures  income = inc
     * @ensures  creditScore = score
     * @ensures  name = n
     *
     */
    Customer( double debt, double inc, int score, String n)
    {

        /*
        Set the monthly debt payments, income, credit score and name
        Credit scores range from 0 - 850
         */

        monthlyDebtPayments = debt;
        income = inc;
        creditScore = score;
        name = n;


    }

    /**
     * Given parameter values, function determines whether or not a loan application is approved
     *
     * @param  downPayment      a potential mortgage's down payment
     * @param  houseCost        cost of house potentially being purchased on a mortage
     * @param  years            duration of potential mortgage
     * @return true or false    (given parameters)
     *
     * @requires   0 <= downPayment >= houseCost and houseCost > 0 and years > 0
     * @ensures    true if (applicable for loan)
     */
    public boolean applyForLoan(double downPayment, double houseCost, int years)
    {
        //Take the parameters and apply for a loan. Save the loan details as the customers current loan
        // Return whether or not the loan was approved

        Customer currentCustomer = new Customer(monthlyDebtPayments, income, creditScore, name);
        loan = new Mortgage(houseCost, downPayment, years, currentCustomer);
        return loan.loanApproved();

    }

    /**
     * Function returns the interest rate on the current loan
     *
     * @return  interest rate on the current loan
     * @ensures getRate() = interest rate
     *
     */
    public double getRate()
    {
        //return the interest rate on the current loan
        return loan.getRate();
    }

    /**
     * Function returns the monthly payment on the current loan
     *
     * @return  monthly payment on the current loan
     * @ensures getMonthlyPay() = interest rate
     *
     */
    public double getMonthlyPay()
    {
        //return the monthly payment on the current loan
        return income / 12;
    }

    /**
     * Function returns the customers monthly debt payments
     *
     * @return  the customers monthly debt payments
     * @ensures getMonthlyDebtPayments() = the customers monthly debt payments
     *
     */
    public double getMonthlyDebtPayments()
    {
        //return the customers monthly debt payments
        return monthlyDebtPayments;
    }

    /**
     * Function returns the customers income
     *
     * @return  the customers income
     * @ensures getIncome() = the customers income
     *
     */
    public double getIncome()
    {
        //return the customers income
        return income;
    }

    /**
     * Function returns the customers credit score
     *
     * @return  the customers credit score
     * @ensures getCreditScore() = the customers credit score
     *
     */
    public int getCreditScore()
    {
        //return the customers credit score
        return creditScore;
    }


    /**
     * Function returns the customers information as a string
     *
     * @return  the customers information
     * @ensures toString() = the customers information as a string
     *
     */
    @Override
    public String toString()
    {
        //this function is provided
        //DO you need contracts for this?
        String str = "";
        str += "Name: " + name + "\n";
        str += "Income: $" + income + "\n";
        str += "Credit Score: " + creditScore + "\n";
        str += "Monthly Debt: $" + monthlyDebtPayments + "\n";
        str += "Mortgage info: \n";
        if(loan != null)
            str += loan.toString();

        return str;

    }
}
