#version 330 core

out vec4 FragColor;

in vec4 fColor;
in vec2 fTexCoord;

uniform sampler2D textureSampler;

void main()
{
//	FragColor = texture(textureSampler, fTexCoord);
	FragColor = fColor;
}
