#include <iostream>
#include "Export.hpp"
#include "FactoryEntity.hpp"
#include "FactoryComponent.hpp"
#include "Entity.hpp"

Export::Export() {
  _setComponentPtr.reserve(128);
//  _data.reserve(64);
  _setComponentPtr[Component::POSITION] = &Export::getCPosition;
  _setComponentPtr[Component::BONUS] = &Export::getCBonus;
  _setComponentPtr[Component::FD] = &Export::getCFd;
  _setComponentPtr[Component::PLAYERINFO] = &Export::getCPlayerInfo;
  _setComponentPtr[Component::RANGE] = &Export::getCRange;
  _setComponentPtr[Component::TIMER] = &Export::getCTimer;
  _setComponentPtr[Component::MOVE] = &Export::getCMove;
  _setComponentPtr[Component::INPUTCONTEXT] = &Export::getCInputContext;
  _setComponentPtr[Component::NBBOMB] = &Export::getCNbBomb;
  _setComponentPtr[Component::ID] = &Export::getCId;
  _setComponentPtr[Component::BREAKABLE] = &Export::getCBreakable;
  _setComponentPtr[Component::SOLID] = &Export::getCSolid;
  _setComponentPtr[Component::ISAI] = &Export::getCIsAI;
}

// TODO: What do you say to the god of the Templates? Not Today
// ADD
void Export::addData(char data) {
  std::cout << " <setDataChar:" << (int)data << "> " << std::endl;
  _data.push_back(data);
}

void Export::addData(unsigned int data) {
  for (int i = sizeof(data) - 1; i >= 0 ; --i) {
    _data.push_back((char)(data >> (i * 8)));
  }
  std::cout << " <setDataUInt:" << data << "> " << std::endl;
}

void Export::addData(int data) {
  for (int i = sizeof(data) - 1; i >= 0 ; --i) {
    _data.push_back((char)(data >> (i * 8)));
  }
  std::cout << " <setDataInt:" << data << "> " << std::endl;
}

void Export::addData(unsigned long int data) {
  for (int i = sizeof(data) - 1; i >= 0 ; --i) {
    _data.push_back((char)(data >> (i * 8)));
  }
  std::cout << " <setDataULong:" << data << "> " << std::endl;
}

void Export::addData(float) {
  // Ah bha non
}

void Export::addData(std::string const & data) {
  for (unsigned int i = 0; i < data.size(); ++i) {
    _data.push_back(data[i]);
  }
  _data.push_back('\0');
  std::cout << " <setDataString:'" << data << "'> " << std::endl;
}

// GET
char Export::getDataChar(unsigned int &off) {
  off++;
  std::cout << " <getDataUInt:" << (int)_data.at(off) << "> " << std::endl;
  return _data.at(off);
}

unsigned int Export::getDataUInt(unsigned int &off) {
  unsigned int d(0);
  unsigned int size = sizeof(unsigned int) - 1;
  for (unsigned int i = 0; i <= size ; ++i) {
    d += (_data.at(off + i) << ((size - i) * 8));
  }
  off += size + 1;
  std::cout << " <getDataUInt:" << d << "> ";
  return d;
}
int Export::getDataInt(unsigned int &off) {
  int d(0);
  unsigned int size = sizeof(d) - 1;
  for (unsigned int i = 0; i <= size ; ++i) {
    d += (_data.at(off + i) << ((size - i) * 8));
  }
  off += size + 1;
  std::cout << " <getDataInt:" << d << "> " << std::endl;
  return d;
}
unsigned long int Export::getDataULong(unsigned int &off) {
  unsigned long int d(0);
  unsigned int size = sizeof(d) - 1;
  for (unsigned int i = 0; i <= size ; ++i) {
    d += (_data.at(off + i) << ((size - i) * 8));
  }
  off += size + 1;
  std::cout << " <getDataULong:" << d << "> " << std::endl;
  return d;
}
float Export::getDataFloat(unsigned int&) {
  // Ah bha non
  return 0.0;
}
std::string Export::getDataString(unsigned int &off) {
  std::string d;
  unsigned int i;
  for (i = off; _data[i] != 0; ++i) {
    d += _data[i];
  }
  off = i;
  std::cout << " <getDataString:'" << d << "'> " << std::endl;
  return d;
}

// MORE
void Export::setData(std::vector<char> const & data) {
  _data = data;
}

void Export::clear() {
  _data.clear();
}

Export::t_data const & Export::getData(void) const {
  return _data;
}

void Export::merge(Export const & data) {
  for (unsigned int i=0; i < data.getData().size(); ++i) {
    addData(data.getData()[i]);
  }
}

void Export::merge(Export const * data) {
  merge(*data);
}

Export * Export::merge(std::vector<Export *> const & data) {
  Export * save = new Export;
  for (unsigned int i=0; i < data.size(); ++i) {
    save->merge(data[i]);
  }
  return save;
}

Export * Export::save(std::vector<Entity> & entities) {
  std::vector<Export *> entitiesExport;
  Export * save;

  for (unsigned int i = 0; i < entities.size(); ++i) {
    entitiesExport.push_back(entities[i].serialize());
  }
  save = Export::merge(entitiesExport);
  for (unsigned int i = 0; i < entitiesExport.size(); ++i) {
    delete entitiesExport[i];
  }
  entitiesExport.clear();
  return save;
}

void Export::getCPosition(unsigned int &offset, BaseComponent *component) {
  unsigned int x, y;
  x = getDataUInt(offset);
  y = getDataUInt(offset);
  static_cast<Component::Position*>(component)->setX(x);
  static_cast<Component::Position*>(component)->setY(y);
}
void Export::getCBonus(unsigned int &offset, BaseComponent *component) {
  int v, t;
  v = getDataInt(offset);
  t = getDataInt(offset);
  static_cast<Component::Bonus*>(component)->setValue(v);
  static_cast<Component::Bonus*>(component)->setType((Component::Bonus::type)t);
}
void Export::getCFd(unsigned int &offset, BaseComponent *component) {
  int fd = getDataInt(offset);
  static_cast<Component::Fd*>(component)->setFd(fd);
}
void Export::getCPlayerInfo(unsigned int &offset, BaseComponent *component) {
//  std::string name = getDataString(offset);
  unsigned int id = getDataUInt(offset);
//  static_cast<Component::PlayerInfo*>(component)->setName(name);
  static_cast<Component::PlayerInfo*>(component)->setId(id);
}
void Export::getCRange(unsigned int &offset, BaseComponent *component) {
  unsigned int range = getDataUInt(offset);
  static_cast<Component::Range*>(component)->setRange(range);
}
void Export::getCTimer(unsigned int &offset, BaseComponent *component) {
  unsigned long int t = getDataULong(offset);
  static_cast<Component::Timer*>(component)->setMs(t);
}
void Export::getCMove(unsigned int &offset, BaseComponent *component) {
  int dir = getDataInt(offset);
  unsigned int speed = getDataUInt(offset);
  static_cast<Component::Move*>(component)->setDir((Component::Move::dir)dir);
  static_cast<Component::Move*>(component)->setSpeed(speed);
}
void Export::getCInputContext(unsigned int &offset, BaseComponent *component) {
  int l, r, u, d, drop;
  l = getDataInt(offset);
  r = getDataInt(offset);
  u = getDataInt(offset);
  d = getDataInt(offset);
  drop = getDataInt(offset);
  static_cast<Component::InputContext*>(component)->setLeft(l);
  static_cast<Component::InputContext*>(component)->setRight(r);
  static_cast<Component::InputContext*>(component)->setUp(u);
  static_cast<Component::InputContext*>(component)->setDown(d);
  static_cast<Component::InputContext*>(component)->setDrop(drop);
}
void Export::getCNbBomb(unsigned int &offset, BaseComponent *component) {
  int n = getDataInt(offset);
  static_cast<Component::NbBomb*>(component)->setNb(n);
}
void Export::getCId(unsigned int &offset, BaseComponent *component) {
  int id = getDataInt(offset);
  static_cast<Component::Id*>(component)->setId(id);
}
void Export::getCBreakable(unsigned int &, BaseComponent *) {
  //static_cast<Component::Breakable*>(component);
}
void Export::getCSolid(unsigned int &, BaseComponent *) {
  //static_cast<Component::Solid*>(component);
}
void Export::getCIsAI(unsigned int &, BaseComponent *) {
  //static_cast<Component::IsAI*>(component);
}

std::vector<Entity> Export::load() {
  unsigned int off = 0;
  std::vector<Entity> entities;
  while (off < _data.size()) {
    Entity::type entType = (Entity::type)getDataInt(off);
    unsigned int entComponentsCount = getDataInt(off);
    Entity ent = FactoryEntity::getInstance()->create(entType);
    unsigned int i = 0;
    while (i++ < entComponentsCount) {
      Component::type componentType = (Component::type)getDataInt(off);
      getDataInt(off); // useless count of variables
      std::cout << "Try to load a component type " << componentType << std::endl;
      BaseComponent * component = FactoryComponent::getInstance()->create(componentType);
      if (_setComponentPtr[componentType] != NULL) {
        (this->*_setComponentPtr[componentType])(off, component);
        std::cout << std::endl;
      }
      ent.addComponent(component);
    }
    entities.push_back(ent);
  }
  return entities;
}
