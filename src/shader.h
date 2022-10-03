/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
private:
  uint32_t compileShader(uint32_t target, const char* source);

public:
  uint32_t ID; 
  
  // constructor
  Shader() = default;

  // sets the current shader as active
  Shader& use();
  
  // compiles the shader from given source code
  // note: geometry source code is optional 
  void compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); 
  
  // utility functions
  void setFloat    (const char* name, float value, bool useShader = false);
  void setInteger  (const char* name, int value, bool useShader = false);
  
  void setVector2f (const char* name, float x, float y, bool useShader = false);
  void setVector2f (const char* name, const glm::vec2& value, bool useShader = false);
  
  void setVector3f (const char* name, float x, float y, float z, bool useShader = false);
  void setVector3f (const char* name, const glm::vec3& value, bool useShader = false);
  
  void setVector4f (const char* name, float x, float y, float z, float w, bool useShader = false);
  void setVector4f (const char* name, const glm::vec4& value, bool useShader = false);
  
  void setMatrix4f  (const char* name, const glm::mat4& matrix, bool useShader = false);
private:
  // checks if compilation or linking failed and if so, print the error logs
  void checkCompileErrors(uint32_t object, const std::string&); 
};

#endif