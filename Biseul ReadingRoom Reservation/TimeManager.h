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
		
	public:
		static TimeManager& instance() {
			static TimeManager* instance = new TimeManager();
			return *instance;
		}
		~TimeManager();

	private:
		TimeManager() {};

	};

	void get_local_time(tm& t);
	void add_tm_hour(tm& t1, int hour);
	bool before_min_timemanager(tm& t1, int minutes);
	bool over_time_timemanager(tm& t1);
	

	

}