#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>

class VertexBuffer
{
private:
  uint32_t m_id;

public:
  VertexBuffer();
  VertexBuffer(uint32_t size, GLenum usage);
  VertexBuffer(uint32_t size, const void* data, GLenum usage);
  ~VertexBuffer();

  void dataBuffer(uint32_t size, const void* data, GLenum usage);
  void subDataBuffer(uint32_t offset, uint32_t size, const void* data);

  void bind();
  void unbind();

  void deleteBuffer();
};

#endif