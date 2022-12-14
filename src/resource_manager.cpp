/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "resource_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>

// Instantiate static variables
std::map<std::string, Shader*>    ResourceManager::shaders;
std::map<std::string, Texture2D*> ResourceManager::textures;

Shader* ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name)
{
  shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
  return shaders[name];
}

Shader* ResourceManager::getShader(const std::string& name)
{
	return shaders[name];
}

Texture2D* ResourceManager::loadTexture(const char* file, bool alpha, const std::string& name)
{
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

Texture2D* ResourceManager::getTexture(const std::string& name)
{
	return textures[name];
}

void ResourceManager::clear()
{
	// (properly) delete all shaders	
	for (auto iter : shaders)
	{
		glDeleteProgram(iter.second->ID);
		delete iter.second;
	}
	
	// (properly) delete all textures
	for (auto iter : textures)
	{
		glDeleteTextures(1, &iter.second->ID);
		delete iter.second;
	}
}

Shader* ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		
		// if geometry shader path is present, also load a geometry shader
		if (gShaderFile)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	// 2. now create shader object from source code
	Shader* shader = new Shader();
	shader->compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D* ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
  // create texture object
  Texture2D* texture = new Texture2D();
  if (alpha)
  {
	  texture->internalFormat = GL_RGBA;
	  texture->imageFormat = GL_RGBA;
  }
  
	// load image
  int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
  
	// now generate texture
  texture->generate(width, height, data);
  
	// and finally free image data
  stbi_image_free(data);
  return texture;
}

