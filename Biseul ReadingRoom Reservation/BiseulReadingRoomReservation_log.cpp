#include "BiseulReadingRoomReservation_log.h"
#include "BiseulReadingRoomReservation_log.h"

void init_file_collecting(boost::shared_ptr< file_sink > sink)
{
    sink->locked_backend()->set_file_collector(sinks::file::make_collector(
        keywords::target = "log",                                              /*< the target directory >*/
        keywords::min_free_space = 100 * 1024 * 1024,                          /*< minimum free space on the drive, in bytes >*/
        keywords::rotation_size = 1024 * 1024,                                 /*< rotate files every 1 MiB... >*/
        keywords::max_files = 20                                               // 파일 수 최대 20개
    ));
}

void init_logging() {
    // Create a text file sink
    boost::shared_ptr< file_sink > sink(new file_sink(
        keywords::file_name = "log/log_%3N.log",                                /*< the resulting file name pattern >*/
        keywords::auto_flush = true
    ));

    boost::shared_ptr< sinks::text_file_backend > backend =
        boost::make_shared< sinks::text_file_backend >(
            keywords::file_name = "log.log",
            keywords::target_file_name = "log_%3N.log",
            keywords::open_mode = std::ios_base::out | std::ios_base::app,
            keywords::enable_final_rotation = false,
            keywords::auto_flush = true
            );

    // Set up where the rotated files will be stored
    init_file_collecting(sink);

    // Upon restart, scan the directory for files matching the file_name pattern
    sink->locked_backend()->scan_for_files();

    sink->set_formatter
    (
        expr::format("timestamp=\"%1%\">%2%</record>")
        % expr::attr< boost::posix_time::ptime >("TimeStamp")
        % expr::xml_decor[expr::stream << expr::smessage]                      /*< the log message has to be decorated, if it contains special characters >*/
    );

    // Add the sink to the core
    logging::core::get()->add_sink(sink);
}

void write_log(std::string msg) {
    // And also add some attributes
    logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());

    // Do some logging
    src::logger lg;
    BOOST_LOG(lg) << msg;
}


namespace biseul_rroom {
    void Loading::load_status()
    {
        std::fstream status_file;
        std::string member;

        status_file.open("log/seat_status.csv", std::ios::in);

        int seat_number_checker = 0;
        while (!status_file.eof()) {
            //csv 파일에서 한 줄씩 읽기
            getline(status_file, member, '\n');

            //string ,로 잘라주려고 std::string에서 char*[]으로 변환
            std::vector<char> str_char(member.begin(), member.end());
            str_char.push_back('\0');
            char* words = &str_char[0];

            // 한 줄을 {자리 번호},{이름},{학번},{rfid_id},{자리상태},{일시정시시간}으로 각각 나눠줌
            char* word[6] = { nullptr, }, * context;

            word[0] = strtok_s(words, ",", &context);
            for (int i = 1; i < 6; i++) {
                word[i] = strtok_s(NULL, ",", &context);
            }

            // seat number 유무 따라서 seat에 채워주기
            if (seat_number_checker != 0) {
                Loading* seat = new Loading;
                if (atoi(word[2]) != 0) {
                    seat->seat_no = atoi(word[0]);
                    seat->name = std::string(word[1]);
                    seat->student_id = atoi(word[2]);
                    seat->rfid_id = _atoi64(word[3]);
                    seat->seat_status = std::string(word[4]);
                    seat->pause_time = atoi(word[5]);
                }
                seats[atoi(word[0]) - 1] = seat;
            }
            ++seat_number_checker;
        }
    }
    bool Loading::get_seat(int seatno)
    {
        if (seats[seatno - 1] == nullptr) {
            return false;
        }
        return true;
    }
}

namespace biseul_rroom {
    SeatStatus Loading::seat_status_converter(int seatno)
    {
        if (seats[seatno - 1] == nullptr) {
            return SeatStatus::Vacant;
        }

        std::string status = seats[seatno - 1]->seat_status;
        if (status.compare("Occupied") == 0) {
            return SeatStatus::Occupied;
        }
        if (status.compare("Paused") == 0) {
            return SeatStatus::Paused;
        }
    }
}
