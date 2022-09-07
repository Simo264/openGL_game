#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
private:
  uint32_t m_buffer;

public:
  IndexBuffer(uint32_t size, const void* data, GLenum usage);
  ~IndexBuffer();
  
  void bind();
  void unbind();
};

#endif