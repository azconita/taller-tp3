#include <string>
#include <vector>
#include "index.h"
#include "socket.h"
#include "server_socket.h"

class VersionController {
private:
  ServerSocket acc_socket;
  Index index;
  std::vector<ServerSocket*> clients;

public:
  VersionController(const std::string port, const char* filename);
  ~VersionController() { }
  void start();
  void push_file(Socket &client);
  void tag_files();
  void pull_tag();
};
