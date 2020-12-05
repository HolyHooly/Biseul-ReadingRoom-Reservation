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
}