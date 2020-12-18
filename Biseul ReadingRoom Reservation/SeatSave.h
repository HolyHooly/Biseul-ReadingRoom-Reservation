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



    // save_status �� ������ CSV ���Ͽ��� ���� ���� �������� ���ο� �����ϴ� class
// class 
    class Loading
    {
    public:
        Loading() {};
        ~Loading() {};
        void load_status(); //�Լ� ����ϸ� class ���� �μ��� seat status �ҷ��� ���� �μ� �־���ϴ� ���� ��������� ��

        bool get_seat(int seatno); // �Լ��� �ѱ� �ڸ� ��ȣ�� �ش��ϴ� �ڸ� ������ ������ false ������ true return

        std::vector<std::pair<int, Loading*>> get_seats_info_vector();// ��ü �ڸ��� ���� ���� ������. SeatManager�� vector�� �����ϰ� pair<�ڸ� ��ȣ, Loading*> �Ѱ���

    private:
        int seat_no = 0;
        std::string name;
        int student_id = 0;
        __int64 rfid_id = 0;
        std::string seat_status;
        int pause_time = 240;
        tm reserved_time;
        tm reserve_end_time;

        SeatStatus seat_status_converter(int);

        Loading* seats[READINGROOM_SEAT] = { nullptr, };
    };
}