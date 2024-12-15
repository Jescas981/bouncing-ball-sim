#include <gmath.h>
#include <math.h>

Vec2f gmath_mat2_mult_vec2f(Mat2 m, Vec2f v) {
  Vec2f n;
  n.x = m.a0 * v.x + m.a1 * v.y;
  n.y = m.b0 * v.x + m.b1 * v.y;
  return n;
}

Vec2f gmath_vec2f_subs(Vec2f p, Vec2f q) {
  Vec2f vec;
  vec.x = p.x - q.x;
  vec.y = p.y - q.y;
  return vec;
}

Vec2f gmath_vec2f_plus(Vec2f p, Vec2f q) {
  Vec2f vec;
  vec.x = p.x + q.x;
  vec.y = p.y + q.y;
  return vec;
}

Vec2f gmath_vec2f_plus_scalar(Vec2f p, float s) {
  Vec2f vec;
  vec.x = p.x + s;
  vec.y = p.y + s;
  return vec;
}

Mat2 gmath_mat2_rot(float theta) {
  Mat2 rot = {{{cosf(theta), sinf(theta)}, {-sinf(theta), cosf(theta)}}};
  return rot;
}

Mat2 gmath_mat2_transpose(Mat2 mat) {
  float temp = mat.a1;
  mat.a1 = mat.b0;
  mat.b0 = temp;
  return mat;
}

float gmath_vec2f_dot(Vec2f p, Vec2f q) { return p.x * q.x + p.y * q.y; }

float gmath_vec2f_mag_squared(Vec2f p) { return p.x * p.x + p.y * p.y; }

Vec2f gmath_vec2f_mult_scalar(Vec2f p, float s) {
  Vec2f vec;
  vec.x = p.x * s;
  vec.y = p.y * s;
  return vec;
}