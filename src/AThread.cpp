#include "AThread.hpp"

AThread::AThread(void *(*routine)(void *), void *arg) {
  _ret = NULL;
  if (pthread_create(&_t, NULL, routine, arg))
    throw ThreadException("Unable to create thread");
}

AThread::~AThread() {}

void AThread::launch() {
  if (pthread_join(_t, &_ret))
    throw ThreadException("Unable to join thread");
}

bool AThread::isAlive() const {
  if (pthread_kill(_t, 0))
    return true;
  return false;
}
