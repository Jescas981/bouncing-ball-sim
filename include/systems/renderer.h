#ifndef BOUNCING_BALL_SYSTEM_RENDERER_H
#define BOUNCING_BALL_SYSTEM_RENDERER_H

typedef struct GameObject GameObject;
typedef struct RendererSystem RendererSystem;

struct RendererSystem {
  GameObject *gameobjects;
  int n_gameobjects;
};

void system_renderer_update(RendererSystem *system, float deltatime);

#endif