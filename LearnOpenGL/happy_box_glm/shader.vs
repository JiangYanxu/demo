#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    // gl_Position = vec4(aPos, 1.0);
    texCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}