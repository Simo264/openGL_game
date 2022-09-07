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
#include "vertex_buffer.h"
#include "index_buffer.h"

// Window size
constexpr int WIDTH = 720;
constexpr int HEIGHT = 720;
constexpr const char* TITLE = "simple 2D game";

class Triangle
{
private:
  std::array<glm::vec2, 3> m_vPositions;
  std::array<glm::vec3, 3> m_vColors;
  uint32_t m_vBuffer;
  uint32_t m_vArray;

  const int NUM_VERTICES = 3;

public:
  Triangle(std::array<glm::vec2, 3> vPos, std::array<glm::vec3, 3> vCol)
  {
    m_vPositions = vPos;
    m_vColors = vCol;

    const uint32_t sizePos = m_vPositions.size()*sizeof(glm::vec2);
    const uint32_t sizeCol = m_vColors.size()*sizeof(glm::vec3);

    glGenVertexArrays(1, &m_vArray);
    glBindVertexArray(m_vArray);

    glGenBuffers(1, &m_vBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizePos + sizeCol, NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizePos, m_vPositions.data());
    glBufferSubData(GL_ARRAY_BUFFER, sizePos, sizeCol, m_vColors.data());

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*) (sizePos));
    glEnableVertexAttribArray(1);
  }
  void render()
  {
    glBindVertexArray(m_vArray);
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
  }
};

const glm::vec2 vPositions[] = 
{
  glm::vec2(+0.5f, +0.5f),  
  glm::vec2(+0.5f, -0.5f),  
  glm::vec2(-0.5f, -0.5f),  

  glm::vec2(-0.5f, +0.5f),  
  glm::vec2(+0.5f, -0.5f),  
  glm::vec2(-0.5f, -0.5f),  
};
const glm::vec3 vColors[] = 
{
  glm::vec3(1, 0, 0),
  glm::vec3(1, 0, 0),
  glm::vec3(1, 0, 0),

  glm::vec3(1, 0, 1),
  glm::vec3(1, 0, 1),
  glm::vec3(1, 0, 1),
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

  uint32_t vertexArray;
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);

  VertexBuffer vertexBuffer { sizeof(vPositions) + sizeof(vColors), GL_DYNAMIC_DRAW };
  vertexBuffer.subData(0, sizeof(vPositions), (void*) vPositions);
  vertexBuffer.subData(sizeof(vPositions), sizeof(vColors), (void*) vColors);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*) sizeof(vPositions));
  glEnableVertexAttribArray(1);


  // render loop
  // -----------
  while (!window.shouldClose())
  {
    window.clear();
    shader.use();

    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    window.swapBuffersAndPullEvents();
  }

  window.terminate();

  return 0;
}