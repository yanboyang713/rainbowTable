/*****************************************************************************
//Student's Name: Boyang YAN
//Student's email address: by932@uowmail.edu.au
//Last modification: 03/08/2016
****************************************************************************/
#ifndef PWDUSEDRECORD_H
#define PWDUSEDRECORD_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct pwdRecordStr
{
	int id;
	string pwd;
	bool used;
};
class PwdUserdRecord
{
	public:
		PwdUserdRecord();
		~PwdUserdRecord();
		void pushPossiblePWDinRecord(int, char *[]);
		std::vector<pwdRecordStr> getRecord() const;
		void changeUsedStateToUsed(int);
		string getPassword(int) const;
		int findFirstUnused();
		void setFirstUnused(int);
		unsigned int getVectorSize() const;
		void checkLoop(bool &, int);
		friend std::ostream& operator << (std::ostream&, PwdUserdRecord&);
		 
	private:
		std::vector<pwdRecordStr> record;
		int firstUnused;
		unsigned int vectorSize;
};
#endif
