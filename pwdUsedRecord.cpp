/*****************************************************************************
//Student's Name: Boyang YAN
//Student's email address: by932@uowmail.edu.au
//Last modification: 03/08/2016
****************************************************************************/
#include "pwdUsedRecord.h"
#include <fstream>
#include <iostream>
using namespace std;
PwdUserdRecord::PwdUserdRecord()
{
	firstUnused = 0;
	vectorSize = 0;
}
PwdUserdRecord::~PwdUserdRecord()
{

}
void PwdUserdRecord::pushPossiblePWDinRecord(int argc, char *argv[])
{
	ifstream pwdFile;
	pwdFile.open (argv[1]);
	int index = 0;
	pwdRecordStr recordOne;
	if (pwdFile.is_open())
	{
		while ( !pwdFile.eof())
		{
			pwdFile >> recordOne.pwd;
			if (!pwdFile.good())
			{
				vectorSize = record.size();
				return;
			}
			recordOne.id = index;
			recordOne.used = false;
			record.push_back(recordOne);
			index++;
		}
    		pwdFile.close();
	}
	else cout << "Unable to open file" << endl;
	vectorSize = record.size();
	return;
}
void PwdUserdRecord::changeUsedStateToUsed(int which)
{
	record[which].used = true;
	return;
}
int PwdUserdRecord::findFirstUnused()
{
	for (unsigned int i = firstUnused; i < vectorSize; i++)
	{
		if (record[i].used == false)
		{
			setFirstUnused(i);
			return i;
		}
	}
	return -1;//all of password have used
}
void PwdUserdRecord::setFirstUnused(int which)
{
	firstUnused = which;
	return;
}
string PwdUserdRecord::getPassword(int which) const
{
	return record[which].pwd;
}
unsigned int PwdUserdRecord::getVectorSize() const
{
	return vectorSize;
}
std::vector<pwdRecordStr> PwdUserdRecord::getRecord() const
{
	return record;
}
std::ostream& operator<<(std::ostream& out, PwdUserdRecord& print)
{
	for (unsigned int i=0; i < print.getVectorSize(); i++)
	{
		out << print.getRecord()[i].id << '\t';
		out << print.getRecord()[i].pwd << '\t';
		out << print.getRecord()[i].used << '\t';
		out << endl;
	}
    	return out;
}
void PwdUserdRecord::checkLoop(bool &findError, int which)
{
	if (record[which].used == false)
		findError = true;
	else
		record[which].used = false;
	return;
}
