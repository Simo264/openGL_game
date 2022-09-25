/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#include "shader.h"

#include <iostream>

Shader& Shader::use()
{
	glUseProgram(ID);
	return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	uint32_t sVertex, sFragment, gShader;

	// vertex Shader
	sVertex = compileShader(GL_VERTEX_SHADER, vertexSource);
	checkCompileErrors(sVertex, "VERTEX");

	// fragment Shader
	sFragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
	checkCompileErrors(sFragment, "FRAGMENT");

	// if geometry shader source code is given, also compile geometry shader
	if(geometrySource)
	{
		gShader = compileShader(GL_GEOMETRY_SHADER, geometrySource);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	// shader program
	ID = glCreateProgram();
	glAttachShader(ID, sVertex);
	glAttachShader(ID, sFragment);
	if(geometrySource)
		glAttachShader(ID, gShader);

	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if(geometrySource)
		glDeleteShader(gShader);
}

uint32_t Shader::compileShader(uint32_t target, const char* source)
{
	uint32_t shader = glCreateShader(target);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	return shader;
}



void Shader::setFloat(const char *name, float value, bool useShader)
{
	if(useShader)
		use();
	glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::setInteger(const char *name, int value, bool useShader)
{
	if(useShader)
		use();
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setVector2f(const char *name, float x, float y, bool useShader)
{
	if(useShader)
		use();
	glUniform2f(glGetUniformLocation(ID, name), x, y);
}
void Shader::setVector2f(const char *name, const glm::vec2 &value, bool useShader)
{
	if(useShader)
		use();
	glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::setVector3f(const char *name, float x, float y, float z, bool useShader)
{
	if(useShader)
		use();
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}
void Shader::setVector3f(const char *name, const glm::vec3 &value, bool useShader)
{
	if(useShader)
		use();
	glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char *name, float x, float y, float z, float w, bool useShader)
{
	if(useShader)
		use();
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}
void Shader::setVector4f(const char *name, const glm::vec4 &value, bool useShader)
{
	if(useShader)
		use();
	glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char *name, const glm::mat4 &matrix, bool useShader)
{
	if(useShader)
		use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, false, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(uint32_t object, const std::string& type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
					<< infoLog << "\n -- --------------------------------------------------- -- "
					<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
					<< infoLog << "\n -- --------------------------------------------------- -- "
					<< std::endl;
		}
	}
}
