///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 18. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

# include <string>
#include "Reserver.h"

biseul_rroom::Reserver::Reserver(__int64 rfid_id) :
	rfid_id(rfid_id)
{
	//db로부터 찾아서 자동으로 생성해주기
}

biseul_rroom::Reserver::Reserver(std::string name, int stud_id, __int64 rfid_id) :
	name(name), stud_id(stud_id), rfid_id(rfid_id)
{

}

biseul_rroom::Reserver::~Reserver()
{

}

bool biseul_rroom::Reserver::operator==(const int input) const    //compare with student id
{
	if (stud_id == input) return true;
	return false;
}

bool biseul_rroom::Reserver::operator==(const Reserver& input) const    //compare both student id and rfid
{
	if (stud_id == input.stud_id && rfid_id == input.rfid_id) return true;
	return false;
}


