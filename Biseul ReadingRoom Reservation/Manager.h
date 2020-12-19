///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////
#pragma once

#include "Reserver.h"

#include <ctime>
#include <string>
#include <map>

#define READINGROOM_SEAT 124

namespace biseul_rroom {

	enum class SeatStatus { Vacant, Occupied, Paused };
	enum class UserAction { Pass, Signup, Warning, OverTime };

	class Manager {
	public:
		virtual ~Manager() {};
	};

	

}