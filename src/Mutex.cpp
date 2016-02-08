#include <cerrno>
#include "Mutex.hpp"
#include "Exceptions.hpp"

Mutex::Mutex() : AMutex() {}

Mutex::~Mutex() {}

void Mutex::lock() {
  if (pthread_mutex_lock(&_mutex))
    throw LockException("Unable to lock the mutex");
}

bool Mutex::trylock() {
  switch (pthread_mutex_lock(&_mutex)) {
  case 0:
    return true;
  case EBUSY:
    return false;
  default:
    throw LockException("Unable to try/lock the mutex");
  }
}

void Mutex::unlock() {
  if (pthread_mutex_unlock(&_mutex))
    throw UnlockException("Unable to unlock the mutex");
}
