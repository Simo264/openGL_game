#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>

#include "vertex_buffer.h"
#include "index_buffer.h"

class VertexArray
{
private:
  uint32_t m_id;

public:
  VertexArray();
  ~VertexArray();

  void addBuffer(VertexBuffer& buffer);
  void addBuffer(IndexBuffer& indexBuffer);

  void setAttribute(uint32_t index, uint32_t size, uint32_t stride, const void* pointer);
  void enableAttribute(uint32_t index);
  void disableAttribute(uint32_t index);

  void bind();
  void unbind();

  void deleteArray();
};

#endif