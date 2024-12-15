#ifndef BOUNCING_BALL_GAMEOBJECT_H
#define BOUNCING_BALL_GAMEOBJECT_H

#include <components/transform.h>
#include <core.h>
#include <gmath.h>

struct ColliderComponent;
struct PhysicsComponent;
struct RendererComponent;

typedef struct GameObject GameObject;
typedef struct PhysicsComponent PhysicsComponent;
typedef struct ColliderComponent ColliderComponent;
typedef struct RendererComponent RendererComponent;
typedef struct TransformComponent TransformComponent;

struct GameObject {
  unsigned int id;
  TransformComponent *transform;
  ColliderComponent *collider;
  PhysicsComponent *physics;
  RendererComponent *renderer;
};

void gameobject_update(GameObject *gameobject, float deltatime);

#endif
