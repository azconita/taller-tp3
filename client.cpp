#include "client_versioner.h"
#include <string>
#include <fstream>
#include <vector>

bool file_exist(const char* filename) {
    std::ifstream infile(filename);
    return infile.good();
}

int main(int argc, char const *argv[]) {
  if (std::string(argv[3]) == "push") {
    if (argc < 6) {
      std::cout << "Error: argumentos invalidos." << '\n';
      return 0;
    }
    if (!file_exist(argv[4])) {
      std::cout << "Error: archivo inexistente." << '\n';
      return 0;
    }
    std::string filename(argv[4]);
    VersionClient client(argv[1], argv[2]);
    std::string hash(argv[5]);
    client.push_file(filename, hash);
  } else if (std::string(argv[3]) == "pull") {
    if (argc < 5) {
      std::cout << "Error: argumentos invalidos." << '\n';
      return 0;
    }
    VersionClient client(argv[1], argv[2]);
    std::string tag(argv[4]);
    client.pull_tag(tag);
  } else if (std::string(argv[3]) == "tag") {
    if (argc < 6) {
      std::cout << "Error: argumentos invalidos." << '\n';
      return 0;
    }
    VersionClient client(argv[1], argv[2]);
    std::string tag(argv[4]);
    std::vector<std::string> v;
    for (int i = 5; i < argc; ++i)
      v.push_back(argv[i]);
    client.tag_hashes(tag, v);
  } else {
    std::cout << "Error: argumentos invalidos." << '\n';
    return 0;
  }
  return 0;
}
