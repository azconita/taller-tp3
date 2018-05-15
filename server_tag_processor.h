#ifndef TAG_PROCESSOR_H
#define TAG_PROCESSOR_H

#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "server_index.h"
#include "common_socket.h"
#include "server_request_processor.h"

/*Thread de proceso Tag*/
class TagProcessor : public RequestProcessor {
public:
  TagProcessor(Index &index, Socket client) :
                RequestProcessor(index, std::move(client)) {}
  ~TagProcessor() {}
  //Al lanzarse el thread, se ejecuta el run del PullProcessor
  void run();
};

#endif
