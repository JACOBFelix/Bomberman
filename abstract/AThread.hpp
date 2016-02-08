#ifndef ATHREAD_HPP_
# define ATHREAD_HPP_

# include <csignal>
# include <pthread.h>
# include "Exceptions.hpp"

class AThread {
protected:
  pthread_t _t;
  void *_ret;

public:
  AThread(void *(*routine)(void *), void *arg);
  virtual ~AThread();
  virtual void launch() = 0;
  bool isAlive() const;
};

#endif
