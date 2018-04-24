#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <iostream>
#include <vector>

class Socket {
private:
  int port;

public:
  Socket(int port) : port(port) {}
  Socket(Socket &&other) : port(other.port) {}
  virtual ~Socket() {}
  std::string recv_filename() {return "A";}
  std::string recv_tag() {return "v2.0";}
  std::string recv_file() {return "texto de prueba";}
  std::string recv_hash() {return "a14242";}
  int recv_tagquantity() {return 2;}
  std::vector<std::string> recv_hashes() {
    std::vector<std::string> v;
    v.push_back("a14242");
    return v;
  };
  void send_file(std::string filename) { std::cout << "sending " << filename << '\n';}
  void send(int i) { std::cout << "socket.send: " << i << '\n';}
  Socket accept_client() { return Socket(1); }
};

#endif
