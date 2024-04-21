#pragma once

#include <iostream>

#define app Application::instance()

class GLFWwindow;

using ResizeCallback = void(*)(int width, int height);
using KeyEventCallback = void(*)(int key, int action, int mods);

// 单例类 Application ，构造函数放在 private 下
class Application
{
public:
	~Application();

	static Application* instance();

	bool init(const int& width = 800, const int& height = 600);
	bool update();
	void release();

	uint32_t width() const;
	uint32_t height() const;

	void set_resize_callback(ResizeCallback callback);
	void set_key_event_callback(KeyEventCallback callback);

private:
	static void framebuffer_size_callback(GLFWwindow* window,int width,int height);
	static void key_event_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	 

private:
	static Application* m_instance;

	uint32_t m_width = 0;
	uint32_t m_height = 0;
	GLFWwindow* m_window = nullptr;

	ResizeCallback m_resize_callback = nullptr;
	KeyEventCallback m_key_event_callback = nullptr;

	Application();

};