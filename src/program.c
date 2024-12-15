#include <core.h>
#include <program.h>
#include <shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLboolean _check_compilation_program(Program *program) {
  GLint success;
  glGetProgramiv(program->id, GL_LINK_STATUS, &success);
  if (!success) {
    GLint log_length;
    glGetProgramiv(program->id, GL_INFO_LOG_LENGTH, &log_length);
    char *log = (char *)malloc(log_length);
    glGetProgramInfoLog(program->id, log_length, &log_length, log);
    printf("Program linking failed: %s\n", log);
    free(log);
    return GL_FALSE;
  }
  return GL_TRUE;
}

Program *program_create(Shader *shader, ...) {
  Program *program = malloc(sizeof(Program));
  program->id = glCreateProgram();

  va_list args;
  va_start(args, shader);
  Shader *current_shader;

  while ((current_shader = va_arg(args, Shader *)) != NULL) {
    glAttachShader(program->id, current_shader->id);
  }

  va_end(args);

  glLinkProgram(program->id);
  _check_compilation_program(program);

  va_start(args, shader);
  while ((current_shader = va_arg(args, Shader *)) != NULL) {
    glDetachShader(program->id, current_shader->id);
  }
  va_end(args);

  return program;
}

void program_use(Program *program) { glUseProgram(program->id); }

void program_destroy(Program *program) { glDeleteProgram(program->id); }