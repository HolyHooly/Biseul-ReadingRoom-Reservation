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



    //로딩된 자리 정보를 저장하는 class
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

    // save_status 로 저장한 CSV 파일에서 내부 정보 가져오고 내부에 저장하는 class
// class 
    class Loading : public SeatInfo
    {
    public:
        Loading() {};
        ~Loading() {};
        void load_status(); //함수 사용하면 class 내부 인수로 seat status 불러옴 각각 인수 넣어야하는 데로 집어넣으면 됨

        std::vector<std::pair<int, SeatInfo*>> get_seats_info_vector();// 전체 자리에 대한 정보 가져옴. SeatManager의 vector랑 동일하게 pair<자리 번호, SeatInfo*> 넘겨줌

    private:
        
        SeatInfo* seats[READINGROOM_SEAT] = { nullptr, };
    };
}