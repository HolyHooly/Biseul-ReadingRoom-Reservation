///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////


#include "TimeManager.h"

namespace biseul_rroom {
	void get_local_time(tm& t)
	{
		time_t time_now;
		time(&time_now);
		t = *localtime(&time_now);

	}
	void add_tm_hour(tm& t1, int hour)
	{
		time_t new_time;
		time(&new_time);
		new_time = new_time + hour * (__int64) 3600;
		t1 = *localtime(&new_time);
	}
	TimeManager::~TimeManager()
	{
	}
}