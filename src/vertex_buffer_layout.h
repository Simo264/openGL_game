#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <GL/glew.h>
#include <vector>

struct BufferElement
{
  uint32_t type;
  uint32_t count;
  uint32_t stride;
  bool normalized;
  void* pointer;
};


class VertexBufferLayout
{
private:  
  std::vector<BufferElement> m_elements;

public:
  VertexBufferLayout() = default;
  ~VertexBufferLayout() = default;

  void pushFloats(int count, void* pointer)
  {
    m_elements.push_back({ 
      GL_FLOAT, 
      static_cast<uint32_t>(count),
      static_cast<uint32_t>(sizeof(float)*count),
      false,
      pointer
    });
  }

  std::vector<BufferElement> getElements() const { return m_elements; }
};

#endif