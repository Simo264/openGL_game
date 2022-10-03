#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glm/glm.hpp>
#include <memory>

class SpriteRenderer
{
private:
  class Shader* m_shader;
  std::unique_ptr<class VertexArray> m_ptrVA;
  std::unique_ptr<class VertexBuffer> m_ptrVB;
  std::unique_ptr<class IndexBuffer> m_ptrIB;

public:
  SpriteRenderer(class Shader* shader);
  ~SpriteRenderer();

  void drawSprite(class Texture2D* texture, 
    glm::vec2 position, 
    glm::vec2 size = glm::vec2(10.0f, 10.0f),
    float rotate = 0.0f
  );
};


#endif