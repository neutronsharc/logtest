#include <iostream>
#include "spdlog/spdlog.h"

using namespace spdlog;
using namespace std;

#define CONCAT(a, b) a #b

#define myinfo(fmt, ...) \
  do { \
  mylogger->info("[{}:{}:{}] " fmt, __FILE__, __func__, __LINE__, __VA_ARGS__);\
} while (0)

int main(int argc, char* argv[]) {
  //Multithreaded console logger(with color support)
  //auto console = spdlog::stdout_color_mt("console");
  //console->info("Welcome to spdlog!") ;
  //console->info("An info message example {}..", 1);
  try {
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>
        ("/tmp/logs/spdlog", "log", 10000, 3));
    auto mylogger =
       std::make_shared<spdlog::logger>("name", begin(sinks), end(sinks));
    mylogger->set_pattern("[%Y-%m-%d %H:%M:%S.%f] %l %v");
    spdlog::register_logger(mylogger);

    // Create basic file logger (not rotated)
    //auto my_logger = spdlog::basic_logger_mt("basic_logger", "/tmp/log/basic.txt");
    // create a file rotating logger with 5mb size max and 3 rotated files
    //auto file_logger =
    //  spdlog::rotating_logger_mt("file_logger", "/tmp/log/spdlog.log", 1024 * 1024, 3);

    for (int i = 0; i < 1000; i++) {
      //mylogger->info("[{}:{}] start to do logging in iter {}",
      //    __FILE__, __LINE__, i);
      myinfo("start to do logging in iter {}", i);
    }
  } catch (const spdlog::spdlog_ex& ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }

}
