#include <string>
#include <vector>
#include <thread>
#include "server_index.h"
#include "common_socket.h"
#include "server_socket.h"
#include "server_request_processor.h"
#include "server_push_processor.h"
#include "server_pull_processor.h"
#include "server_tag_processor.h"

class VersionController {
private:
  std::thread thread;
  ServerSocket acc_socket;
  Index index;
  std::vector<PushProcessor*> pushs;
  std::vector<TagProcessor*> tags;
  std::vector<PullProcessor*> pulls;
  bool keep = true;

public:
  VersionController(const std::string port, const char* filename);
  ~VersionController() { this->thread.join();}
  void start();
  void run();
  void stop();
};
