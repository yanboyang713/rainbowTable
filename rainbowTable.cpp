/*****************************************************************************
//Student's Name: Boyang YAN
//Student's email address: by932@uowmail.edu.au
//Last modification: 03/08/2016
****************************************************************************/
#include "rainbowTable.h"
#include "pwdUsedRecord.h"
#include "md5.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
rainbowTable::rainbowTable()
{

}
rainbowTable::~rainbowTable()
{

}
void rainbowTable::generateRainbowTable(PwdUserdRecord &passwordUserdRecord)
{
	unsigned int sz = passwordUserdRecord.getVectorSize();
	rainbowTableStr recordOne;
	for (unsigned int m = 0; m < sz; m++)
	{
		//get and put first unused password, make it used
		int pwd = passwordUserdRecord.findFirstUnused();
		if (pwd == -1)//all password have used
			return;		
		recordOne.orignal = passwordUserdRecord.getPassword(pwd);
		passwordUserdRecord.changeUsedStateToUsed(pwd);//change Used State To Used
		for (int i = 0; i < 3; i++)
		{
			//Apply the hash function H to the word W to produce a hash
			//value H(W ), which we refer to as the current hash	
			setCurrentHash(md5(passwordUserdRecord.getPassword(pwd)));
			//Apply the reduction function R to the current hash,
			// which will give a different possible password
			pwd = HexReductionFunction(passwordUserdRecord);
			//marked as used
			passwordUserdRecord.changeUsedStateToUsed(pwd);
		}
		//hashed and the resulting hash value is recorded as the
		//current hash
		setCurrentHash(md5(passwordUserdRecord.getPassword(pwd)));
		//put orignal and hash to rainbowTable
		recordOne.hash = getCurrentHash();
		record.push_back(recordOne);
	}
	return;
}
int rainbowTable::ASCIIreductionFunction(PwdUserdRecord &passwordUserdRecord)
{
	int hashASCII = atoi(getCurrentHash().c_str());
	return hashASCII % passwordUserdRecord.getRecord().size();
}
int rainbowTable::HexReductionFunction(PwdUserdRecord &passwordUserdRecord)
{
	std::vector<pwdRecordStr>::size_type sz = passwordUserdRecord.getVectorSize();
	
	int recordCount = sz;
	//find the length of an integer
	int numberOfDigits = 0;
	do {
	     ++numberOfDigits; 
	     sz /= 10;
	} while (sz);
	int output = hexToDec(getCurrentHash().substr(0, numberOfDigits - 1));
	return output % recordCount;
}
bool cmp(const rainbowTableStr& lhs, const rainbowTableStr & rhs)
{
	return lhs.hash < rhs.hash;
}
void rainbowTable::sort()
{
	std::sort(record.begin(), record.end(), cmp);
	return;
}
void rainbowTable::searchPreImage(string hashInput, PwdUserdRecord &passwordUserdRecord) //hashInput is user input hash for find preImage
{
	int whichPwd = 0;
	bool exit = false;
	int reductionTime = 1;	
	std::pair<std::vector<rainbowTableStr>::iterator, std::vector<rainbowTableStr>::iterator> bounds;	
	setCurrentHash(hashInput);	
	do
	{
		if (binary_find(bounds))
		{
			int sameHashAmount = std::distance(record.begin(), bounds.second) - std::distance(record.begin(), bounds.first);
			for (int i = 0; i < sameHashAmount; i++)
			{
				setCurrentPwd(getOrignal(*(bounds.first + i)));
				setCurrentHash(md5(getCurrentPwd()));
				if (hashInput == getCurrentHash())
				{
					cout << "Great, find pre-image: " << getCurrentPwd() << endl;
					return;
				}
				else
				{
					int oneLineReductionTime = 1;
					do
					{
						whichPwd = HexReductionFunction(passwordUserdRecord);
						setCurrentPwd(passwordUserdRecord.getPassword(whichPwd));
						setCurrentHash(md5(getCurrentPwd()));
						if (hashInput == getCurrentHash())
						{
							cout << "Great, find pre-image: " << getCurrentPwd() << endl;
							return;
						}
						oneLineReductionTime++;
					}while(oneLineReductionTime < 4);			
				}
			}
			reductionAndHashAfterCheckAgain(reductionTime, whichPwd, exit, passwordUserdRecord);			
		}
		else//not found
			reductionAndHashAfterCheckAgain(reductionTime, whichPwd, exit, passwordUserdRecord);
	}while(exit == false);
	if (exit == true)
		cout << "Can not find pro-image :(" << endl;
	return;
}
void rainbowTable::reductionAndHashAfterCheckAgain(int & reductionTime, int & whichPwd, bool & exit, PwdUserdRecord &passwordUserdRecord)//if hash are not in rainbow reduction and hash again
{
	if (reductionTime == 4)
	{
		exit = true;
		return;
	}
	whichPwd = HexReductionFunction(passwordUserdRecord);
	setCurrentHash(md5(passwordUserdRecord.getPassword(whichPwd)));
	reductionTime++;
	return;
}
string rainbowTable::getOrignal(rainbowTableStr& which) const
{
	return which.orignal;
}
void rainbowTable::allRduction(bool &findError, PwdUserdRecord &passwordUserdRecord)
{
	for (unsigned int i = 0; i < passwordUserdRecord.getVectorSize(); i++)
	{
		if (findError == true)
			return;
		if (passwordUserdRecord.getRecord()[i].used == true)
			continue;
	}
	findError = true;
	return;
}
bool operator <(const rainbowTableStr & ms, const string &i)
{
	return ms.hash < i;
}
bool operator <(const string &i, const rainbowTableStr & ms)
{
	return ms.hash > i;
}
bool rainbowTable::binary_find(std::pair<std::vector<rainbowTableStr>::iterator,std::vector<rainbowTableStr>::iterator> & rainbowTableIter)
{
	rainbowTableIter=std::equal_range (record.begin(), record.end(), currentHash);
	if (std::distance(record.begin(), rainbowTableIter.first) != std::distance(record.begin(), rainbowTableIter.second))
		return true; // found
	else
		return false; // not found
		
}
bool rainbowTable::checkInRainbowTable() const
{
	rainbowTableStr findHash = {"", getCurrentHash()};
	if (std::binary_search (record.begin(), record.end(), findHash, cmp)) //found
		return true;
	return false;//not found
}
int rainbowTable::hexToDec(string hex)
{
    int result = 0;
    for (unsigned int i = 0; i < hex.length(); i++)
    {
        if (hex[i] >= 48 && hex[i] <= 57)
            result += (hex[i] - 48) * pow(16.00, static_cast<double>(hex.length() -i -1));
        else if (hex[i] >= 65 && hex[i] <= 70)
            result += (hex[i] - 55) * pow(16.00, static_cast<double>(hex.length() -i -1));
        else if (hex[i] >= 97 && hex[i] <= 102)
            result += (hex[i] - 87) * pow(16.00, static_cast<double>(hex.length() -i -1));
    }
    return result;
}
std::vector<rainbowTableStr> rainbowTable::getRecord() const
{
	return record;
}
std::ostream& operator<<(std::ostream& out, rainbowTableStr& print)
{
	out << print.orignal << '\t';
	out << print.hash;
    	return out;
}
std::ostream& operator<<(std::ostream& out, vector<rainbowTableStr>& print)
{
	std::vector<rainbowTableStr>::size_type sz = print.size();
	for (unsigned int i = 0; i < sz; i++)
		out << print[i];
    	return out;
}
std::ostream& operator << (std::ostream& out, rainbowTable& print)
{
	for (std::vector<rainbowTableStr>::iterator it = print.record.begin(); it != print.record.end(); ++it)
		out << *it << endl;
    	return out;
}
string rainbowTable::getCurrentHash() const
{
	return currentHash;
}
void rainbowTable::setCurrentHash(string hash)
{
	currentHash = hash;
	return;
}
string rainbowTable::getCurrentPwd() const
{
	return currentPwd;
}
void rainbowTable::setCurrentPwd(string pwd)
{
	currentPwd = pwd;
	return;
}
void rainbowTable::outputRainbowTabToFile(rainbowTable &printFile, string fileName)
{
	ofstream outFile;
	outFile.open (fileName.c_str());
	if (outFile.is_open())
	{
		outFile << printFile;
    		outFile.close();
	}
	else cout << "Unable to open file" << endl;
	return;
}
