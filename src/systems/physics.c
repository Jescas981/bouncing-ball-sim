#include <components/physics.h>
#include <gameobject.h>
#include <systems/physics.h>

void system_physics_reset(PhysicsSystem *system, float deltatime) {
  for (int i = 0; i < system->n_gameobjects; i++) {
    PhysicsComponent *physics = system->gameobjects[i].physics;
    if (physics != NULL) {
      physics->forces.x = 0.0f;
      physics->acceleration.x = 0.0f;

      if (physics->enable_gravity) {
        physics->forces.y = physics->mass * -9.81f;
        physics->acceleration.y = -9.81f;
      }
    }
  }
}

void system_physics_update(PhysicsSystem *system, float deltatime) {
  for (int i = 0; i < system->n_gameobjects; i++) {
    GameObject *gm = &system->gameobjects[i];
    if (gm->physics != NULL) {
      components_physics_update(gm, deltatime);
    }
  }
}