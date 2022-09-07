#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>

class VertexBuffer
{
private:
  uint32_t m_buffer;

public:
  VertexBuffer(uint32_t size, GLenum usage);
  VertexBuffer(uint32_t size, const void* data, GLenum usage);
  ~VertexBuffer();

  void subData(uint32_t offset, uint32_t size, const void* data);
  
  void bind();
  void unbind();
};

#endif