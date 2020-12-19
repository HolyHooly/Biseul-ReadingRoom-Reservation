///////////////////////////////////////////////////////////
// Manager that controls seat status
// 2020. 12. 20. Last modified
// (C) Taehyun Kim & OOP Lecture Team Project
//////////////////////////////////////////////////////////

#include "SeatManager.h"

namespace biseul_rroom {


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

	Seat* SeatManager::create_seat(Reserver* reserver, SeatStatus status, tm reserved_time, tm reserve_end_time, int pause)
	{
		Seat* new_seat = new Seat(reserver, status, reserved_time, reserve_end_time, pause);
		return new_seat;
	}

	Seat* SeatManager::get_seat(int num)
	{
		return rroom_seat[num-1];
	}

	/// <summary>
	/// �ڸ��� ����ǰų� �ڸ���� �Ǿ��ִ� �ڸ��� vector�� ����ش�.
	/// vector�� ���Ŀ� pair<int, Seat*> �� �ִ� ������
	/// int���� �ڸ� ��ȣ(1~124), Seat* ���� �ڸ��� �����Ͱ� ����.
	/// �ڼ��� pair����: https://blockdmask.tistory.com/64
	/// </summary>
	std::vector<std::pair<int, Seat*>> SeatManager::get_reserved_seat_vector()
	{
		std::vector<std::pair<int,Seat*>> seat_vector;
		for (int i = 0; i < READINGROOM_SEAT; ++i) { //��� �ڸ� ����
			if (rroom_seat[i] != nullptr) { //���ڸ��� �ƴ϶��
				seat_vector.push_back(std::make_pair(i,rroom_seat[i])); //�ڸ� ��ȣ�� Seat*�� pair�� ��� vector�� �־��ش�
			}
		}
		return seat_vector; //���� ����
	}

	
	bool SeatManager::load_seat_vector(std::vector<std::pair<int, Seat*>> input_data)
	{
		for (auto it = input_data.begin(); it != input_data.end(); ++it) {
			int num = it->first;
			Seat* cur_seat = it->second;

			Reserver* reserver = new Reserver(cur_seat->get_reserver()->get_name(), cur_seat->get_reserver()->get_stud_id(), cur_seat->get_reserver()->get_rfid_id());
			Seat* seat = create_seat(reserver, cur_seat->get_status(), cur_seat->vget_reserved_time(), cur_seat->vget_reserve_end_time(), cur_seat->get_pause_time());
			rroom_seat[num] = seat;
			rroom_seat[num]->setStatus(SeatStatus::Occupied);
			++_seat_cnt;
		}
		return false;
	}

	void SeatManager::delete_seat(int num)
	{
		if (rroom_seat[num] != nullptr) {
			delete rroom_seat[num]->get_reserver(); //delete reserver instance
			delete rroom_seat[num]; // delete seat instance
		}
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
				if (rfid_id == rroom_seat[i]->get_reserver()->get_rfid_id()) {
					return i + 1; // return as seat number (not array index)
				}
			}
		}

		return -1; //return -1 as for error value (not existing)
	}

	void SeatManager::reset_all()
	{
		for (int i = 0; i < READINGROOM_SEAT; ++i) {
			if (rroom_seat[i] != nullptr) { //if seat is reserved
				return_seat(i + 1);
			}
		}

	}

	

}