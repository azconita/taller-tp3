#include <string>
#include <vector>
#include <thread>
#include "index.h"
#include "socket.h"
#include "server_socket.h"
#include "request_processor.h"

class VersionController {
private:
  std::thread thread;
  ServerSocket acc_socket;
  Index index;
  std::vector<PushProcessor*> pushs;
  std::vector<TagProcessor*> tags;
  std::vector<PullProcessor*> pulls;

public:
  VersionController(const std::string port, const char* filename);
  ~VersionController() { }
  void start();
  void run();
};
