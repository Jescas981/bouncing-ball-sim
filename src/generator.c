#include <generator.h>
#include <math.h>

void generator_circle_vertices(float radius, int num_segments,
                               Vec2f *vertices) {

  for (int i = 0; i < num_segments; i++) {
    float theta = 2.0f * M_PI * (float)i / (float)num_segments;
    float x = radius * cosf(theta);
    float y = radius * sinf(theta);
    vertices[i].x = x;
    vertices[i].y = y;
  }
}

void generator_rect_vertices(float width, float height, Vec2f *vertices) {
  // Bottom-left corner
  vertices[0].x = -width * 0.5f;
  vertices[0].y = -height * 0.5f;

  // Bottom-right corner
  vertices[1].x = width * 0.5f;
  vertices[1].y = -height * 0.5f;

  // Top-right corner
  vertices[2].x = width * 0.5f;
  vertices[2].y = height * 0.5f;

  // Top-left corner
  vertices[3] = vertices[2];

  // Bottom-left corner
  vertices[4].x = -width * 0.5f;
  vertices[4].y = height * 0.5f;

  // Bottom-right corner
  vertices[5] = vertices[0];
}
