#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "game.h"
#include "resource_manager.h"

// Screen dimension
constexpr int WIDTH = 720;
constexpr int HEIGHT = 720;
constexpr const char* TITLE = "Breakout";

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Game breakout { WIDTH, HEIGHT };

int main()
{
  GLFWwindow* window;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, false);

  window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glew: init
  // ----------------
  glewInit();

  // OpenGL configuration
  // --------------------
  glViewport(0, 0, WIDTH, HEIGHT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // initialize game
  // ---------------
  breakout.init();


  // deltaTime variables
  // -------------------
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;
  while (!glfwWindowShouldClose(window))
  {
    // calculate delta time
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    // manage user input
    // -----------------
    breakout.processInput(deltaTime);

    // update game state
    // -----------------
    breakout.update(deltaTime);

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    breakout.render();

    glfwSwapBuffers(window);
  }

  // delete all resources as loaded using the resource manager
  // ---------------------------------------------------------
  ResourceManager::clear();

  glfwTerminate();

  return 0;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  
  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
      breakout.keys[key] = true;

    else if (action == GLFW_RELEASE)
      breakout.keys[key] = false;
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}