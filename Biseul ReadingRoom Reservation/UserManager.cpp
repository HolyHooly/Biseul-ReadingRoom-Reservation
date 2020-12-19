///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////


#include "UserManager.h"


namespace biseul_rroom {

	UserAction UserManger::user_valid_check(__int64 rfid_id, DBinterface* db_interface)
	{
		if (db_interface->existence_check_byrfid(rfid_id)) { //db check result
			std::string name;
			std::string* nameptr = &name;
			int stud_id;
			int warnings;
			db_interface->get_studinf_byrfid(nameptr, stud_id, rfid_id, warnings);

			if (warnings < 3) {
				//get daily reservation times
				if (reserve_cnt[rfid_id] >= 3) return UserAction::OverTime;
				else return UserAction::Pass;
			}
			else return UserAction::Warning; //warning exceed
		}
		else return UserAction::Signup; //not signed up
	}


	int UserManger::get_user_reserve_cnt(__int64 rfid_id)
	{
		return reserve_cnt[rfid_id];
	}

	int UserManger::available_reserve_hour(__int64 rfid_id)
	{
		int cnt = reserve_cnt[rfid_id];
		if (cnt == 0) return 5; // 5 hours available
		else if (cnt < 3 && cnt >0) return 3; // 3 hours available
		else return 0;
	}
	int UserManger::get_user_pause_left(__int64 rfid_id)
	{
		//할것: 처음예약시 바꿀것
		auto it = pause_left.find(rfid_id);
		if (it == pause_left.end()) {
			pause_left[rfid_id] = 240;
		}
		return pause_left[rfid_id];
	}
	void UserManger::add_user_reserve_cnt(__int64 rfid_id)
	{
		++reserve_cnt[rfid_id];
	}
	void UserManger::reset_all()
	{
		reserve_cnt.clear();
		pause_left.clear();
	}
}