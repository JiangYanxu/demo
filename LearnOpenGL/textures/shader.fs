#version 430 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
void main()
{
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = texture(texture1, texCoord) * vec4(ourColor, 1.0);
}