///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 12. 19. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////
#pragma once

#include <ctime>

#include "Manager.h"
#include "TimeManager.h"
#include "Reserver.h"

namespace biseul_rroom {
	/// Basic class for the Seat
		/// This contains reserver's info (basically on reserver class)
		/// Time info about reserved time, left time of pausing
		/// class generates its reserved_time automatically
	class Seat {
	public:
		Seat() {};
		Seat(Reserver* reserver, SeatStatus status, int reserve_hour, int pause_minutes);
		Seat(Reserver* reserver, SeatStatus status, tm reserved_time, tm reserve_end_time, int pause_minutes);
		virtual ~Seat();

		Reserver* get_reserver();
		SeatStatus get_status();
		int get_pause_time();
		tm* get_reserved_time() { return &reserved_time; };
		tm* get_reserve_end_time() { return &reserve_end_time; };

		tm vget_reserved_time() { return reserved_time; };
		tm vget_reserve_end_time() { return reserve_end_time; };

		void setStatus(SeatStatus);
		void add_time_hour(int);
		void minus_pause_time();

		bool before_minutes(int minutes);
		bool over_time();

	private:
		Reserver* seat_reserver = nullptr;     //reserver class that contains info
		SeatStatus status = SeatStatus::Vacant;//seat status of reservation
		struct tm reserved_time = { 0 };
		struct tm reserve_end_time = { 0 };
		int pause_minutes_left = 240; //240min = 4 hrs

	};
}