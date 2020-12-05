/*
boost logging ���̺귯�� c ����̺꿡 ��ġ�� �Ŀ� ������ ����
https://miragecore.tistory.com/entry/Boost-152-BoostLog-%EC%84%A4%EC%B9%98 ����!
boost libraries ver.1.74.0
*/
///////////////////////////////////////////////////////////////////////////////////////
//  log �ۼ�
//
//  ���� �̸� = log_000.log, log_001.log, log_002.log, log_003.log ... �� rotating ��
//  �� ������ �ִ� ũ�� 1mb, �ִ� ���� ���� 20��(ä��� ó�� �ۼ��� ���� ����)
//  ����ý� �� ���� �ۼ� (������ 00.log �� �� �־����� ������Ŀ��� 01.log�� �ۼ�)
//     -> ����� ���� �� �� ������ ���� �� ���Ƽ� �̷��� ����
//  ���α׷� ���� �߿� �ٷιٷ� �α� �ۼ� ����
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

void init_file_collecting(boost::shared_ptr< file_sink > sink); // init_logging ���Ͽ��� ����ϴ� sink ���� �Լ� �� �� ����
void init_logging();  // log ���� ���� �ʱ� �Լ�, ��ó���� ���α׷� ������ �� ���� �� ���� �ҷ���� ��.
void write_log(std::string); 
// log �ۼ�, parameter�� string �����ϸ� 
// [�ۼ��ð�] �Է����� string 
// �������� �Էµ�  



// save_status �� ������ CSV ���Ͽ��� ���� ���� �������� ���ο� �����ϴ� class
// class 
namespace biseul_rroom {
    class Loading
    {
    public:
        Loading() {};
        ~Loading() {};
        void load_status(); //�Լ� ����ϸ� class ���� �μ��� seat status �ҷ��� ���� �μ� �־���ϴ� ���� ��������� ��


        bool get_seat(int seatno); // �Լ��� �ѱ� �ڸ� ��ȣ�� �ش��ϴ� �ڸ� ������ ������ false ������ true return

        //�ڸ� ��ȣ �Է��ϸ� �� �ڸ��� �ش��ϴ� �� return (�� �ڸ� ��ȣ �Է��ϸ� ������)
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