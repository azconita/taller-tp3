#ifndef PUSH_PROCESSOR_H
#define PUSH_PROCESSOR_H

#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "server_index.h"
#include "common_socket.h"
#include "server_request_processor.h"

/*Thread de proceso Push*/
class PushProcessor : public RequestProcessor {
public:
  PushProcessor(Index &index, Socket client) :
          RequestProcessor(index, std::move(client)) {}
  ~PushProcessor() {}
  //Al lanzarse el thread, se ejecuta el run del PushProcessor
  void run();
};


#endif
