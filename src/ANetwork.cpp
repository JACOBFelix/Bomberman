#include "ANetwork.hpp"

ANetwork::ANetwork(std::string const& port) :
  _socket(-1) {
  _port = std::atoi(port.data());
}

ANetwork::~ANetwork() {
  if (_socket != -1
      && close(_socket) == -1)
    throw ServerException(std::string("close : ") + strerror(errno));
}

int ANetwork::getSocket(void) const {
  return _socket;
}
