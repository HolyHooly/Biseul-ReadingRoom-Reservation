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



    // save_status 로 저장한 CSV 파일에서 내부 정보 가져오고 내부에 저장하는 class
// class 
    class Loading
    {
    public:
        Loading() {};
        ~Loading() {};
        void load_status(); //함수 사용하면 class 내부 인수로 seat status 불러옴 각각 인수 넣어야하는 데로 집어넣으면 됨

        bool get_seat(int seatno); // 함수에 넘긴 자리 번호에 해당하는 자리 정보가 없으면 false 있으면 true return

        std::vector<std::pair<int, Loading*>> get_seats_info_vector();// 전체 자리에 대한 정보 가져옴. SeatManager의 vector랑 동일하게 pair<자리 번호, Loading*> 넘겨줌

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