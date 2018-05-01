#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "index.h"
#include "socket.h"

class RequestProcessor {
  std::thread t;
protected:
  Socket &client;
  Index &index;
public:

  RequestProcessor(Index &index, Socket &client) : index(index), client(client) {}
  virtual ~RequestProcessor() {}
  void start() {
    this->t = std::thread(&RequestProcessor::run, this);
  }
  void join() {
    this->t.join();
  }
  virtual void run() = 0;
  RequestProcessor(const RequestProcessor&) = delete;
  RequestProcessor& operator=(const RequestProcessor&) = delete;
  RequestProcessor(RequestProcessor&& other) : client(other.client), index(other.index)  {
    this->t = std::move(other.t);
  }
  RequestProcessor& operator=(RequestProcessor&& other) {
    this->t = std::move(other.t);
    return *this;
  }
};

class PushProcessor : public RequestProcessor {
private:

public:
  PushProcessor(Index &index, Socket &client) : RequestProcessor(index, client) {}
  virtual ~PushProcessor() {}
  void save_file(std::string filename, std::string filecontent) {
    std::cout << "PushProcessor: " << filename << '\n' << filecontent << '\n';
  }
  void run() {
    std::cout << "[debug] [PushProcessor] run" << '\n';
    std::string filename = this->client.recv_string();
    std::cout << "[debug] [PushProcessor] run: recv filename: " << filename << '\n';
    std::string hash = this->client.recv_string();
    std::cout << "[debug] [PushProcessor] run: recv hash: " << hash << '\n';
    if(this->index.file_has_hash(filename, hash)) {
      //return 0;
      std::cout << "[debug] [PushProcessor] run: ya esta el archivo en el server" << '\n';
      this->client.send_int(0);
    } else {
      std::cout << "[debug] [PushProcessor] run: no esta el archivo en el server" << '\n';
      //return 1; //se debe retornar 1 al cliente
      this->client.send_int(1);
      std::string filecontent = this->client.recv_file();
      save_file(filename, filecontent); // deberia ser un file manager?
      this->index.add_file_hash(filename, hash);
    }
  }
};

class PullProcessor : public RequestProcessor {
private:

public:
  PullProcessor(Index &index, Socket &client) : RequestProcessor(index, client) {}
  virtual ~PullProcessor() {}
  void run() {
    std::cout << "run PullProcessor" << '\n';
    std::string tag = this->client.recv_string();
    if (this->index.tag_exists(tag)) {
      this->client.send_int(1);
      std::vector<std::string> files = this->index.get_files_with_tag(tag);
      for (auto &f : files) {
        this->client.send_file(f);
      }
    } else {
      this->client.send_int(0);
    }
  }
};

class TagProcessor : public RequestProcessor {
private:

public:
  TagProcessor(Index &index, Socket &client) : RequestProcessor(index, client) {}
  virtual ~TagProcessor() {}

  void run() {
    std::cout << "run TagProcessor" << '\n';
    int hash_quantity = this->client.recv_int();
    std::string tag = this->client.recv_string();
    std::vector<std::string> hashes = this->client.recv_vector();
    if (this->index.tag_exists(tag)) {
      this->client.send_int(0);
    } else {
      for (auto &h: hashes) {
        if (!this->index.hash_exists(h)) {
          this->client.send_int(0);
          return;
        }
      }
      this->index.create_tag_with_hashes(tag, hashes);
      this->client.send_int(1);
    }
  }
};
