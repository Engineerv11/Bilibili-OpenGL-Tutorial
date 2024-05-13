#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 in_color;

uniform float time;
uniform float speed;

out vec3 vs_color;

void main()
{
	float delta_x = 0.3;
	float offset_x = sin(time * speed) * delta_x;
	gl_Position = vec4(pos.x + offset_x, pos.y, pos.z, 1.0);
	vs_color = in_color * (sin(time) + 1.0) / 2.0;
}