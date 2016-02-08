#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <string>
# include <vector>
# include "Game.hh"
# include "Texture.hh"
# include "Geometry.hh"
# include "OpenGL.hh"
# include "BasicShader.hh"
# include "SdlContext.hh"
# include "Model.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"
# include "Cube.hpp"
# include "Engine.hpp"

class Display : public gdl::Game
{
public:
  enum viewType {MENU, OPTIONS, GAME};

public:
  Display(unsigned int, unsigned int);
  ~Display();
  bool initialize();
  bool update();
  void draw();
  bool updateGame();
  void loop();
  void PrintIntroScreen();

private:
  Display(const Display &) {};
  Display &operator=(const Display &) { return *this; };

  Engine* _engine;
  unsigned int _nbPlayers;

  viewType _view;
  std::vector<int (Display::*)(void)> _viewTab;
  int menu();
  int options();
  int game();

  std::vector<void (Display::*)(void)> _updateTab;
  void updateMenu();
  void updateOptions();

  std::vector<std::pair<void (Display::*)(void), int> > _menuKeys;
  void keyMenuQuit();
  void keyMenuM();
  void keyMenuN();
  void keyMenuO();

  gdl::SdlContext _context;
  gdl::BasicShader _shader;
  gdl::Clock _clock;
  gdl::Input _input;
  gdl::Texture _backgroundTexture;
  gdl::Texture _introTexture;
  gdl::Texture _wallTexture;
  gdl::Texture _brokenWallTexture;
  gdl::Texture _optionsTexture;
  gdl::Texture _optionsTexture2;
  gdl::Geometry _background;
  gdl::Geometry _digit;

  std::vector<gdl::Texture*> _digitTextures;

  Uint32 _wavLength;
  Uint8 *_wavBuffer;

  unsigned int _width;
  unsigned int _height;
  float x;
  float y;
};

#endif
