#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
uniform vec2 move;
out vec4 v_c;
void main()
{
    gl_Position = vec4(aPos.x + move.x, aPos.y + move.y, aPos.z, 1.0);
    v_c = vec4(aCol.x, aCol.y, aCol.z, 1.0);
}