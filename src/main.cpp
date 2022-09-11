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

  Square square { 
    std::array<glm::vec2, 4>{
      Position(-0.5f, +0.5f),  // top left
      Position(+0.5f, +0.5f),  // top right
      Position(-0.5f, -0.5f),  // bottom left
      Position(+0.5f, -0.5f),  // bottom right
    },
    std::array<glm::vec3, 4>{
      Color(1, 0, 0),
      Color(0, 1, 0),
      Color(0, 0, 1),
      Color(0, 1, 1)
    },
    std::array<uint32_t, 6>{ 0,1,2, 1,2,3 }
  };


  // render loop
  // -----------
  while (!window.shouldClose())
  {
    window.clear();
    shader.use();

    square.render();
    
    window.swapBuffersAndPullEvents();
  }

  window.terminate();

  return 0;
}