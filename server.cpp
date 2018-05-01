#include "server_controller.h"
#include <string>
#include <thread>

int main(int argc, char const *argv[]) {
  VersionController server(argv[1], argv[2]);
  server.start();
  //std::thread controller {VersionController(argv[1], argv[2])};
  while (getchar() != 'q') {
    continue;
  }
  //controller.join();
  return 0;
}
