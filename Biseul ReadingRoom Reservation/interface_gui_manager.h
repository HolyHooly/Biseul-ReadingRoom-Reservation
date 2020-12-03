///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 26. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#pragma once
#include "Manager.h"
#include "Reserver.h"
#include "SeatManager.h"
#include "UserManager.h"
#include "TimeManager.h"

namespace biseul_rroom {

	void seat_button_click(int);
	void pause_button_click(int);
	void renew_button_click(int);
	void return_button_click(int);

	void signup_button_click();
	void admin_button_click();
}