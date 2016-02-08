#include <vector>
#include <iostream>
#include "FactoryEntity.hpp"
#include "Entity.hpp"
#include "Systems/AI.hpp"
//#include "testy.hpp"

int testAiMapState1(System::AI const & ai) {
  // It checks if the map has the wanted state at the initialization
  (void)ai;
  return 0;
}

int testAiSmellState1(std::vector<int> const & hodor_map) {
  // It checks if the hodor_map has the wanted state at the initialization
  (void)hodor_map;
  return 0;
}

int testAi() {
  // define the map
  std::vector<Entity> map;
  // define the ent sent by the <update> method
  Entity const player = FactoryEntity::getInstance()->create(Entity::PLAYER);
  //Entity const & ent(player);
  // Init AISystem
  System::AI ai(map);
  //std::vector<int> hodor_map(IA_VIEW_MAP_SIZE, 0);// char hodor_map[IA_VIEW_MAP_SIZE];
  //ai.moveBot(ent, hodor_map);

  std::cout << "Map initialization" << std::endl;
  testAiMapState1(ai);

  std::cout << "Detections of smells" << std::endl;
  //testAiSmellState1(hodor_map);

  std::cout << "Movements" << std::endl;
  // static_cast<Move *>(ent.getComponent(Component::MOVE))->setDir(translationActionToMove[move]);

  std::cout << "Backtracer pathfinder" << std::endl;
  // AISystem::choseActionP
  return 0;
}
