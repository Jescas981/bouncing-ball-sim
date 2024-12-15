#include <components/collider.h>
#include <components/physics.h>
#include <components/renderer.h>
#include <components/transform.h>
#include <config.h>
#include <gameobject.h>
#include <gmath.h>
#include <string.h>

void gameobject_update(GameObject *gameobject, float deltatime) {
  // Update physics first
  components_physics_update(gameobject, deltatime);
  // Update render second
  components_render_update(gameobject, deltatime);
}