#version 410 core

in vec2 fUv;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    // FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);
    FragColor = texture(tex, fUv);
}