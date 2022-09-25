#include "sprite_renderer.h"
#include "shader.h"
#include "vertex.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

#include <array>

SpriteRender::SpriteRender(Shader* shader)
{
  std::array<Vertex, 6> vertices = {
    Vertex{ glm::vec2{ 0.0f,1.0f }, glm::vec2{ 0.0f,1.0f } },
    Vertex{ glm::vec2{ 1.0f,0.0f }, glm::vec2{ 1.0f,0.0f } },
    Vertex{ glm::vec2{ 0.0f,0.0f }, glm::vec2{ 0.0f,0.0f } },

    Vertex{ glm::vec2{ 0.0f,1.0f }, glm::vec2{ 0.0f,1.0f } },
    Vertex{ glm::vec2{ 1.0f,1.0f }, glm::vec2{ 1.0f,1.0f } },
    Vertex{ glm::vec2{ 1.0f,0.0f }, glm::vec2{ 1.0f,0.0f } },
  };

  m_shader = shader;

  m_ptrVA.reset(new VertexArray());
  m_ptrVB.reset(new VertexBuffer(sizeof(vertices), vertices.data()));

  VertexArray* va = m_ptrVA.get();
  VertexBuffer* vb = m_ptrVB.get();

  VertexBufferLayout layout;
  layout.pushFloats(2, (void*) 0);
  layout.pushFloats(2, (void*) sizeof(glm::vec2));

  va->addBuffer(*vb, layout);
}

SpriteRender::~SpriteRender()
{
}