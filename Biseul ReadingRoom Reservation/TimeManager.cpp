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
		time_t new_time = mktime(&t1);
		new_time = new_time + hour * (__int64) 3600;
		t1 = *localtime(&new_time);
	}

	bool before_min_timemanager(tm& t1, int minutes)
	{
		time_t time_now; 
		time(&time_now); //time of now

		time_t time_end = mktime(&t1); //end time to time_t type

		if (time_end - time_now <= (__int64) 60 * minutes) { //time difference is less or equal than minutes
			return true;
		}
		return false;
	}

	bool over_time_timemanager(tm& t1)
	{
		time_t time_now;
		time(&time_now);

		time_t time_end = mktime(&t1);
		if (time_end < time_now) {
			return true;
		}
		return false;
	}



	TimeManager::~TimeManager()
	{
	}
}