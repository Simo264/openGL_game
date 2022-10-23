#version 430 core

in vec2 TexCoords;
out vec4 fragColor;

uniform vec3 imageColor;
uniform sampler2D image;

void main()
{
  fragColor = vec4(imageColor, 1.0) * texture(image, TexCoords);
} 