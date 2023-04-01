#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec4 fColor;

uniform mat4 viewTimesProj;

void main()
{
	gl_Position = viewTimesProj * vec4(aPos, 1.0);
	fColor = aColor;
}
