///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#pragma once


#include "Manager.h"


namespace biseul_rroom {


	/// counts student's reservation times in a day
	/// This is for blocking multi-time reservation per a day
	class UserManger : public Manager {
	public:
		UserManger() {};
		~UserManger() {};

		/// validating user's permission to reserve new seat
		/// it includes 1) existence check 2) warning check 3) reserve count check
		/// returns each action value: Signup, Warning, OverTime, or Pass
		/// parm: (int)rfid_id
		/// return: (UserAction)
		UserAction user_valid_check(int); //rfid_id as an input

		//parm: (int) stud_id
		int get_user_reserve_cnt(int);

	private:
		//counts student's reservation times in a day
		//This is for blocking multi-time reservation per a day
		std::map<int, int> reserve_cnt; // <stud_id, cnt>

	};


}