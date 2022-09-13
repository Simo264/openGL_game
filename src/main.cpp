#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

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

const std::array<Position, 4> vPositions = {
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
  Triangle triangle {
    { Position(-0.5f, +0.5f),Position(+0.5f, +0.5f),Position(-0.5f, -0.5f) }, 
    { Color(1,0,0),Color(0,1,0),Color(0,0,1) },
    GL_DYNAMIC_DRAW
  };

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

    triangle.render(shader);
    triangle.scale(0.5, 0.5);
    triangle.rotate(deltaTime, { 0,0,1 });
    triangle.translate(sin(deltaTime), +1);
                          
    window.swapBuffersAndPullEvents();
  }

  window.terminate();

  return 0;
}