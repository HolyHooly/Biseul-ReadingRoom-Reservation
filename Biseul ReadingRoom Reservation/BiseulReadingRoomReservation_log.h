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

void log_init();  // info log 파일 생성 초기 함수
void write_log(std::string); // info log 작성
bool save_status(std::string); // 현재 자리 csv 파일로 저장, string이나 class 전부 받을 수 있을 듯! parameter주면 알아서 구현하겠음


void log_init() {
    logging::add_file_log
    (
        keywords::file_name = "log_%N.log",                                      /*< file name pattern >*/
        keywords::rotation_size = 1024 * 1024,                                   /*< rotate files every 1 MiB... >*/
        keywords::max_files = 20,                                                // 파일 수 최대 20개
        keywords::format = "[%TimeStamp%]: %Message%"                            /*< log record format >*/
    );

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
}

void write_log(std::string msg) {
    logging::add_common_attributes();

    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, info) << msg;
}

bool save_status(std::string)
{
    //뭐 받는진 모르겠는데 csv 파일 열 바꾸는 건 string ,로 구분한대 class로 그대로 줘도 될듯~~ 맨위에 저장 시간도 적을 수 있을 듯~~
    return false;
}