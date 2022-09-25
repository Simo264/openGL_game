#ifndef ENTITY_INTERFACE_H
#define ENTITY_INTERFACE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "transform.h"

class BasicObjectInterface
{
protected:
  Transformation m_transform;

public:
  BasicObjectInterface() = default;
  ~BasicObjectInterface() = default;

  void scale(float x, float y)    
  { 
    m_transform.scaling = glm::scale(glm::mat4(1.0f), { x,y,0 } );
  }
  void translate(float x, float y) 
  { 
    m_transform.translation = glm::translate(glm::mat4(1.0f), { x,y,0 });
  }
  void rotate(float angle, glm::vec3 rotationAxis)
  {
    m_transform.rotation = glm::rotate(glm::mat4(1.0f), angle, rotationAxis);
  }
  Transformation getTransform() const { return m_transform; }

  // glm::mat4 getModel() const 
  // {
  //   return m_transform.scaling * m_transform.translation * m_transform.rotation;
  // }

  virtual void render(const class Shader& shader) = 0;
};

#endif