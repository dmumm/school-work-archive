/**
 * Simulate queue data structure with two stacks.
 * This version makes dequeue() operation expensive. 
 * 
 * Author: Guoxi Liu
 * Clemson University
 * Date: 01/26/2023
*/

#include <cassert>
#include <iostream>
#include <stack>
#include <vector>


class Queue
{
private:
    std::stack<int> in_stack, out_stack;
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
    in_stack.push(e);
}

int Queue::dequeue()
{
    assert(!in_stack.empty() || !out_stack.empty());
    // Move elements to the second stack only when it is empty
    if (out_stack.empty()) {
        while (!in_stack.empty()) {
            out_stack.push(in_stack.top());
            in_stack.pop();
        }
    }

    int res = out_stack.top();
    out_stack.pop();
    return res;
}

void Queue::print()
{
    std::stack<int> tmp = out_stack;
    std::cout << "queue size " << in_stack.size() + out_stack.size() << ", [ ";
    while (!tmp.empty()) {
        std::cout << tmp.top() << " ";
        tmp.pop();
    }

    // A little bit tricky to deal with the in_stack
    tmp = in_stack;
    std::vector<int> v{};
    while (!tmp.empty()) {
        v.push_back(tmp.top());
        tmp.pop();
    }
    for (int i = v.size() - 1; i >= 0; i--) {
        std::cout << v[i] << " ";
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
    return 0;
}

