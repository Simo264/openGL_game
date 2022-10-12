#version 430 core

in vec2 TexCoords;
out vec4 fragColor;

uniform vec3 spriteColor;
uniform sampler2D image;

void main()
{
  fragColor = vec4(spriteColor, 1.0) * texture(image, TexCoords);
} 