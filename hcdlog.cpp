#include "assert.h"
#include "hcdlog.h"

std::unique_ptr<HcdLogger> hcdlogger;

std::shared_ptr<spdlog::logger>& HcdLogger::GetSpdlogger() {
  if (!spdlogger_) {
    printf("logger not inititialized\n");
    assert(0);
  }
  return spdlogger_;
}

bool HcdLogger::Init(const string& filename,
                     int size_mb,
                     int num_files,
                     bool logtostderr) {
  if (hcdlogger) {
    return true;
  }
  hcdlogger.reset(new HcdLogger());

  try {
    std::vector<spdlog::sink_ptr> sinks;
    if (logtostderr) {
      sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    }
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>
        (filename, "log", size_mb * 1024L * 1024, num_files));
    auto spdlogger =
        std::make_shared<spdlog::logger>("hcdlog", begin(sinks), end(sinks));
    spdlogger->set_pattern("[%Y-%m-%d %H:%M:%S.%f] %l %v");
    hcdlogger->SetSpdlogger(spdlogger);
    spdlog::register_logger(hcdlogger->GetSpdlogger());
  } catch (const spdlog::spdlog_ex& ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
    return false;
  }
}

HcdLogger::HcdLogger() {
}

HcdLogger::~HcdLogger() {
  // release spdlogger here.
  info("tear down hcdlogger");
  spdlog::drop_all();
}

void HcdLogger::SetLogLevel(LogLevel level) {
  if (!hcdlogger) return;

  if (level > LogLevel::off) return;

  spdlog::level::level_enum spdlevel;
  if (level == LogLevel::trace) {
    spdlevel = spdlog::level::level_enum::trace;
  } else if (level == LogLevel::debug) {
    spdlevel = spdlog::level::level_enum::debug;
  } else if (level == LogLevel::info) {
    spdlevel = spdlog::level::level_enum::info;
  } else if (level == LogLevel::warn) {
    spdlevel = spdlog::level::level_enum::warn;
  } else if (level == LogLevel::err) {
    spdlevel = spdlog::level::level_enum::err;
  } else if (level == LogLevel::critical) {
    spdlevel = spdlog::level::level_enum::critical;
  } else if (level == LogLevel::off) {
    spdlevel = spdlog::level::level_enum::off;
  }

  hcdlogger->GetSpdlogger()->set_level(spdlevel);

}

