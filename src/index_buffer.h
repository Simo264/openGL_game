#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
private:
  uint32_t m_id;

public:
  IndexBuffer();
  IndexBuffer(uint32_t size, const void* data, GLenum usage);
  ~IndexBuffer();
  
  void bufferData(uint32_t size, const void* data, GLenum usage);

  void bind();
  void unbind();
  void deleteBuffer();
};

#endif