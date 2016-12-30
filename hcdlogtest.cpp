#include <iostream>
//#include "spdlog/spdlog.h"
#include "hcdlog.h"

using namespace std;

int main(int argc, char* argv[]) {
  HcdLogger::Init("/tmp/logs/spdlog", 1, 3, true);

  std::vector<LogLevel> levels = {trace, debug, info, warn, err, critical, off};

  for (int i = 0; i < levels.size(); i++) {
    printf("\n\nuse log level %d\n", levels[i]);

    HcdLogger::SetLogLevel(levels[i]);

    trace("current lvl = {}", levels[i]);
    debug("current lvl = {}", levels[i]);
    info("current lvl = {}", levels[i]);
    warn("current lvl = {}", levels[i]);
    error("current lvl = {}", levels[i]);
    critical("current lvl = {}", levels[i]);

  }
  return 0;
}
