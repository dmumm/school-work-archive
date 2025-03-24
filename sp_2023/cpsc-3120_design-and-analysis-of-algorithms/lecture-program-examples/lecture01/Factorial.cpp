/**
 * Compute the factorial of a given integer n.
 * 
 * Author: Guoxi Liu
 * Clemson University
 * Date: 01/23/2023
*/

#include <assert.h>
#include <iostream>

/**
 * Compute the factorial using recursion.
*/
int compute_factorial_recursion(int n)
{
    assert(n > 0);
    if (n == 1) return n;
    return n * compute_factorial_recursion(n - 1);
}


/**
 * Compute the factorial using for loop.
*/
int compute_factorial_for_loop(int n)
{
    assert(n > 0);
    int res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

/**
 * Main function.
*/
int main()
{
    int version = 1, num = 0;
    std::cout << "Select the version you want to use to compute factorial: " << std::endl;
    std::cout << "1. Recursion " << std::endl; 
    std::cout << "2. For loop " << std::endl;
    std::cout << "Please input your selection and press Enter: ";

    std::cin >> version;
    assert(version == 1 || version == 2);

    std::cout << "Please input the number n: ";
    if (version == 1) {
        while (std::cin >> num) {
            std::cout << compute_factorial_recursion(num) << std::endl;
            std::cout << "Please input the number n: ";
        }
    }
    else {
        while (std::cin >> num) {
            std::cout << compute_factorial_for_loop(num) << std::endl;
            std::cout << "Please input the number n: ";
        }
    }

    // Bonus question: what is the largest number n for this program to get the correct factorial?

    return 0;
}
