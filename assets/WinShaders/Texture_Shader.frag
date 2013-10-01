#version 150 core

in vec2 pass_UV;
out vec4 out_Color;

uniform sampler2D texSampler;

void main(void)
{
	  out_Color = texture( texSampler, pass_UV );
}