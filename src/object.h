#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ObjectInterface
{
protected:
  Transformation m_transform;

public:
  ObjectInterface() = default;
  ~ObjectInterface() = default;

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
  glm::mat4 getModel() const 
  {
    return m_transform.scaling * m_transform.translation * m_transform.rotation;
  }

  virtual void render(const Shader& shader) = 0;
};

#endif