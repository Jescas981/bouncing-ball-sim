#ifndef BOUNCING_BALL_COMPONENTS_TRANSFORM_H
#define BOUNCING_BALL_COMPONENTS_TRANSFORM_H
#include <core.h>
#include <gmath.h>

struct GameObject;
typedef struct GameObject GameObject;

struct TransformComponent {
  Vec2f position;
  float angle;
};

void components_transform_update(GameObject *gameobject, float deltatime);

#endif