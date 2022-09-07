#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
  std::string vertexShaderSrc;  
  std::string fragmentShaderSrc; 
  parseShader(vertexFilePath, vertexShaderSrc);
  parseShader(fragmentFilePath, fragmentShaderSrc);

  m_shader = createShaderProgram(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
}
Shader::~Shader()
{
  glDeleteProgram(m_shader);
}


/****** Public methods *****/
/***************************/
void Shader::use()
{
  glUseProgram(m_shader);
}

void Shader::setBool(const char* name, bool value) const
{
  glUniform1i(glGetUniformLocation(m_shader, name), (int)value); 
}
void Shader::setInt(const char* name, int value) const  
{
  glUniform1i(glGetUniformLocation(m_shader, name), value); 
}
void Shader::setFloat(const char* name, float value) const
{
  glUniform1f(glGetUniformLocation(m_shader, name), value);
}
void Shader::setMatrix4Float(const char* name, const glm::mat4 &mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_shader, name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::getAttribLocation(const char* name)
{
  return glGetAttribLocation(m_shader, name);
}

/****** Private methods *****/
/****************************/
void Shader::parseShader(const char* filePath, std::string& shader)
{
  std::ifstream file(filePath);
  file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
  try
  {
    std::stringstream shaderStream;
    shaderStream << file.rdbuf();
    shader = shaderStream.str();
  }
  catch(const std::ifstream::failure& e)
  {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  file.close();
}
uint32_t Shader::compileShader(uint32_t type, const char* shaderSource)
{
  uint32_t shader = glCreateShader(type);
  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);

  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::" 
      << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") 
      << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    return 0;
  }

  return shader;
}
uint32_t Shader::createShaderProgram(const char* vShaderSource, const char* fShaderSource)
{
  uint32_t program = glCreateProgram();
  uint32_t vShader = compileShader(GL_VERTEX_SHADER, vShaderSource);
  uint32_t fShader = compileShader(GL_FRAGMENT_SHADER, fShaderSource);
  
  glAttachShader(program, vShader);
  glAttachShader(program, fShader);
  glLinkProgram(program);

  // print linking errors if any
  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vShader);
  glDeleteShader(fShader);

  return program;
}