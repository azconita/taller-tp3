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
  void start();
  bool is_finished();
  void join();
  virtual void run() = 0;
  RequestProcessor(const RequestProcessor&) = delete;
  RequestProcessor& operator=(const RequestProcessor&) = delete;
  RequestProcessor(RequestProcessor&& other);
  RequestProcessor& operator=(RequestProcessor&& other);

  std::thread::id get_id() {
    return this->t.get_id();
  }
};

#endif
