///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 18. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////
#pragma once

#include <string>

namespace biseul_rroom {

	class Reserver { //base class for a person
	public:
		Reserver() {};
		Reserver(const std::string name, const int stud_id, const __int64 rfid_id);
		~Reserver();
		bool operator==(const int) const;
		bool operator==(const Reserver&) const;

		std::string get_name() { return name; }
		int get_stud_id() { return stud_id; }
		__int64 get_rfid_id() { return rfid_id; }

	private:
		std::string name;
		int stud_id = 0;
		__int64 rfid_id = 0;
	};

}