/*
**This program simulates some actions performed in a browser
*/

#include <iostream>
#include "webAddressInfo.h"
#include "browserTab.h"

using namespace std;


int main() {
	char buffer[256];
	browserTab myTabs[20];		//array of Tabs

	int tabNumber;
	char blank;
	char action;
	char* url;

	while (!cin.eof()) {		//read until the end of the file

		cin >> tabNumber;		//get the tabNumber
		cin.get(blank);			//get a blank space
		cin.get(action);		//get action character

		switch (action) {
		case 'N':
			cout << "Action: add (N) on tab " << tabNumber << endl;
			cin.get(blank);			//get a blank character
			cin.getline(buffer, 256); //puts the rest of the line on buffer
			myTabs[tabNumber].addAddress(buffer); //add address to browserTab in position tabNumber on myTabs
			cout << "\"" << buffer << "\" successfully added on tab " << tabNumber << endl;
			cout << "\n";
			break;
		case 'F':
			cout << "Action: forward (F) on tab " << tabNumber << endl;
			url = myTabs[tabNumber].foward().getWebAdressInfo();   //gets url of forward address of browserTab in position tabNumber on myTabs
			cout << "Successfully moved forward to url: " << url << endl;
			cout << "\n";
			break;
		case 'B':
			cout << "Action: backward (B) on tab " << tabNumber << endl;
			url = myTabs[tabNumber].backward().getWebAdressInfo(); //gets url of backard address of browserTab in position tabNumber on myTabs
			cout << "Successfully moved backward to url: " << url << endl;
			cout << "\n";
			break;
		case 'P':
			cout << "Action: print (P) tab " << tabNumber << endl;
			myTabs[tabNumber].display(); //calls browserTab::display() for browserTab in position tabNumber on myTabs
			cout << "\n";
			break;
		default:
			cout << "Illegal action";  //no other options
			cout << "\n";
		}
		
	}
	return 0;
}