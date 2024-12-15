#include <components/renderer.h>
#include <config.h>
#include <core.h>
#include <gameobject.h>
#include <gmath.h>
#include <stdlib.h>

RendererComponent components_render_create(Vec2f *vertices, int n_vertices,
                                           int draw) {
  // Memory allocation for vertex
  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2f) * n_vertices, vertices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2f), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  RendererComponent renderer_cmp;
  renderer_cmp.vao_id = vao;
  renderer_cmp.vbo_id = vbo;
  renderer_cmp.vertices = vertices;
  renderer_cmp.n_vertices = n_vertices;
  renderer_cmp.coords = malloc(sizeof(Vec2f) * n_vertices);
  renderer_cmp.draw = draw;

  return renderer_cmp;
}

void components_render_destroy(RendererComponent *renderer) {
  free(renderer->coords);
  glDeleteBuffers(1, &renderer->vbo_id);
  glDeleteVertexArrays(1, &renderer->vao_id);
}

void components_render_update(GameObject *gameobject, float deltatime) {
  RendererComponent *renderer = gameobject->renderer;
  TransformComponent *transform = gameobject->transform;

  if (renderer == NULL) {
    return;
  }

  // Model coordinates in world
  float aspect_ratio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
  Mat2 world_matrix = {{{2 / (VIEW_MAX_X - VIEW_MIN_X), 0},
                        {0, 2 / (VIEW_MAX_Y - VIEW_MIN_Y) * aspect_ratio}}};

  // Bind vao
  glBindVertexArray(renderer->vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo_id);

  // Update GPU Buffer
  Vec2f *vertices_gpu = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

  // Transform
  for (int i = 0; i < renderer->n_vertices; i++) {
    Vec2f vert = renderer->vertices[i];
    // Rotation
    Mat2 rot =gmath_mat2_rot(transform->angle);
    vert = gmath_mat2_mult_vec2f(rot, vert);
    // Translation
    vert = gmath_vec2f_plus(vert, transform->position);
    // To world transform
    renderer->coords[i] = gmath_mat2_mult_vec2f(world_matrix, vert);
    vertices_gpu[i] = renderer->coords[i];
  }
  glUnmapBuffer(GL_ARRAY_BUFFER);

  glDrawArrays(renderer->draw, 0, renderer->n_vertices);
}