#ifndef BOUNCING_BALL_PROGRAM_H
#define BOUNCING_BALL_PROGRAM_H
#include <shader.h>
#include <stdarg.h>

struct Program {
  unsigned int id;
};

typedef struct Program Program;

Program *program_create(Shader *shader, ...);

void program_link_shaders(Program *program, Shader *shader, ...);

void program_use(Program *program);
void program_destroy(Program *program);

#endif
