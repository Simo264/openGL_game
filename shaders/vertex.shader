#version 430 core
layout (location = 0) in vec2 position;   // (x, y)
layout (location = 1) in vec2 textCoord;  // (s, t)

out vec2 outTextCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  outTextCoord  = textCoord;
  gl_Position   = projection * model * vec4(position, 0, 1);
}