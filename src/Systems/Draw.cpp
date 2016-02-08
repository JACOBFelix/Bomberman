#include <iostream>
#include <sstream>
#include "Systems/Draw.hpp"

System::Draw::Draw(std::vector<Entity>& entities) :
  ASystem(entities),
  _width(1600),_height(PIXELS_BY_CASE) {
  if (!_shader.load("./lib/shaders/basic.fp", GL_FRAGMENT_SHADER)
    || !_shader.load("./lib/shaders/basic.vp", GL_VERTEX_SHADER)
	 || !_shader.build())
	 throw DisplayException("Could not load shader");  int mapWidth = 5;
  int mapHeight = 5;
  int mapMax = mapWidth > mapHeight ? mapWidth : mapHeight;

  glm::mat4 projection = glm::perspective(60.0f, float(_width) / float(_height), 0.1f, 100.0f);
  glm::mat4 transformation = glm::lookAt(glm::vec3(mapWidth / 2, mapMax * 1.2, mapHeight / 2 + 1), glm::vec3(mapWidth / 2, 0, mapHeight / 2), glm::vec3(0, 1, 0));

  for (int i = 0; i < 10; i++) {
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

  _digit.pushUv(glm::vec2(1, 1));
  _digit.pushVertex(glm::vec3(-float(25) / 2, -float(25) / 2, 0.25f));
  _digit.pushUv(glm::vec2(0, 1));
  _digit.pushVertex(glm::vec3(float(25) / 2, -float(25) / 2, 0.25f));
  _digit.pushUv(glm::vec2(0, 0));
  _digit.pushVertex(glm::vec3(float(25) / 2, float(25) / 2, 0.25f));
  _digit.pushUv(glm::vec2(1, 0));
  _digit.pushVertex(glm::vec3(-float(25) / 2, float(25) / 2, 0.25f));

  _digit.build();

  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);
}

System::Draw::~Draw() {}

int	System::Draw::update(float const timer __attribute__((unused))) {
  std::vector<Entity>::iterator it = _entities.begin();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float x = 5;
  float y = 5;

  glm::mat4 projection = glm::perspective(60.0f, float(_width) / float(_height), 0.1f, 100.0f);
  glm::mat4 transformation = glm::lookAt(glm::vec3(y, 8, x + 1), glm::vec3(y, 0, x), glm::vec3(0, 1, 0));

  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);

  for (; it != _entities.end(); ++it)
    if ((_mod = static_cast<Component::Model *>((*it)[Component::MODEL]))) {
      _move = static_cast<Component::Move *>((*it)[Component::MOVE]);
      _pos = static_cast<Component::Position *>((*it)[Component::POSITION]);
      draw();
    }

  unsigned int score = 123;
  unsigned int tempScore = score;
  float pos = -10;
  while (tempScore > 0) {
    int d = tempScore % 10;
    _digitTextures[d]->bind();
    glm::vec3 position, rotation, scale;
    rotation.z = 0;
    rotation.x = 90;
    rotation.y = 180;
    position.y = 2;
    position.x = pos;
    position.z = 2;
    scale.x = scale.y = scale.z = 0.01;

    glm::mat4 transformDigit(1);
    transformDigit = glm::rotate(transformDigit, rotation.x, glm::vec3(1, 0, 0));
    transformDigit = glm::rotate(transformDigit, rotation.y, glm::vec3(0, 1, 0));
    transformDigit = glm::rotate(transformDigit, rotation.z, glm::vec3(0, 0, 1));
    transformDigit = glm::translate(transformDigit, position);
    transformDigit = glm::scale(transformDigit, scale);

    _digit.draw(_shader, transformDigit, GL_QUADS);
    tempScore = tempScore / 10;
    pos += 0.25;
  }

  _context.flush();
  return 0;
}

void	System::Draw::drawSouth(glm::vec3 & rot, glm::vec3 & pos, float x, float y) {
  rot.y = -90;
  pos.x = x;
  pos.z = -y;
}

void	System::Draw::drawWest(glm::vec3 & rot, glm::vec3 & pos, float x, float y) {
  rot.y = 180;
  pos.x = -y;
  pos.z = -x;
}

void	System::Draw::drawEast(glm::vec3 & rot, glm::vec3 & pos, float x, float y) {
  rot.y = 0;
  pos.x = y;
  pos.z = x;
}

void	System::Draw::drawNorth(glm::vec3 & rot, glm::vec3 & pos, float x, float y) {
  rot.y = 90;
  pos.x = -x;
  pos.z = y;
}

glm::mat4	System::Draw::dessineMoiUneMatrice() {
  glm::vec3 position, rotation, sc;
  std::vector <void (System::Draw::*)(glm::vec3 &, glm::vec3 &, float, float)> dirTab = {
    &System::Draw::drawEast,
    &System::Draw::drawNorth,
    &System::Draw::drawEast,
    &System::Draw::drawSouth,
    &System::Draw::drawWest
  };
  rotation.x = rotation.z = 0;
  position.y = 0;
  sc.x = sc.y = sc.z = _mod->getScale();

  (this->*dirTab[_move->getDir()])(rotation, position, float(_pos->getX()) / PIXELS_BY_CASE, float(_pos->getY()) / PIXELS_BY_CASE);

  glm::mat4 transform(1);
  transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
  transform = glm::translate(transform, position);
  transform = glm::scale(transform, sc);
  return transform;
}
void	System::Draw::draw() {
  glm::mat4 transform = dessineMoiUneMatrice();
  _mod->getModel().draw(_shader, transform, _clock.getElapsed());
}

void	System::Draw::setContext(gdl::SdlContext const & context) {
  _context = context;
}
