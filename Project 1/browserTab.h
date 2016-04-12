#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include "webAddressInfo.h"

/*
*This class contains a maximum of 20 addresses for one specific tab
*storing how many addresses you have (numAddresses), storing the info of 
each address in the webAddresses array and the index of the webAddress 
*array of the currentAddress being shown on the browser */

class browserTab {
protected:
	int numAddresses;						//current number of addresses in this tab
	webAddressInfo webAddresses[20];		//web addresses in this tab (maximum of 20)
	int currentAddress;						//index of current adress in webAdresses
public:
	browserTab();
	browserTab(char* inputString);
	webAddressInfo& foward();
	webAddressInfo& backward();
	void addAddress(char* inputString);
	void display();
};

#endif
