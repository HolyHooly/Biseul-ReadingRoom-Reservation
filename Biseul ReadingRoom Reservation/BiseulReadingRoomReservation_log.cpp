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
