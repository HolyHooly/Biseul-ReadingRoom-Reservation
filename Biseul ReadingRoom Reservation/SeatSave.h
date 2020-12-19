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
	// 자리 정보 담은 vector 값 받으면 {자리 번호},{이름},{학번},{rfid_id},{자리상태},{일시정시시간} 로 std::string return
 
	void save_seats(std::string); // csv 파일로 저장 

	void save_status(std::vector<std::pair<int, Seat*>>); 
	// 위에 두 함수 한 번에 처리하는 함수. 
	// 현재 자리 저장할 때에는 위에 두 함수 무시하고 save_status(vector<>); 로 입력하면 됨.


    // save_status 로 저장한 CSV 파일에서 내부 정보 가져오고 내부에 저장하는 class
// class 
    class Loading
    {
    public:
        Loading() {};
        ~Loading() {};
        void load_status(); //함수 사용하면 class 내부 인수로 seat status 불러옴 각각 인수 넣어야하는 데로 집어넣으면 됨

        std::vector<std::pair<int, Seat*>> get_seats_info_vector();

    private:
        SeatStatus seat_status_converter(std::string);

        Seat* seats[READINGROOM_SEAT] = { nullptr, };
    };
}