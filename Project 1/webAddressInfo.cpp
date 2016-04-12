#include "webAddressInfo.h"
#include <iostream>

/*default constructor*/
webAddressInfo::webAddressInfo() {
	//creates a null array
	for (int i = 0; i < 201; i++) {
		url[i] = '\0';
	}
}

/*constructor*/
webAddressInfo::webAddressInfo(char* inputString) {
	int i = 0;
	//copies inputString to url
	do {
		url[i] = inputString[i];
		i++;
	} while (inputString[i] != '\0');
	url[i] = '\0';	//adds \0 to the last valid position in url
}

/*sets webAddressInfo*/
void webAddressInfo::setWebAddressInfo(char* inputString) {
	int i = 0;
	//copies inputString to url
	do {
		url[i] = inputString[i];
		i++;
	} while (inputString[i] != '\0');
	url[i] = '\0';   //adds \0 to the last valid position in url
}

/*gets webAddressInfo*/
char* webAddressInfo::getWebAdressInfo() {
	return url;
}

/*prints webAddress info*/
void webAddressInfo::display() {
	int i = 0;
	//print each character of the url
	do {
		std::cout << url[i];
		i++;
	} while (url[i] != '\0');
}
