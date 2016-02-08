#pragma once

#include <vector>
#include <string>

#include "BaseComponent.hpp"

class Entity;

class Export
{
public:
  enum dataType {ENTITY, COMPONENT};
  typedef std::vector<char> t_data;

public:
  Export();
  ~Export() {}

  void addData(char);
  void addData(unsigned int);
  void addData(int);
  void addData(unsigned long int);
  void addData(float);
  void addData(std::string const &);

  char getDataChar(unsigned int &off);
  unsigned int getDataUInt(unsigned int &off);
  int getDataInt(unsigned int &off);
  unsigned long int getDataULong(unsigned int &off);
  float getDataFloat(unsigned int &off);
  std::string getDataString(unsigned int &off);

  void setData(std::vector<char> const & data);
  void clear();
  t_data const & getData(void) const;
  void merge(Export const & data);
  void merge(Export const * data);

  static Export * merge(std::vector<Export *> const & data);

  static Export * save(std::vector<Entity> & entities);

  void getCPosition(unsigned int &offset, BaseComponent *component);
  void getCBonus(unsigned int &offset, BaseComponent *component);
  void getCFd(unsigned int &offset, BaseComponent *component);
  void getCPlayerInfo(unsigned int &offset, BaseComponent *component);
  void getCRange(unsigned int &offset, BaseComponent *component);
  void getCTimer(unsigned int &offset, BaseComponent *component);
  void getCMove(unsigned int &offset, BaseComponent *component);
  void getCInputContext(unsigned int &offset, BaseComponent *component);
  void getCNbBomb(unsigned int &offset, BaseComponent *component);
  void getCId(unsigned int &offset, BaseComponent *component);
  void getCBreakable(unsigned int &offset, BaseComponent *component);
  void getCSolid(unsigned int &offset, BaseComponent *component);
  void getCSkin(unsigned int &offset, BaseComponent *component);
  void getCIsAI(unsigned int &offset, BaseComponent *component);

  std::vector<Entity> load();

private:
  t_data _data;
  std::vector<void (Export::*)(unsigned int &, BaseComponent *)> _setComponentPtr;
};

#include "Entity.hpp"
