#include "sprite_renderer.h"
#include "texture2D.h"
#include "shader.h"

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"

#include <GLFW/glfw3.h>
#include <array>

SpriteRenderer::SpriteRenderer(Shader* shader)
{
  m_shader = shader;

  const std::array<glm::vec2, 4> positions = {
    glm::vec2{ 1, 1 },  // top right
    glm::vec2{ 0, 1 },  // top left
    glm::vec2{ 1, 0 },  // bottom right 
    glm::vec2{ 0, 0 }   // bottom left
  };
  const std::array<glm::vec2, 4> textCoords = {
    glm::vec2{ 1, 1 },  // top right
    glm::vec2{ 0, 1 },  // top left
    glm::vec2{ 1, 0 },  // bottom right
    glm::vec2{ 0, 0 }   // bottom left
  };
  const std::array<uint32_t, 6> indices = { 0,1,2,  1,2,3 };
  
  m_ptrVA = std::unique_ptr<VertexArray>(new VertexArray());
  m_ptrVB = std::unique_ptr<VertexBuffer>(new VertexBuffer(sizeof(positions)+sizeof(textCoords), nullptr));
  m_ptrIB = std::unique_ptr<IndexBuffer>(new IndexBuffer(sizeof(indices), indices.data()));
  
  m_ptrVB->bufferSubData(0, sizeof(positions), positions.data());
  m_ptrVB->bufferSubData(sizeof(positions), sizeof(textCoords), textCoords.data());

  VertexBufferLayout layout;
  layout.pushFloats(2, (void*) 0);
  layout.pushFloats(2, (void*) (sizeof(positions)));

  m_ptrVA->addBuffer(*m_ptrVB, layout);
}

SpriteRenderer::~SpriteRenderer() { }


void SpriteRenderer::drawSprite(Texture2D* texture, 
  glm::vec2 position, 
  glm::vec2 size, 
  float rotate
)
{ 
  m_shader->use();

  glm::mat4 scaling     = glm::mat4(1.0f);
  glm::mat4 translation = glm::mat4(1.0f);
  glm::mat4 rotation    = glm::mat4(1.0f);

  // translation = glm::translate(translation, glm::vec3(-0.5f, -0.5f, 0));
  // scaling = glm::scale(scaling, glm::vec3(sin(glfwGetTime()), 1, 0));
  rotation = glm::rotate(rotation, (float) glfwGetTime(), glm::vec3(0, 0, 1));

  const glm::mat4 model = scaling * translation * rotation;
  m_shader->setMatrix4f("model", model);

  texture->activeTexture();
  texture->bind();

  m_ptrVA->bind();

  glDrawElements(GL_TRIANGLES, m_ptrIB->size(), GL_UNSIGNED_INT, 0);
}
