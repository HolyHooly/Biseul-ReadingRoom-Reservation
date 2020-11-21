/*
boost logging ���̺귯�� c ����̺꿡 ��ġ�� �Ŀ� ������ ����
https://miragecore.tistory.com/entry/Boost-152-BoostLog-%EC%84%A4%EC%B9%98 ����!
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

void log_init();  // info log ���� ���� �ʱ� �Լ�
void write_log(std::string); // info log �ۼ�
bool save_status(std::string); // ���� �ڸ� csv ���Ϸ� ����, string�̳� class ���� ���� �� ���� ��! parameter�ָ� �˾Ƽ� �����ϰ���


void log_init() {
    logging::add_file_log
    (
        keywords::file_name = "log_%N.log",                                      /*< file name pattern >*/
        keywords::rotation_size = 1024 * 1024,                                   /*< rotate files every 1 MiB... >*/
        keywords::max_files = 20,                                                // ���� �� �ִ� 20��
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
    //�� �޴��� �𸣰ڴµ� csv ���� �� �ٲٴ� �� string ,�� �����Ѵ� class�� �״�� �൵ �ɵ�~~ ������ ���� �ð��� ���� �� ���� ��~~
    return false;
}