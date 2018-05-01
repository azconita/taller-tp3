#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <iostream>
#include <vector>


class Socket {
protected:
  int sock;

public:
  Socket();
  Socket(int sock);
  Socket(Socket &&other);
  ~Socket();
  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;

  int bind_and_listen(const char* port);
  int connect_to_server(const char* host, const char* port);
  Socket accept_connection();
  void shut();
  int send_buffer(size_t size, unsigned char *buffer);
  int receive_buffer(size_t size, unsigned char *buffer);
  int recv_int();
  std::string recv_string();
  void send_int(int i);
  void send_string(std::string s);

  void recv_file(std::string filename);
  std::vector<std::string> recv_vector() {
    std::vector<std::string> v;
    v.push_back("a14242");
    return v;
  };
  void send_file(std::string filename);

private:
  int get_hosts(struct addrinfo **result, const char* port, const char* host);
};

#endif
