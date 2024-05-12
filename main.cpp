#include <iostream>
#include <string>
#include <cassert>

#include "glframework/shader.h"

#include "wrapper/errorcheck.h"
#include "application/Application.h"

GLuint vao;
Shader* shader = nullptr;

void on_resize(int width, int height)
{
	GL_CALL(glViewport(0, 0, width, height));
}

void on_key_event(int key, int action, int mods)
{
	std::cout << "| action " << action << " |  mods " << mods << " | key -> " << key << std::endl;
}

void prepare_shader()
{
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/pixel.glsl");
}

void prepare_vao()
{
	float positions[] =
	{
		-0.5f,-0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f
	};

	float colors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	unsigned indices[] =
	{
		0, 1, 2
	};


	GLuint position_vbo;
	GLuint color_vbo;

	// 创建 vbo
	glGenBuffers(1, &position_vbo);
	// 绑定 vbo 到插槽 GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	// 传输数据到插槽 GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// 创建 vbo
	glGenBuffers(1, &color_vbo);
	// 绑定 vbo 到插槽 GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	// 传输数据到插槽 GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	GLuint ebo;

	// 创建 ebo
	glGenBuffers(1, &ebo);
	// 绑定 ebo 到插槽 GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// 传输数据到插槽 GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 创建 vao
	glGenVertexArrays(1, &vao);
	// 绑定 vao 到全局环境
	glBindVertexArray(vao);


	// 绑定 vbo 到插槽 GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	// 启用 0 号位
	glEnableVertexAttribArray(0);
	// 向 0 号位添加描述信息
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3,(void*)0);


	// 绑定 vbo 到插槽 GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	// 启用 1 号位
	glEnableVertexAttribArray(1);
	// 向 1 号位添加描述信息
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);



	// 将 ebo 加入 vao ，此前已将 vao 绑定到全局环境
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// 解除 vao 在全局环境的绑定
	glBindVertexArray(0);
}

void render()
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	shader->enable();

	shader->set_uniform("time", glfwGetTime());

	glBindVertexArray(vao);
	 
	// 发出绘制指令，绘制的索引数量为 6，数字 0 代表使用当前和 vao 关联的 veo
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	shader->disable();
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

	prepare_shader();
	prepare_vao();

	while (app->update())
	{
		render();
	}

	app->release();


	return 0;
}