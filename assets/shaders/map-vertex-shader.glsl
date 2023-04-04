#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 fColor;
out vec2 fTexCoord;

uniform mat4 viewTimesProj;

void main()
{
	gl_Position = viewTimesProj * vec4(aPos, 1.0);
	fColor = aColor;
	fTexCoord = aTexCoord;
}
