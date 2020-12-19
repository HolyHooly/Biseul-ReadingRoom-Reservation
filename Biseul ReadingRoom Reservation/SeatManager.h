///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 12. 20. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#pragma once

#include "Manager.h"
#include "Reserver.h"
#include "TimeManager.h"

#include "Seat.h"

#include "SeatSave.h"

#include <ctime>
#include <string>
#include <vector>
#include <utility>

namespace biseul_rroom {


	/// Manages overall seats
	/// provides seat control functions
	class SeatManager : public Manager {
	public:
		//singleton
		static SeatManager& instance() {
			static SeatManager* instance = new SeatManager();
			return *instance;
		}
		virtual ~SeatManager();

		SeatStatus seat_status_check(int); //seat number as an input
		Seat* create_seat(Reserver* reserver, int hour, int pause);
		Seat* create_seat(Reserver* reserver, SeatStatus status, tm reserved_time, tm reserve_end_time, int pause);
		Seat* get_seat(int num);
		
		std::vector<std::pair<int, Seat*>> get_reserved_seat_vector();
		bool load_seat_vector(std::vector<std::pair<int, Seat*>>);


		void delete_seat(int num);

		void reserve_seat(int num, std::string name, int stud_id, __int64 rfid_id, int hour, int pause);
		void return_seat(int);
		void renew_seat(int, int);
		void pause_seat(int);
		void unpause_seat(int);
		void move_seat(int from, int to);

		int find_seat(__int64 rfid_id);

		void reset_all();

	private:
		SeatManager() {};

		int _seat_cnt = 0;
		Seat* rroom_seat[READINGROOM_SEAT] = { nullptr, }; //total 124 seats in the reading room


	};
}