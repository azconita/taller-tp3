#include <vector>
#include <string>
#include "common_socket.h"
#include "client_socket.h"

class VersionClient {
private:
  ClientSocket client;

public:
  VersionClient(const char *hostname, const char* port);
  ~VersionClient() {}
  void push_file(std::string &filename, std::string &hash);
  void tag_hashes(std::string &tag, std::vector<std::string> &hashes);
  void pull_tag(std::string &tag);
};
