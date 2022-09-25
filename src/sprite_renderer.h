#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glm/glm.hpp>
#include <memory>

class SpriteRender
{
private:
  class Shader* m_shader;
  std::unique_ptr<class VertexArray> m_ptrVA;
  std::unique_ptr<class VertexBuffer> m_ptrVB;

  void initRenderData();

public:
  SpriteRender(class Shader* shader);
  ~SpriteRender();

  void DrawSprite(class Texture2D* texture, 
    glm::vec2 position, 
    glm::vec2 size = glm::vec2(10, 10), 
    float rotate = 0.0f, 
    glm::vec3 color = glm::vec3(1)
  );
};




#endif