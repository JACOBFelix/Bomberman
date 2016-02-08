#ifndef FACTORYENTITY_HPP_
# define FACTORYENTITY_HPP_

# include <vector>
# include "MapConfiguration.hpp"
# include "Model.hh"
# include "Entity.hpp"
# include "Components/Model.hpp"

class FactoryEntity {
private:
  FactoryEntity();
  ~FactoryEntity();

public:
  static FactoryEntity *getInstance(void);
  Entity create(Entity::type const);

  gdl::Model& getBonusPink(void);
  gdl::Model& getBonusIce(void);
  gdl::Model& getBonusFlame(void);

private:
  std::vector<Entity> _ct;
  std::vector<Entity (FactoryEntity::*)(void)> const _ptr;

  Entity newPlayer(void);
  Entity newTile(void);
  Entity newBomb(void);
  Entity newPowerUp(void);
  Entity newExplosion(void);
  Entity newWall(void);
  Entity newDestructibleWall(void);

  // TODO: suffix Model
  gdl::Model _bonusIce;
  gdl::Model _bonusFlame;
  gdl::Model _bonusPink;
  gdl::Model _flames;
  gdl::Model _bombModel;
  gdl::Model _wallModel;
  gdl::Model _groundModel;
  gdl::Model _koalaModel;
  gdl::Model _brokenWallModel;
};

#endif
