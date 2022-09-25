/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <iostream>

#include "texture2D.h"


Texture2D::Texture2D() : 
  width(0), 
  height(0), 
  internalFormat(GL_RGB), 
  imageFormat(GL_RGB), 
  wrapS(GL_REPEAT), 
  wrapT(GL_REPEAT), 
  filterMin(GL_LINEAR), 
  filterMax(GL_LINEAR)
{
  glGenTextures(1, &ID);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
  this->width = width;
  this->height = height;

  // create Texture
  bind();

  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

  // set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

  // unbind texture
  unbind();
}

void Texture2D::bind() const
{
  glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
