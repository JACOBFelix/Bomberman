#include "Components/Id.hpp"

Component::Id::Id() : BaseComponent(Component::ID),
		      _id(0) {
}

Component::Id::~Id() {}

Component::Id::Id(Id const& rhs) : BaseComponent(Component::ID) {
  _id = rhs._id;
}

Component::Id& Component::Id::operator=(Id const& rhs) {
  if (this != &rhs) {
    _id = rhs._id;
  }
  return *this;
}
int Component::Id::getId(void) const {
  return _id;
}

void Component::Id::setId(int const& id) {
  _id = id;
}

Export * Component::Id::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(1);
  save->addData(_id);
  return save;
}
