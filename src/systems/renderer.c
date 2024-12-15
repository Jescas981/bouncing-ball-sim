#include <components/renderer.h>
#include <gameobject.h>
#include <systems/renderer.h>

void system_renderer_update(RendererSystem *system, float deltatime) {
  for (int i = 0; i < system->n_gameobjects; i++) {
    GameObject *gm = &system->gameobjects[i];
    if (gm->renderer != NULL) {
      components_render_update(gm, deltatime);
    }
  }
}