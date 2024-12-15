#include <components/physics.h>
#include <gameobject.h>
#include <stdio.h>

void components_physics_update(GameObject *gameobject, float deltatime) {
  PhysicsComponent *physics = gameobject->physics;
  TransformComponent *transform = gameobject->transform;
  if (physics == NULL) {
    return;
  }

  // Compute velocity
  physics->velocity.y += deltatime * physics->acceleration.y;
  physics->velocity.x += deltatime * physics->acceleration.x;

  // Update transform
  transform->position.x += physics->velocity.x * deltatime;
  transform->position.y += physics->velocity.y * deltatime;


}