#include "client_versioner.h"
#include <string>

int main(int argc, char const *argv[]) {
  VersionClient client(argv[1], argv[2]);
  if (std::string(argv[3]) == "push")
    client.push_file(argv[4], argv[5]);
  else if (std::string(argv[3]) == "pull")
    client.pull_tag(argv[4]);
  else if (std::string(argv[3]) == "tag") {
    std::vector<std::string> v;
    for (int i = 5; i < argc; ++i)
      v.push_back(argv[i]);
    client.tag_hashes(argv[4], v);
  }
  return 0;
}
