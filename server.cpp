#include "version_controller.h"
#include <string>

int main(int argc, char const *argv[]) {
  VersionController server(argv[1], argv[2]);
  //server.push_file("test","hash");
  //server.pull_tag("v1.0");
  //server.tag_files();
  server.start();
  return 0;
}
