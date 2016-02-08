#include "Components/PlayerInfo.hpp"

Component::PlayerInfo::PlayerInfo() : BaseComponent(Component::PLAYERINFO) {}

Component::PlayerInfo::~PlayerInfo() {}

Component::PlayerInfo::PlayerInfo(PlayerInfo const& rhs) : BaseComponent(Component::PLAYERINFO) {
  _name = rhs._name;
  _id = rhs._id;
}

Component::PlayerInfo& Component::PlayerInfo::operator=(PlayerInfo const& rhs) {
  if (this != &rhs) {
    _name = rhs._name;
    _id = rhs._id;
  }
  return *this;
}

std::string const& Component::PlayerInfo::getName(void) const {
  return _name;
}

void Component::PlayerInfo::setName(std::string const& name) {
  _name = name;
}

unsigned int Component::PlayerInfo::getId(void) const {
  return _id;
}

int Component::PlayerInfo::getScore(void) const {
  return _score;
}

void Component::PlayerInfo::setId(unsigned int const& id) {
  _id = id;
}

void Component::PlayerInfo::setScore(int const& score) {
  _score = score;
}

Export * Component::PlayerInfo::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(2);
//  save->addData(_name);
  save->addData(_id);
  return save;
}
