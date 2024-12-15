#ifndef BOUNCING_BALL_SHADER_H
#define BOUNCING_BALL_SHADER_H

struct Shader {
  unsigned int id;
};

typedef struct Shader Shader;

Shader *shader_create(const char *str, int type);
void shader_destroy(Shader *shader);

#endif