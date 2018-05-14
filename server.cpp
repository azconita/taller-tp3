#include "server_controller.h"
#include <string>
#include <thread>

int main(int argc, char const *argv[]) {
  VersionController server(argv[1], argv[2]);
  server.start();
  while (getchar() != 'q') {
    continue;
  }
  std::cout << "stoping server..." << '\n';
  server.stop();
  return 0;
}
