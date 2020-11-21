/*
boost logging 라이브러리 c 드라이브에 설치한 후에 컴파일 가능
https://miragecore.tistory.com/entry/Boost-152-BoostLog-%EC%84%A4%EC%B9%98 참고!
*/


#include "string.h"

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

class Logger {
public:
    void log_init();  // info log 파일 생성 초기 함수
    void write_log(std::string); // info log 작성
    bool save_status(std::string); // 현재 자리 csv 파일로 저장, string이나 class 전부 받을 수 있을 듯! parameter주면 알아서 구현하겠음
};