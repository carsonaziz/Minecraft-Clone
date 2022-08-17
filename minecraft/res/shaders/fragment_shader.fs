#version 410 core

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    // FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);
    // FragColor = vec4(uv, 0.0f, 1.0f);
    FragColor = texture(tex, uv);
}