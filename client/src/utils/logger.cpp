#include <utils/logger.hpp>
#include <utils/util.hpp>

namespace util {
namespace logger {
void initLogger() {
  if (client::config::LOG_PATH != "") {
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(client::config::DEBUG ? plog::debug : plog::info,
               client::config::LOG_PATH.c_str())
        .addAppender(&consoleAppender);
  }
}
}  // namespace logger
}  // namespace util