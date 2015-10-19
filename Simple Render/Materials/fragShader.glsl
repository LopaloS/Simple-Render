#version 330 core

in vec2 uv;
out vec4 color;

uniform sampler2D sampler;

void main()
{
	color = texture2D(sampler, uv);
	if(color.a < 0.5f)
		discard;
}