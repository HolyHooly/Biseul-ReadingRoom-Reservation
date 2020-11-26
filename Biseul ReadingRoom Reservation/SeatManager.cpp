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

	void SeatManager::reserve_seat(int num, Seat* seat)
	{
		num = num - 1;
		rroom_seat[num] = seat;
		++_seat_cnt;
	}

	void SeatManager::return_seat(int num)
	{
		num = num - 1;
		delete rroom_seat[num];
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

	

}