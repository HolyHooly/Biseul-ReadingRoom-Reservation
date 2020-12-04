///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 11. 22. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#include "SeatManager.h"

namespace biseul_rroom {

	Seat::Seat(Reserver * reserver, SeatStatus status, int reserve_hour, int pause_minutes)
		: seat_reserver(reserver), status(status), pause_minutes_left(pause_minutes)
	{
		get_local_time(reserved_time); //reserved time initializing
		add_tm_hour(reserve_end_time, reserve_hour); //reserve end time
	}

	Seat::~Seat()
	{
	}

	Reserver* Seat::get_reserver()
	{
		return seat_reserver;
	}

	SeatStatus Seat::get_status()
	{
		return status;
	}

	int Seat::get_pause_time()
	{
		return pause_minutes_left;
	}

	void Seat::setStatus(SeatStatus input)
	{
		status = input;
	}

	void Seat::add_time_hour(int hour)
	{
		add_tm_hour(reserve_end_time, hour);
	}

	void Seat::minus_pause_time()
	{
		--pause_minutes_left;
	}


	SeatManager::~SeatManager()
	{
	}

	SeatStatus SeatManager::seat_status_check(int num)
	{
		num = num - 1; //arranging seat number and array index
		if (rroom_seat[num] == nullptr) return SeatStatus::Vacant;
		else return rroom_seat[num]->get_status();
	}

	Seat* SeatManager::create_seat(Reserver* reserver, int hour, int pause)
	{
		Seat* new_seat = new Seat(reserver, SeatStatus::Vacant, hour, pause);
		return new_seat;
	}

	void SeatManager::delete_seat(int num)
	{
		delete rroom_seat[num]->get_reserver(); //delete reserver instance
		delete rroom_seat[num]; // delete seat instance
	}

	void SeatManager::reserve_seat(int num, std::string name, int stud_id, __int64 rfid_id, int hour, int pause)
	{
		num = num - 1;
		Reserver* reserver = new Reserver(name, stud_id, rfid_id);
		Seat* seat = create_seat(reserver, hour, pause);
		rroom_seat[num] = seat;
		rroom_seat[num]->setStatus(SeatStatus::Occupied);
		++_seat_cnt;
	}

	void SeatManager::return_seat(int num)
	{
		num = num - 1;
		delete_seat(num);
		rroom_seat[num] = nullptr;
		--_seat_cnt;
	}

	void SeatManager::renew_seat(int num, int hour)
	{
		num = num - 1;
		rroom_seat[num]->add_time_hour(hour);
	}

	void SeatManager::pause_seat(int num)
	{
		num = num - 1;
		rroom_seat[num]->setStatus(SeatStatus::Paused);
	}

	void SeatManager::unpause_seat(int num)
	{
		num = num - 1;
		rroom_seat[num]->setStatus(SeatStatus::Occupied);
	}

	void SeatManager::move_seat(int from, int to)
	{
		from = from - 1;
		to = to - 1;
		rroom_seat[to] = rroom_seat[from];
		rroom_seat[from] = nullptr;
	}

	int SeatManager::find_seat(__int64 rfid_id)
	{
		for (int i = 0; i < READINGROOM_SEAT; ++i) {
			if (rroom_seat[i] != nullptr) { //if seat is reserved
				if (rfid_id = rroom_seat[i]->get_reserver()->get_rfid_id()) {
					return i + 1; // return as seat number (not array index)
				}
			}
		}

		return -1; //return -1 as for error value (not existing)
	}

	

}