///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////


#include "UserManager.h"


namespace biseul_rroom {

	UserAction UserManger::user_valid_check(__int64 rfid_id)
	{
		//db existence check
		if (true) { //db check result
			int warning = 0; //get_warning from db

			if (warning < 3) {
				//get daily reservation times
				if (reserve_cnt[rfid_id] >= 3) return UserAction::OverTime;
				else return UserAction::Pass;
			}
			else return UserAction::Warning;
		}
		else return UserAction::Signup;
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
	int UserManger::get_user_pause_left(int stud_id)
	{
		return pause_left[stud_id];
	}
}