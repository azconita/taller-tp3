#include "server_pull_processor.h"

void PullProcessor::run() {
  std::string tag = this->client.recv_string();
  std::vector<std::string> files = this->index.get_files_with_tag(tag);
  if (!files.empty()) {
    this->client.send_int(1);
    this->client.send_int(files.size());
    for (auto &f : files) {
      std::string filename = this->index.get_filename_of_hash(f);
      this->client.send_string(filename);
      this->client.send_file(f);
    }
  } else {
    this->client.send_int(0);
  }
  this->finished = true;
  this->client.shut();
}
