#include "BiseulReadingRoomReservation_log.h"

void Logger::log_init(){
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

void Logger::write_log(std::string msg){
    logging::add_common_attributes();

    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, info) << msg;
}

bool Logger::save_status(std::string)
{
    //�� �޴��� �𸣰ڴµ� csv ���� �� �ٲٴ� �� string ,�� �����Ѵ� class�� �״�� �൵ �ɵ�~~ ������ ���� �ð��� ���� �� ���� ��~~
    return false;
}
