#include "window.h"

#include <iostream>

Window::Window(const uint16_t width, const uint16_t height, const char* title)
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  // --------------------
  m_window = glfwCreateWindow(width, height, title, NULL, NULL);
  glfwMakeContextCurrent(m_window);

}

Window::~Window()
{
  terminate();
}

const bool Window::shouldClose() const
{
  return glfwWindowShouldClose(m_window);
}

void Window::close()
{
  glfwSetWindowShouldClose(m_window, true);
}

void Window::terminate()
{
  glfwTerminate();
}

void Window::clear()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
}

void Window::swapBuffersAndPullEvents()
{
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

void Window::flush()
{
  glFlush();
}

const int Window::getKey(int key) const
{
  return glfwGetKey(m_window, key);
}
