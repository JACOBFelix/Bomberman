#include "Client.hpp"

Client::Client(std::string const& port, std::string const& ip) :
  ANetwork(port), _ip(ip)  {
  int err;
  struct sockaddr_in s_in;
  struct addrinfo hints;
  struct addrinfo *ai;

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((err = getaddrinfo(ip.data(), port.data(), &hints, &ai)))
    throw ClientException(std::string("getaddrinfo : ") + gai_strerror(err));
  if ((_socket = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1)
    throw ClientException(std::string("socket : ") + strerror(errno));
  if (connect(_socket, reinterpret_cast<struct sockaddr *>(&s_in), sizeof(s_in)) == -1) {
    close(_socket);
    throw ClientException(std::string("connect : ") + strerror(errno));
  }
  freeaddrinfo(ai);
}
