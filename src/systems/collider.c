#include <components/collider.h>
#include <gameobject.h>
#include <systems/collider.h>

void system_collider_update(ColliderSystem *system, float deltatime) {
  if (system->n_gameobjects < 2) {
    return;
  }

  for (int i = 0; i < system->n_gameobjects; i++) {
    GameObject *gm1 = &system->gameobjects[i];
    for (int j = i + 1; j < system->n_gameobjects; j++) {
      GameObject *gm2 = &system->gameobjects[j];
      // Ensure both objects have colliders
      if (gm1->collider != NULL && gm2->collider != NULL) {
        // Call resolve function to handle collision
        components_collider_resolve(gm1, gm2);
      }
    }
  }
}