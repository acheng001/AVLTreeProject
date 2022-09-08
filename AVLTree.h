#include <iostream>
#include <vector>
using namespace std;
// AVL Node Class
// AVL IS A SELF BALANCING BINARY SEARCH TREE
// A map is a container that maps a key to a value allowing the value to be found
// By accessing the key
// INSERT AND DELETE MUST USE ROTATIONS TO KEEP AVL TREE BALANCED
template <class K, class V>
class AVLTreeNode {
 public:
	// Should have attributes named:
	// parent - pointer to parent
	AVLTreeNode<K,V>* parent;
	// left - pointer to left child
	AVLTreeNode<K,V>* left;
	// right - pointer to right child
	AVLTreeNode<K,V>* right;
	// key - node's key
	// KEY IS HOW NODES ARE ORDERED
	// Ex: Similar to arrays: keys = indices and value = array element
	K key;
	// value - node's value
	V value;
	// height - node's height
	// Height is individual for each node 
	unsigned int height;

	// Constructors ...
	AVLTreeNode(){
		parent = NULL;
		left = NULL;
		right = NULL;
		height = 0;
		
	}

};
/*
void inOrder(AVLTreeNode* r){
	if(r == NULL){
		return;
	}
	inOrder(r->left);
	cout<<r->value<<endl;
	inOrder(r->right);
}
*/
// AVL Tree class
template <class K, class V>
class AVLTree
{
private:
	// Tree attributes go here
	// Your tree MUST have a root node named root
	AVLTreeNode<K, V>* root;
	// Have a size variable which keeps tracks of the number of items in the tree
	unsigned currSize;
	// Helper Methods are private
	// DeleteNode Helper Method
	void deleteNode(AVLTreeNode<K,V>* &curr){
		// Base case
		if(curr== NULL){
			return;
		}
		deleteNode(curr->left);
		deleteNode(curr->right);
		delete curr; // Delete the current node then go back in the call stack
		return;
	}
	
	// Create node helper method
	AVLTreeNode<K,V>* create(K k, V v) const{
		// Creating a new node and setting its left and right to be NULL and a height of 0
		AVLTreeNode<K,V>* newNode = new AVLTreeNode<K,V>();
		newNode->value = v;
		newNode->key = k;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 0;
		return newNode;
	}

	// Have a helper method which gets the height of the tree
	int maxHeight(AVLTreeNode<K,V>* &testNode){
		if (testNode == NULL){
			return 0; // We return 0 instead of -1 because 0 incoportates the extra 1 height form our actual root
		}
		else{
			// We go recursively and get the left and right height
			int LeftHeight = maxHeight(testNode->left);
			int RightHeight = maxHeight(testNode->right);

			// If leftHeight is bigger than rightHeight return leftHeight + 1
			if(LeftHeight > RightHeight){
				return(LeftHeight + 1);
			}
			// Else return rightHeight + 1 (We return plus one since it is height of one from our root node to our input node)
			else{
				return(RightHeight + 1);
			}
		}
	}
	
	// Max function (Get the Max between a and b)
	int max(int a, int b){
		if(a > b){
			return a;
		}
		else{
			return b;
		}
		
	}

	// Balance the tree by comparing the left and right subtree
	// And see which ones bigger by subtracting them
	int getBalance(AVLTreeNode<K,V>* t){
		// Base case
		if(t == NULL){
			return 0;
		}
		// Subtracting the height of the left and right subtree
		return maxHeight(t->left) - maxHeight(t->right);
	}
	// Right Rotation
	AVLTreeNode<K,V>* rightRotate(AVLTreeNode<K,V>* &ancestor){
		// Point to the ancestor and child nodes
		AVLTreeNode<K,V>* child = ancestor->left;
		AVLTreeNode<K,V>* z = child->right;

		// Perform rotations
		// Moving child to become the parent of ancestor
		child->right = ancestor;
		// Since z was on the right side of child, it is bigger than child but smaller than ancestor
		// So we move it to be on the left side of ancestor
		ancestor->left = z;

		// Update the height of the trees
		// Ancestors height is compared with the left and right subtrees
		// Setting the ancestors height to be the max between the left and right subtree
		ancestor->height = max(maxHeight(ancestor->left),maxHeight(ancestor->right));
		// Child is now the root and we are getting the height of the left and right tree
		// Setting the childs height to be the max between the left and right subtree
		child->height = max(maxHeight(child->left),maxHeight(child->right));

		// Return the new root which is child
		return child;


	}

	// Left Rotation
	AVLTreeNode<K,V>* leftRotate(AVLTreeNode<K,V>* &ancestor){
		// Point to the ancestor and child nodes
		AVLTreeNode<K,V>* child = ancestor->right;
		AVLTreeNode<K,V>* z = child->left;
		

		// Perform rotations
		// Moving child left to become the parent of ancestor
		child->left = ancestor;
		// Since z was on the left side of the child, it is smaller than child but bigger than ancestor
		// So we move it to the right side of ancestor
		ancestor->right = z;

		// Update the height of the trees
		// Setting the ancestors height to be the max between the left and right subtree
		ancestor->height = max(maxHeight(ancestor->left),maxHeight(ancestor->right));
		// Child is now the root and we are getting the height of the left and right tree
		// Setting the childs height to be the max between the left and right subtree
		child->height = max(maxHeight(child->left),maxHeight(child->right));

		// Return the new root which is child
		return child;

	}

	// PreOrder traversal (Helper)
	void preOrder(AVLTreeNode<K,V>* r){
		// Base case
		if(r == NULL){
			return;
		}
		cout<<"New Tree's Key: "<<r->key<<endl;
		preOrder(r->left);
		preOrder(r->right);
	}

	// Insert helper method
	bool helpInsert(AVLTreeNode<K,V>* &root, K key, V value, bool &d){
		if(root == NULL){
			// Call the create node helper function
			root = create(key,value);
			// Increase the size by one since we have a new node
			currSize++;
			// Return true since we were able to put it in the tree
			// When we return true it returns true FOR THAT FUNCTION CALL ONLY
			return true;
		}
		// Compare the key if it is smaller than root, go in the left subtree
		if(key < root->key){
			helpInsert(root->left,key,value,d);
			if(d == false){
				return false;
			}
			
		}
		// Else if the key is bigger than root, go in the right subtree
		else if(key > root->key){
			helpInsert(root->right,key,value,d);
			if(d == false){
				return false;
			}
		}
		// This means there are duplicate keys which ISNT ALLOWED so set d to be false
		else{
			d = false;
			return d;
		}

		// 2) Update height of the ancestor node
		// We get the height from the ancestor node which we pretend to be the root in that case
		// Since we are pretending the ancestor node to be the root, we get the height by getting the max
		// Of the left and right subtree
		root->height = max(maxHeight(root->left),maxHeight(root->right));

		// TempBalance stores the balance of the left and right subtree
		// Positive number = Left subtree is bigger
		// Negative number = Right subtree is bigger
		int tempBalance = getBalance(root);

		// After insertion, we get pointers to all ancestors one by one in a bottom up manner
		// This we dont need a parent pointer to travel up
		// The recursive code itself travels ip and visits all the ancestors of the NEWLY INSERTED NODE

		// If it is a left left case (Right rotate once)
		if(tempBalance > 1 && key< root->left->key){
			root = rightRotate(root);
		}
		// If it is a right right case (Left rotate once)
		if(tempBalance < -1 && key > root->right->key){
			root = leftRotate(root);
		}
		// If it is a left right case (Left rotate, then right rotate)
		if(tempBalance > 1 && key > root->left->key){
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}
		// If it is a right left case (Right rotate, then left rotate)
		if(tempBalance < -1 && key < root->right->key){
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}
		// If tree is balanced, just return true and keep going in the recursive call stack
		return true; 
	}	
	// Helper function for the helpDelete function
	AVLTreeNode<K,V>* minValue(AVLTreeNode<K,V>* &n){
		AVLTreeNode<K,V>*curr = n;
		while(curr->left!= NULL){
			// Going to the smallest key in the subtree
			curr = curr->left;
		}
		return curr;
	}

	// Our delete function which will rebalance too 
	// We need a reference for test or else it doesn't work
	bool helpDelete(AVLTreeNode<K,V>* &r, K k, bool &test){
		// Base cases
		// This means the key wasnt in the tree so set test to false and return false
		if(r == NULL){
			test = false;
			return test;
		}
		// If the key we are deleting is less than the current key go to the left side of the tree
		if(k < r->key){
			helpDelete(r->left, k, test);
			// If test is false, will keep recursively returning false and end each call in the call stack
			if(test == false){
				return false;
			}
		}
		// If the key we are deleting is greater than the current key go to the right side of the tree
		else if(k > r->key){
			helpDelete(r->right, k, test);
			if(test == false){
				return false;
			}
		}
		// Else we have found the key but there are three different cases
		// 1) The key has zero children 2) The key has one child 3) The key has two children 
		// THIS IS THE NODE WE WANT TO DELETE
		else{
			// Zero chidren case (Leaf Node)
			if(r->left == NULL && r->right == NULL){
				delete r;
				// r still has its address so after deleting it we can just set it to NULL
				r = NULL;
				currSize--;
			}
			// One child case (If the left child is NULL) 
			else if(r-> left == NULL){
				// Have a temporary pointer to the node
				AVLTreeNode<K,V>* temp = r;
				// Root is now pointing to the right child so the previous node goes to root
				r = r->right;
				// We have to delete temp because it will not go to temp anymore
				delete temp;
				currSize--;
			}
			// One child case (If the right child is NULL) 
			else if(r->right == NULL){	
				// Have a temporary pointer to the node
				AVLTreeNode<K,V>* tempTwo = r;
				// Root is now pointing to the left child so the previous node goes to root
				r = r->left;
				// We have to delete temp because it will not go to tempTwo anymore
				delete tempTwo;
				currSize--;

			}
			// Two children case (Final case) 
			else{
				// Creating a temporary node pointer to the smallest key in the right subtree
				AVLTreeNode<K,V>*temporary = minValue(r->right);
				// Setting our roots key to be the temporary's key and value
				r->key = temporary->key;
				r->value = temporary->value;
				// Go in the right subtree and update our key to be the temporary's key
				helpDelete(r->right,temporary->key,test);

			}
			
		}
		
		
		// AVL Tree Implementation here
		// Get the balance
		int bal = getBalance(r);

		
		// Left right case
		if(bal > 1 && getBalance(r->left) < 0){
			// Rotate
			r->left = leftRotate(r->left);
			r = rightRotate(r);
			return true;

		}
		// If it is a right left case
		if(bal < -1 && getBalance(r->right) > 0){
			// Rotate
			r->right = rightRotate(r->right);
			r = leftRotate(r);
			return true;

		}
		// Right right case
		if(bal < -1 && getBalance(r->left) >= 0){
			// Rotate
			r = leftRotate(r);
			return true;
			
		}
		// Left left case 
		if(bal >1 && getBalance(r->right) <= 0){
			// Rotate
			r = rightRotate(r);
			return true;

		}
		
		// Return true for the function 
		return true;
	}

	
	// In order traversal helper method (Values)
	vector <V> inOrder(AVLTreeNode<K,V>* temp, vector<V> &arr) const{
		if(temp == NULL){
			return arr;
		}
		inOrder(temp->left, arr);
		arr.push_back(temp->value);
		inOrder(temp->right,arr);
		// Ends that specific call in the call stack
		return arr;
	}

	// In order traversal helper method (Keys)
	vector <K> inOrderKey(AVLTreeNode<K,V>* temp, vector<K> &arr) const{
		if(temp == NULL){
			return arr;
		}
		inOrderKey(temp->left, arr);
		arr.push_back(temp->key);
		inOrderKey(temp->right,arr);
		// Ends that specific call in the call stack
		return arr;
	}

	// copyConstructor help function
	AVLTreeNode<K,V>*  newRoot(const AVLTreeNode<K,V>* ourPointer)const{
		/*
		// If ourPointer != NULL, keep creating a new node
		if(ourPointer != NULL){
			AVLTreeNode<K,V> * currentPoint = create(ourPointer->key, ourPointer->value);
			currentPoint->left = newRoot(ourPointer->left);
			currentPoint->right = newRoot(ourPointer->right);
			return currentPoint;
		}
		
		// If it is NULL, return NULL!
		return NULL;
		*/
		if(ourPointer == NULL){
			return NULL;
		}
		AVLTreeNode<K,V> * currentPoint = create(ourPointer->key, ourPointer->value);
		currentPoint->left = newRoot(ourPointer->left);
		currentPoint->right = newRoot(ourPointer->right);
		return currentPoint;
	}
	
	
public:
	// Constructor (Creates an empty tree where root is a null pointer)
	AVLTree();
	// Copy Constrctor
	AVLTree(const AVLTree<K,V>& t);
	// Operator constructor
	AVLTree<K,V>& operator=(const AVLTree<K,V>& t);
	// Destructor
	~AVLTree();
	// Insert function (Returns true if it is successfully inserted) (We need roatation for this)
	// Insert it in AVL tree by pretending it's like a BST and then rotate after
	bool insert(K k, V v);
	// Remove function (K represents the key) (We need toation for this)
	// Delete it in AVL tree by pretending it's like a BST and then rotate after
	bool remove(K k);
	// Search function (K is the method's single parameter and returns value)
	// Throws a runtime error if it is not found
	V search(K k) const;
	// Values function 
	// Returns a vector that contains all of the values in the tree in ascending key order
	// If the tree is empty, the returned vector will also be empty
	vector <V> values() const;
	// Keys function
	// Returns a vector that contains all of the keys in the tree in ascending order
	// If the tree is empty, the returned vector will also be empty
	vector <K> keys() const;
	// Size function
	unsigned size() const;
	// getRoot function
	void* getRoot() const { return root; }; // DO NOT REMOVE
};

template<class K, class V>
// AVL Tree Methods go here (ALL METHODS)
// Constructor Implementation
AVLTree<K,V>::AVLTree(){
	root = NULL;
	currSize = 0;
}

// Copy constructor implementation (Copying from the tree t)
template<class K, class V>
AVLTree<K,V>::AVLTree(const AVLTree<K,V>& t){
	// Setting our root to be t's root (t.root is a pointer to the root of t)
	//root = t.AVLTree;
	root = t.newRoot(t.root);
	currSize = t.currSize;
	
}

// Operator constructor
template<class K, class V>
AVLTree<K,V>& AVLTree<K,V>::operator=(const AVLTree<K,V>& t){
	// Delete everything from the old tree
	deleteNode(root);
	currSize = 0;
	// Copy everything from the new tree
	root = t.newRoot(t.root);
	currSize = t.currSize;
	// Return* this (Ends the function)
	return* this;
}

// Destructor Implementation 
template<class K, class V>
AVLTree<K,V>::~AVLTree(){
	// Calling the deleteNode method to help us dynamically delete everything 
	deleteNode(root); 
	currSize = 0;
	
}

// Insert Impelementiation (We call rotate in it)
template<class K, class V>
bool AVLTree<K,V>::insert(K k, V v){
	// 1) Perform the BST insertion
	bool duplicate = true;
	bool test = helpInsert(root,k,v,duplicate);

	// If there was a duplicate key, return false as it wasn't added
	if(test == false){
		return false;
	}
	// Else return true since the node was added in properly and balanced
	else{
		return true;
	}
	
}

// Delete Implementation (we call rotate in it)
template<class K, class V>
bool AVLTree<K,V>::remove(K k){
	// 1) Perform the BST delete
	bool copy= true;
	bool t = helpDelete(root,k,copy);
	// If there was a duplicate key, return false as it wasn't added
	if(t == false){
		return false;
	}
	// Else return true since the node was added in properly and balanced
	else{
		return true;
	}
}

// Search Implementation
template<class K, class V>
V AVLTree<K,V>::search(K k) const{
	// Check if the root is NULL
	try{
		if(root == NULL){
			// Throw an error
			throw runtime_error("Tree is empty so we can't find anything!");
		}
	// Catch the error and end the function if it's truee
	}catch(runtime_error& e){
		cout<<"ERROR: "<<e.what()<<endl;
		return 0;
	}
		
	try{
		// Create a current node
		AVLTreeNode<K,V>*curr = root;
		// Base case where the key is the same as our roots key
		while(curr!= NULL){
			// If the two keys are the same, return currents value
			if(k == curr->key){
				return curr->value; // Return the value and end the function
			}
			// If the key is less than current's key, go to the left of the tree
			if(k <= curr->key){
				curr = curr->left;
			}
			// Else go to the right
			else{
				curr = curr->right;
			}
		}
		// Throw an error if the key couldn't be found in the tree
		throw runtime_error("Key doesn't exist in the tree as it couldn't be found");
	}
	// Catch the error and return 0
	catch(runtime_error& e){
		cout<<"ERROR: "<<e.what()<<endl;
		return 0;
	}
}

// Values Implementation
template<class K, class V>
vector <V> AVLTree<K,V>::values()const{
	vector <V> newVector; // newVector is completely empty right now when we intialize it
	// Since it goes in ascending key order, we should do left root right (In order traversal) 
	inOrder(root,newVector);
	// We return newVector where it has the values in terms of ascending order for keys
	return newVector;
}


// Keys Implementation
template<class K, class V>
vector <K> AVLTree<K,V>::keys() const{
	vector <K> newVector; // newVector is completely empty right now
	// Since it goes in ascending key order, we should do left root right (In order traversal)
	inOrderKey(root,newVector);
	// We return newVector where it has the values 
	return newVector;
}


// Size Implementation
template<class K, class V>
unsigned AVLTree<K,V>::size() const{
	// We return the size of the tree(Number of nodes)
	return currSize;
}