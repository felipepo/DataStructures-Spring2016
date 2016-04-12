/*
**This program simulates some actions performed in a browser
*/

#include <iostream>
#include "UndefinedActionException.h"
#include "TabBoundsException.h"

using namespace std;
/*============================================================CLASS WebAddressInfo============================================================*/

/*Stores information of one webAddress*/
class WebAddressInfo {
public:
	int urlSize;	//urlSize
	char* url;		//array of a maximum of 200 characters for url

	WebAddressInfo();
	WebAddressInfo(char* inputString);
	WebAddressInfo(WebAddressInfo& copied);
	~WebAddressInfo();
	void operator=(const WebAddressInfo& copied);
	friend std::ostream& operator<<(std::ostream& s, WebAddressInfo& ac);
	void setWebAddressInfo(char* inputString);
	char* getWebAdressInfo();
	void display();
};

/*default constructor*/
WebAddressInfo::WebAddressInfo() {
	//creates a null array
	urlSize = 201;
	url = new char[urlSize];
	for (int i = 0; i < urlSize; i++) {
		url[i] = '\0';
	}
}

/*Initializer*/
WebAddressInfo::WebAddressInfo(char* inputString) {
	urlSize = 0;
	do {
		urlSize++;
	} while (inputString[urlSize] != '\0');
	urlSize++;
	url = new char[urlSize];
	int i = 0;
	//copies inputString to url
	do {
		url[i] = inputString[i];
		i++;
	} while (inputString[i] != '\0');
	url[i] = '\0';	//adds \0 to the last valid position in url
}

/*Copy constructor*/
WebAddressInfo::WebAddressInfo(WebAddressInfo& copied) {
	urlSize = copied.urlSize;
	url = new char[urlSize];
	for (int i = 0; i < urlSize; i++) {
		url[i] = copied.url[i];
	}
}

/*Destructor*/
WebAddressInfo::~WebAddressInfo() {
	delete[] url;
	url = NULL;
}

/*Overloaded operator=*/
void WebAddressInfo::operator=(const WebAddressInfo & copied) {
	if (url != NULL) {
		delete[] url;
	}
	urlSize = copied.urlSize;
	url = new char[urlSize];
	for (int i = 0; i < urlSize; i++) {
		url[i] = copied.url[i];
	}
}


/*sets webAddressInfo*/
void WebAddressInfo::setWebAddressInfo(char* inputString) {
	int i = 0;
	//copies inputString to url
	do {
		url[i] = inputString[i];
		i++;
	} while (inputString[i] != '\0');
	url[i] = '\0';   //adds \0 to the last valid position in url
}

/*gets webAddressInfo*/
char* WebAddressInfo::getWebAdressInfo() {
	return url;
}

/*prints webAddress info*/
void WebAddressInfo::display() {
	int i = 0;
	//print each character of the url
	do {
		std::cout << url[i];
		i++;
	} while (url[i] != '\0');
}

/*Overloaded ostream operator <<*/
std::ostream& operator<<(std::ostream & s, WebAddressInfo & ac) {
	s << "\"";
	int i = 0;
	while (ac.url[i] != '\0') {
		s << ac.url[i];
		i++;
	}
	s << "\"";
	return s;
}

/*==========================================================================================================================================*/
/*=============================================================CLASS BrowserTab=============================================================*/

/*
**This class contains a maximum of 20 addresses for one specific tab
**storing how many addresses you have (numAddresses), storing the info of
**each address in the webAddresses array and the index of the webAddress
**array of the currentAddress being shown on the browser
*/

class BrowserTab {
protected:
	int maxNumAddresses;
	int currentAddress;					    //index of current adress in webAdresses
public:
	int numAddresses;						//current number of addresses in this tab
	WebAddressInfo* webAddresses;		    //web addresses in this tab (maximum of 20)

	BrowserTab();
	BrowserTab(char* inputString);
	BrowserTab(BrowserTab& copied);
	~BrowserTab();
	void copy(const BrowserTab& copied);
	void operator=(const BrowserTab& ac);
	void foward();
	void backward();
	void addAddress(char* inputString);
	void change(char* inputString);
	void display();
	friend std::ostream& operator<< (std::ostream& s, BrowserTab& ac);
};

/*default constructor*/
BrowserTab::BrowserTab() {
	maxNumAddresses = 20;								//not fixed maxNumAddresses
	webAddresses = new WebAddressInfo[maxNumAddresses]; //dynamically initializing array
	currentAddress = -1;		// -1 because addAddress increments currentAddress when it adds a new address, so the position in the array should be 0
	numAddresses = 0;			// initially 0 addresses
}

/*constructor*/
BrowserTab::BrowserTab(char* inputString) {
	maxNumAddresses = 20;								//not fixed maxNumAddresses
	webAddresses = new WebAddressInfo[maxNumAddresses]; //dynamically initializing array
	currentAddress = 0;							//sets the current address to position 0 in webAddresses
	numAddresses = 1;							//since it adds an address, the numAddresses is 1
	webAddresses[0].setWebAddressInfo(inputString);	//sets the webAddress's info in position 0 of webAddresses with inputString
}

/*Copy constructor*/
BrowserTab::BrowserTab(BrowserTab & copied) {
	maxNumAddresses = copied.maxNumAddresses;
	numAddresses = copied.numAddresses;
	currentAddress = copied.currentAddress;
	webAddresses = new WebAddressInfo[maxNumAddresses];
	for (int i = 0; i < maxNumAddresses; i++) {
		webAddresses[i] = copied.webAddresses[i];
	}
}

/*Destructor*/
BrowserTab::~BrowserTab() {
	delete[] webAddresses;
	webAddresses = NULL;
}

/*Copy method*/
void BrowserTab::copy(const BrowserTab& copied) {
	maxNumAddresses = copied.maxNumAddresses;
	numAddresses = copied.numAddresses;
	currentAddress = copied.currentAddress;
	webAddresses = new WebAddressInfo[maxNumAddresses];
	for (int i = 0; i < maxNumAddresses; i++) {
		webAddresses[i] = copied.webAddresses[i];
	}
}

/*Overloaded operator =*/
void BrowserTab::operator=(const BrowserTab& ac) {
	if (webAddresses != NULL) {
		delete[] webAddresses;
	}
	copy(ac);
}


/*goes to next address*/
void BrowserTab::foward() {

	//there are numAddresses, thus for a next address exist, currentAddress must be smaller than
	//numAddresses - 1, because currentAddress is an index and numAddresses is a lenght
	if (currentAddress < numAddresses - 1) {
		currentAddress++;
		std::cout << "Successfully moved forward to url: " << webAddresses[currentAddress] << std::endl;
	}
	else {
		std::cout << "cannot go forward" << std::endl;
	}
}

/*goes to previous address*/
void BrowserTab::backward() {
	int previousAddress = currentAddress - 1;
	if (previousAddress < 0) {
		std::cout << "cannot go back" << std::endl;
	}
	else {
		currentAddress--;
		std::cout << "Successfully moved backward to url: " << webAddresses[currentAddress] << std::endl;
	}
}

/*adds an address to webAddresses*/
void BrowserTab::addAddress(char* inputString) {
	if (numAddresses < maxNumAddresses) {
		currentAddress++;	                                             //when you add an address on the browser, you change your current address
		numAddresses = currentAddress + 1;                               //update the numAddresses currentAddress + previousOnes (+1 because of index 0)
		WebAddressInfo* webAddressPtr = new WebAddressInfo(inputString); //new webAddressInfo
		webAddresses[currentAddress] = *webAddressPtr;                   //add webAddressInfo to array
		int nextAddress = currentAddress + 1;
		/*
		**all addresses in next positions should be emptyied, but instead I made all of them point to the current address.
		**Anyway, the only accessed webAddresses are from 0 to currentAddress (but just in case)
		*/
		for (int i = nextAddress; i < 20; i++) {
			webAddresses[i] = *webAddressPtr;
		}
		(*webAddressPtr).~WebAddressInfo();                               //Destruct temporary pointer
	}
	else {
		maxNumAddresses = 2 * maxNumAddresses;                                //if the user adds more than the current maxNumAddresses, double the max quantity allowed	
		WebAddressInfo* tempWebAddresses = new WebAddressInfo(*webAddresses); //use copy constructor to copy previous webAddressInfo to a temporaty array WebAddresses
		delete[] webAddresses;                                                //delete old instance of webAddresses
		webAddresses = tempWebAddresses;                                      //point webAddresses to temporary array of webAddresses making them the current webAddresses
		tempWebAddresses = NULL;                                              //make tempWebAddresses point to nothing
		BrowserTab::addAddress(inputString);                                   //Add the new webAddress to webAddresses which now has double the size
	}
}

/*Prints info of all webAddresses on tab*/
void BrowserTab::display() {
	//for all addresses in webAddress array
	for (int i = 0; i < numAddresses; i++) {
		//prints URL: and calls webInfo::display and after that prints a new line
		std::cout << "URL: " << webAddresses[i];
		std::cout << std::endl;
	}
}

/*Overloaded ostream operator <<*/
std::ostream& operator<< (std::ostream& s, BrowserTab& ac) {
	for (int i = 0; i < ac.numAddresses; i++) {
		s << "URL: " << ac.webAddresses[i];
		s << std::endl;
	}
	return s;
}

/*Change current webAddressInfo of current tab*/
void BrowserTab::change(char* inputString) {
	webAddresses[currentAddress].~WebAddressInfo();
	WebAddressInfo* newWebAddress = new WebAddressInfo(inputString);
	webAddresses[currentAddress] = *newWebAddress;
}

/*==========================================================================================================================================*/
/*==============================================================CLASS Browser===============================================================*/

/*
**I am going to add a PDF explaining the reason why I created this class
** Basically the class BrowserTab stores a collection of webAddresses (its historic).
** But Project 2 requires deletion of entire tabs from the list of tabs and movement
** among tabs. To do so the way it is required in the assignment (within the BrowserTab class)
** is impossible, using my design in Project 1, since in Project 1 my collection
** of tabs (an array of BrowserTabs) was in the main function of the program.
*/

class Browser {
public:
	int bufferSize;         //size of buffer
	char* buffer;			//buffer to get the WebAddress
	int numTabs;			//Number of tabs
	int tabNumber;          //current tab number being operated at
	BrowserTab* myTabs;		//array of Tabs dynamically allocated (but not taking advantage of this, still using 20 tabs at most)
	Browser();
	Browser(const BrowserTab & inputTab);
	Browser(const Browser& copied);
	void copy(const Browser & copied);
	void operator=(const Browser & ac);
	friend std::ostream& operator<< (std::ostream& s, Browser& ac);
	~Browser();
	void moveTab(int tabNumber2);
	void removeTab();
};

/*Default constructor*/
Browser::Browser() {
	bufferSize = 256;
	numTabs = 21;
	tabNumber = 0;
	buffer = new char[bufferSize];
	myTabs = new BrowserTab[numTabs];
}

/*Initializer constructor*/
Browser::Browser(const BrowserTab& inputTab) {
	bufferSize = 256;
	numTabs = 21;
	tabNumber = 0;
	buffer = new char[bufferSize];
	myTabs = new BrowserTab[numTabs];
	myTabs[tabNumber] = inputTab;
}

/*Copy constructor*/
Browser::Browser(const Browser& copied) {
	bufferSize = copied.bufferSize;
	numTabs = copied.numTabs;
	tabNumber = copied.tabNumber;
	for (int i = 0; i < bufferSize; i++) {
		buffer[i] = copied.buffer[i];
	}
	for (int i = 0; i < numTabs; i++) {
		myTabs[i] = copied.myTabs[i];
	}
}

/*Copy method*/
void Browser::copy(const Browser& copied) {
	bufferSize = copied.bufferSize;
	numTabs = copied.numTabs;
	tabNumber = copied.tabNumber;
	for (int i = 0; i < bufferSize; i++) {
		buffer[i] = copied.buffer[i];
	}
	for (int i = 0; i < numTabs; i++) {
		myTabs[i] = copied.myTabs[i];
	}
}

/*Overloaded operator =*/
void Browser::operator= (const Browser& ac) {
	if (myTabs != NULL) {
		delete[] myTabs;
	}
	if (buffer != NULL) {
		delete[] buffer;
	}
	copy(ac);
}

/*Overloaded ostream operator <<*/
std::ostream& operator<< (std::ostream& s, Browser& ac) {
	s << ac.myTabs[ac.tabNumber] << std::endl;
	return s;
}

/*Destructor*/
Browser::~Browser() {
	delete[] buffer;
	buffer = NULL;
	delete[] myTabs;
	myTabs = NULL;
}

/*
**Move tab in index tabNumber to the position right in front of tabNumber2
**I am going to add a PDF file describing how I interpreted this
*/
void Browser::moveTab(int tabNumber2) {
	BrowserTab* temp = new BrowserTab();
	*temp = myTabs[tabNumber];             //get tab info which is at index tabNumber

	/*
	**If tabNumber is after tabNumber2 get all tabs since tabNumber2 and shift them one position to the left until you
	**reach the element at index tabNumber - 1 (shifted to position tabNumber). Then put temp at position tabNumber2.
	*/
	if (tabNumber > tabNumber2) {
		for (int i = tabNumber - 1; i > tabNumber2; i--) {
			myTabs[i + 1] = myTabs[i];
		}
		myTabs[tabNumber2] = *temp;
	}
	/*
	**Else, shift all elements that are greater than tabNumber and smaller than tabNumber2 one position to the right.
	**Then put temp at position tabNumber2 -1.
	*/
	else {
		for (int i = tabNumber + 1; i < tabNumber2; i++) {
			cout << myTabs[i - 1] << endl;
			myTabs[i - 1] = myTabs[i];
		}
		myTabs[tabNumber2 - 1] = *temp;
	}

	(*temp).~BrowserTab();   //destruct temp
}

/*Remove the tab in position tabNumber*/
void Browser::removeTab() {
	for (int i = tabNumber + 1; i < numTabs; i++) {
		myTabs[i] = myTabs[i - 1];
	}
}

/*==========================================================================================================================================*/
/*===================================================================MAIN===================================================================*/

int main() {
	Browser* browserInstance = new Browser();            //instantiates a browser object (a collection of browserTabs)
	char blank;
	char action;
	int tabNumber2 = 0;

	while (!cin.eof()) {		                        //read until the end of the file

		try {
			cin >> (*browserInstance).tabNumber;		//get the tabNumber
														/* Throws an exception if the user try to add more than 20 tabs or a tab in a negative index*/
			if ((*browserInstance).tabNumber > (*browserInstance).numTabs || (*browserInstance).tabNumber < 0) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the rest of the line
				throw TabBoundsException();
			}
		}
		catch (TabBoundsException myexception) {
			cout << "Tab bound exception" << std::endl;
			cout << '\n';
		}

		cin.get(blank);			//get a blank space
		cin.get(action);		//get action character

		try {
			/* Throws an exception if the user selects an undefined action*/
			if (action != 'N' && action != 'F' && action != 'B' && action != 'P' && action != 'M' && action != 'R' && action != 'C') {
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the rest of the line
				throw UndefinedActionException();
			}

			switch (action) {
			case 'N':
				cout << "Action: add (N) on tab " << (*browserInstance).tabNumber << endl;
				cin.get(blank);			//get a blank character
				cin.getline((*browserInstance).buffer, (*browserInstance).bufferSize); //put the rest of the line on buffer
				(*browserInstance).myTabs[(*browserInstance).tabNumber].addAddress((*browserInstance).buffer); //add address to browserTab in position tabNumber on myTabs
				cout << "\"" << (*browserInstance).buffer << "\" successfully added on tab " << (*browserInstance).tabNumber << endl;
				cout << "\n";
				break;
			case 'F':
				cout << "Action: forward (F) on tab " << (*browserInstance).tabNumber << endl;
				(*browserInstance).myTabs[(*browserInstance).tabNumber].foward();     //move forward on myTabs if there is an webAddressInfo stored in next index
				cout << "\n";
				break;
			case 'B':
				cout << "Action: backward (B) on tab " << (*browserInstance).tabNumber << endl;
				(*browserInstance).myTabs[(*browserInstance).tabNumber].backward();   //move backward on myTabs if there is an webAddressInfo stored in next index
				cout << "\n";
				break;
			case 'P':
				cout << "Action: print (P) tab " << (*browserInstance).tabNumber << endl;
				cout << (*browserInstance);   //print all the webAddressInfo's stored in current tab using the overloaded operator << for Browser class
				break;
			case 'M':
				cout << "Action: move (M) tab " << (*browserInstance).tabNumber << endl;
				cin.get(blank);               //get a blank character
				cin >> tabNumber2;            //get the tab to index of the tab to be moved
				/*
				**Move tab to be moved to the position right before (in the left) of tab that is in position tabNumber.
				**I am going to add a pdf file explaining how I interpreted this
				*/
				(*browserInstance).moveTab(tabNumber2);
				cout << "Moved successfully" << std::endl;
				cout << "\n";
				break;
			case 'R':
				cout << "Action: remove (R) tab " << (*browserInstance).tabNumber << endl;
				(*browserInstance).removeTab();   //remove tab
				cout << "Removed successfully" << std::endl;
				cout << "\n";
				break;
			case 'C':
				cout << "Action: change (C) on tab " << (*browserInstance).tabNumber << endl;
				cin.get(blank);			                                                                   //get a blank character
				cin.getline((*browserInstance).buffer, (*browserInstance).bufferSize);                     //puts the rest of the line on buffer
				(*browserInstance).myTabs[(*browserInstance).tabNumber].change((*browserInstance).buffer); //change current tab to the new address
				cout << "Successfully changed current url to: " << (*browserInstance).buffer << endl;
				cout << "\n";
				break;
			}
		}
		catch (UndefinedActionException exception) {
			cout << "Illegal action" << std::endl;  //Option added is undefined
			cout << "\n";
		}

	}
	return 0;
}