#include "Exceptions.hpp"

BomberException::BomberException(std::string const& str, std::string const& type) :
  std::exception(), _str(str), _type(type) {}

BomberException::~BomberException() throw() {}

const char *BomberException::what() const throw() {
  return (_type + _str).data();
}

ThreadException::ThreadException(std::string const& str) : BomberException(str, "Thread error : ") {}

MutexException::MutexException(std::string const& str) : BomberException(str, "Mutex error : ") {}

LockException::LockException(std::string const& str) : BomberException(str, "Mutex Lock error : ") {}

UnlockException::UnlockException(std::string const& str) : BomberException(str, "Mutex unlock error : ") {}

NetworkException::NetworkException(std::string const& str) : BomberException(str, "Network error : ") {}

ServerException::ServerException(std::string const& str) : BomberException(str, "Server error : ") {}

ClientException::ClientException(std::string const& str) : BomberException(str, "Client error : ") {}

DisplayException::DisplayException(std::string const& str) : BomberException(str, "Display error : ") {}
