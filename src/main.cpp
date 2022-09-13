#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <array> 

#include "window.h"
#include "shader.h"
#include "vertex.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

#include "transform.h"
#include "object.h"
#include "triangle.h"
#include "square.h"

// Window size
constexpr int WIDTH = 720;
constexpr int HEIGHT = 720;
constexpr const char* TITLE = "simple 2D game";

const Position vPositions[] = 
{
  Position(-0.5f, +0.5f),  // top left
  Position(+0.5f, +0.5f),  // top right
  Position(-0.5f, -0.5f),  // bottom left
  Position(+0.5f, -0.5f),  // bottom right
};

int main()
{
  Window window{ WIDTH, HEIGHT, TITLE };

  // glew: initialize
  // ---------------------------------------
  glewInit();

  // build and compile our shader program
  // ------------------------------------
  Shader shader { "../shaders/vertex.shader", "../shaders/fragment.shader" };

  Square square;

  // render loop
  // -----------
  while (!window.shouldClose())
  {
    const float deltaTime = static_cast<float>(glfwGetTime());

    window.clear();
    shader.use();

    square.render(shader);
    square.scale(0.5, 0.5);
    square.rotate(deltaTime*5, { 0,0,1 });
    square.translate(sin(deltaTime), 0);
                          
    window.swapBuffersAndPullEvents();
  }

  window.terminate();

  return 0;
}