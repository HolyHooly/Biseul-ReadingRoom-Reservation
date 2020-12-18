#pragma once

#include <string>
#include <sstream>
#include <fstream>

#include "SeatManager.h"
#include "UserManager.h"


namespace biseul_rroom {
	std::string status_to_string(std::vector<std::pair<int, Seat*>>);	
	// �ڸ� ���� ���� vector �� ������ {�ڸ� ��ȣ},{�̸�},{�й�},{rfid_id},{�ڸ�����},{�Ͻ����ýð�} �� std::string return
 
	void save_seats(std::string); // csv ���Ϸ� ���� 

	void save_status(std::vector<std::pair<int, Seat*>>); 
	// ���� �� �Լ� �� ���� ó���ϴ� �Լ�. 
	// ���� �ڸ� ������ ������ ���� �� �Լ� �����ϰ� save_status(vector<>); �� �Է��ϸ� ��.



    //�ε��� �ڸ� ������ �����ϴ� class
    class SeatInfo {
    public:
        SeatInfo() {}
        SeatInfo(int, std::string, int, __int64, std::string, int, tm, tm);
        virtual ~SeatInfo() {}

        std::string get_name() { return name; }
        int get_student_id() { return student_id; }
        __int64 get_rfid_id() { return rfid_id; }
        SeatStatus get_seat_status() { return seat_status; }
        int get_pause_time() { return pause_time; }
        tm get_reserved_time() { return reserved_time; }
        tm get_reserve_end_time() { return reserve_end_time; }

    private:
        SeatStatus seat_status_converter(std::string);

        int seat_no = 0;
        std::string name;
        int student_id = 0;
        __int64 rfid_id = 0;
        SeatStatus seat_status;
        int pause_time = 240;
        tm reserved_time = { 0, };
        tm reserve_end_time = { 0, };
    };

    // save_status �� ������ CSV ���Ͽ��� ���� ���� �������� ���ο� �����ϴ� class
// class 
    class Loading : public SeatInfo
    {
    public:
        Loading() {};
        ~Loading() {};
        void load_status(); //�Լ� ����ϸ� class ���� �μ��� seat status �ҷ��� ���� �μ� �־���ϴ� ���� ��������� ��

        std::vector<std::pair<int, SeatInfo*>> get_seats_info_vector();// ��ü �ڸ��� ���� ���� ������. SeatManager�� vector�� �����ϰ� pair<�ڸ� ��ȣ, SeatInfo*> �Ѱ���

    private:
        
        SeatInfo* seats[READINGROOM_SEAT] = { nullptr, };
    };
}