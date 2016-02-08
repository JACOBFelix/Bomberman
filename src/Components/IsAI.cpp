#include "Components/IsAI.hpp"

Component::IsAI::IsAI() : BaseComponent(Component::ISAI) {}
Component::IsAI::~IsAI() {}

Export * Component::IsAI::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(0);
  return save;
}
