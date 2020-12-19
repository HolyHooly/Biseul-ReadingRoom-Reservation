///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 12. 20. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#include "Seat.h"

namespace biseul_rroom {
	
	Seat::Seat(Reserver* reserver, SeatStatus status, int reserve_hour, int pause_minutes)
		: seat_reserver(reserver), status(status), pause_minutes_left(pause_minutes)
	{
		get_local_time(reserved_time); //reserved time initializing
		get_local_time(reserve_end_time);
		add_tm_hour(reserve_end_time, reserve_hour); //reserve end time
	}

	Seat::Seat(Reserver* reserver, SeatStatus status, tm reserved_time, tm reserve_end_time, int pause_minutes)
		: seat_reserver(reserver), status(status), reserved_time(reserved_time), reserve_end_time(reserve_end_time), pause_minutes_left(pause_minutes)
	{
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

	bool Seat::before_minutes(int minutes)
	{
		return before_min_timemanager(reserve_end_time, minutes);
	}

	bool Seat::over_time()
	{
		return over_time_timemanager(reserve_end_time);
	}
}