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

	void set_uniform(const std::string& name,float value);

	void set_uniform_v3(const std::string& name, float x, float y, float z);
	
	void set_uniform_v3(const std::string& name, const float* values);

private:
	void check_shader_error(GLuint target,std::string type);

private:
	GLuint m_program = 0;
};