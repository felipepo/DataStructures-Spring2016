#include <iostream>

using namespace std;

/*=====================================CALSS CELL=========================================================*/
/* This class stores a linked list os cells. Each cell stores a value and a pointer to the next cell */
template <class DT>
class Cell {
protected:
	DT* _value;
	Cell<DT>* _right;
public:
	Cell();
	Cell(DT& value);
	Cell(Cell<DT>& copied);
	~Cell();
	void add(DT& value);
	int size();
	DT getValue();
	void copy(Cell<DT>& copied);
	void operator=(const Cell<DT>& copied);
	Cell<DT>* getRight();
	void setValue(DT& value);
	void setRight(Cell<DT>* right);
	bool searchValue(DT value);
};

//Empty constructor
template <class DT>
Cell<DT>::Cell() {
	_value = new DT(NULL);
	_right = NULL;
}

//Non-empty constructor
template <class DT>
Cell<DT>::Cell(DT& value) {
	_value = new DT(value);
	_right = NULL;
}

//copy function used on copy constructor and on overloaded equal operator
template <class DT>
void Cell<DT>::copy(Cell<DT>& copied) {
	if (copied._value == NULL) {
		_value = NULL;
	}
	else {
		_value = new DT(*(copied._value));
	}
	if (copied._right == NULL) {
		_right = NULL;
	}
	else {
		_right = new Cell<DT>(*(copied._right));
	}
}

//copy constructor
template <class DT>
Cell<DT>::Cell(Cell<DT>& copied) {
	copy(copied);
}

//destructor
template <class DT>
Cell<DT>::~Cell() {
	if (_value != NULL) {
		delete _value;
		delete _right;
	}
}

//adds a new cell to the list of cells
template <class DT>
void Cell<DT>::add(DT& value) {
	DT* current = new DT(*_value);
	Cell<DT>* temp = new Cell<DT>(*current);
	(*temp)._value = _value;
	(*temp)._right = _right;
	_right = temp;
	_value = new DT(value);
}

//returns the size od the list of cells
template <class DT>
int Cell<DT>::size() {
	if (_right == NULL) return 0;
	else return (1 + (*_right).size());
}

//gets the value of the current cell
template <class DT>
DT Cell<DT>::getValue() {
	return *_value;
}

//gets the cell pointed by the current cell
template <class DT>
Cell<DT>* Cell<DT>::getRight() {
	return _right;
}

//overloaded equal operator
template <class DT>
void Cell<DT>::operator=(const Cell<DT>& copied) {
	if (_value != NULL) {
		delete _value;
	}
	if (_right != NULL) {
		delete _right;
	}
	copy(copied);
}

//overloaded osteam << operator
template <class DT>
std::ostream& operator<<(std::ostream &s, Cell<DT>& cell) {
	if (cell.getValue() != NULL) {
		s << cell.getValue() << " ";
	}
	if (cell.getRight() != NULL) {
		s << (*cell.getRight());
	}
	return s;
}

//sets value to the current cell
template <class DT>
void Cell<DT>::setValue(DT& value) {
	_value = new DT(value);
}

//sets the cell on the right of the current cell
template <class DT>
void Cell<DT>::setRight(Cell<DT>* right) {
	_right = right;
}

//returns true if value is on linked list, false otherwise
template <class DT>
bool Cell<DT>::searchValue(DT value) {
	if (*_value == value) {
		return true;
	}
	else {
		if (_right != NULL) {
			(*_right).searchValue(value);
		}
		else {
			return false;
		}
	}
}
/*================================================================================================================*/
/*============================================CLASS CELLNODE======================================================*/
/*This class stores a CellNode which contains an info and a pointer to an Cell opbject*/
template <class DT1, class DT2>
class CellNode {
protected:
	DT1* _info;
	Cell<DT2>* _myCell;
public:
	CellNode();
	CellNode(DT1& info, Cell<DT2>* myCell);
	CellNode(CellNode& copied);
	~CellNode();
	void addCell(Cell<DT2>* cell);
	DT1* getInfo();
	void operator=(CellNode& copied);
	void setInfo(DT1& info);
	void copy(CellNode& copied);
	Cell<DT2>* getCell();
};

//empty constructor
template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode() {
	_info = NULL;
	_myCell = NULL;
}

//Non-empty constructor
template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(DT1& info, Cell<DT2>* myCell) {
	_info = new DT1(info);
	_myCell = myCell;
}

//copy method used on copy constructor and on overloaded equal operator
template <class DT1, class DT2>
void CellNode<DT1, DT2>::copy(CellNode<DT1, DT2>& copied) {
	_info = new DT1(*(copied._info));
	_myCell = new Cell<DT2>(*(copied._myCell));

}

//copy constructor
template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(CellNode<DT1, DT2>& copied) {
	copy(copied);
}

//destructor
template <class DT1, class DT2>
CellNode<DT1, DT2>::~CellNode() {
	if (_info != NULL) {
		delete _info;
		delete _myCell;
	}
}

//adds a Cell to the field which is a pointer to the cell
template <class DT1, class DT2>
void CellNode<DT1, DT2>::addCell(Cell<DT2>* cell) {
	(*_myCell).setRight(cell);
}

//gets info
template <class DT1, class DT2>
DT1* CellNode<DT1, DT2>::getInfo() {
	return _info;
}

//sets info
template<class DT1, class DT2>
void CellNode<DT1, DT2>::setInfo(DT1& info) {
	_info = new DT1(info);
}

//gets the cell to which CellNode points to
template <class DT1, class DT2>
Cell<DT2>* CellNode<DT1, DT2>::getCell() {
	return _myCell;
}

//overloaded operator equal
template <class DT1, class DT2>
void CellNode<DT1, DT2>::operator=(CellNode& copied) {
	if (_info != NULL) {
		_info = NULL;
	}
	if (_myCell != NULL) {
		_myCell = NULL;
	}
	copy(copied);
}

//overloaded ostream << operator
template <class DT1, class DT2>
std::ostream& operator<<(std::ostream &s, CellNode<DT1, DT2>& cellNode) {
	if (cellNode.getInfo() != NULL) {
		s << *(cellNode.getInfo()) << " ";
	}
	if (cellNode.getCell() != NULL) {
		s << *(cellNode.getCell());
	}
	s << endl;
	return s;
}
/*================================================================================================================*/
/*=============================================CLASS MASTER CELL=================================================*/
/*This class stores an array of CellNodes*/
template <class DT1, class DT2>
class MasterCell {
protected:
	CellNode<DT1, DT2>* _myCellNodes;
	int numOfCellNodes;
	int currentCellNode;
public:
	MasterCell();
	MasterCell(int size);
	MasterCell(MasterCell<DT1, DT2>& copied);
	void addCellNode(CellNode<DT1, DT2>& cellNode);
	int size();
	CellNode<DT1, DT2> getCellNode(int i);
	~MasterCell();
	void copy(MasterCell<DT1, DT2>& copied);
	void operator=(MasterCell<DT1, DT2>& copied);
	DT1* findKeywords(DT2 input);
	DT2* And(DT1 first, DT1 second);
	DT2* OR(DT1 first, DT1 second);
	DT2* ExclusiveOR(DT1 first, DT1 second);
	DT2* And(DT2* firstValues, DT1 second);
	DT2* OR(DT2* firstValues, DT1 second);
	DT2* ExclusiveOR(DT2* firstValues, DT1 second);
};

//empty constructor
template <class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell() {
	numOfCellNodes = 10;
	currentCellNode = -1;
	_myCellNodes = new CellNode<DT1, DT2>[numOfCellNodes];
}

//non-empty constructor
template <class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell(int size) {
	numOfCellNodes = size;
	currentCellNode = -1;
	_myCellNodes = new CellNode<DT1, DT2>[numOfCellNodes];
}


//destructor
template <class DT1, class DT2>
MasterCell<DT1, DT2>::~MasterCell() {
	delete[] _myCellNodes;
}

//adds a CellNode to the array of cell nodes
template <class DT1, class DT2>
void MasterCell<DT1, DT2>::addCellNode(CellNode<DT1, DT2>& cellNode) {
	currentCellNode++;
	if (currentCellNode + 1 > numOfCellNodes) {
		numOfCellNodes = 2 * numOfCellNodes;
		CellNode<DT1, DT2>* temp = new CellNode<DT1, DT2>[numOfCellNodes];
		for (int j = 0; j < numOfCellNodes / 2; j++) {
			temp[j] = _myCellNodes[j];
		}
		delete[] _myCellNodes;
		_myCellNodes = temp;
	}
	CellNode<DT1, DT2>* temp = new CellNode<DT1, DT2>(cellNode);
	_myCellNodes[currentCellNode] = *temp;
}

//gets CellNode at position i of array of CellNodes
template <class DT1, class DT2>
CellNode<DT1, DT2> MasterCell<DT1, DT2>::getCellNode(int i) {
	return _myCellNodes[i];
}

//returns the size of the array of CellNodes
template <class DT1, class DT2>
int MasterCell<DT1, DT2>::size() {
	return (currentCellNode + 1);
}

//copy method used on the overloaded equal operator and on the copy constructor
template <class DT1, class DT2>
void MasterCell<DT1, DT2>::copy(MasterCell<DT1, DT2>& copied) {
	numOfCellNodes = copied.numOfCellNodes;
	currentCellNode = copied.currentCellNode;
	delete[] _myCellNodes;
	_myCellNodes = new CellNode<DT1, DT2>[numOfCellNodes];
	for (int i = 0; i < copied.size(); i++) {
		_myCellNodes[i] = copied._myCellNodes[i];
	}
}

//overloaded ostream << operator
template <class DT1, class DT2>
std::ostream& operator<<(std::ostream &s, MasterCell<DT1, DT2>& masterCell) {
	for (int i = 0; i < (masterCell).size(); i++) {
		s << (masterCell).getCellNode(i);
	}
	return s;
}

//copy constructor
template <class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell(MasterCell<DT1, DT2>& copied) {
	copy(copied);
}

//overloaded equal operator
template <class DT1, class DT2>
void MasterCell<DT1, DT2>::operator=(MasterCell<DT1, DT2>& copied) {
	copy(copied);
}

//given a value, returns an array of all the keywords that have that value
template <class DT1, class DT2>
DT1* MasterCell<DT1, DT2>::findKeywords(DT2 input) {
	DT1* result = new DT1[size()];
	for (int i = 0; i < size(); i++) {
		result[i] = "/0";
	}
	int index = 0;
	for (int i = 0; i < size(); i++) {
		DT1 info = *(getCellNode(i).getInfo());
		Cell<DT2> cell = *(getCellNode(i).getCell());
		bool found = cell.searchValue(input);
		if (found) {
			result[index] = info;
			index++;
		}
	}
	return result;
}

//Takes	two	keywords and returns all the integers that are common of both
template <class DT1, class DT2>
DT2* MasterCell<DT1, DT2>::And(DT1 first, DT1 second) {
	int firstSize = 0;
	DT2* firstValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(first, *(getCellNode(i).getInfo()))) {
			firstSize = (*(getCellNode(i).getCell())).size();
			firstValues = new DT2[firstSize];
			for (int j = 0; j < firstSize; j++) {
				firstValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}

	int secondSize = 0;
	DT2* secondValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(second, *(getCellNode(i).getInfo()))) {
			secondSize = (*(getCellNode(i).getCell())).size();
			secondValues = new DT2[secondSize];
			for (int j = 0; j < secondSize; j++) {
				secondValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}


	int size = firstSize + 1;
	if (firstSize > secondSize) {
		size = secondSize + 1;
	}
	DT2* result = new DT2[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}
	int index = 0;
	for (int i = 0; i < firstSize; i++) {
		for (int j = 0; j < secondSize; j++) {
			if (firstValues[i] == secondValues[j]) {
				result[index] = firstValues[i];
				index++;
			}
		}
	}

	return result;
}

//Takes	two	keywords and returns all the integers that are in eighter of them
template <class DT1, class DT2>
DT2* MasterCell<DT1, DT2>::OR(DT1 first, DT1 second) {
	int firstSize = 0;
	DT2* firstValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(first, *(getCellNode(i).getInfo()))) {
			firstSize = (*(getCellNode(i).getCell())).size();
			firstValues = new DT2[firstSize];
			for (int j = 0; j < firstSize; j++) {
				firstValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}


	int secondSize = 0;
	DT2* secondValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(second, *(getCellNode(i).getInfo()))) {
			secondSize = (*(getCellNode(i).getCell())).size();
			secondValues = new DT2[secondSize];
			for (int j = 0; j < secondSize; j++) {
				secondValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}


	int size = firstSize + secondSize + 1;

	DT2* result = new DT2[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}
	int index = firstSize;
	for (int i = 0; i < firstSize; i++) {
		result[i] = firstValues[i];
	}
	bool found = false;
	for (int j = 0; j < secondSize; j++) {
		for (int i = 0; i < firstSize; i++) {
			if (firstValues[i] == secondValues[j]) {
				found = true;
			}
		}
		if (!found) {
			result[index] = secondValues[j];
			index++;
		}
		found = false;
	}
	return result;
}

//Takes	two	keywords and returns all the integers that are not common in both
template <class DT1, class DT2>
DT2* MasterCell<DT1, DT2>::ExclusiveOR(DT1 first, DT1 second) {
	int firstSize = 0;
	DT2* firstValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(first, *(getCellNode(i).getInfo()))) {
			firstSize = (*(getCellNode(i).getCell())).size();
			firstValues = new DT2[firstSize];
			for (int j = 0; j < firstSize; j++) {
				firstValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}


	int secondSize = 0;
	DT2* secondValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(second, *(getCellNode(i).getInfo()))) {
			secondSize = (*(getCellNode(i).getCell())).size();
			secondValues = new DT2[secondSize];
			for (int j = 0; j < secondSize; j++) {
				secondValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}


	int size = firstSize + secondSize + 1;
	DT2* result = new DT2[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}
	int index = 0;
	bool found = false;
	for (int i = 0; i < firstSize; i++) {
		for (int j = 0; j < secondSize; j++) {
			if (firstValues[i] == secondValues[j]) {
				found = true;
			}
		}
		if (!found) {
			result[index] = firstValues[i];
			index++;
		}
		found = false;
	}
	found = false;
	for (int j = 0; j < secondSize; j++) {
		for (int i = 0; i < firstSize; i++) {
			if (firstValues[i] == secondValues[j]) {
				found = true;
			}
		}
		if (!found) {
			result[index] = secondValues[j];
			index++;
		}
		found = false;
	}
	return result;
}

//implementation of AND with array instead of keyword
template <class DT1, class DT2>
DT2* MasterCell<DT1, DT2>::And(DT2* firstValues, DT1 second) {
	int secondSize = 0;
	DT2* secondValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(second, *(getCellNode(i).getInfo()))) {
			secondSize = (*(getCellNode(i).getCell())).size();
			secondValues = new DT2[secondSize];
			for (int j = 0; j < secondSize; j++) {
				secondValues[j] = (*cell).getValue();
				//cout << (*cell).getValue() << "\t" << firstValues[j] << "\n";
				cell = (*cell).getRight();
			}
			break;
		}
	}
	int firstSize = 0;
	int index = -1;
	do {
		index++;
		firstSize++;
	} while (firstValues[index] != -1);

	int size = firstSize + 1;
	if (firstSize > secondSize) {
		size = secondSize + 1;
	}
	DT2* result = new DT2[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}
	index = 0;
	for (int i = 0; i < firstSize; i++) {
		for (int j = 0; j < secondSize; j++) {
			if (firstValues[i] == secondValues[j]) {
				result[index] = firstValues[i];
				index++;
			}
		}
	}
	return result;
}

//implementation of OR with array instead of keyword
template <class DT1, class DT2>
DT2* MasterCell<DT1, DT2>::OR(DT2* firstValues, DT1 second) {
	int firstSize = 0;
	int index = -1;
	do {
		index++;
		firstSize++;
	} while (firstValues[index] != -1);


	int secondSize = 0;
	DT2* secondValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(second, *(getCellNode(i).getInfo()))) {
			secondSize = (*(getCellNode(i).getCell())).size();
			secondValues = new DT2[secondSize];
			for (int j = 0; j < secondSize; j++) {
				secondValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}


	int size = firstSize + secondSize + 1;
	DT2* result = new DT2[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}
	index = firstSize;
	for (int i = 0; i < firstSize; i++) {
		result[i] = firstValues[i];
	}
	bool found = false;
	for (int j = 0; j < secondSize; j++) {
		for (int i = 0; i < firstSize; i++) {
			if (firstValues[i] == secondValues[j]) {
				found = true;
			}
		}
		if (!found) {
			result[index] = secondValues[j];
			index++;
		}
		found = false;
	}
	return result;
}

//implementation of ExclusiveOR with array instead of keyword
template <class DT1, class DT2>
DT2* MasterCell<DT1, DT2>::ExclusiveOR(DT2* firstValues, DT1 second) {
	int firstSize = 0;
	int index = -1;
	do {
		index++;
		firstSize++;
	} while (firstValues[index] != -1);

	int secondSize = 0;
	DT2* secondValues = new DT2;
	for (int i = 0; i < size(); i++) {
		Cell<DT2>* cell = new Cell<DT2>(*(getCellNode(i).getCell()));
		if (strCompare(second, *(getCellNode(i).getInfo()))) {
			secondSize = (*(getCellNode(i).getCell())).size();
			secondValues = new DT2[secondSize];
			for (int j = 0; j < secondSize; j++) {
				secondValues[j] = (*cell).getValue();
				cell = (*cell).getRight();
			}
			break;
		}
	}


	int size = firstSize + secondSize + 1;
	DT2* result = new DT2[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}
	index = 0;
	bool found = false;
	for (int i = 0; i < firstSize; i++) {
		for (int j = 0; j < secondSize; j++) {
			if (firstValues[i] == secondValues[j]) {
				found = true;
			}
		}
		if (!found) {
			result[index] = firstValues[i];
			index++;
		}
		found = false;
	}
	found = false;
	for (int j = 0; j < secondSize; j++) {
		for (int i = 0; i < firstSize; i++) {
			if (firstValues[i] == secondValues[j]) {
				found = true;
			}
		}
		if (!found) {
			result[index] = secondValues[j];
			index++;
		}
		found = false;
	}
	return result;
}

bool strCompare(char* x, char* y)
{
	int i = 0;
	bool result = false;

	while ((!result) && (x[i] == y[i]))
		if (x[i] == '\0')
			result = true;
		else i++;

		return result;
}

int main() {
	MasterCell<char*, int>* masterCell = new MasterCell<char*, int>();

	int numCellNodes = 0;
	char* first_buffer = new char[256];
	cin.getline(first_buffer, 256);
	int index = 0;
	numCellNodes = atoi(first_buffer);

	while (!cin.eof()) {
		for (int jj = 0; jj < numCellNodes; jj++) {
			int infoSize = 40;
			char* info = new char[infoSize];
			int i = -1;
			do {
				i++;
				cin.get(info[i]);
			} while (info[i] != ',');
			info[i] = '\0';

			char blank = NULL;
			blank = cin.get();
			int noItems = 0;
			char* noItemsString = new char[5];
			i = -1;
			do {
				i++;
				noItemsString[i] = cin.get();
			} while (noItemsString[i] != ' ');
			noItemsString[i] = '\0';
			noItems = atoi(noItemsString);
			//cout << noItems + 1 << " ";
			int currentValue = 0;
			//cin.ignore(1000, '\n');
			int start = 0;
			Cell<int> *cell = new Cell<int>();
			char* buffer = new char[256];
			int j = -1;
			for (int i = 0; i < noItems; i++) {
				j = -1;
				do {
					j++;
					buffer[j] = cin.get();
				} while (buffer[j] != ' ' && buffer[j] != '\n' && buffer != '\0');
				currentValue = atoi(buffer);
				(*cell).add(currentValue);
			}
			if (buffer[j] == ' ' || buffer[j] == '\0') {
				cin.ignore(1000, '\n');
			}
			CellNode<char*, int>* cellNode = new CellNode<char*, int>(info, cell);
			(*masterCell).addCellNode(*cellNode);
		}


		while (!cin.fail()) {
			char* opBuffer = new char[256];
			int bufferIndex = 0;
			cin.getline(opBuffer, 256);
			int j = -1;
			char* firstValue = new char[40];
			if (opBuffer[0] != '\n' && opBuffer[0] != '\0') {
				do {
					j++;
					firstValue[j] = opBuffer[bufferIndex];
					bufferIndex++;
				} while (opBuffer[bufferIndex] != '&' && opBuffer[bufferIndex] != '|' && opBuffer[bufferIndex] != '%' &&
					opBuffer[bufferIndex] != '\0' && !cin.eof());
				char firstOperation = opBuffer[bufferIndex];
				firstValue[j] = '\0';
				bufferIndex++;
				bufferIndex++;

				j = -1;
				char* secondValue = new char[40];
				do {
					j++;
					secondValue[j] = opBuffer[bufferIndex];
					bufferIndex++;
				} while (opBuffer[bufferIndex] != '&' && opBuffer[bufferIndex] != '|' && opBuffer[bufferIndex] != '%' &&
					opBuffer[bufferIndex] != '\0' && !cin.eof());
				char secondOperation = opBuffer[bufferIndex];
				secondValue[j] = '\0';
				bufferIndex++;
				bufferIndex++;

				j = -1;
				char* thirdValue = new char[40];
				do {
					j++;
					thirdValue[j] = opBuffer[bufferIndex];
					bufferIndex++;
				} while (opBuffer[bufferIndex] != '&' && opBuffer[bufferIndex] != '|' && opBuffer[bufferIndex] != '%' &&
					opBuffer[bufferIndex] != '\0' && !cin.eof());
				thirdValue[++j] = '\0';
				cout << "=================================================================================================================" << endl;
				cout << "Performing operation: " << opBuffer << endl;
				int* searched = NULL;
				switch (firstOperation) {
				case '&':
					searched = (*masterCell).And(firstValue, secondValue);
					break;
				case '|':
					searched = (*masterCell).OR(firstValue, secondValue);
					break;
				case '%':
					searched = (*masterCell).ExclusiveOR(firstValue, secondValue);
					break;
				}

				int* searched2 = NULL;
				switch (secondOperation) {
				case '&':
					searched2 = (*masterCell).And(searched, thirdValue);
					break;
				case '|':
					searched2 = (*masterCell).OR(searched, thirdValue);
					break;
				case '%':
					searched2 = (*masterCell).ExclusiveOR(searched, thirdValue);
					break;
				}

				cout << "------------------------------------------------RESULTS------------------------------------------------" << endl;
				index = 0;
				if (searched2 != NULL) {
					while (searched2[index] != -1) {
						cout << searched2[index] << "\n";
						index++;
					}
					if (index == 0) {
						cout << "NO RESULTS" << endl;
					}
					searched2 = NULL;
				}
				cout << "=================================================================================================================";
			}
		}

	}

	cout << "=========================================SHOWING FIND-KEYWORDS METHOD=========================================" << endl;
	cout << "OPERATION: Appling findKeywords(30) to CellMaster" << endl;
	cout << "------------------------------------------------RESULTS------------------------------------------------" << endl;
	char** searched = (*masterCell).findKeywords(30);
	index = 0;
	do {
		cout << searched[index] << "\n";
		index++;
	} while (searched[index] != "/0");
	cout << "==============================================================================================================" << endl;

	return 0;
}