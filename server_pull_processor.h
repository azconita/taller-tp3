#ifndef PULL_PROCESSOR_H
#define PULL_PROCESSOR_H

#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "server_index.h"
#include "common_socket.h"
#include "server_request_processor.h"

/*Thread de proceso Pull*/
class PullProcessor : public RequestProcessor {
public:
  PullProcessor(Index &index, Socket client) :
                    RequestProcessor(index, std::move(client)) {}
  ~PullProcessor() {}
  //Al lanzarse el thread, se ejecuta el run del PullProcessor
  void run();
};

#endif
