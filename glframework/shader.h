#pragma once

#include "core.h"
#include <string>

class Shader
{
public:
	Shader(const char* vertex_path,const char* pixel_path);
	~Shader();

	// 启用当前Shader
	void enable();

	// 禁用当前Shader
	void disable();

private:
	void check_shader_error(GLuint target,std::string type);

private:
	GLuint m_program = 0;
};