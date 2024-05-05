#include "unnamedEngine/world.hpp"

void World::update() {
  for (Entity *entity : entities) {
    entity->update();
  }
}
