#include <iostream>
#include <string>
#include <sstream>
#include "Display.hpp"
#include "Exceptions.hpp"

static Uint32 audioLength;
static Uint8 *audioPos;

Display::Display(unsigned int w, unsigned int h) : _engine(NULL) {
  _height = h;
  _width = w;
  _view = MENU;

  _viewTab.push_back(&Display::menu);
  _viewTab.push_back(&Display::menu);
  _viewTab.push_back(&Display::game);

  _updateTab.push_back(&Display::updateMenu);
  _updateTab.push_back(&Display::updateOptions);

  _menuKeys.push_back(std::pair<void (Display::*)(void), int>(&Display::keyMenuQuit, SDLK_ESCAPE));
  _menuKeys.push_back(std::pair<void (Display::*)(void), int>(&Display::keyMenuM, SDLK_m));
  _menuKeys.push_back(std::pair<void (Display::*)(void), int>(&Display::keyMenuN, SDLK_n));
  _menuKeys.push_back(std::pair<void (Display::*)(void), int>(&Display::keyMenuO, SDLK_o));
}

Display::~Display() {
  if (_engine)
    delete _engine;
}

int Display::menu() {
  if (!update())
    return 0;
  draw();
  return 1;
}

int Display::game() {
  if (!updateGame())
    _view = MENU;
  return 1;
}

void AudioCallback(void *, Uint8 *music, int length) {
  if (audioLength == 0)
    return;
  length = (length > (int)audioLength ? audioLength : length);
  SDL_memcpy (music, audioPos, length);
  SDL_MixAudio(music, audioPos, length, SDL_MIX_MAXVOLUME);
  audioPos = audioPos + length;
  audioLength = audioLength - length;
}

int Display::options() {
  return 1;
}

void Display::loop() {
  (this->*_viewTab[_view])();
}

void Display::PrintIntroScreen() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();

  _introTexture.bind();

  glm::vec3 _position, _rotation, _scale;
  _rotation.x = _rotation.y = _rotation.z = 0;
  _position.x = _position.y = _position.z = 0;
  _scale.x = _scale.y = _scale.z = 0.652;

  glm::mat4 transform(1);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);

  _background.draw(_shader, transform, GL_QUADS);

  _context.flush();
}

bool Display::initialize() {
  if (!_context.start(_width, _height, "Ponies roxx"))
    throw DisplayException("Could not start SDL context");
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./lib/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./lib/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    throw DisplayException("Could not load shader");

  glm::mat4 projection = glm::perspective(574.0f, float(_width) / float(_height), 0.1f, 100.0f);
  glm::mat4 transformation = glm::lookAt(glm::vec3(0, 0, 90), glm::vec3(0, 0, 0), glm::vec3(0, 10, 0));

  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);

  for (int i = 0; i < 10; i++)
    {
      gdl::Texture *temp = new gdl::Texture;
      std::stringstream ss;
      ss << "./assets/digit";
      ss << i;
      ss << ".tga";
      std::string str;
      ss >> str;
      if (!temp->load(str.c_str()))
	throw DisplayException("Could not load digit texture");
      _digitTextures.push_back(temp);
    }

  // On charge l'image du menu
  if (!_introTexture.load("./assets/intro.tga"))
    throw DisplayException("Could not load intro texture");
  if (!_backgroundTexture.load("./assets/menu.tga"))
    throw DisplayException("Could not load background texture");
  if (!_optionsTexture.load("./assets/options.tga"))
    throw DisplayException("Could not load options texture");
  if (!_optionsTexture2.load("./assets/options2.tga"))
    throw DisplayException("Could not load options texture");

  /* Background "square" creation */
  _background.pushUv(glm::vec2(1, 1));
  _background.pushVertex(glm::vec3(-float(_width) / 2, -float(_height) / 2, 0.5f));
  _background.pushUv(glm::vec2(0, 1));
  _background.pushVertex(glm::vec3(float(_width) / 2, -float(_height) / 2, 0.5f));
  _background.pushUv(glm::vec2(0, 0));
  _background.pushVertex(glm::vec3(float(_width) / 2, float(_height) / 2, 0.5f));
  _background.pushUv(glm::vec2(1, 0));
  _background.pushVertex(glm::vec3(-float(_width) / 2, float(_height) / 2, 0.5f));

  _background.build();

  /* Digit square creation */
  _digit.pushUv(glm::vec2(1, 1));
  _digit.pushVertex(glm::vec3(-float(50) / 2, -float(50) / 2, 0.5f));
  _digit.pushUv(glm::vec2(0, 1));
  _digit.pushVertex(glm::vec3(float(50) / 2, -float(50) / 2, 0.5f));
  _digit.pushUv(glm::vec2(0, 0));
  _digit.pushVertex(glm::vec3(float(50) / 2, float(50) / 2, 0.5f));
  _digit.pushUv(glm::vec2(1, 0));
  _digit.pushVertex(glm::vec3(-float(50) / 2, float(50) / 2, 0.5f));

  _digit.build();

  PrintIntroScreen();

  /* Musique */

  if (SDL_Init(SDL_INIT_AUDIO) < 0)
    throw DisplayException("Could not initialize SDL_Audio");

  SDL_AudioSpec wav_spec;
  if (!SDL_LoadWAV("./assets/music.wav", &wav_spec, &_wavBuffer, &_wavLength))
    throw DisplayException("Could not load music file");

  wav_spec.callback = AudioCallback;
  wav_spec.userdata = NULL;

  audioPos = _wavBuffer;
  audioLength = _wavLength;

  if (SDL_OpenAudio(&wav_spec, NULL) < 0)
    throw DisplayException("Could not open audio");
  SDL_PauseAudio(0);

  while (audioLength > 0 && !_input.getKey(SDLK_RETURN)) {
    SDL_Delay(10);
    _context.updateInputs(_input);
  }

  SDL_CloseAudio();
  SDL_FreeWAV(_wavBuffer);

  return true;
}

void Display::keyMenuQuit() {
  exit(0);
}


void Display::keyMenuN() {
  _view = GAME;
  _engine = new Engine(10, 10, 10, 1, 1);
  _engine->setInput(_input);
  _engine->setContext(_context);
}

void Display::keyMenuM() {
  _view = GAME;
  _engine = new Engine(10, 10, 10, 2, 0);
  _engine->setInput(_input);
  _engine->setContext(_context);
}

void Display::keyMenuO() {
  _view = OPTIONS;
}

void Display::updateMenu() {
  std::vector<std::pair<void (Display::*)(void), int> >::iterator it = _menuKeys.begin();
  std::vector<std::pair<void (Display::*)(void), int> >::iterator end = _menuKeys.end();

  if (_input.getInput(SDL_QUIT))
    keyMenuQuit();
  for (; it != end; ++it) {
    if (_input.getKey(it->second, true))
      (this->*(it->first))();
  }
}

void Display::updateOptions() {
  if (_input.getKey(SDLK_ESCAPE, true) || _input.getInput(SDL_QUIT))
    _view = MENU;
  else if (_input.getKey(SDLK_p))
    _nbPlayers = 1 ? 2 : 1;
}

bool Display::update() {
  (this->*_updateTab[_view])();
  _context.updateInputs(_input);
  return true;
}

void Display::draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();

  if (_view == MENU)
    _backgroundTexture.bind();
  else
    _optionsTexture.bind();
  glm::vec3 _position, _rotation, _scale;
  _rotation.x = _rotation.y = _rotation.z = 0;
  _position.x = _position.y = _position.z = 0;
  _scale.x = _scale.y = _scale.z = 0.652;

  glm::mat4 transform(1);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);

  _background.draw(_shader, transform, GL_QUADS);

  if (_view == OPTIONS)
    {
      unsigned int nbEnemies = 12;
      unsigned int nbEnemiesTemp = nbEnemies;
      int pos = -250;
      while (nbEnemiesTemp > 0)
	{
	  int d = nbEnemiesTemp % 10;
	  _digitTextures[d]->bind();
	  glm::vec3 position, rotation, scale;
	  rotation.x = rotation.y = rotation.z = 0;
	  position.y = 1;
	  position.x = pos;
	  position.z = 15;
	  scale.x = scale.y = scale.z = 1;

	  glm::mat4 transformDigit(1);
	  transformDigit = glm::rotate(transformDigit, rotation.x, glm::vec3(1, 0, 0));
	  transformDigit = glm::rotate(transformDigit, rotation.y, glm::vec3(0, 1, 0));
	  transformDigit = glm::rotate(transformDigit, rotation.z, glm::vec3(0, 0, 1));
	  transformDigit = glm::translate(transformDigit, position);
	  transformDigit = glm::scale(transformDigit, scale);

	  _digit.draw(_shader, transformDigit, GL_QUADS);
	  nbEnemiesTemp = nbEnemiesTemp / 10;
	  pos += 50;
	}
    }

  _context.flush();
}

bool Display::updateGame() {
  if (_engine->update())
    return false;
  return true;
}
