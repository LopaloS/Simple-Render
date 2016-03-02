#version 330 core

in vec2 uv;
uniform sampler2D mainTex;

void main()
{
	if(texture(mainTex, uv).a < 0.5f)
		discard;
}