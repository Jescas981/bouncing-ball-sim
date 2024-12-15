#ifndef BOUNCING_BALL_GENERATOR_H
#define BOUNCING_BALL_GENERATOR_H
#include <gmath.h>

void generator_circle_vertices(float radius, int num_segments, Vec2f *vertices);
void generator_rect_vertices(float width, float height, Vec2f *vertices);

#endif