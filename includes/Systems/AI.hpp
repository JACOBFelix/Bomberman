#pragma once

#include "MapConfiguration.hpp"
#include "ASystem.hpp"

#define MAPS 10
#define MAPPS 1000
#define ENTROPY 15

namespace System {
  class AI : public ASystem {
  public:
    enum Action {
      ERROR,
      NORTH,
      EAST,
      SOUTH,
      WEST,
      NONE,
      BOMB,
    };
    typedef int (*t_functionCmpPtr)(int, int);

  public:
    AI(std::vector<Entity>&);
    ~AI();

    int update(float timer);
    void updateBot(Entity & ent);

    // iterate on each entities
    void initMapSmells(const Entity &ent);
    void propagation(Entity & ent, int idx);
    void propagationWall(Entity &, int idx);
    void propagationDestructibleWall(Entity &, int idx);
    void propagationBomb(Entity &, int idx);
    void propagationBonus(Entity &, int idx);
    void propagationPlayer(Entity &, int idx);
    void propagationExplosion(Entity &, int idx);
    void propagationTile(Entity &, int idx);

    // chose an action with mapSmells
    Action choseAction(Entity & ent, int idx);
    // Action to do (change the state of ent)
    void act(Entity & ent, Action move);
    Action moveToBetter(Entity & ent, int idx);
    Action moveToRandom(Entity & ent, int idx);
    Action placeBomb(Entity & ent, int idx);

    // smells test / alterations
    bool isInDanger(int idx);
    Entity const * getEntityAt(int idx);
    Entity::type getEntityTypeAt(int idx);
    int getSmellAt(int from, int x, int y, int range = 1);
    int getSmellAtNorth(int idx);
    int getSmellAtEast(int idx);
    int getSmellAtSouth(int idx);
    int getSmellAtWest(int idx);
    Action nearTo(int idx, Entity::type type);
    int nearToNothing(Entity & ent, int idx);

    void addToComponentDir(Component::Move::dir dir, int v, int from, int range);
    void addToActionDir(Action dir, int v, int from, int range);
    void addAt(int v, int from, int x, int y, int range = 1);
    void addNorth(int v, int from, int range = 1);
    void addEast(int v, int from, int range = 1);
    void addSouth(int v, int from, int range = 1);
    void addWest(int v, int from, int range = 1);
    void addAround(int v, int from, int range = 1);

    static bool predictIsABot(Entity & ent);

  private:
    typedef std::vector<int> t_hodor;
    t_hodor _mapSmells;
    std::vector<Entity const *> _mapEntities;
    std::vector<void (System::AI::*)(Entity &, int)> _propagationPtrs;
    std::vector<void (System::AI::*)(int, int, int)> _addSmellPtrs;
    std::vector<std::pair<Action, int>> _nearTo;
  };
}
