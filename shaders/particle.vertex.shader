#version 430 core
layout (location = 0) in vec2 aPosition;   // (x, y)
layout (location = 1) in vec2 aTextCoords; // (s, t)

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;

void main()
{
  TexCoords = aTextCoords;
  ParticleColor = color;
  gl_Position = projection * vec4((aPosition * 10.f) + offset, 0.0, 1.0);
}
