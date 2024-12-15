#ifndef BOUNCING_BALL_SYSTEM_PHYSICS_H
#define BOUNCING_BALL_SYSTEM_PHYSICS_H

typedef struct GameObject GameObject;
typedef struct PhysicsSystem PhysicsSystem;

struct PhysicsSystem {
  GameObject *gameobjects;
  int n_gameobjects;
};

void system_physics_reset(PhysicsSystem *system, float deltatime);
void system_physics_update(PhysicsSystem *system, float deltatime);

#endif