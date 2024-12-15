#ifndef BOUNCING_BALL_GMATH_H
#define BOUNCING_BALL_GMATH_H

typedef union {
  float data[2][2];
  struct {
    float a0;
    float b0;
    float a1;
    float b1;
  };
} Mat2;

typedef union {
  float data[2];
  struct {
    float x;
    float y;
  };
} Vec2f;

Vec2f gmath_mat2_mult_vec2f(Mat2 m, Vec2f v);
Vec2f gmath_vec2f_subs(Vec2f p, Vec2f q);
Vec2f gmath_vec2f_plus(Vec2f p, Vec2f q);
Vec2f gmath_vec2f_plus_scalar(Vec2f p, float s);

Mat2 gmath_mat2_rot(float theta);
Mat2 gmath_mat2_transpose(Mat2 mat);

float gmath_vec2f_dot(Vec2f p, Vec2f q);
float gmath_vec2f_mag_squared(Vec2f p);
Vec2f gmath_vec2f_mult_scalar(Vec2f p, float s);

#endif