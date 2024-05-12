#version 330 core
out vec4 ps_color;
in vec3 vs_color;
void main()
{
	ps_color = vec4(vs_color, 1.0f);
}