///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////


#include "UserManager.h"


namespace biseul_rroom {

	UserAction UserManger::user_valid_check(int rfid_id)
	{
		//db existence check
		if (true) { //db check result
			int warning = 0; //get_warning from db
			int stud_id = 0; //get from db

			if (warning < 3) {
				//get daily reservation times
				if (reserve_cnt[stud_id] >= 3) return UserAction::OverTime;
				else return UserAction::Pass;
			}
			else return UserAction::Warning;
		}
		else return UserAction::Signup;
	}


	int UserManger::get_user_reserve_cnt(int stud_id)
	{
		return reserve_cnt[stud_id];
	}
}