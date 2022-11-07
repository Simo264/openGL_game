#include "game_object.h"

#include <GL/glew.h>
#include <glm/gtx/transform.hpp>

GameObject::GameObject(uint32_t usage,
  glm::vec2 position_, 
  glm::vec2 dimension_, 
  Texture2D* texture_, 
  glm::vec3 color_,
  float rotation_,
  glm::vec2 velocity_
) 
  : Object(usage), 
  position  { position_ },
  dimension { dimension_},
  texture   { texture_  }, 
  color     { color_    },
  rotation  { rotation_ },
  velocity  { velocity_ },
  isSolid   { false     },
  destroyed { false     }
{
}
void GameObject::render(Shader* shader) const
{
  shader->use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f)); 
  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0,0,1)); 
  model = glm::scale(model, glm::vec3(dimension, 1.0f)); 

  shader->setMatrix4f("model", model);
  shader->setMatrix4f("projection", glm::ortho(0.0f, 720.f, 720.f, 0.0f, -1.0f, 1.0f));
  shader->setVector3f("imageColor", color);

  texture->activeTexture();
  texture->bind();
  m_vertexArray->bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
} 
