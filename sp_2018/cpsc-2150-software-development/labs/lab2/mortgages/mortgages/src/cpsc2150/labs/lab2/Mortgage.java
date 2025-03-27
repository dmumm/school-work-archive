package cpsc2150.labs.lab2;


/**
 * Created by kplis on 1/23/2018.
 * Modified by dmumm on 2/9/2018
 */

/**
 * @invariant houseCost >= 0
 * @invariant 0 <= downPayment <= houseCost
 * @invariant 0 <= percentDown <=  1
 * @invariant percentDown = downPayment / houseCost
 * @invariant years > 0
 * @invariant .03 <= interestRate <= .14
 * @invariant payment >= 0
 */
public class Mortgage {



    private double houseCost;
    private double downPayment;
    private double percentDown;
    private int years;
    private double interestRate;
    private double payment;
    private Customer customer;


    /**
     * This constructor sets house cost, down payment, years, and customer for a mortgage
     * and calculates the percent down, interest rate, and payment
     *
     * @param cost     the cost of a house being mortgaged
     * @param dp       the downpayment for a house being mortgaged
     * @param y        the duration of a mortgage
     * @param cust     the customer receiving a morgage
     *
     * @requires cost >= 0
     * @requires 0 <= dp <= cost
     * @requires y > 0
     * @requires cust not null
     *
     * @ensures  houseCost = cost
     * @ensures  downPayment = dp
     * @ensures  years = y
     * @ensures  customer = cust
     *
     */
    Mortgage(double cost, double dp, int y, Customer cust)
    {


        /*
        Sets the house cost, down payment, years and customer. Calculates the percent down, rate, and payment
         */
        houseCost = cost;
        downPayment = dp;
        years = y;
        customer = cust;

        percentDown = downPayment / houseCost;
        calcRate();
        calcPayment();
    }

    /**
     * This function calculates the interest rate to use
     * @returns the interest rate that will be used
     *
     * @ensures .03 <= interestRate <= .14
     * @ensures interestRate = .025 + year penalty + credit score penalty + down payment penalty
     *
     */
    private void calcRate()
    {
        /*
        Calculates the interest rate to use.
        The rate starts at the base rate of 2.5%
        If the loan is for 30 years, add the normal addition of 1%
        If the loan is for for less than 30 years, add the good addition of .5%
        The loan must be for 15, 20, 25 or 30 years

        Add the rate for the credit score based on the following table
        Credit rating | Credit score | add to rate
        Bad           | 0 - 499      | 10%
        Fair          | 500 - 599    | 5%
        Good          | 600 - 699    | 1%
        Great         | 700 - 749    | .5%
        Excellent     | 750 - 850    | 0%

        If the down payment is less than 20% of the price of the house, add .5%
         */

        final double base = .025;
        final double yearPenalty;
        final double creditPenalty;
        final double downPaymentPenalty;

        if(years < 30)
            yearPenalty = .005;
        else
            yearPenalty = .01;

        if(customer.getCreditScore() < 500)
            creditPenalty = .1;

        else if(customer.getCreditScore() < 600)
            creditPenalty = .05;

        else if(customer.getCreditScore() < 700)
            creditPenalty = .01;

        else if(customer.getCreditScore() < 750)
            creditPenalty = .005;

        else
            creditPenalty = 0;

        if(downPayment / houseCost < .2)
            downPaymentPenalty = .005;

        else
            downPaymentPenalty = 0;

        interestRate = base + yearPenalty + creditPenalty + downPaymentPenalty;

    }


    /**
     * Calculates the monthly payment
     * @returns payment
     *
     * @ensures payment = (interestRate * (houseCost - downPayment)) / ( 1 - (1 + interestRate)^(-numPayment))
     *
     */
    private void calcPayment()
    {
        /*
        Calculate the monthly payment
        terms:
        r - monthly rate - the interest rate divided by 12
        p - principal balance - the cost of the house minus the down payment
        n - number of payments - the total number of monthly payments

        monthly payment is (rp)/(1-(1+r)^-n)
         */

        final double  monthlyRate = interestRate / 12;
        final double  principalBalance = houseCost - downPayment;
        final double  numPayments = years * 12;


        payment = (monthlyRate * principalBalance) / (1 - Math.pow((1 + monthlyRate), 0 - numPayments));

    }


    /**
     * Returns whether or not the loan is approved
     * @returns True if loan approved, false if not
     *
     * @ensures Returns true iff
     *            (interestRate < .10 and (downPayment / houseCost) > .035 and  (monthlyDebtPayment / income) < .4)
     * @ensures Returns false if otherwise
     *
     */
    public boolean loanApproved()
    {
        /*
        If the intereset rate is too high (10% or higher) the loan is denied
        If the down payment is less than 3.5% of the price of the house then the loan is denied

        If the Debt to income ratio is above 40% the loan is denied
        The debt to income ratio is the total monthly debt payments (including the mortgage payment) / monthly income

        Otherwise the loan is approved
         */

        if(interestRate > .1)
            return false;

        if(downPayment / houseCost < 0.035)
            return false;

        if((customer.getMonthlyDebtPayments() + payment)/ (customer.getIncome() / 12) > .4)
            return false;

        return true;
    }

    /**
     * Function returns the monthly payment on the loan
     *
     * @return  payment
     * @ensures getPayment() = the monthly payment on the loan
     *
     */
    public double getPayment()
    {
        //return the monthly payment on the loan
        return payment;
    }

    /**
     * Function returns the interest rate on the loan
     *
     * @return  interestRate
     * @ensures getRate() = the interest rate on the loan
     *
     */
    public double getRate()
    {
        //return the interest rate on the loan
        return interestRate;
    }


    /**
     * Function returns the mortgage information as a string
     *
     * @return  the mortgage's information
     * @ensures toString() = the mortgage information as a string
     *
     */
    @Override
    public String toString()
    {
        //this function is provided
        //DO you need contracts for this?
        String str = "";
        if(loanApproved())
        {
            str += "Principal Amount: $" + (houseCost - downPayment) + "\n";
            str += "Interest Rate: " + (interestRate * 100) + "%\n";
            str += "Term: " + years + " years\n";
            str += "Monthly Payment: $" + payment + "\n";
        }
        else
        {
            str += "Loan was not approved";
        }
        return str;
    }

}
