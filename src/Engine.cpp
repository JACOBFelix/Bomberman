#include <ctime>
#include "Engine.hpp"
#include "Export.hpp"

Engine::Engine(int const timer, unsigned int const w, unsigned int const h, unsigned int const human, unsigned int const ai)  : _timer(timer), _width(w), _height(h) {
  _systems.push_back(new System::Input(_entities));
  _systems.push_back(new System::Move(_entities));
  _systems.push_back(new System::Draw(_entities));
  _systems.push_back(new System::AI(_entities));
  _systems.push_back(new System::Bomb(_entities));
  std::srand(std::time(NULL));
  for (unsigned int i = 0; i < _width; ++i)
    for (unsigned int j = 0; j < _height; ++j)
      if (i == 0 || j == 0 || i + 1 == _width || j + 1 == _height
	  || (i % 2 == 0 && j % 2 == 0))
	  generateWall(i, j);
  generatePlayers(human, ai);
  generateDestructibleWalls();
}

Engine::~Engine() {}

void Engine::saveGame(std::string const & path) {
  Export * save = Export::save(_entities);
  std::ofstream f(path);
  for (unsigned int i = 0; i < save->getData().size(); ++i)
    f << save->getData()[i];
  f.flush();
}

void Engine::loadGame(std::string const & path) {
  Export * save = new Export;
  std::ifstream f(path);
  while (!f.eof()) {
    char c;
    f.get(c);
    save->addData(c);
  }
  _entities = save->load();
}

void	Engine::generateWall(unsigned int const i, unsigned int const j) {
  Entity wall = FactoryEntity::getInstance()->create(Entity::WALL);

  static_cast<Component::Position *>(wall[Component::POSITION])->setX(i * PIXELS_BY_CASE);
  static_cast<Component::Position *>(wall[Component::POSITION])->setY(j * PIXELS_BY_CASE);
  static_cast<Component::Move *>(wall[Component::MOVE])->setDir(Component::Move::NONE);
  _entities.push_back(wall);
}

void	Engine::generatePlayers(unsigned int const human, unsigned int const ai) {
  unsigned int const w2 = _width * _width / (human + ai) + 1;
  unsigned int const h2 = _height * _height / (human + ai) + 1;
  Component::InputContext *input;
  for (unsigned int i = 0; i < human + ai; ++i) {
    unsigned int x = (w2 / 2 + i * w2) % _width;
    unsigned int y = (h2 / 2 + i * h2) % _height;
    if (x == 0 || y == 0 || x + 1 == _width || y + 1 == _height
	|| (x % 2 == 0 && y % 2 == 0))
      ++x;
    Entity player = FactoryEntity::getInstance()->create(Entity::PLAYER);
    if (i >= human)
      player.addComponent(Component::ISAI);

    input = static_cast<Component::InputContext *>(player[Component::INPUTCONTEXT]);
    if (!i) {
      input->setUp(SDLK_z);
      input->setDown(SDLK_s);
      input->setLeft(SDLK_q);
      input->setRight(SDLK_d);
      input->setDrop(SDLK_LCTRL);
    } else if (i < human) {
      input->setUp(SDLK_UP);
      input->setDown(SDLK_DOWN);
      input->setLeft(SDLK_LEFT);
      input->setRight(SDLK_RIGHT);
      input->setDrop(SDLK_RCTRL);
    }
    static_cast<Component::Position *>(player[Component::POSITION])->setX(x * PIXELS_BY_CASE);
    static_cast<Component::Position *>(player[Component::POSITION])->setY(y * PIXELS_BY_CASE);
    static_cast<Component::PlayerInfo *>(player[Component::PLAYERINFO])->setId(i);
    static_cast<Component::Range *>(player[Component::RANGE])->setRange(2000);
    _entities.push_back(player);
  }
}

bool	Engine::isNearPlayer(unsigned int const i, unsigned int const j) {
  std::vector<Entity>::iterator it = _entities.begin();
  Component::Position *pos;

  for (; it != _entities.end(); ++it)
    if (it->getType() == Entity::PLAYER
	&& (pos = static_cast<Component::Position *>((*it)[Component::POSITION]))) {
      if ((i == pos->getX() / PIXELS_BY_CASE && j >= pos->getY() / PIXELS_BY_CASE - 1 && j <= pos->getY() / PIXELS_BY_CASE + 1)
	  || (j == pos->getY() / PIXELS_BY_CASE && i >= pos->getX() / PIXELS_BY_CASE - 1 && i <= pos->getX() / PIXELS_BY_CASE + 1)) {
	return true;
      }
    }
  return false;
}

void	Engine::generateDestructibleWalls(void) {
  for (unsigned int i = 1; i < _width - 1; ++i)
    for (unsigned int j = 1; j < _height - 1; ++j) {
      if (!isNearPlayer(i, j)
	  && !(i == 0 || j == 0 || i + 1 == _width || j + 1 == _height
	       || (i % 2 == 0 && j % 2 == 0))
	  && std::rand() % 100 < 70) {
	Entity destructibleWall = FactoryEntity::getInstance()->create(Entity::DESTRUCTIBLEWALL);
	static_cast<Component::Position *>(destructibleWall[Component::POSITION])->setX(i * PIXELS_BY_CASE);
	static_cast<Component::Position *>(destructibleWall[Component::POSITION])->setY(j * PIXELS_BY_CASE);
	static_cast<Component::Move *>(destructibleWall[Component::MOVE])->setDir(Component::Move::NONE);
	_entities.push_back(destructibleWall);
      }
    }
}

int	Engine::update(void) {
  std::vector<ASystem *>::iterator it;
  std::vector<ASystem *>::iterator end = _systems.end();

  for (it = _systems.begin(); it != end; ++it) {
    if ((*it)->update(_timer))
      return 1;
  }
  int i = 0;
  for (std::vector<Entity>::iterator ite = _entities.begin(); ite < _entities.end(); ++ite, i += (ite->getType() == Entity::PLAYER));
  return i <= 1;
}

void	Engine::mainLoop(void) {
  while (42) {
    update();
  }
}

void	Engine::setInput(gdl::Input const &input) {
  _input = input;
  static_cast<System::Input *>(_systems[0])->setInput(input);
}

void	Engine::setContext(gdl::SdlContext const &context) {
  _context = context;
  static_cast<System::Draw *>(_systems[2])->setContext(context);
  static_cast<System::Input *>(_systems[0])->setContext(context);
}
