#include "server.h"
#include <string>


int main(int argc, char const *argv[]) {
  Server server(std::stoi(argv[1]), argv[2]);
  server.push_file("test","hash");
  server.pull_tag("v1.0");
  server.tag_files();
  return 0;
}
