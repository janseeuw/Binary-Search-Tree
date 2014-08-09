#Binary Search Tree

A binary search tree is a binary tree that has a key associated with each of its internal nodes, with the additional property that the key in any node is larger than (or equal to) the keys in all nodes in that node's left subtree and smaller than (or equal to) the keys in all nodes in that node's right subtree.

The underlying data structure allows efficiënt algorithms for the _search_, _insert_, _select_ and _sort_ symbol-table operations.


We have a _Tree_ class with contains a pointer to a _Node_ (the root of the tree). Each _Node_ has two _Tree_ variables _left_ and _right_ who represent the left and right subtree. We will start by implementing searching and inserting nodes in the tree. At the end of the post you will see how to delete a node.

#Searching for a given key
Given this structure, a recursive algorithm to search for a key is easy. If the key is equal to the key at the root, we have a search hit. Otherwise, we search (recursively) in the appropriate subtree.


#Searching for the minimum (and maximum)
This can be implemented recursive and nonrecursive.

To find the _minimum_ in a binary search tree we start at the root. If the left subtree is empty, we have the minimum. If not, we search in the left subtree for the minimum. This is equal to following left pointers until we hit a node without left subtree.


#Inserting a new node
We have to insert the new node, where it will be found when we search for it. So we search for the key and when we hit the nullpointer (because the node isn't there yet), we insert the node.


#Deleting a node
This is the most challenging function to implement. We need to change the pointer in the structure that points to the node being removed. There are at least three methods to solve this problem.

1. We could add a third link in each node pointing to its parent
2. We could use a pointer to the pointer to the node as the handle.
3. We could use _lazy deletion_ and just mark them as deleted.

We will use the second solution since this won't waste additional memory to keep a third pointer in each node.

The node has to be found first before we can delete it. After that there are three posibilities:

* No subtrees. The node can be deleted without consequences.
* One subtree. The node's parent (if exists) will become the parent of the subtree. It will be a left subtree if the parent was a left child and vice versa.
* Twoo subtrees. This is more complex, because there becomes only one parent pointer vacant, while there are two subtrees without parent tree. Because the right subtree of the node is not empty, it contains the successor of the node. We will make that node parent of the new tree.
