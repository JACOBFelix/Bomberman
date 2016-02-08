#pragma once

#include <string>
#include <vector>

#include "Game.hh"
#include "Texture.hh"
#include "Geometry.hh"
#include "OpenGL.hh"
#include "BasicShader.hh"
#include "SdlContext.hh"
#include "Model.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Cube.hpp"
#include "Engine.hpp"

#include "MapConfiguration.hpp"

# include "ASystem.hpp"
# include "Components/Move.hpp"
# include "Components/Position.hpp"
# include "Components/Model.hpp"
# include "Exceptions.hpp"

namespace System {
  class Draw : public ASystem {
  private:
    void drawSouth(glm::vec3 & rot, glm::vec3 & pos, float x, float y);
    void drawNorth(glm::vec3 & rot, glm::vec3 & pos, float x, float y);
    void drawEast(glm::vec3 & rot, glm::vec3 & pos, float x, float y);
    void drawWest(glm::vec3 & rot, glm::vec3 & pos, float x, float y);
    void draw();

    float _scale;
    gdl::Model _model;
    gdl::Geometry _digit;
    gdl::BasicShader _shader;
    gdl::Clock _clock;
    gdl::SdlContext _context;
    unsigned int _width;
    unsigned int _height;

    Component::Position *_pos;
    Component::Move *_move;
    Component::Model *_mod;
    std::vector<gdl::Texture*> _digitTextures;
  public:
    Draw(std::vector<Entity>&);
    ~Draw();

    int update(float const timer);

    glm::mat4 dessineMoiUneMatrice();
    void setContext(gdl::SdlContext const &);
  };
}
