#ifndef BOUNCING_BALL_SYSTEM_COLLIDER_H
#define BOUNCING_BALL_SYSTEM_COLLIDER_H

typedef struct GameObject GameObject;
typedef struct ColliderSystem ColliderSystem;

struct ColliderSystem {
  GameObject *gameobjects;
  int n_gameobjects;
};

void system_collider_update(ColliderSystem *system, float deltatime);

#endif