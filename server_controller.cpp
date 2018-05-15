#include <vector>
#include "server_index.h"
#include "server_request_processor.h"
#include <string>
#include "server_controller.h"

VersionController::VersionController(const std::string port,
                                    const char* filename) :
                              acc_socket(port), index(filename) { }

VersionController::~VersionController() {
  this->stop();
  this->thread.join();
}

void VersionController::stop() {
  this->acc_socket.shut();
  this->keep = false;
  for (auto &client : this->pushs) {
    client->join();
    delete(client);
  }
  this->pushs.clear();
  for (auto &client : this->tags) {
    client->join();
    delete(client);
  }
  this->tags.clear();
  for (auto &client : this->pulls) {
    client->join();
    delete(client);
  }
  this->pulls.clear();
}

void VersionController::start() {
  this->thread = std::thread(&VersionController::run, this);
}

void VersionController::run() {
  while (this->keep) {
    try {
      Socket client = this->acc_socket.accept_client();
      if (client.not_valid())
        continue;
      int code = client.recv_int();
      switch (code) {
        case PUSH_REQUEST: {
          PushProcessor* p = new PushProcessor(this->index, std::move(client));
          this->pushs.push_back(p);
          p->start();
          }
          break;
        case TAG_REQUEST: {
          TagProcessor* p = new TagProcessor(this->index, std::move(client));
          this->tags.push_back(p);
          p->start();
          }
          break;
        case PULL_REQUEST: {
          PullProcessor* p = new PullProcessor(this->index, std::move(client));
          this->pulls.push_back(p);
          p->start();
          }
          break;
      }
      /*for(auto &client : this->pushs) {
        if (client->is_finished()) {
          std::cout << "[debug] [VersionController] joining push thread \n";
          client->join();
          //se debe borrar el item del vector
        }
      }
      for(auto &client : this->tags) {
        if (client->is_finished()) {
          std::cout << "[debug] [VersionController] joining tag thread \n";
          client->join();
          //se debe brrar el item del vector
        }
      }
      for(auto &client : this->pulls) {
        if (client->is_finished()) {
          std::cout << "[debug] [VersionController] joining pull thread \n";
          client->join();
          //se debe borrar el item del vector
        }
      }*/
    } catch (int e) {
      continue;
    }
  }
}
