#include "gmath.h"
#include <components/collider.h>
#include <components/physics.h>
#include <gameobject.h>
#include <stdio.h>

#define COLLIDER_PAIR(type1, type2) ((type1 << 4) | type2)

// void handle_circle_circle_collision(GameObject *self, GameObject *other) {
//   TransformComponent *tf1 = self->transform;
//   TransformComponent *tf2 = other->transform;

//   ColliderComponent *col1 = self->collider;
//   ColliderComponent *col2 = other->collider;

//   PhysicsComponent *ph1 = self->physics;
//   PhysicsComponent *ph2 = self->physics;

//   // Both must have collider
//   if (col1 == NULL || col2 == NULL) {
//     return;
//   }

//   //
//   if (col2->type == RECT_COLLIDER) {
//     RectColliderComponent *col2_base = (RectColliderComponent *)col2->base;

//   } else if (col2->type == CIRCLE_COLLIDER) {
//     CircleColliderComponent *col2_base = (CircleColliderComponent
//     *)col2->base;
//   }
// }

void handle_circle_rect_collision(GameObject *circle_gm, GameObject *rect_gm) {
  TransformComponent *circle_tf = circle_gm->transform;
  TransformComponent *rect_tf = rect_gm->transform;

  CircleColliderComponent *circle_col =
      (CircleColliderComponent *)circle_gm->collider->base;

  RectColliderComponent *rect_col =
      (RectColliderComponent *)rect_gm->collider->base;

  PhysicsComponent *circle_ph = circle_gm->physics;
  // PhysicsComponent *rect_ph = rect_gm->physics;

  // Circle to rect coordinates
  Vec2f v = gmath_vec2f_subs(circle_tf->position, rect_tf->position);
  // Reverse of rotation matrix
  Mat2 rot = gmath_mat2_rot(rect_tf->angle);
  Mat2 rot_inv = gmath_mat2_transpose(rot);
  Vec2f v_local = gmath_mat2_mult_vec2f(rot_inv, v);
  float alpha = 1.0f;

  if ((-rect_col->width * 0.5f - circle_col->radius <= v_local.x &&
       v_local.x <= rect_col->width * 0.5f + circle_col->radius) &&
      (-rect_col->height * 0.5f - circle_col->radius <= v_local.y &&
       v_local.y <= rect_col->height * 0.5f + circle_col->radius)) {
    Vec2f normal = gmath_mat2_mult_vec2f(
        rot, gmath_vec2f_mult_scalar(circle_ph->velocity, -1));
    circle_ph->velocity = gmath_vec2f_mult_scalar(normal, alpha);

    printf("Position: %.2f,%2.f\n", v_local.x, v_local.y);
  }
}

void components_collider_resolve(GameObject *gm1, GameObject *gm2) {
  ColliderComponent *col1 = gm1->collider;
  ColliderComponent *col2 = gm2->collider;
  // Dispatcher
  switch (COLLIDER_PAIR(col1->type, col2->type)) {

  case COLLIDER_PAIR(CIRCLE_COLLIDER, CIRCLE_COLLIDER):
    // handle_circle_circle_collision(gm1, gm2);
    break;
  case COLLIDER_PAIR(CIRCLE_COLLIDER, RECT_COLLIDER):
    handle_circle_rect_collision(gm1, gm2);
    break;
  case COLLIDER_PAIR(RECT_COLLIDER, CIRCLE_COLLIDER):
    handle_circle_rect_collision(gm2, gm1);
    break;
  }
}

ColliderComponent components_collider_create(BaseColliderComponent *base,
                                             int type) {
  ColliderComponent collider;
  collider.type = type;
  collider.base = base;
  return collider;
}

void components_collider_destroy(ColliderComponent *collider) {}