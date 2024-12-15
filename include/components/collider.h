#ifndef BOUNCING_BALL_COMPONENTS_COLLIDER_H
#define BOUNCING_BALL_COMPONENTS_COLLIDER_H
#include <core.h>
#include <gmath.h>

struct GameObject;
typedef struct GameObject GameObject;
typedef void *BaseColliderComponent;
typedef struct ColliderComponent ColliderComponent;
typedef struct CircleColliderComponent CircleColliderComponent;
typedef struct LineColliderComponent LineColliderComponent;
typedef struct RectColliderComponent RectColliderComponent;

#define CIRCLE_COLLIDER 0x01
#define LINE_COLLIDER 0x02
#define RECT_COLLIDER 0x04

struct LineColliderComponent {
  float width;
};

struct RectColliderComponent {
  float width;
  float height;
};

struct CircleColliderComponent {
  float radius;
};

struct ColliderComponent {
  int type;
  BaseColliderComponent base;
};

ColliderComponent components_collider_create(BaseColliderComponent *base,
                                             int type);

void components_collider_resolve(GameObject *gm1, GameObject *gm2);

void components_collider_destroy(ColliderComponent *collider);

#endif