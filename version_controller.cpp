#include <string>
#include <vector>
#include "index.h"
#include "request_processor.h"
#include "version_controller.h"

VersionController::VersionController(const std::string port, const char* filename) :
                              acc_socket(port), index(filename) { }

void VersionController::push_file(std::string filename, std::string hash) {
  ServerSocket client = this->acc_socket.accept_client();
  PushProcessor proc(this->index, client);
  proc.run();
}

void VersionController::tag_files() {
  ServerSocket client = this->acc_socket.accept_client();
  TagProcessor proc(this->index, client);
  proc.run();
}

void VersionController::pull_tag(std::string tag) {
  ServerSocket client = this->acc_socket.accept_client();
  PullProcessor proc(this->index, client);
  proc.run();
}
