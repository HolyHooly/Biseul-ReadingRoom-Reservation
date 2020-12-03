/*
boost logging 라이브러리 c 드라이브에 설치한 후에 컴파일 가능
https://miragecore.tistory.com/entry/Boost-152-BoostLog-%EC%84%A4%EC%B9%98 참고!
boost libraries ver.1.74.0
*/
///////////////////////////////////////////////////////////////////////////////////////
/* 
	write_log(std::string)
파일 이름 = log_000.log, log_001.log, log_002.log, log_003.log ... 로 rotating 됨
한 파일의 최대 크기 1mb, 최대 파일 개수 20개(채우면 처음 작성한 파일 삭제)
재부팅시 새 파일 작성 (기존에 00.log 쓸 수 있었으면 재부팅후에는 01.log로 작성)
	-> 재부팅 시점 알 수 있으면 좋을 거 같아서 이렇게 했음
프로그램 실행 중에 바로바로 로그 작성 가능
	-> 근데 이러면 프로그램 종료시에 한 번에 작성되는 것보단 시스템이 조금 느려진다고 함. 대신 로그 잃지는 않으니까 그냥 실시간 작성이 낫긴 할듯


	save_status(std::string)
한 번 사용할 때마다 기존 csv 파일에 덮어쓰기 됨. 행은 \n 열은 , 로 구분해서 string만 입력하면 될듯
*/ 
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BISEUL_LOGGING
#define BISEUL_LOGGING

#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;


void init_logging();  // info log 파일 생성 초기 함수, 맨처음에 프로그램 실행할 때에만 불러주면 됨
void write_log(std::string); // info log 작성 parameter로 입력하려는 값 넣어주면 됨
void save_status(std::string); // 현재 자리 csv 파일로 저장 

#endif
