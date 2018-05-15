#ifndef REQUEST_PROCESS_H
#define REQUEST_PROCESS_H

#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "server_index.h"
#include "common_socket.h"

#define RETURN_CODE_OK 1
#define RETURN_CODE_FAIL 0

/*Thread: interfaz de procesos posibles (push, pull, tag)*/
class RequestProcessor {
private:
  std::thread t;
protected:
  Socket client;
  Index &index;
  bool finished = false;
  bool joined = false;
public:
  RequestProcessor(Index &index, Socket client) : client(std::move(client)),
              index(index) {}
  virtual ~RequestProcessor() {}
  void start();
  bool is_finished();
  bool not_joined();
  void mark_joined();
  void join();
  virtual void run() = 0;
  RequestProcessor(const RequestProcessor&) = delete;
  RequestProcessor& operator=(const RequestProcessor&) = delete;
  RequestProcessor(RequestProcessor&& other);
  RequestProcessor& operator=(RequestProcessor&& other);
};

#endif
