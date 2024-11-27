#version 430 core
out vec4 FragColor;
uniform float breathe;
in vec4 v_c;
void main()
{
    FragColor = vec4(v_c.x, v_c.y, v_c.z, v_c.w);
    // FragColor = vec4(v_c.x * breathe, v_c.y * breathe, v_c.z * breathe, v_c.w);
    // FragColor = vec4(1, 0, 0, 0);
}