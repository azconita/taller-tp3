#include "client_versioner.h"
#include <string>

int main(int argc, char const *argv[]) {
  VersionClient client(argv[1], argv[2]);
  if (std::string(argv[3]) == "push") {
    std::string filename(argv[4]);
    std::string hash(argv[5]);
    client.push_file(filename, hash);
  } else if (std::string(argv[3]) == "pull") {
    std::string tag(argv[4]);
    client.pull_tag(tag);
  } else if (std::string(argv[3]) == "tag") {
    std::string tag(argv[4]);
    std::vector<std::string> v;
    for (int i = 5; i < argc; ++i)
      v.push_back(argv[i]);
    client.tag_hashes(tag, v);
  }
  return 0;
}
