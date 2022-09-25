#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>

class VertexBuffer
{
private:
  uint32_t m_id;
  uint32_t m_bufferSize;

public:
  VertexBuffer();
  VertexBuffer(uint32_t size, const void* data, GLenum usage = GL_STATIC_DRAW);
  ~VertexBuffer();

  void dataBuffer(uint32_t size, const void* data, GLenum usage);
  void subDataBuffer(uint32_t offset, uint32_t size, const void* data);

  void bind();
  void unbind();

  void deleteBuffer();

  uint32_t size() const { return m_bufferSize; }
};

#endif