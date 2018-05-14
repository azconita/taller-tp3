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
  for(auto &client : this->pushs) {
    client->join();
    delete(client);
  }
  this->pushs.clear();
  for(auto &client : this->tags) {
    client->join();
    delete(client);
  }
  this->tags.clear();
  for(auto &client : this->pulls) {
    client->join();
    delete(client);
  }
  this->pulls.clear();
}

void VersionController::run() {
  while(this->keep) {
    try {
      Socket client = this->acc_socket.accept_client();
      if (client.not_valid())
        continue;
      int code = client.recv_int();
      switch (code) {
        case 1: {
            //PushProcessor proc(this->index, client);
            //this->clients.push_back(&proc);
            //proc.start();
            PushProcessor* p = new PushProcessor(this->index, std::move(client));
            this->pushs.push_back(p);
            p->start();
          }
          break;
        case 2: {
            //TagProcessor proc(this->index, client);
            //this->tags.push_back(&proc);
            //proc.start();
            TagProcessor* p = new TagProcessor(this->index, std::move(client));
            this->tags.push_back(p);
            p->start();
          }
          break;
        case 3: {
            //PullProcessor proc(this->index, client);
            //this->pulls.push_back(&proc);
            //proc.start();
            PullProcessor* p = new PullProcessor(this->index, std::move(client));
            this->pulls.push_back(p);
            p->start();
          }
          break;
        //default:
      }
      /*for(auto &client : this->pushs) {
        if (client->is_finished()) {
          std::cout << "[debug] [VersionController] joining push thread \n";
          client->join();
          std::cout << "[debug] [VersionController] joined push thread \n";

        }
      }
      for(auto &client : this->tags) {
        if (client->is_finished()) {
          std::cout << "[debug] [VersionController] joining tag thread \n";
          client->join();
          std::cout << "[debug] [VersionController] joined tag thread \n";
        }
      }
      for(auto &client : this->pulls) {
        if (client->is_finished()) {
          std::cout << "[debug] [VersionController] joining pull thread \n";
          client->join();
          std::cout << "[debug] [VersionController] joined pull thread \n";
        }
      }*/
    } catch (int e) {
      continue;
    }
  }
}
