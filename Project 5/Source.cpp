#include<iostream>

using namespace std;

template <class DT>
class ParentBinaryTree {
protected:
	//Array that represents the parent of each node
	DT* parentArray;
	// number of nodes
	int numNodes;
	//array to decide if a child is a left or a right child
	int* childArray;
	//stack used for postorder and inorder
	DT* stack;
	//top of the stack
	int lastIndex; //for stack
public:
	ParentBinaryTree();
	ParentBinaryTree(int size);
	ParentBinaryTree(const ParentBinaryTree<DT> &copied);
	~ParentBinaryTree();
	void operator=(const ParentBinaryTree<DT> &copied);
	void copy(const ParentBinaryTree<DT> &copied);
	int size();
	void fillDepth(int i, int depth[]);
	int height();
	DT getLeft(DT parent);
	DT getRight(DT parent);
	void preorderTraversal();
	void inorderTraversal();
	void postorderTraversal();
	void addParent(DT node, DT parent);
	void setLeft(DT node);
	void setRight(DT node);
	void pushToBottonLeft(DT node);
	DT* getParentArray();
};

//gets the´parent array for iostream operator
template <class DT>
DT* ParentBinaryTree<DT>::getParentArray() {
	return parentArray;
}

//default constructor
template <class DT>
ParentBinaryTree<DT>::ParentBinaryTree() {
	numNodes = 0;
	lastIndex = -1;
	stack = NULL;
	parentArray = NULL;
	childArray = NULL;
}

//non-default constructor
template <class DT>
ParentBinaryTree<DT>::ParentBinaryTree(int size) {
	numNodes = size;
	lastIndex = -1;
	stack = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		stack[i] = -1;
	}
	parentArray = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		parentArray[i] = -1;
	}
	childArray = new int[numNodes];
	for (int i = 0; i < numNodes; i++) {
		childArray[i] = -1;
	}
}

//copy constructor
template <class DT>
ParentBinaryTree<DT>::ParentBinaryTree(const ParentBinaryTree<DT> &copied) {
	copy(copied);
}

//destructor
template <class DT>
ParentBinaryTree<DT>::~ParentBinaryTree() {
	if (stack != NULL) {
		delete[] stack;
		stack = NULL;
	}
	if (parentArray != NULL) {
		delete[] parentArray;
		parentArray = NULL;
	}
	if (childArray != NULL) {
		delete[] childArray;
		childArray = NULL;
	}
}

//copy method for overloaded equal operator and copy constructor
template <class DT>
void ParentBinaryTree<DT>::copy(const ParentBinaryTree<DT> &copied) {
	numNodes = copied.numNodes;
	if (parentArray != NULL) {
		delete[] parentArray;
	}
	if (childArray != NULL) {
		delete[] childArray;
	}
	parentArray = new DT[numNodes];
	childArray = new int[numNodes];
	for (int i = 0; i < numNodes; i++) {
		parentArray[i] = copied.parentArray[i];
		childArray[i] = copied.childArray[i];
	}
}

//overloaded equal operator
template <class DT>
void ParentBinaryTree<DT>::operator=(const ParentBinaryTree<DT> &copied) {
	copy(copied);
}

//returns the size of the tree
template <class DT>
int ParentBinaryTree<DT>::size() {
	return numNodes;
}

//gets the depth for each node (distance to root) and store in an depth array
template <class DT>
void ParentBinaryTree<DT>::fillDepth(int i, int depth[]) {
	if (depth[i])
		return;

	if (parentArray[i] == -1) {
		depth[i] = 1;
		return;
	}
	if (depth[parentArray[i]] == 0) {
		fillDepth(parentArray[i], depth);
	}

	depth[i] = depth[parentArray[i]] + 1;
}

//return the height of the tree
template <class DT>
int ParentBinaryTree<DT>::height() {
	int* depth = new int[numNodes];
	for (int i = 0; i < numNodes; i++) {
		depth[i] = 0;
	}
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] != 1) {
			fillDepth(i, depth);
		}
	}
	int height = depth[0];
	for (int i = 1; i < numNodes; i++)
		if (height < depth[i]) {
			height = depth[i];
		}
	return height;
}

//get the left child of the given parent
template <class DT>
DT ParentBinaryTree<DT>::getLeft(DT parent) {
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] == parent) {
			if (childArray[i] == 0) {
				return i;
				break;
			}
		}
	}
	return -1;
}

//get the right child of the given parent
template <class DT>
DT ParentBinaryTree<DT>::getRight(DT parent) {
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] == parent) {
			if (childArray[i] == 1) {
				return i;
				break;
			}
		}
	}
	return -1;
}

//prints the preorder transversal of the tree
template <class DT>
void ParentBinaryTree<DT>::preorderTraversal() {
	cout << *this;
}

//used in the inorder transversal - pushes all children that are to the left 'till reaches the bottom on the stack
template <class DT>
void ParentBinaryTree<DT>::pushToBottonLeft(DT node) {
	while (node != -1) {
		lastIndex++;
		stack[lastIndex] = node;
		node = getLeft(node);
	}
}

//prints the inorder transversal of the tree
template <class DT>
void ParentBinaryTree<DT>::inorderTraversal() {
	//find the root 
	int root = -1;
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] == -1) {
			root = i;
			break;
		}
	}
	pushToBottonLeft(root);

	//while there are elements in the stack
	while (lastIndex >= 0) {

		root = stack[lastIndex];
		//remove last element from stack
		cout << stack[lastIndex] << " ";
		stack[lastIndex] = -1;
		lastIndex--;

		if (getRight(root) != -1) {
			pushToBottonLeft(getRight(root));
		}
	}
	cout << endl;
}

//prints the postorder transversal of the tree
template <class DT>
void ParentBinaryTree<DT>::postorderTraversal() {
	//find the root 
	int root = -1;
	int previous = -1;
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] == -1) {
			root = i;
			break;
		}
	}
	lastIndex = 0;
	stack[lastIndex] = root;

	//while there are elements in the stack
	while (lastIndex >= 0) {
		int current = stack[lastIndex];
		if (previous == -1 || getLeft(previous) == current || getRight(previous) == current) {
			if (getLeft(current) != -1) {
				lastIndex++;
				stack[lastIndex] = getLeft(current);
			}
			else if (getRight(current) != -1) {
				lastIndex++;
				stack[lastIndex] = getRight(current);
			}
			else {
				cout << stack[lastIndex] << " ";
				stack[lastIndex] = -1;
				lastIndex--;
			}
		}
		else if (getLeft(current) == previous) {
			if (getRight(current) != -1) {
				lastIndex++;
				stack[lastIndex] = getRight(current);
			}
			else {
				cout << current << " ";
				stack[lastIndex] = -1;
				lastIndex--;
			}
		}
		else if (getRight(current) == previous) {
			cout << current << " ";
			stack[lastIndex] = -1;
			lastIndex--;
		}
		previous = current;
	}
	cout << endl;
}

//adds a parent in the parent array
template <class DT>
void ParentBinaryTree<DT>::addParent(DT node, DT parent) {
	parentArray[node] = parent;
}

//sets child as left in the child array
template <class DT>
void ParentBinaryTree<DT>::setLeft(DT node) {
	childArray[node] = 0;
}

//sets child as right in the child array
template <class DT>
void ParentBinaryTree<DT>::setRight(DT node) {
	childArray[node] = 1;
}

//overloaded ostream operator << to print the preorder transversal
template <class DT>
ostream& operator<<(ostream &s, ParentBinaryTree<DT> &parentBinaryTree) {
	int numNodes = parentBinaryTree.size();
	DT* stack = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		stack[i] = -1;
	}
	DT* parentArray = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		parentArray[i] = parentBinaryTree.getParentArray()[i];
	}
	int lastIndex = 0;
	//find the root 
	int root = -1;
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] == -1) {
			root = i;
			stack[lastIndex] = root;
			break;
		}
	}

	//while there are elements in the stack
	while (lastIndex >= 0) {

		root = stack[lastIndex];
		//remove last element from stack
		s << stack[lastIndex] << " ";
		stack[lastIndex] = -1;
		lastIndex--;

		if (parentBinaryTree.getRight(root) != -1) {
			lastIndex++;
			stack[lastIndex] = parentBinaryTree.getRight(root);
		}
		if (parentBinaryTree.getLeft(root) != -1) {
			lastIndex++;
			stack[lastIndex] = parentBinaryTree.getLeft(root);
		}
	}
	s << endl;
	delete[] stack;
	return s;
}

//main function
int main() {
	while (!cin.eof()) {
		int infoSize = 40;
		char* info = new char[infoSize];
		int i = -1;
		do {
			i++;
			cin.get(info[i]);
		} while (info[i] != '\n' && info[i] != '\0' && info[i] != ' ');
		info[i] = '\0';
		int noItems = atoi(info);
		ParentBinaryTree<int>* parentBinaryTree = new ParentBinaryTree<int>(noItems);
		
		for (int j = 0; j < noItems; j++) {
			i = -1;
			do {
				i++;
				cin.get(info[i]);
			} while (info[i] != '\n' && info[i] != '\0' && info[i] != ' ');
			info[i] = '\0';
			int parent = atoi(info);
			i = -1;
			do {
				i++;
				cin.get(info[i]);
			} while (info[i] != '\n' && info[i] != '\0' && info[i] != ' ');
			info[i] = '\0';
			int left = atoi(info);
			i = -1;
			do {
				i++;
				cin.get(info[i]);
			} while (info[i] != '\n' && info[i] != '\0' && info[i] != ' ');
			info[i] = '\0';
			int right = atoi(info);
			
			(*parentBinaryTree).setLeft(left);
			(*parentBinaryTree).addParent(left, parent);
			(*parentBinaryTree).setRight(right);
			(*parentBinaryTree).addParent(right, parent);
			//cout << parent << " " << (*parentBinaryTree).getLeft(parent) << " " << (*parentBinaryTree).getRight(parent) << endl;
		}
		cout << "===================================Starting Demo==================================" << endl;
		cout << "+++++demo for: ostream operator <<" << endl;
		cout << (*parentBinaryTree);
		cout << "+++++demo for: preorder method" << endl;
		(*parentBinaryTree).preorderTraversal();
		cout << "+++++demo for: inorder method" << endl;
		(*parentBinaryTree).inorderTraversal();
		cout << "+++++demo for: postorder method" << endl;
		(*parentBinaryTree).postorderTraversal();
		cout << "+++++demo for: size method" << endl;
		cout<< (*parentBinaryTree).size() << endl;
		cout << "+++++demo for: height method" << endl;
		cout << (*parentBinaryTree).height() << endl;
		cout << "+++++demo for: overloaded equal (=) operator" << endl;
		cout << "+++++printing preorder+++++" << endl;
		ParentBinaryTree<int> parentBinaryTree2 = (*parentBinaryTree);
		cout << parentBinaryTree2;
		cout << "+++++demo for: copy constructor" << endl;
		cout << "+++++printing preorder+++++" << endl;
		ParentBinaryTree<int>* parentBinaryTree3 = new ParentBinaryTree<int>(*parentBinaryTree);
		cout << (*parentBinaryTree3);
	}
	return 0;
}