#pragma once

#include "SdlContext.hh"
#include "FactoryEntity.hpp"
#include "ASystem.hpp"

namespace System {
  class Input : public ASystem {
  private:
    Component::Move *_move;
    Component::InputContext *_inputPlayer;
    gdl::Input _input;
    gdl::SdlContext _context;

    bool keyRight(Entity& entity);
    bool keyUp(Entity& entity);
    bool keyLeft(Entity& entity);
    bool keyDown(Entity& entity);
    bool keyDrop(Entity& entity);
    bool keyPut(Entity& entity);

  public:
    Input(std::vector<Entity>& entities);
    ~Input();
    int update(float const timer);
    void setInput(gdl::Input const &);
    void setContext(gdl::SdlContext const &);
  };
}
