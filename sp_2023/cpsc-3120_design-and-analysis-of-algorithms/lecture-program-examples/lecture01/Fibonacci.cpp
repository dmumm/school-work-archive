/**
 * Compute the n-th Fibonacci number (n > 0).
 * Fibonacci sequence is given as: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
 * 
 * Author: Guoxi Liu
 * Clemson University
 * Date: 01/23/2023
*/

#include <assert.h>
#include <iostream>

/**
 * Compute the fibonacci using recursion.
*/
int compute_fibonacci_recursion(int n)
{
    assert(n > 0);
    if (n <= 2) return 1;
    return compute_fibonacci_recursion(n-1) + compute_fibonacci_recursion(n-2);
}


/**
 * Compute the fibonacci using for loop.
*/
int compute_fibonacci_for_loop(int n)
{
    assert(n > 0);
    int a1 = 1, a2 = 1, res = 1;
    for (int i = 2; i < n; i++) {
        res = a1 + a2;
        a1 = a2;
        a2 = res;
    }
    return res;
}

/**
 * Main function.
*/
int main()
{
    int version = 1, num = 0;
    std::cout << "Select the version you want to use to compute fibonacci: " << std::endl;
    std::cout << "1. Recursion " << std::endl; 
    std::cout << "2. For loop " << std::endl;
    std::cout << "Please input your selection and press Enter: ";

    std::cin >> version;
    assert(version == 1 || version == 2);

    std::cout << "Please input the number n: ";
    if (version == 1) {
        while (std::cin >> num) {
            std::cout << compute_fibonacci_recursion(num) << std::endl;
            std::cout << "Please input the number n: ";
        }
    }
    else {
        while (std::cin >> num) {
            std::cout << compute_fibonacci_for_loop(num) << std::endl;
            std::cout << "Please input the number n: ";
        }
    }

    // Bonus question: what is the largest n-th fibonacci number can this program compute?

    return 0;
}
