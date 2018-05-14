#ifndef PUSH_PROCESSOR_H
#define PUSH_PROCESSOR_H

#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "server_index.h"
#include "common_socket.h"
#include "server_request_processor.h"

class PushProcessor : public RequestProcessor {
public:
  PushProcessor(Index &index, Socket client) :
          RequestProcessor(index, std::move(client)) {}
  ~PushProcessor() {std::cout << "PushProcessor destructor\n";}
  void run();
};


#endif
