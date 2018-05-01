#include <vector>
#include "index.h"
#include "request_processor.h"
#include <string>
#include "version_controller.h"

VersionController::VersionController(const std::string port, const char* filename) :
                              acc_socket(port), index(filename) { }

void VersionController::start() {
  this->thread = std::thread(&VersionController::run, this);
}

void VersionController::run() {
  while(true) {
    Socket client = this->acc_socket.accept_client();
    int code = client.recv_int();
    std::cout << "[debug] [VersionController] start: recv code: " << code << '\n';
    switch (code) {
      case 1: {
          std::cout << "[debug] [VersionController] push file \n";
          //PushProcessor proc(this->index, client);
          //this->clients.push_back(&proc);
          //proc.start();
          PushProcessor* p = new PushProcessor(this->index, std::move(client));
          this->pushs.push_back(p);
          p->start();
        }
        break;
      case 2: {
          std::cout << "[debug] [VersionController] tag hashes \n";
          TagProcessor proc(this->index, client);
          this->tags.push_back(&proc);
          proc.start();
        }
        break;
      case 3: {
          std::cout << "[debug] [VersionController] pull tag \n";
          PullProcessor proc(this->index, client);
          this->pulls.push_back(&proc);
          proc.start();
        }
        break;
      default:
        std::cout << "comando recibido invalido\n";
    }
    for(auto &client : this->pushs) {
      if (client->is_finished()) {
        std::cout << "[debug] [VersionController] joining push thread \n";
        client->join();
        delete client;
      }
    }
    for(auto &client : this->tags) {
      if (client->is_finished())
        client->join();
    }
    for(auto &client : this->pulls) {
      if (client->is_finished())
        client->join();
    }
  }
}
