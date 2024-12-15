#include <components/transform.h>
#include <config.h>
#include <gameobject.h>

void components_transform_update(GameObject *gameobject, float deltatime) {
  TransformComponent *transform = gameobject->transform;
  if (transform == NULL) {
    return;
  }
}