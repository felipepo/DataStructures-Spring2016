#include<iostream>
#include<queue>

using namespace std;

template <class DT>
class ParentMultiTree {
protected:
	//Array that represents the parent of each node
	DT* parentArray;
	// number of nodes
	int numNodes;
	//array to decide if a child is a left or a right child
	int* childPosition;
	//queue used for level order transversal
	queue<DT> queue;
public:
	ParentMultiTree();
	ParentMultiTree(int size);
	ParentMultiTree(const ParentMultiTree<DT> &copied);
	~ParentMultiTree();
	void operator=(const ParentMultiTree<DT> &copied);
	void copy(const ParentMultiTree<DT> &copied);
	int size();
	void fillDepth(int i, int depth[]);
	int height();
	void preorderTraversal();
	void levelorderTransversal();
	void addParent(DT node, DT parent);
	void setChildPosition(DT node, int position);
	DT* getParentArray();
	DT* getChildren(DT parent);
	int getNumberOfChildren(DT parent);
	int* getChildPosition();
};

//gets the parent array for iostream operator
template <class DT>
DT* ParentMultiTree<DT>::getParentArray() {
	return parentArray;
}

//gets the number of chidren of a given node
template <class DT>
int ParentMultiTree<DT>::getNumberOfChildren(DT parent) {
	int numOfChildren = 0;
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] == parent) {
			numOfChildren++;
		}
	}
	return numOfChildren;
}

//gets the children of a given node
template <class DT>
DT* ParentMultiTree<DT>::getChildren(DT parent) {
	int numOfChildren = getNumberOfChildren(parent);
	DT* children = new DT[numOfChildren];
	int j = 0;
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] == parent) {
			children[j] = i;
			j++;
		}
	}
	return children;
}

//gets the parent array for iostream operator
template <class DT>
int* ParentMultiTree<DT>::getChildPosition() {
	return childPosition;
}

//default constructor
template <class DT>
ParentMultiTree<DT>::ParentMultiTree() {
	numNodes = 0;
	parentArray = NULL;
	childPosition = NULL;
}

//non-default constructor
template <class DT>
ParentMultiTree<DT>::ParentMultiTree(int size) {
	numNodes = size;
	parentArray = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		parentArray[i] = -1;
	}
	childPosition = new int[numNodes];
	for (int i = 0; i < numNodes; i++) {
		childPosition[i] = -1;
	}
}

//copy constructor
template <class DT>
ParentMultiTree<DT>::ParentMultiTree(const ParentMultiTree<DT> &copied) {
	copy(copied);
}

//destructor
template <class DT>
ParentMultiTree<DT>::~ParentMultiTree() {
	if (parentArray != NULL) {
		delete[] parentArray;
		parentArray = NULL;
	}
	if (childPosition != NULL) {
		delete[] childPosition;
		childPosition = NULL;
	}
}

//copy method for overloaded equal operator and copy constructor
template <class DT>
void ParentMultiTree<DT>::copy(const ParentMultiTree<DT> &copied) {
	numNodes = copied.numNodes;
	if (parentArray != NULL) {
		delete[] parentArray;
	}
	if (childPosition != NULL) {
		delete[] childPosition;
	}
	parentArray = new DT[numNodes];
	childPosition = new int[numNodes];
	for (int i = 0; i < numNodes; i++) {
		parentArray[i] = copied.parentArray[i];
		childPosition[i] = copied.childPosition[i];
	}
}

//overloaded equal operator
template <class DT>
void ParentMultiTree<DT>::operator=(const ParentMultiTree<DT> &copied) {
	copy(copied);
}

//returns the size of the tree
template <class DT>
int ParentMultiTree<DT>::size() {
	return numNodes;
}

//gets the depth for each node (distance to root) and store in an depth array
template <class DT>
void ParentMultiTree<DT>::fillDepth(int i, int depth[]) {
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
int ParentMultiTree<DT>::height() {
	int* depth = new int[numNodes];
	for (int i = 0; i < numNodes; i++) {
		depth[i] = 0;
	}
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] != -1) {
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



//prints the preorder transversal of the tree
template <class DT>
void ParentMultiTree<DT>::preorderTraversal() {
	cout << *this;
}

//prints the levelorder transversal of the tree
template <class DT>
void ParentMultiTree<DT>::levelorderTransversal() {
	int root;
	for (int i = 0; i < size(); i++) {
		if (parentArray[i] == -1) {
			root = i;
			break;
		}
	}
	queue.push(root);
	int* depth = new int[numNodes];
	for (int i = 0; i < numNodes; i++) {
		depth[i] = 0;
	}
	for (int i = 0; i < numNodes; i++) {
		if (parentArray[i] != -1) {
			fillDepth(i, depth);
		}
	}
	/*for (int i = 0; i < numNodes; i++) {
		cout << depth[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < numNodes; i++) {
		cout << parentArray[i] << " ";
	}
	cout << endl;*/
	int level = 1;
	while (!queue.empty()) {
		DT* temp = new DT(queue.front());
		if (depth[*temp] > level) {
			cout << endl;
			level++;
		}
		cout << (*temp) << " ";
		queue.pop();
		int numOfChildren = getNumberOfChildren(*temp);
		DT* children = new DT[numOfChildren];
		children = getChildren(*temp);
		for (int i = 0; i < numOfChildren; i++) {
			queue.push(children[i]);
		}
	}
}

//adds a parent in the parent array
template <class DT>
void ParentMultiTree<DT>::addParent(DT node, DT parent) {
	parentArray[node] = parent;
}

//sets the position of the given child
template <class DT>
void ParentMultiTree<DT>::setChildPosition(DT node, int position) {
	childPosition[node] = position;
}

//overloaded ostream operator << to print the preorder transversal
template <class DT>
ostream& operator<<(ostream &s, ParentMultiTree<DT> &parentMultiTree) {
	int numNodes = parentMultiTree.size();
	DT* stack = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		stack[i] = -1;
	}
	DT* parentArray = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		parentArray[i] = parentMultiTree.getParentArray()[i];
	}

	int* childPosition = new DT[numNodes];
	for (int i = 0; i < numNodes; i++) {
		childPosition[i] = parentMultiTree.getChildPosition()[i];
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

		int numOfChildren = 0;
		for (int i = 0; i < numNodes; i++) {
			if (parentArray[i] == root) {
				numOfChildren++;
			}
		}
		DT* children = new DT[numOfChildren];
		int* childrenPositions = new int[numOfChildren];
		int j = 0;
		for (int i = 0; i < numNodes; i++) {
			if (parentArray[i] == root) {
				children[j] = i;
				childrenPositions[j] = childPosition[i];
				j++;
			}
		}
		
		//sort childrenPositions
		int ii;
		for (int i = 0; i < numOfChildren; i++) {
			ii = i;
			while (ii > 0 && childrenPositions[ii] < childrenPositions[ii - 1]) {
				swap(childrenPositions, i, ii);
				swap(children, i, ii);
				ii--;
			}
		}

		//children array is sorted from right to left so push all of its elements in order to the stack
		//FROM RIGHT TO LEFT
		for (int i = numOfChildren-1; i >=0 ; i--) {
				lastIndex++;
				stack[lastIndex] = children[i];
		}
	}
	s << endl;
	delete[] stack;
	return s;
}

void swap(int* array, int i, int j) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
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
		delete[] info;
		ParentMultiTree<int>* parentMultiTree = new ParentMultiTree<int>(noItems);

		for (int j = 0; j < noItems; j++) {
			char* info1 = new char[infoSize];
			i = -1;
			do {
				i++;
				cin.get(info1[i]);
			} while (info1[i] != '\n' && info1[i] != '\0' && info1[i] != ' ');
			info1[i] = '\0';
			int parent = atoi(info1);
			delete[] info1;
			char* info2 = new char[infoSize];
			i = -1;
			do {
				i++;
				cin.get(info2[i]);
			} while (info2[i] != '\n' && info2[i] != '\0' && info2[i] != ' ');
			info2[i] = '\0';
			int numOfChildren = atoi(info2);
			delete[] info2;
			for (int j = 0; j < numOfChildren; j++) {
				char* info3 = new char[infoSize];
				i = -1;
				do {
					i++;
					cin.get(info3[i]);
				} while (info3[i] != '\n' && info3[i] != '\0' && info3[i] != ' ' && !cin.eof());
				info3[i] = '\0';
				int child = atoi(info3);
				delete[] info3;
				(*parentMultiTree).addParent(child, parent);
				(*parentMultiTree).setChildPosition(child, j);
				if (cin.eof()) {
					break;
				}
			}
		}

		if (cin.eof() || cin.fail()) {
			return 0;
		}

		cout << "===================================Starting Demo==================================" << endl;
		cout << "+++++demo for: ostream operator <<" << endl;
		cout << (*parentMultiTree);
		cout << "+++++demo for: preorder method" << endl;
		(*parentMultiTree).preorderTraversal();
		cout << "+++++demo for: size method" << endl;
		cout << (*parentMultiTree).size() << endl;
		cout << "+++++demo for: height method" << endl;
		cout << (*parentMultiTree).height() << endl;
		cout << "+++++demo for: overloaded equal (=) operator" << endl;
		cout << "+++++printing preorder+++++" << endl;
		ParentMultiTree<int> parentMultiTree2 = (*parentMultiTree);
		cout << parentMultiTree2;
		cout << "+++++demo for: copy constructor" << endl;
		cout << "+++++printing preorder+++++" << endl;
		ParentMultiTree<int>* parentMultiTree3 = new ParentMultiTree<int>(*parentMultiTree);
		cout << (*parentMultiTree3);
		cout << "+++++demo for: get children method" << endl;
		//finding the root
		int root;
		for (int i = 0; i < parentMultiTree2.size(); i++) {
			if (parentMultiTree2.getParentArray()[i] == -1) {
				root = i;
				break;
			}
		}
		cout << "+++++printing the children of the root+++++" << endl;
		for (int i = 0; i < parentMultiTree2.getNumberOfChildren(root); i++) {
			cout << parentMultiTree2.getChildren(root)[i] << " ";
		}
		cout << endl;
		cout << "+++++demo for: level order transversal (BONUS POINTS)" << endl;
		parentMultiTree2.levelorderTransversal();
		cout << endl;
	}
	return 0;
}