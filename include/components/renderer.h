#ifndef BOUNCING_BALL_COMPONENTS_RENDERER_H
#define BOUNCING_BALL_COMPONENTS_RENDERER_H
#include <core.h>
#include <gameobject.h>
#include <gmath.h>

struct GameObject;
typedef struct GameObject GameObject;
struct RendererComponent;

typedef struct RendererComponent RendererComponent;

struct RendererComponent {
  GLuint vao_id;
  GLuint vbo_id;
  GLuint ibo_id;
  Vec2f *vertices;
  int draw;
  int n_vertices;
  Vec2f *coords;
};

RendererComponent components_render_create(Vec2f *vertices, int n_vertices, int draw);
void components_render_destroy(RendererComponent *renderer);

void components_render_update(GameObject *gameobject, float deltatime);

#endif