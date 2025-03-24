/**
 * A stack data structure support multipop operation.
 * 
 * Author: Guoxi Liu
 * Clemson University
 * Date: 01/23/2023
*/

#include <iostream>
#include <vector>

/**
 * Use STL vector to implement stack structure.
*/
class Stack
{
private:
    std::vector<int> st;

public:
    // add an element to the top of the stack
    void push(int num) {
        st.push_back(num);
    }

    // remove the top element from the stack
    void pop() {
        if (!st.empty()) st.pop_back();
    }

    // remove k elements from the top of the stack 
    void multipop(int k) {
        while (!st.empty() && k > 0) {
            st.pop_back();
            k--;
        }
    }

    void print() {
        std::cout << "stack size " << st.size() << ", [ ";
        for (size_t i = 0; i < st.size(); i++) {
            std::cout << st[i] << " ";
        }
        std::cout << "]" << std::endl;
    }
};

/**
 * Main Entry of the program. 
*/
int main()
{
    Stack stack;
    stack.push(4);
    stack.push(3);
    stack.push(2);
    stack.print();
    stack.pop();
    stack.print();
    stack.push(5);
    stack.push(6);
    stack.print();
    stack.multipop(3);
    stack.print();

    return 0;
}