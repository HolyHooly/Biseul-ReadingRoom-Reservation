///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#pragma once

#include "Manager.h"

#include <ctime>

namespace biseul_rroom {

	class TimeManager : public Manager {
		//스레드 해야댐

	};

	void get_local_time(tm& t);
	void add_tm_hour(tm& t1, int hour);
	

	

}