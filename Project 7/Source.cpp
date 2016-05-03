#include <iostream>
#include <list>
#include <queue>
#include "ParentMultiTree.h"

using namespace std;

template <class DT>
class GraphAdjList {
protected:
	list<DT>* adjList;
	int n;
	int m;
	int topPosition;
public:
	GraphAdjList();
	GraphAdjList(int n, int m);
	~GraphAdjList();
	void addEdge(DT x, DT y);
	int size();
	list<DT>* getAdjList();
	int getM();
	ParentMultiTree<DT>* dfs(DT x);
	DT* bfs(DT x);
};

//default constructor
template <class DT>
GraphAdjList<DT>::GraphAdjList() {
	adjList = NULL;
	m = 0;
	n = 0;
	topPosition = 0;
}

//non default constructor
template <class DT>
GraphAdjList<DT>::GraphAdjList(int n, int m) {
	this->n = n;
	this->m = m;
	topPosition = 0;
	adjList = new list<DT>[n];
}

//destructor
template <class DT>
GraphAdjList<DT>::~GraphAdjList() {
	if (adjList != NULL) {
		delete[] adjList;
		adjList = NULL;
	}
}

//adds the edge x-y to the graph
template <class DT>
void GraphAdjList<DT>::addEdge(DT x, DT y) {
	//verify if x is a node of the array of lists
	bool xfound = false;
	for (int i = 0; i < n; i++) {
		//x found so add x-y as an edge
		if (!adjList[i].empty()) {
			if (adjList[i].front() == x) {
				adjList[i].push_back(y);
				xfound = true;
				break;
			}
		}
	}
	//x not found so create a node x and add edge x-y
	if (!xfound) {
		adjList[topPosition].push_front(x);
		adjList[topPosition].push_back(y);
		//cout << "Adding node " << x << " to position " << topPosition << endl;
		topPosition++;
	}
	//y is analogous
	bool yfound = false;
	for (int i = 0; i < n; i++) {
		if (!adjList[i].empty()) {
			if (adjList[i].front() == y) {
				adjList[i].push_back(x);
				yfound = true;
				break;
			}
		}
	}
	if (!yfound) {
		adjList[topPosition].push_front(y);
		adjList[topPosition].push_back(x);
		//cout << "Adding node " << y << " to position " << topPosition << endl;
		topPosition++;
	}
	//if x-y was already an edge, remove duplicates
	for (int i = 0; i < n; i++) {
		if (!adjList[i].empty()) {
			adjList[i].unique();
		}
	}
}

//Returns the number of nodes
template <class DT>
int GraphAdjList<DT>::size() {
	return n;
}

//getter for adjList
template <class DT>
list<DT>* GraphAdjList<DT>::getAdjList() {
	return adjList;
}

//returns the number of edges
template <class DT>
int GraphAdjList<DT>::getM() {
	return m;
}

//overloaded ostream operator <<
template <class DT>
ostream& operator<<(ostream& s, GraphAdjList<DT> graph) {
	list<DT>* list = graph.getAdjList();
	for (int i = 0; i < graph.size(); i++) {
		if (!list[i].empty()) {
			for (std::list<int>::iterator j = list[i].begin(); j != list[i].end(); j++) {
				s << *j << " ";
			}
			s << endl;
		}
	}
	return s;
}

//DFS
template <class DT>
ParentMultiTree<DT>* GraphAdjList<DT>::dfs(DT x) {
	ParentMultiTree<DT>* result = new ParentMultiTree<DT>(n);
	queue<DT> queue;
	queue.push(x);
	while (!queue.empty()) {
		DT root = queue.front();
		queue.pop();
		for (int i = 0; i < n; i++) {
			if (!adjList[i].empty()) {
				if(adjList[i].front() == root) {
					for (std::list<int>::iterator j = adjList[i].begin(); j != adjList[i].end(); j++) {
						//if j doesn't have a parent make the front of the list its parent
						if (j == adjList[i].begin()) {
							continue;
						}
						if ((*result).getParentArray()[*j] == -1) {
							//cout << root << " " << *j;
							(*result).addParent(*j, root);
							int childPosition = (*result).getNumberOfChildren(adjList[i].front()) + 1;
							(*result).setChildPosition(*j, childPosition);
							queue.push(*j);
						}
					}
				}
			}
		}
	}
	(*result).addParent(x, -1);
	return result;
}

//BFS
template <class DT>
DT* GraphAdjList<DT>::bfs(DT x) {
	DT* distance = new DT[n];
	for (int i = 0; i < n; i++) {
		distance[i] = -1; //-1 represents infinity
	}

	DT* parent = new DT[n];
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}

	distance[x] = 0;

	queue<DT> queue;
	queue.push(x);
	while (!queue.empty()) {
		DT root = queue.front();
		queue.pop();
		for (int i = 0; i < n; i++) {
			if (!adjList[i].empty()) {
				if (adjList[i].front() == root) {
					for (std::list<int>::iterator j = adjList[i].begin(); j != adjList[i].end(); j++) {
						//if j doesn't have a parent make the front of the list its parent
						if (j == adjList[i].begin()) {
							continue;
						}
						if (distance[*j] == -1) {
							parent[*j] = root;
							distance[*j] = distance[root] + 1;
							queue.push(*j);
						}
					}
				}
			}
		}
	}

	return distance;
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

		i = -1;
		do {
			i++;
			cin.get(info[i]);
		} while (info[i] != '\n' && info[i] != '\0' && info[i] != ' ');
		info[i] = '\0';
		int numEdges = atoi(info);

		delete[] info;

		GraphAdjList<int>* graph = new GraphAdjList<int>(noItems, numEdges);
		GraphAdjList<int>* graph2 = new GraphAdjList<int>(noItems, numEdges);
		GraphAdjList<int>* graph3 = new GraphAdjList<int>(noItems, numEdges);
		
		for (int j = 0; j < numEdges; j++) {
			char* info1 = new char[infoSize];
			i = -1;
			do {
				i++;
				cin.get(info1[i]);
			} while (info1[i] != '\n' && info1[i] != '\0' && info1[i] != ' ');
			info1[i] = '\0';
			int node1 = atoi(info1);
			delete[] info1;
			char* info2 = new char[infoSize];
			i = -1;
			do {
				i++;
				cin.get(info2[i]);
			} while (info2[i] != '\n' && info2[i] != '\0' && info2[i] != ' ');
			info2[i] = '\0';
			int node2 = atoi(info2);
			delete[] info2;

			(*graph).addEdge(node1, node2);
			(*graph2).addEdge(node1, node2);
			(*graph3).addEdge(node1, node2);
		}

		cout << "===================================Starting Demo==================================" << endl;
		cout << "+++++demo for: ostream operator <<" << endl;
		cout << (*graph);
		cout << "+++++demo for: DFS for node 0" << endl;
		cout << "+++++printing level order transversal+++++" << endl;
		(*(*graph2).dfs(0)).levelorderTransversal();
		cout << "+++++printing preorder transversal+++++" << endl;
		cout << (*(*graph2).dfs(0));
		cout << "+++++demo for: BFS for node 0" << endl;
		int* bfs = (*graph3).bfs(0);
		for (int i = 0; i < (*graph3).size(); i++) {
			cout << "node " << i << " has a distance to node 0 of " << bfs[i] << endl;
		}
	}
	return 0;
}