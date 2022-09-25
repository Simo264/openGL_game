/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
  // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
  uint32_t ID;

  // texture image dimensions
  uint32_t width, height; // width and height of loaded image in pixels

  // texture Format
  uint32_t internalFormat; // format of texture object
  uint32_t imageFormat; // format of loaded image

  // texture configuration
  uint32_t wrapS; // wrapping mode on S axis
  uint32_t wrapT; // wrapping mode on T axis
  uint32_t filterMin; // filtering mode if texture pixels < screen pixels
  uint32_t filterMax; // filtering mode if texture pixels > screen pixels

  // constructor (sets default texture modes)
  Texture2D();

  // generates texture from image data
  void generate(unsigned int width, unsigned int height, unsigned char* data);

  // binds the texture as the current active GL_TEXTURE_2D texture object
  void bind() const;
  void unbind() const;
};

#endif

