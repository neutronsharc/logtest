#define ELPP_THREAD_SAFE
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
  el::Configurations conf("./log.conf");
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::reconfigureAllLoggers(conf);

  for (int i = 0; i < 1000; i++) {
    LOG(INFO) << "My info log using default logger " << i;
  }
  return 0;
}
