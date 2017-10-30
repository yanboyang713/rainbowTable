/*****************************************************************************
//Student's Name: Boyang YAN
//Student's email address: by932@uowmail.edu.au
//Last modification: 03/08/2016
****************************************************************************/
#ifndef RAINBOWTABLE_H
#define RAINBOWTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include "pwdUsedRecord.h"
using namespace std;
struct rainbowTableStr
{
	string orignal;
	string hash;
	friend std::ostream& operator<<(std::ostream&, rainbowTableStr&);
};
class rainbowTable
{
	public:
		rainbowTable();
		~rainbowTable();
		std::vector<rainbowTableStr> getRecord() const;
		void generateRainbowTable(PwdUserdRecord &);
		string getCurrentHash() const;
		void setCurrentHash(string);
		string getCurrentPwd() const;
		void setCurrentPwd(string);
		int ASCIIreductionFunction(PwdUserdRecord &);
		int HexReductionFunction(PwdUserdRecord &);
		void outputRainbowTabToFile(rainbowTable &, string);
		int hexToDec(string);
		void sort();
		void searchPreImage(string, PwdUserdRecord &);
		bool checkInRainbowTable() const;
		void allRduction(bool &, PwdUserdRecord &);
		friend bool cmp(const rainbowTableStr&, const rainbowTableStr &);
		friend std::ostream& operator << (std::ostream&, rainbowTable&);
		friend std::ostream& operator << (std::ostream&, vector<rainbowTableStr>&);
		friend bool operator <(const rainbowTableStr &, const string&);
		friend bool operator <(const string &, const rainbowTableStr &);
		bool binary_find(std::pair<std::vector<rainbowTableStr>::iterator,std::vector<rainbowTableStr>::iterator> &);
		string getOrignal(rainbowTableStr&) const;
		void reductionAndHashAfterCheckAgain(int &, int &, bool &, PwdUserdRecord &);
				 
	private:
		std::vector<rainbowTableStr> record;
		string currentHash;
		string currentPwd;
};
#endif
