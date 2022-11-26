#include <utils/logger.hpp>
#include <utils/util.hpp>

namespace util {
namespace logger {
void initLogger() {
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(server::config::DEBUG ? plog::debug : plog::info,
           server::config::LOG_PATH.c_str())
    .addAppender(&consoleAppender);
}
}  // namespace logger
}  // namespace util
