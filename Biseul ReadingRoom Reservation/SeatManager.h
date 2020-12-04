///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#pragma once

#include "Manager.h"
#include "Reserver.h"
#include "TimeManager.h"

#include <ctime>
#include <string>

namespace biseul_rroom {


	/// Basic class for the Seat
	/// This contains reserver's info (basically on reserver class)
	/// Time info about reserved time, left time of pausing
	/// class generates its reserved_time automatically
	class Seat {
	public:
		Seat() {};
		Seat(Reserver* reserver, SeatStatus status, int reserve_hour, int pause_minutes);
		~Seat();

		Reserver* get_reserver();
		SeatStatus get_status();
		int get_pause_time();

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


	/// Manages overall seats
	/// provides seat control functions
	class SeatManager : public Manager {
	public:
		//singleton
		static SeatManager& instance() {
			static SeatManager* instance = new SeatManager();
			return *instance;
		}
		~SeatManager();

		SeatStatus seat_status_check(int); //seat number as an input
		Seat* create_seat(Reserver* reserver, int hour, int pause);
		Seat* get_seat(int num);
		void delete_seat(int num);

		void reserve_seat(int num, std::string name, int stud_id, __int64 rfid_id, int hour, int pause);
		void return_seat(int);
		void renew_seat(int, int);
		void pause_seat(int);
		void unpause_seat(int);
		void move_seat(int, int);

		int find_seat(__int64 rfid_id);

	private:
		SeatManager() {};

		int _seat_cnt = 0;
		Seat* rroom_seat[READINGROOM_SEAT] = { nullptr, }; //total 124 seats in the reading room


	};
}