#version 150 core
in vec3 in_Position;
in vec2 in_UV;

out vec2 pass_UV;

void main(void)
{
     gl_Position = vec4(in_Position, 1.0);
     
	 pass_UV = in_UV;
}