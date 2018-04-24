#include <vector>
#include <string>
#include "socket.h"

class Client {
private:
  Socket server;

public:
  Client(std::string hostname, int port) : server(port) {}
  virtual ~Client() {}
  void push_file(std::string filename, std::string hash);
  void tag_hashes(std::string tag, std::vector<std::string> hashes);
  void pull_tag(std::string tag);
};
