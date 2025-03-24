Binary Trees
 
* Set of nodes linked with parent-child relationship
* Each tree has special parent node R, the root, with no parent nodes
* Parents have at most children
* Left child of node is strictly less than the parent node, and right is greater
* Balance
	- Left and right subtree height differs by at most 1
	- Balanced tree has height of log(n)
	- Most operations depend on height
* Proper [full]
	- Every node other leaves has two children
* Complete
	- Tree in which every level (except possibly last???) is completely filled
	- All nodes are as far left as possible 

Operations {
	
	void Insert(e) {	// O(logn) if balanced, otherwise O(n)

		crawlerNode = this.getRoot();
		crawlerParent = NULL;
		while(crawlerNode != NULL) {
			crawlerParent = crawlerNode;
			if(crawlerNode.key > e) {
				crawlerNode = crawlerNode.left;
			} else {
				crawlerNode = crawlerNode.right;
			}
		}
		newNode = new Node(e);
		newNode.parent = crawlerParent;
		if(crawlerParent.key > newNode.key) {
			crawlerParent = crawlerNode
		} else {
			crawlerParent.right = crawlerNode
		}
	}

	void Remote(e)		// O(logn) if balanced, otherwise o(n)
	bool Search(e) {	// O(logn) if balanced, otherwise o(n)

		crawlerNode = this.getRoot()

		while(crawlerNode.key != e) {

			if(crawlerNode == NULL) { break; }

			if(crawlerNode.key > e) {
				crawlerNode = crawlerNode.left;
			} else {
				crawlerNode = crawlerNode.right;
			}
		}
		return (node != NULL);
	}


	Node* getRoot()

}

Iterate {

	// In binary search tree, prints in order ascending (if left then right)
	void print_inorder(Node* crawlerNode) {
		print_inorder(crawlerNode->left);
		print(crawlerNode);
		print_inorder(crawlerNode->right);
	}

	// In binary search tree, starts from parent, goes to bottom right, then up, and bottom right (breadth based search)
	void print_preorder(Node* crawlerNode) {
		print(crawlerNode);
		print_preorder(crawlerNode->left);
		print_preorder(crawlerNode->right);
	}

	// In binary search tree, depth first left to right
	void print_postorder(Node* crawlerNode) {
		print_postorder(crawlerNode->left);
		print_postorder(crawlerNode->right);
		print(crawlerNode);
	}

}

AVL Trees

* Most literal way to ensure balance in all operations
	- Utilizes rotations to ensure height of left and right differ by no more than 1

Balanced(node) {
	if(node.left.get)
}