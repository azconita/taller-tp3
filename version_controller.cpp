#include <vector>
#include "index.h"
#include "request_processor.h"
#include <string>
#include "version_controller.h"

VersionController::VersionController(const std::string port, const char* filename) :
                              acc_socket(port), index(filename) { }

void VersionController::push_file(Socket &client) {
  PushProcessor proc(this->index, client);
  proc.run();
}

void VersionController::tag_files() {
  Socket client = this->acc_socket.accept_client();
  TagProcessor proc(this->index, client);
  proc.run();
}

void VersionController::pull_tag() {
  Socket client = this->acc_socket.accept_client();
  PullProcessor proc(this->index, client);
  proc.run();
}

void VersionController::start() {
  Socket client = this->acc_socket.accept_client();
  int code = client.recv_int();
  std::cout << "[debug] [VersionController] start: recv code: " << code << '\n';
  switch (code) {
    case 1: {
      //this->push_file(client);
      std::cout << "[debug] [VersionController] push file \n";
      PushProcessor proc(this->index, client);
      proc.run();
    }
      break;
    case 2:
      this->tag_files();
      break;
    case 3:
      this->pull_tag();
      break;
    default:
      std::cout << "comando recibido invalido\n";
  }
}
