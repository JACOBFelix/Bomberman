#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <vector>
# include <fstream>
# include <string>

# include "MapConfiguration.hpp"

# include "ASystem.hpp"
# include "Entity.hpp"
# include "Systems/Bomb.hpp"
# include "Systems/Draw.hpp"
# include "Systems/Input.hpp"
# include "Systems/AI.hpp"
# include "Systems/Move.hpp"
# include "FactoryEntity.hpp"

class Engine {
public:
  Engine(int const timer, unsigned int const w = 10, unsigned int const h = 10, unsigned int const player = 2, unsigned int const ia = 1);
  ~Engine();

  void saveGame(std::string const & path);
  void loadGame(std::string const & path);

  int update(void);
  void mainLoop(void);
  void setInput(gdl::Input const &);
  void setContext(gdl::SdlContext const &);

private:
  int const _timer;
  unsigned int const _width;
  unsigned int const _height;
  std::vector<ASystem *> _systems;
  std::vector<Entity> _entities;
  gdl::Input _input;
  gdl::SdlContext _context;

  void generateWall(unsigned int const i, unsigned int const j);
  void generatePlayers(unsigned int const human, unsigned int const ai);
  bool isNearPlayer(unsigned int const i, unsigned int const j);
  void generateDestructibleWalls(void);
};

#endif
