#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window
{
protected:
  GLFWwindow* m_window;
  
public:
  Window(const uint16_t width, const uint16_t height, const char* title);
  ~Window();

  const bool shouldClose() const;
  void close();
  void terminate();
  void clear();

  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
  // -------------------------------------------------------------------------------
  void swapBuffersAndPullEvents();
  void flush();
  const int getKey(int key) const;
};

#endif