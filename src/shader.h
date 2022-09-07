#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
private:
  uint32_t m_shader;
  
  void parseShader(const char* filePath, std::string& shader);
  uint32_t compileShader(uint32_t type, const char* shaderSource);
  uint32_t createShaderProgram(const char* vShaderSource, const char* fShaderSource);

public:
  Shader(const char* vertexFilePath, const char* fragmentFilePath);
  ~Shader();

  void use();

  void setBool(const char* name, bool value) const;  
  void setInt(const char* name, int value) const;   
  void setFloat(const char* name, float value) const;
  void setMatrix4Float(const char* name, const glm::mat4 &mat) const;
  
  int getAttribLocation(const char* name);
};

#endif