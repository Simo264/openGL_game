#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

#include <cstdint>

class VertexArray
{
private:
  uint32_t m_id;

public:
  VertexArray();
  ~VertexArray();

  void addBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);

  void setAttribute(uint32_t index, uint32_t count, uint32_t type, 
    bool normalized, uint64_t stride, const void* pointer);

  void enableAttribute(uint32_t index);
  void disableAttribute(uint32_t index);
    
  void bind();
  void unbind();

  void deleteArray();
};

#endif