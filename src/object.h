#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

#include "vertex_array.h"
#include "index_buffer.h"

class Object
{
protected:
  std::unique_ptr<VertexArray> m_vertexArray;
  std::unique_ptr<VertexBuffer> m_vertexBuffer;
  std::unique_ptr<IndexBuffer> m_indexBuffer;

public:
  Object(uint32_t usage);
};

#endif