#pragma once

namespace Component {
  enum type {
    POSITION,
    BONUS,
    FD,
    PLAYERINFO,
    RANGE,
    TIMER,
    MOVE,
    BINDINGS,
    NBBOMB,
    ID,
    BREAKABLE,
    SOLID,
    SKIN,
    ISAI,
    MODEL,
    INPUTCONTEXT,
  };
}

class BaseComponent {
public:
  BaseComponent(Component::type);
  ~BaseComponent();

  BaseComponent(BaseComponent const &);
  BaseComponent& operator=(BaseComponent const &);
  Component::type getType() const;

private:
  Component::type _type;
};
