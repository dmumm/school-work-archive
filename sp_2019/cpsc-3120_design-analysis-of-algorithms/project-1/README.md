# Binary trees and Splay trees

In this assignment, we will implement two distinct data structures. One is a simple Binary Search Tree and the second one is a Splay tree.

All the information you need regarding these two data structures can be found in your textbook (Algorithm Analysis and Design, Chapter 4).



### Step 1 - Setup

The `main.cpp` file provided with the assignment will be used at the end for testing the performances of the data structures. For the initial debugging phase I suggest to create a simple main file with the minimal instructions you will need for verifying that the implemented structures are working correctly.

###### Suggestion
keep your code hierarchy simple. Ideally, you should always be able to compile everything with something like `g++ main.cpp -o main`

### Step 2 - Implementing the Binary tree

Use the draft provided in `BinaryTree.h` for implementing a binary search tree. The comments provided in the file should guide you through all the required variables/functions you will need to define.


###### Suggestion
Simplify your code by creating simpler recursive functions. For example, instead of creating a function `insert(int val)` that accepts only the key, define a function `insert(int val, Node* node)` that also accepts the node from which starting the insertion. This way you can implement only one function instead of two by using the recursive call directly on `insert`.

###### Suggestion
The inorder visit can be a powerful debugging tool. Remember that in a Binary search tree as well as in the Splay tree an inorder visit should always return the keys stored in the tree in ascending order. If this is not happening, it means that something is wrong with your insert/splay implementations.

###### Suggestion
Every time you perform a search and an insert in a Splay tree you need to return the last (non null) node touched. You can implement this in the Binary search tree as well. This way we will reuse this function for implementing the `insert` and `search` in the Splay tree.  



### Step 3 - Implementing the Splay tree

Use the draft provided in `SplayTree.h` for implementing a Splay tree. The comments provided in the file should guide you through all the required variables/functions you will need to define.

###### Suggestion
There are three types of rotations in the Splay tree (zig, zig zig, zig zag). Each of them can be performed on the left or on the right. I strongly encourage you to define six distinct functions for implementing each combination (zig_left, zig_right, zig_zig_left, zig_zig_right, etc.)

###### Suggestion
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

### Step 4 - Evaluation and Submission

Assuming that you have implemented everything and debugged your code now it is time to evaluate these two data structures. You can go back to the `main.cpp` file provided with the assignment and fill the missing lines identified by `TODO` (these should be only simple calls to your data structure functions).

###### Objectice
We want to evaluate the performances when we are executing a number of searches on both structures when the input varies. The `main.cpp` file implement this idea by creating a list of integers of various size (the maximum number of integers is controlled by the variable `tot`). These integers are randomly generated over an interval defined by the variables `min` and `max`. Every time we defined these three variables the program will

1. create a binary tree from the input
2. perform a search for each value in the input list
3. create a Splay tree from the input
4. perform a search for each value in the input list
5. save the timings for performing both searches into two distinct text files

###### Setup

You should be able to compile everything with `g++ main.cpp Timer.cpp -o main`

Play with the code and compare the timings you get when changing the parameters `tot`, `min`, `max`. What do you notice?

[Put your answer here removing this line]


###### Experiments

Here we want to visualize the results obtained by plotting timings over an increasing number of inputs. Every time you run `main.cpp` you will get two text files representing the trend for your timings when using an increasing number of input keys.

If you are familiar with Jupyter Notebooks you can simply follow the instructions in `plot_results.ipynb`. Otherwise, you can reimplement or visualize the results with any other software/library (R, Tableau, Excel, etc.)

1. [Run 1] run your program with `tot=10000000`, `min=0`, `max=20`  
2. [Run 2] run your program with `tot=10000000`, `min=0`, `max=100000`  
3. Compare all the results together in a single graph.
4. Compare the performances of the binary tree from Run 1 and Run 2 in a new graph.
5. Compare the performances of the Splay tree from Run 1 and Run 2 in a new graph.

What can we conclude from the graphs created in 3,4 and 5?

[Put your answer here removing this line. Also upload the graph you have produced describing how you have created them.]
