#include <vector>
#include "server_index.h"
#include "server_request_processor.h"
#include <string>
#include "server_controller.h"

VersionController::VersionController(const std::string port, const char* filename) :
                              acc_socket(port), index(filename) { }

void VersionController::start() {
  this->thread = std::thread(&VersionController::run, this);
}

void VersionController::stop() {
  this->acc_socket.shut();
  this->keep = false;
  for(auto &client : this->pushs)
    client->join();
  for(auto &client : this->tags)
    client->join();
  for(auto &client : this->pulls)
    client->join();
}

void VersionController::run() {
  while(this->keep) {
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
          //TagProcessor proc(this->index, client);
          //this->tags.push_back(&proc);
          //proc.start();
          TagProcessor* p = new TagProcessor(this->index, std::move(client));
          this->tags.push_back(p);
          p->start();
        }
        break;
      case 3: {
          std::cout << "[debug] [VersionController] pull tag \n";
          //PullProcessor proc(this->index, client);
          //this->pulls.push_back(&proc);
          //proc.start();
          PullProcessor* p = new PullProcessor(this->index, std::move(client));
          this->pulls.push_back(p);
          p->start();
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
