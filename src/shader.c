// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLboolean _check_compilation_shader(Shader *shader) {
  GLint success;
  glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint log_length;
    glGetShaderiv(shader->id, GL_INFO_LOG_LENGTH, &log_length);
    char *log = (char *)malloc(log_length);
    glGetShaderInfoLog(shader->id, log_length, &log_length, log);
    printf("Shader compilation failed: %s\n", log);
    free(log);
    return GL_FALSE;
  }
  return GL_TRUE;
}

Shader *shader_create(const char *source, int type) {
  Shader *shader = (Shader *)malloc(sizeof(Shader));

  if (shader == NULL) {
    printf("Failed to allocate memory for shader\n");
    return NULL;
  }

  shader->id = glCreateShader(type);

  // Check if shader creation was successful
  if (shader->id == 0) {
    printf("Failed to create shader\n");
    free(shader);
    return NULL;
  }

  glShaderSource(shader->id, 1, &source, NULL);
  glCompileShader(shader->id);

  GLboolean compile_success = _check_compilation_shader(shader);
  if (!compile_success) {
    glDeleteShader(shader->id);
    free(shader);
    return NULL;
  }

  return shader;
}

void shader_destroy(Shader *shader) {
  if (shader != NULL) {
    glDeleteShader(shader->id);
    free(shader);
  }
}