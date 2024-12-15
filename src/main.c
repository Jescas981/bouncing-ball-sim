// clang-format off
#include <systems/renderer.h>
#include <components/collider.h>
#include <systems/collider.h>
#include <systems/physics.h>
#include <components/physics.h>
#include <components/renderer.h>
#include <gameobject.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <config.h>
#include <generator.h>
#include <gmath.h>
#include <io.h>
#include <program.h>
#include <shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(void) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                        "Bouncing Ball", NULL, NULL);

  if (window == NULL) {
    printf("Failed to create GLFW Window\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Begin systems
  PhysicsSystem physics_system;
  ColliderSystem collider_system;
  RendererSystem renderer_system;

  // Generate shapes
  int num_segments = 200;
  float radius = 20.0f;

  Vec2f *circle_vertices = malloc(sizeof(Vec2f) * num_segments);
  generator_circle_vertices(radius, num_segments, circle_vertices);

  // Create list of gameobjects
  GameObject gameobjects[2];

  // Create gameobject for ball
  gameobjects[0].id = 1;

  CircleColliderComponent circle_collider;
  circle_collider.radius = radius;
  ColliderComponent collider_cmp = components_collider_create(
      (BaseColliderComponent *)&circle_collider, CIRCLE_COLLIDER);

  TransformComponent transform_cmp;
  transform_cmp.position.x = 0.0f;
  transform_cmp.position.y = 150.0f;
  // Initial state
  PhysicsComponent physics_cmp;
  physics_cmp.enable_gravity = GL_TRUE;
  physics_cmp.mass = 10.0f;
  physics_cmp.velocity.x = 0;
  physics_cmp.velocity.y = 0;

  // Render
  RendererComponent renderer_cmp =
      components_render_create(circle_vertices, num_segments, GL_TRIANGLE_FAN);
  gameobjects[0].transform = &transform_cmp;
  gameobjects[0].renderer = &renderer_cmp;
  gameobjects[0].physics = &physics_cmp;
  gameobjects[0].collider = &collider_cmp;

  // Create soild without renderer
  gameobjects[1].id = 2;

  float soil_height = 20.0f;
  float soil_width = 350.0f;

  Vec2f *soil_vertices = malloc(sizeof(Vec2f) * 6);
  generator_rect_vertices(soil_width, soil_height, soil_vertices);

  RendererComponent soil_renderer_cmp =
      components_render_create(soil_vertices, 6, GL_TRIANGLES);

  RectColliderComponent rect_collider;
  rect_collider.width = soil_width;
  rect_collider.height = soil_height;

  ColliderComponent soil_collider_cmp = components_collider_create(
      (BaseColliderComponent *)&rect_collider, RECT_COLLIDER);

  TransformComponent soil_transform_cmp;
  soil_transform_cmp.position.x = 0.0f;
  soil_transform_cmp.position.y = -150.0f;
  soil_transform_cmp.angle = 0.0;

  gameobjects[1].transform = &soil_transform_cmp;
  gameobjects[1].collider = &soil_collider_cmp;
  gameobjects[1].physics = NULL;
  gameobjects[1].renderer = &soil_renderer_cmp;

  // Assign
  physics_system.n_gameobjects = 2;
  physics_system.gameobjects = gameobjects;
  collider_system.n_gameobjects = 2;
  collider_system.gameobjects = gameobjects;
  renderer_system.n_gameobjects = 2;
  renderer_system.gameobjects = gameobjects;

  // Shader compilation
  char *frag_src = read_plain_file(
      "/home/jescas/Projects/BouncingBall/shaders/fragment_shader.glsl");
  char *vert_src = read_plain_file(
      "/home/jescas/Projects/BouncingBall/shaders/vertex_shader.glsl");

  Shader *vert_shader = shader_create(vert_src, GL_VERTEX_SHADER);
  Shader *frag_shader = shader_create(frag_src, GL_FRAGMENT_SHADER);

  Program *program = program_create(vert_shader, frag_shader, NULL);

  free(frag_src);
  free(vert_src);
  shader_destroy(vert_shader);
  shader_destroy(frag_shader);

  // Deltatime
  float last_time = glfwGetTime();

  // Window loop
  while (!glfwWindowShouldClose(window)) {
    // Rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Get time
    float current_time = glfwGetTime();
    float deltatime = current_time - last_time;
    last_time = current_time;
    // Draw
    system_physics_reset(&physics_system, deltatime);
    system_collider_update(&collider_system, deltatime);
    system_physics_update(&physics_system, deltatime);

    program_use(program);
    system_renderer_update(&renderer_system, deltatime);

    // Events and swap buffer
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  free(circle_vertices);
  free(soil_vertices);
  program_destroy(program);
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  printf("Changing size of window\n");
}