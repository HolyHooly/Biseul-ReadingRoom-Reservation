///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#pragma once


#include "Manager.h"
#include "DBInterface.h"
#include "DBsystem.h"

namespace biseul_rroom {


	/// counts student's reservation times in a day
	/// This is for blocking multi-time reservation per a day
	class UserManger : public Manager {
	public:
		// singleton
		static UserManger& instance() {
			static UserManger* instance = new UserManger();
			return *instance;
		}
		virtual ~UserManger() {};

		/// validating user's permission to reserve new seat
		/// it includes 1) existence check 2) warning check 3) reserve count check
		/// returns each action value: Signup, Warning, OverTime, or Pass
		/// parm: (int)rfid_id
		/// return: (UserAction)
		UserAction user_valid_check(__int64, DBinterface*); //rfid_id as an input

		//parm: (int) stud_id
		int get_user_reserve_cnt(__int64 rfid_id);
		int available_reserve_hour(__int64 rfid_id);
		int get_user_pause_left(__int64 rfid_id);

		void add_user_reserve_cnt(__int64 rfid_id);

		void reset_all();

	private:
		UserManger() {};

		//counts student's reservation times in a day
		//This is for blocking multi-time reservation per a day
		std::map<__int64, int> reserve_cnt; // <rfid_id, cnt>
		std::map<__int64, int> pause_left; // <rfid_id, pause_left>

	};


}