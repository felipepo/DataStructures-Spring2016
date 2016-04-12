#include "browserTab.h"
#include <iostream>

/*default constructor*/
browserTab::browserTab() {		
	currentAddress = -1;		// -1 because addAddress increments currentAddress when it adds a new address, so the position in the array should be 0
	numAddresses = 0;			// initially 0 addresses
}

/*constructor*/
browserTab::browserTab(char* inputString) {		
	currentAddress = 0;							//sets the current address to position 0 in webAddresses
	numAddresses = 1;							//since it adds an address, the numAddresses is 1
	webAddresses[0].setWebAddressInfo(inputString);	//sets the webAddress's info in position 0 of webAddresses with inputString
}

/*goes to next address*/
webAddressInfo& browserTab::foward() {

	//there are numAddresses, thus for a next address exist, currentAddress must be smaller than
	//numAddresses - 1, because currentAddress is an index and numAddresses is a lenght
	if (currentAddress < numAddresses - 1) {	
		currentAddress++;
	}
	return webAddresses[currentAddress];
}

/*goes to previous address*/
webAddressInfo& browserTab::backward() {
	int previousAddress = currentAddress - 1;
	if (previousAddress < 0) {
		std::cout << "cannot go back" << std::endl;
	}
	else {
		currentAddress--;
	}
	return webAddresses[currentAddress];
}

/*adds an address to webAddresses*/
void browserTab::addAddress(char* inputString) {
	if (numAddresses < 20) {  //can't add more than 20 addresses
		currentAddress++;	  //when you add an address on the browser, you change your current address
		numAddresses = currentAddress + 1; //update the numAddresses currentAddress + previousOnes (+1 because of index 0)
		webAddressInfo* webAddressPtr = new webAddressInfo(inputString); //new webAddressInfo
		webAddresses[currentAddress] = *webAddressPtr;                   //add webAddressInfo to array
		int nextAddress = currentAddress + 1;
		//all addresses in next positions should be emptyied, but instead I made all of them point to the current address
		//anyway, the only accessed webAddresses are from 0 to currentAddress (but just in case)
		for (int i = nextAddress; i < 20; i++) {
			webAddresses[i] = *webAddressPtr;
		}
	}
}

/*Prints info of all webAddresses on tab*/
void browserTab::display() {
	//for all addresses in webAddress array
	for (int i = 0; i < numAddresses; i++) {
		//prints URL: and calls webInfo::display and after that prints a new line
		std::cout << "URL: ";
		webAddresses[i].display();
		std::cout << std::endl;
	}
}

