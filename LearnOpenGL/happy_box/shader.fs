#version 430 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
    // FragColor = texture(texture1, texCoord);
    // FragColor = texture(texture2, texCoord);
}