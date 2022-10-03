#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
private:
  uint32_t m_id;
  uint32_t m_size;

public:
  IndexBuffer(uint32_t size, const void* data, GLenum usage = GL_STATIC_DRAW);
  ~IndexBuffer();
  
  void bufferData(uint32_t size, const void* data, GLenum usage = GL_STATIC_DRAW);

  void bind();
  void unbind();
  void deleteBuffer();

  uint32_t size() const { return m_size; }
};

#endif