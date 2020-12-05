#pragma once

#include <string>
#include <sstream>
#include <fstream>

#include "SeatManager.h"
#include "UserManager.h"


namespace biseul_rroom {
	std::string status_to_string(std::vector<std::pair<int, Seat*>>);	
	// 자리 정보 담은 vector 값 받으면 {자리 번호},{이름},{학번},{rfid_id},{자리상태},{일시정시시간} 로 std::string return
 
	void save_seats(std::string); // csv 파일로 저장 

	void save_status(std::vector<std::pair<int, Seat*>>); 
	// 위에 두 함수 한 번에 처리하는 함수. 
	// 현재 자리 저장할 때에는 위에 두 함수 무시하고 save_status(vector<>); 로 입력하면 됨.
}