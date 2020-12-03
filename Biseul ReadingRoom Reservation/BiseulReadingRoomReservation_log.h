/*
boost logging ���̺귯�� c ����̺꿡 ��ġ�� �Ŀ� ������ ����
https://miragecore.tistory.com/entry/Boost-152-BoostLog-%EC%84%A4%EC%B9%98 ����!
boost libraries ver.1.74.0
*/
///////////////////////////////////////////////////////////////////////////////////////
/* 
	write_log(std::string)
���� �̸� = log_000.log, log_001.log, log_002.log, log_003.log ... �� rotating ��
�� ������ �ִ� ũ�� 1mb, �ִ� ���� ���� 20��(ä��� ó�� �ۼ��� ���� ����)
����ý� �� ���� �ۼ� (������ 00.log �� �� �־����� ������Ŀ��� 01.log�� �ۼ�)
	-> ����� ���� �� �� ������ ���� �� ���Ƽ� �̷��� ����
���α׷� ���� �߿� �ٷιٷ� �α� �ۼ� ����
	-> �ٵ� �̷��� ���α׷� ����ÿ� �� ���� �ۼ��Ǵ� �ͺ��� �ý����� ���� �������ٰ� ��. ��� �α� ������ �����ϱ� �׳� �ǽð� �ۼ��� ���� �ҵ�


	save_status(std::string)
�� �� ����� ������ ���� csv ���Ͽ� ����� ��. ���� \n ���� , �� �����ؼ� string�� �Է��ϸ� �ɵ�
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


void init_logging();  // info log ���� ���� �ʱ� �Լ�, ��ó���� ���α׷� ������ ������ �ҷ��ָ� ��
void write_log(std::string); // info log �ۼ� parameter�� �Է��Ϸ��� �� �־��ָ� ��
void save_status(std::string); // ���� �ڸ� csv ���Ϸ� ���� 

#endif
