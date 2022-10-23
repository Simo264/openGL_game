#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <cstdint>

class VertexBuffer
{
private:
  uint32_t m_id;

public:
  VertexBuffer();
  VertexBuffer(uint32_t size, const void* data, uint32_t usage);
  ~VertexBuffer();

  void bufferData(uint32_t size, const void* data, uint32_t usage);
  void bufferSubData(uint32_t offset, uint32_t size, const void* data);

  void bind();
  void unbind();

  void deleteBuffer();
};

#endif