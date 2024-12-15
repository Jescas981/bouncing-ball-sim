#ifndef BOUNCING_BALL_COMPONENTS_PHYSICS_H
#define BOUNCING_BALL_COMPONENTS_PHYSICS_H
#include <core.h>
#include <gmath.h>

struct GameObject;
typedef struct GameObject GameObject;
typedef struct PhysicsComponent PhysicsComponent;

struct PhysicsComponent {
  float mass;
  Vec2f velocity;
  Vec2f forces;
  Vec2f acceleration;
  GLboolean enable_gravity;
  GLboolean enable_kinematics;
};
void components_physics_update(GameObject *gameobject, float deltatime);

#endif