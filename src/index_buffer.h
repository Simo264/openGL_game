#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <cstdint>

class IndexBuffer
{
private:
  uint32_t m_id;

public:
  IndexBuffer(uint32_t size, const void* data, uint32_t usage);
  ~IndexBuffer();
  
  void bufferData(uint32_t size, const void* data, uint32_t usage);

  void bind();
  void unbind();
  void deleteBuffer();
};

#endif