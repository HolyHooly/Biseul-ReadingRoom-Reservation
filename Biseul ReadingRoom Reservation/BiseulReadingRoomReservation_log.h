
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
    void log_init();  // info log ���� ���� �ʱ� �Լ�
    void write_log(std::string msg); // info log �ۼ�
    bool save_status(std::string); // ���� �ڸ� csv ���Ϸ� ����, string�̳� class ���� ���� �� ������!
};