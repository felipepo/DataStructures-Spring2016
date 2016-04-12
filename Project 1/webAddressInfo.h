#ifndef WEBADDRESSINFO_H
#define WEBADDRESSINFO_H

/*Stores information of one webAddress*/
class webAddressInfo {
private:
	char url[201];		//array of a maximum of 200 characters for url
public:
	webAddressInfo();
	webAddressInfo(char* inputString);
	void setWebAddressInfo(char* inputString);
	char* getWebAdressInfo();
	void display();
};

#endif