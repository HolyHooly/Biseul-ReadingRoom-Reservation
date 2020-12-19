#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>

#include "Seat.h"
#include "Reserver.h"
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

        std::vector<std::pair<int, Seat*>> get_seats_info_vector();

    private:
        SeatStatus seat_status_converter(std::string);

        Seat* seats[READINGROOM_SEAT] = { nullptr, };
    };
}