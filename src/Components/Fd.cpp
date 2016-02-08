#include "Components/Fd.hpp"

Component::Fd::Fd() : BaseComponent(Component::FD) {}

Component::Fd::~Fd() {}

Component::Fd::Fd(Fd const& rhs) : BaseComponent(Component::FD) {
  _fd = rhs._fd;
}

Component::Fd& Component::Fd::operator=(Fd const& rhs) {
  if (this != &rhs) {
    _fd = rhs._fd;
  }
  return *this;
}
int Component::Fd::getFd(void) const {
  return _fd;
}

void Component::Fd::setFd(int const& fd) {
  _fd = fd;
}

Export * Component::Fd::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(1);
  save->addData(_fd);
  return save;
}
