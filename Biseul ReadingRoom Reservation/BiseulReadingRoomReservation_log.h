/*
boost logging 라이브러리 c 드라이브에 설치한 후에 컴파일 가능
https://miragecore.tistory.com/entry/Boost-152-BoostLog-%EC%84%A4%EC%B9%98 참고!
boost libraries ver.1.74.0
*/
///////////////////////////////////////////////////////////////////////////////////////
//  log 작성
//
//  파일 이름 = log_000.log, log_001.log, log_002.log, log_003.log ... 로 rotating 됨
//  한 파일의 최대 크기 1mb, 최대 파일 개수 20개(채우면 처음 작성한 파일 삭제)
//  재부팅시 새 파일 작성 (기존에 00.log 쓸 수 있었으면 재부팅후에는 01.log로 작성)
//     -> 재부팅 시점 알 수 있으면 좋을 거 같아서 이렇게 했음
//  프로그램 실행 중에 바로바로 로그 작성 가능
///////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>

#include "SeatSave.h"
#include "SeatManager.h"

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;

void init_file_collecting(boost::shared_ptr< file_sink > sink); // init_logging 파일에서 사용하는 sink 생성 함수 쓸 일 없음
void init_logging();  // log 파일 생성 초기 함수, 맨처음에 프로그램 실행할 때 최초 한 번만 불러줘야 함.
void write_log(std::string); 
// log 작성, parameter로 string 전달하면 
// [작성시간] 입력해준 string 
// 형식으로 입력됨  



// save_status 로 저장한 CSV 파일에서 내부 정보 가져오고 내부에 저장하는 class
// class 
namespace biseul_rroom {
    class Loading
    {
    public:
        Loading() {};
        ~Loading() {};
        void load_status(); //함수 사용하면 class 내부 인수로 seat status 불러옴 각각 인수 넣어야하는 데로 집어넣으면 됨


        bool get_seat(int seatno); // 함수에 넘긴 자리 번호에 해당하는 자리 정보가 없으면 false 있으면 true return

        //자리 번호 입력하면 그 자리에 해당하는 값 return (빈 자리 번호 입력하면 오류남)
        std::string get_name(int seatno) { return seats[seatno - 1]->name; }
        int get_student_id(int seatno) { return seats[seatno - 1]->student_id; }
        __int64 get_rfid_id(int seatno) { return seats[seatno - 1]->rfid_id; }
        SeatStatus get_seat_status(int seatno) { return seat_status_converter(seatno); }
        int get_pause_time(int seatno) { return seats[seatno - 1]->pause_time; }

    private:
        int seat_no = 0;
        std::string name;
        int student_id = 0;
        __int64 rfid_id = 0;
        std::string seat_status;
        int pause_time = 240;

        SeatStatus seat_status_converter(int);

        Loading* seats[READINGROOM_SEAT] = { nullptr, };
    };
}