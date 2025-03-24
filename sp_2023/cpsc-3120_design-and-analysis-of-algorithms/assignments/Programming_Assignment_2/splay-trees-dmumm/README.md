# Binary trees and Splay trees

In this assignment, we will implement two distinct data structures. One is a simple Binary Search Tree and the second one is a Splay tree.

All the information you need regarding these two data structures can be found in your textbook (Algorithm Analysis and Design, Chapter 4).


# Step 1 - Setup

The `main.cpp` file provided with the assignment will be used at the end for testing the performances of the data structures. For the initial debugging phase I suggest you create a simple `main.cpp` file with the minimal instructions you need for verifying that the implemented structures are working correctly.

### Suggestion
keep your code hierarchy simple. Ideally, you should always be able to compile everything with something like `g++ main.cpp -o main`

# Step 2 - Implementing the Binary tree

Use the draft provided in `BinaryTree.h` for implementing a binary search tree. The comments provided in the file should guide you through the definition of all the required variables/functions.

Once you have implemented all functions, complete the `main.cpp` file provided with the assignment by filling the missing lines identified by `TODO` (these should be only simple calls to your data structure functions).
Then, run the program and copy the timings obtained here

Insert - `Time for building 1.7e-05`

Search - `Time for searches 8e-06`


### Important!!!
You are asked to implement an inorder visit of the tree. Implement this function so that it will print (in output) ONLY the keys of the nodes visited. This long string will be used by the autograder later.

The string should contain only the list of keys visited separated by a simple space.


### Suggestion
The inorder visit can be a powerful debugging tool. Remember that in a Binary search tree, as well as in the Splay tree, an inorder visit should always return the keys stored in the tree in ascending order. If this is not happening, it means that something is wrong with your insert/splay implementations.


### Suggestion
Every time you perform a `search` and an `insert` in a Splay tree you need to return the last (non null) node touched. You can implement this in the Binary search tree as well. This way we will reuse the same functions for implementing the `insert` and `search` in the Splay tree.  


# Step 3 - Implementing the Splay tree

Use the draft provided in `SplayTree.h` for implementing a Splay tree. The comments provided in the file should guide you through all the required variables/functions you will need to define.

#### Suggestion
There are three types of rotations in the Splay tree (zig, zig zig, zig zag). Each of them can be performed on the left or on the right. I strongly encourage you to define six distinct functions for implementing each combination (zig_left, zig_right, zig_zig_left, zig_zig_right, etc.)

### Suggestion
If you have implemented the `insert` and `search` functions in the Binary tree as suggested, you should be able to reuse your code. Ideally, your functions here should be something like

```c++
  bool insert(int key){
    Node* last = BinaryTree::insert(key, getRoot());
    splay(last)
  }
```

```c++
  bool search(int key){
    Node* last = BinaryTree::search(key, getRoot());
    splay(last)
  }
```

# Step 4 - Submission

Assuming that you have implemented everything and debugged your code you can go back to the `main.cpp` and modify the file this time using the Splay tree instead of the Binary tree constructors.
Then, run the program and copy the timings obtained here

Insert - `Time for building 0.000168`

Search - `Time for searches 1.2e-05`


Now, 
- remove the calls to `cout` from `main.cpp` 
- make a final call to the inorder visit function
- submit your code on Gradescope. Your submission should contain only the source files and the `README.md` file

### Notes for a correct autograding 
Be sure that your submitted program prints in output only the list of nodes visited by the inorder visit function.
