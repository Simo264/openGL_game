#version 430 core

in vec2 outTextCoord;
out vec4 fragColor;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
  fragColor = texture(image, outTextCoord);
} 