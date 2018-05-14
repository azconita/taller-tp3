#ifndef REQUEST_PROCESS_H
#define REQUEST_PROCESS_H

#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "server_index.h"
#include "common_socket.h"

class RequestProcessor {
private:
  std::thread t;
protected:
  Socket client;
  Index &index;
  bool finished = false;
public:

  RequestProcessor(Index &index, Socket client) : client(std::move(client)),
              index(index) {}
  virtual ~RequestProcessor() {}
  void start() {
    this->t = std::thread(&RequestProcessor::run, this);
    //this->finished = true;
  }
  std::thread::id get_id() {
    return this->t.get_id();
  }
  bool is_finished() {
    return this->finished;
  }
  void join() {
    this->t.join();
  }
  virtual void run() = 0;
  RequestProcessor(const RequestProcessor&) = delete;
  RequestProcessor& operator=(const RequestProcessor&) = delete;
  RequestProcessor(RequestProcessor&& other) :
                      client(std::move(other.client)), index(other.index)  {
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
  PushProcessor(Index &index, Socket client) :
          RequestProcessor(index, std::move(client)) {}
  virtual ~PushProcessor() {}
  void save_file(std::string filename, std::string filecontent) {
    std::cout << "PushProcessor: " << filename << '\n' << filecontent << '\n';
  }
  void run() {
    std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
              << "] run" << '\n';
    std::string filename = this->client.recv_string();
    std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
              << "] run: recv filename: " << filename << '\n';
    std::string hash = this->client.recv_string();
    std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
              << "] run: recv hash: " << hash << '\n';
    if(!this->index.file_add_hash_if_possible(filename, hash)) {
      std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
                << "] run: ya esta el archivo en el server" << '\n';
      this->client.send_int(0);
    } else {
      std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
                << "] run: no esta el archivo en el server" << '\n';
      //se debe retornar 1 al cliente
      this->client.send_int(1);
      this->client.recv_file(hash);
    }
    this->finished = true;
    this->client.shut();
  }
};

class PullProcessor : public RequestProcessor {
private:

public:
  PullProcessor(Index &index, Socket client) :
                    RequestProcessor(index, std::move(client)) {}
  virtual ~PullProcessor() {}
  void run() {
    std::cout << "run PullProcessor" << '\n';
    std::string tag = this->client.recv_string();
    std::vector<std::string> files = this->index.get_files_with_tag(tag);
    if (!files.empty()) {
      this->client.send_int(1);
      this->client.send_int(files.size());
      for (auto &f : files) {
        this->client.send_string(this->index.get_filename_of_hash(f));
        this->client.send_file(f);
      }
    } else {
      this->client.send_int(0);
    }
    this->finished = true;
    this->client.shut();
  }
};

class TagProcessor : public RequestProcessor {
private:

public:
  TagProcessor(Index &index, Socket client) :
                    RequestProcessor(index, std::move(client)) {}
  virtual ~TagProcessor() {}

  void run() {
    std::cout << "[debug] [TagProcessor] [thread:" << this->get_id()
              << "] run" << '\n';
    int hash_quantity = this->client.recv_int();
    std::cout << "[debug] [TagProcessor] [thread:" << this->get_id()
              << "] hash quantity: " << hash_quantity << '\n';
    std::string tag = this->client.recv_string();
    std::cout << "[debug] [TagProcessor] [thread:" << this->get_id()
              << "] tag: " << tag << '\n';
    std::vector<std::string> hashes;
    for (int i = 0; i < hash_quantity; ++i) {
      hashes.push_back(this->client.recv_string());
    }
    if (this->index.add_tag_if_possible(tag, hashes))
      this->client.send_int(1);
    else
      this->client.send_int(0);
    this->finished = true;
    this->client.shut();
  }
};

#endif
