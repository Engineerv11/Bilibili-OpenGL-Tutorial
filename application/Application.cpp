#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

Application* Application::m_instance = nullptr;

Application* Application::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Application();
	}

	return m_instance;
}

bool Application::init(const int& width,const int& height)
{
	m_width = width;
	m_height = height;

	// 初始化GLFW基本环境
	glfwInit();

	// 设置OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

	// 设置OpenGL的次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// 设置OpenGL启用核心模式（非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// 创建窗体对象
	m_window = glfwCreateWindow(m_width, m_height, "OpenGLStudy", NULL, NULL);

	if (m_window == nullptr)
	{
		return false;
	}


	// 设置当前窗口为OpenGL的绘制舞台
	glfwMakeContextCurrent(m_window);

	// 使用glad加载所有当前opengl版本的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	glfwSetWindowUserPointer(m_window, this);

	glfwSetKeyCallback(m_window, key_event_callback);

	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(m_window))
	{
		return false;
	}

	// 接收并分发窗体消息
	glfwPollEvents();



	// 交换缓冲区指针，反转后台缓冲区和前台缓冲区
	glfwSwapBuffers(m_window);

	return true;
}

void Application::release()
{
	// 退出程序前做相关清理
	glfwTerminate();
}

void Application::set_resize_callback(ResizeCallback callback)
{
	m_resize_callback = callback;
}

void Application::set_key_event_callback(KeyEventCallback callback)
{
	m_key_event_callback = callback;
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);

	if (self->m_resize_callback != nullptr)
	{
		self->m_resize_callback(width, height);
	}
}

void Application::key_event_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);

	if (self->m_key_event_callback != nullptr)
	{
		self->m_key_event_callback(key, action, mods);
	}
}


Application::~Application()
{
}

Application::Application()
{
}
