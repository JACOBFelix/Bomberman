#include "ScopeLock.hpp"

ScopeLock::ScopeLock(AMutex& mutex) : _mutex(mutex) {
  _mutex.lock();
}

ScopeLock::~ScopeLock() {
  _mutex.unlock();
}
