#ifndef EXCEPTIONS_HPP_
# define EXCEPTIONS_HPP_

# include <exception>
# include <string>

class BomberException : public std::exception {
protected:
  std::string const _str;
  std::string const _type;

public:
  BomberException(std::string const& str, std::string const& type = "");
  ~BomberException() throw();
  const char *what() const throw();
};

class ThreadException : public BomberException {
public:
  ThreadException(std::string const& str);
};

class MutexException : public BomberException {
public:
  MutexException(std::string const& str);
};

class LockException : public BomberException {
public:
  LockException(std::string const& str);
};

class UnlockException : public BomberException {
public:
  UnlockException(std::string const& str);
};

class NetworkException : public BomberException {
public:
  NetworkException(std::string const& str);
};

class ServerException : public BomberException {
public:
  ServerException(std::string const& str);
};

class ClientException : public BomberException {
public:
  ClientException(std::string const& str);
};

class DisplayException : public BomberException {
public:
  DisplayException(std::string const& str);
};

#endif
