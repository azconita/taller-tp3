#ifndef PULL_PROCESSOR_H
#define PULL_PROCESSOR_H

#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include "server_index.h"
#include "common_socket.h"
#include "server_request_processor.h"


class PullProcessor : public RequestProcessor {
private:

public:
  PullProcessor(Index &index, Socket client) :
                    RequestProcessor(index, std::move(client)) {}
  ~PullProcessor() {std::cout << "PullProcessor destructor\n";}
  void run();
};


#endif
