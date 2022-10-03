#version 430 core
layout (location = 0) in vec2 aPosition;   // (x, y)
layout (location = 1) in vec2 aTextCoords; // (s, t)

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  TexCoords = aTextCoords;
  gl_Position = model * vec4(aPosition, 0, 1);
}