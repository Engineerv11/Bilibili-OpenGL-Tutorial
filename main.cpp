#include <iostream>
#include <string>
#include <cassert>

#include <glad/glad.h>  // 此include语句应放在#include <GLFW/glfw3.h>上方
#include <GLFW/glfw3.h>

#include "wrapper/errorcheck.h"
#include "application/Application.h"

GLuint vao, program;

void on_resize(int width, int height)
{
	GL_CALL(glViewport(0, 0, width, height));
}

void on_key_event(int key, int action, int mods)
{
	std::cout << "| action " << action << " |  mods " << mods << " | key -> " << key << std::endl;
}

void prepare_single_buffer()
{
	float positions[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	float colors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	// 创建vbo
	GLuint position_vbo;
	GLuint color_vbo;

	glGenBuffers(1, &position_vbo);
	glGenBuffers(1, &color_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);	// 绑定vao

	// 之后执行的属性描述操作将与此时绑定的vbo关联，因此首先绑定vbo
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glDisableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 将vao解除绑定
	glBindVertexArray(0);
}

void prepare_interleaved_buffer()
{
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};


	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 位置描述信息
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// 颜色描述信息
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// 解除vao绑定
	glBindVertexArray(0);
}

void prepare_shader()
{
	const char* vertex_shader_source =
		"#version 460 core\n"
		"layout(location = 0) in vec3 pos;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
		"}\0";

	const char* fragment_shader_source =
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	GLuint vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vertex_shader_source, NULL);

	glShaderSource(fragment, 1, &fragment_shader_source, NULL);

	int success = 0;
	char info_log[1024];

	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, info_log);
		std::cout << "Error: Shader compile error - vertex\n" << info_log << std::endl;
	}

	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, info_log);
		std::cout << "Error: Shader compile error - fragment\n" << info_log << std::endl;
	}

	program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, info_log);
		std::cout << "Error: Shader link error - program\n" << info_log << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void render()
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	glUseProgram(program);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

int main()
{
	if (!app->init())
	{
		return -1;
	}

	app->set_resize_callback(on_resize);
	app->set_key_event_callback(on_key_event);

	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 1.0f, 1.0f));

	prepare_interleaved_buffer();
	prepare_shader();

	while (app->update())
	{
		render();
	}

	app->release();


	return 0;
}