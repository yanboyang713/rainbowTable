/*****************************************************************************
//Student's Name: Boyang YAN
//Student's email address: by932@uowmail.edu.au
//Last modification: 03/08/2016
****************************************************************************/
#include <iostream>
#include "md5.h"
#include "rainbowTable.h"
#include "pwdUsedRecord.h"
#include <string>
using std::cout; using std::endl;
bool checkMD5Length(string);
int main(int argc, char *argv[])
{
	//initial computations to generate the rainbow table
	PwdUserdRecord passwordUserdRecord;
	passwordUserdRecord.pushPossiblePWDinRecord(argc, argv);
	//rainbow	
	rainbowTable rainbow;
	rainbow.generateRainbowTable(passwordUserdRecord);	
	rainbow.sort();
	rainbow.outputRainbowTabToFile(rainbow, "Rainbow.txt");
	
	//finding pre-images
	string hashInput;
	do
        	std::cout << "Please input MD5 hash value for find pre-image: ";
        while (std::cin >> hashInput && checkMD5Length(hashInput));
	rainbow.searchPreImage(hashInput, passwordUserdRecord);
    return 0;
}
bool checkMD5Length(string MD5)
{
	if (MD5.length() != 32)
	{
		cout << "This is not MD5 :(" << endl << endl;
		return true;
	}
	return false;
}

