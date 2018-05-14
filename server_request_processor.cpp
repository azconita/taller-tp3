#include "server_request_processor.h"

void RequestProcessor::start() {
  this->t = std::thread(&RequestProcessor::run, this);
}

bool RequestProcessor::is_finished() {
  return this->finished;
}

void RequestProcessor::join() {
  this->t.join();
}

RequestProcessor::RequestProcessor(RequestProcessor&& other) :
                   client(std::move(other.client)), index(other.index)  {
 this->t = std::move(other.t);
}

RequestProcessor& RequestProcessor::operator=(RequestProcessor&& other) {
  this->t = std::move(other.t);
  return *this;
}
