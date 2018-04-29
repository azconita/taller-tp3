#include <vector>
#include <string>
#include "socket.h"
#include "client_socket.h"

class VersionClient {
private:
  ClientSocket client;

public:
  VersionClient(std::string hostname, std::string port);
  ~VersionClient() {}
  void push_file(std::string filename, std::string hash);
  void tag_hashes(std::string tag, std::vector<std::string> hashes);
  void pull_tag(std::string tag);
};