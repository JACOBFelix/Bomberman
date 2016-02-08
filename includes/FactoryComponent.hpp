#ifndef FACTORYCOMPONENT_HPP
# define FACTORYCOMPONENT_HPP

# include <vector>
# include "BaseComponent.hpp"
# include "Components/InputContext.hpp"
# include "Components/Bonus.hpp"
# include "Components/Breakable.hpp"
# include "Components/Fd.hpp"
# include "Components/Id.hpp"
# include "Components/Move.hpp"
# include "Components/NbBomb.hpp"
# include "Components/PlayerInfo.hpp"
# include "Components/Position.hpp"
# include "Components/Range.hpp"
# include "Components/Solid.hpp"
# include "Components/Timer.hpp"
# include "Components/InputContext.hpp"
# include "Components/IsAI.hpp"

class FactoryComponent {
private:
  FactoryComponent();
  ~FactoryComponent();

public:
  static FactoryComponent *getInstance(void);
  BaseComponent * create(Component::type const);

  BaseComponent * createPosition();
  BaseComponent * createBonus();
  BaseComponent * createFd();
  BaseComponent * createPlayerInfo();
  BaseComponent * createRange();
  BaseComponent * createTimer();
  BaseComponent * createMove();
  BaseComponent * createInputContext();
  BaseComponent * createNbBomb();
  BaseComponent * createId();
  BaseComponent * createBreakable();
  BaseComponent * createSolid();
  BaseComponent * createIsAI();
  //TODO: Add InputContext

private:
  std::vector<BaseComponent * (FactoryComponent::*)()> _createPtrs;
};

#endif
