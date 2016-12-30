#ifndef HCDLOG_H
#define HCDLOG_H

#include <iostream>
#include "spdlog/spdlog.h"

using namespace std;

// logging level. Given a level limit, only severity levels >= limit
// will be outputted to log.
enum LogLevel {
  trace = 0,
  debug = 1,
  info = 2,
  warn = 3,
  err = 4,
  critical = 5,
  off = 6
};

// A wrapper class to provide access to spdlog.
class HcdLogger {
 public:

  // Init logger.
  //
  // NOTE: User must call this method once at beginning of program
  // before doing any logging.
  //
  // filename:   log filename base including the leading dir path, such as
  //             "/var/log/hcdlog/mylog"
  // size_mb:    max size of each log file in MB.
  // num_files:  max number of log files to cumulate.
  static bool Init(const string& filename,
                   int size_mb,
                   int num_files,
                   bool logtostderr);

  static void SetLogLevel(LogLevel level);

  std::shared_ptr<spdlog::logger>& GetSpdlogger();

  void SetSpdlogger(std::shared_ptr<spdlog::logger>& spdlogger) {
    spdlogger_ = std::move(spdlogger);
  }


  virtual ~HcdLogger();

 private:
  HcdLogger();

  // assignment is private.
  HcdLogger& operator=(HcdLogger const&) {};

  // Spd logger that does actual logging.
  std::shared_ptr<spdlog::logger> spdlogger_;

  //static std::unique_ptr<HcdLogger> instance_;
};

//extern spdlog::logger* logger;
extern std::unique_ptr<HcdLogger> hcdlogger;

#define trace(fmt, ...)                                    \
  do {                                                     \
    hcdlogger->GetSpdlogger()->trace("[{}:{}:{}] " fmt,    \
        __FILE__, __func__, __LINE__, ##__VA_ARGS__);      \
  } while (0)

#define debug(fmt, ...)                                    \
  do {                                                     \
    hcdlogger->GetSpdlogger()->debug("[{}:{}:{}] " fmt,    \
        __FILE__, __func__, __LINE__, ##__VA_ARGS__);      \
  } while (0)

#define info(fmt, ...)                                     \
  do {                                                     \
    hcdlogger->GetSpdlogger()->info("[{}:{}:{}] " fmt,     \
        __FILE__, __func__, __LINE__, ##__VA_ARGS__);      \
  } while (0)

#define warn(fmt, ...)                                     \
  do {                                                     \
    hcdlogger->GetSpdlogger()->warn("[{}:{}:{}] " fmt,     \
        __FILE__, __func__, __LINE__, ##__VA_ARGS__);      \
  } while (0)

#define error(fmt, ...)                                    \
  do {                                                     \
    hcdlogger->GetSpdlogger()->error("[{}:{}:{}] " fmt,    \
        __FILE__, __func__, __LINE__, ##__VA_ARGS__);      \
  } while (0)

#define critical(fmt, ...)                                 \
  do {                                                     \
    hcdlogger->GetSpdlogger()->critical("[{}:{}:{}] " fmt, \
        __FILE__, __func__, __LINE__, ##__VA_ARGS__);      \
  } while (0)


#endif   // HCDLOG_H
