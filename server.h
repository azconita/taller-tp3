#include <string>
#include <vector>
#include "index.h"
#include "socket.h"
#include "request_processor.h"

class Server {
private:
  Socket acc_socket;
  Index index;
  std::vector<Socket*> clients;

public:
  Server(int port, const char* filename) : acc_socket(port), index(filename) {}
  virtual ~Server() { }
  void push_file(std::string filename, std::string hash) {
    Socket client = this->acc_socket.accept_client();
    PushProcessor proc(this->index, client);
    proc.run();
  }
  void tag_files() {
    Socket client = this->acc_socket.accept_client();
    TagProcessor proc(this->index, client);
    proc.run();
  }
  void pull_tag(std::string tag) {
    Socket client = this->acc_socket.accept_client();
    PullProcessor proc(this->index, client);
    proc.run();
  }
};
