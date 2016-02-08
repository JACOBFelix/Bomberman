#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <vector>

# include "FactoryComponent.hpp"
# include "BaseComponent.hpp"
# include "Export.hpp"

class Entity {
public:
  enum type {PLAYER, TILE, BOMB, POWERUP, EXPLOSION, WALL, DESTRUCTIBLEWALL};

public:
  Entity(type const type);
  ~Entity();

  Entity(Entity const& o);
  Entity& operator=(Entity const& o);

  BaseComponent* operator[](Component::type const type) const;
  Entity& operator<<(Component::type const type);
  Entity& operator<<(BaseComponent *);

  void addComponent(Component::type const type);
  void addComponent(BaseComponent *);
  BaseComponent* getComponent(Component::type const type) const;
  type getType(void) const;

  Export * serialize() const;

private:
  type _type;
  std::vector<BaseComponent *> _components;
};

#endif
