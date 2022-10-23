#include "index_buffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(uint32_t size, const void* data, uint32_t usage)
{
  glGenBuffers(1, &m_id);
  bind();
  bufferData(size, data, usage); 
}

IndexBuffer::~IndexBuffer()
{
  deleteBuffer();
}

void IndexBuffer::bufferData(uint32_t size, const void* data, uint32_t usage)
{
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage); 
}
  
void IndexBuffer::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
void IndexBuffer::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::deleteBuffer()
{
  glDeleteBuffers(1, &m_id);
}