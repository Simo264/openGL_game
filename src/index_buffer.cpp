#include "index_buffer.h"

IndexBuffer::IndexBuffer()
{
  glGenBuffers(1, &m_buffer);
}

IndexBuffer::IndexBuffer(uint32_t size, const void* data, GLenum usage)
{
  glGenBuffers(1, &m_buffer);
  bind();
  bufferData(size, data, usage); 
}

IndexBuffer::~IndexBuffer()
{
  deleteBuffer();
}

void IndexBuffer::bufferData(uint32_t size, const void* data, GLenum usage)
{
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage); 
}
  
void IndexBuffer::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}
void IndexBuffer::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::deleteBuffer()
{
  glDeleteBuffers(1, &m_buffer);
}