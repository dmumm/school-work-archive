/**
 * Simulate queue data structure with two stacks.
 * This version makes enqueue() operation expensive. 
 * 
 * Author: Guoxi Liu
 * Clemson University
 * Date: 01/26/2023
*/

#include <cassert>
#include <iostream>
#include <stack>


class Queue
{
private:
    std::stack<int> q_stack, helper_stack;
public:
    Queue(/* args */);
    ~Queue();
    void enqueue(int e);
    int dequeue();
    void print();
};

Queue::Queue() {}

Queue::~Queue() {}

void Queue::enqueue(int e) 
{
    // Move the elements in the first stack to the second one
    while (!q_stack.empty()) {
        helper_stack.push(q_stack.top());
        q_stack.pop();
    }

    // Add the current element
    q_stack.push(e);

    // Move the elements back to the first stack
    while (!helper_stack.empty()) {
        q_stack.push(helper_stack.top());
        helper_stack.pop();
    }
}

int Queue::dequeue()
{
    assert(!q_stack.empty());
    int res = q_stack.top();
    q_stack.pop();
    return res;
}

void Queue::print()
{
    std::stack<int> tmp = q_stack;
    std::cout << "queue size " << tmp.size() << ", [ ";
    while (!tmp.empty()) {
        std::cout << tmp.top() << " ";
        tmp.pop();
    }
    std::cout << "]" << std::endl;
}


/**
 * Main entry. 
*/
int main()
{
    Queue q;
    q.enqueue(1); q.enqueue(3); q.enqueue(5);
    q.print();
    q.dequeue();
    std::cout << "calling dequeue()" << std::endl;
    q.print();
    q.dequeue();
    std::cout << "calling dequeue()" << std::endl;
    q.print();
    q.enqueue(8); q.enqueue(10);
    q.print();
    q.dequeue();
    std::cout << "calling dequeue()" << std::endl;
    q.print();
}

