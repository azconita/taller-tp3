#include "version_client.h"
#include <string>

int main(int argc, char const *argv[]) {
  VersionClient client(argv[1], argv[2]);
  client.push_file(argv[4], argv[5]);
  //client.pull_tag(argv[4]);
  //std::vector<std::string> v;
  //v.push_back(argv[5]);
  //v.push_back(argv[6]);
  //client.tag_hashes(argv[4], v);
  return 0;
}
