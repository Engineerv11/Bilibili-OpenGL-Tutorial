#include "shader.h"
#include "shader.h"
#include "../wrapper/errorcheck.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertex_path, const char* pixel_path)
{
	std::string vertex_code;
	std::string pixel_code;

	std::ifstream in_vertex_file;
	std::ifstream in_pixel_file;

	in_vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	in_pixel_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		in_vertex_file.open(vertex_path);
		in_pixel_file.open(pixel_path);

		std::stringstream vertex_shader_stream;
		std::stringstream pixel_shader_stream;

		vertex_shader_stream << in_vertex_file.rdbuf();
		pixel_shader_stream << in_pixel_file.rdbuf();

		in_vertex_file.close();
		in_pixel_file.close();

		vertex_code = vertex_shader_stream.str();
		pixel_code = pixel_shader_stream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "error: failed to read shader file" << e.what() << std::endl;
	}

	const char* vertex_shader_source = vertex_code.c_str();
	const char* pixel_shader_source = pixel_code.c_str();

	GLuint vertex, pixel;

	vertex = glCreateShader(GL_VERTEX_SHADER);

	pixel = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vertex_shader_source, NULL);

	glShaderSource(pixel, 1, &pixel_shader_source, NULL);

	int success = 0;
	char info_log[1024];

	glCompileShader(vertex);

	check_shader_error(vertex,"COMPILE");

	glCompileShader(pixel);

	check_shader_error(pixel, "COMPILE");

	m_program = glCreateProgram();
	
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, pixel);

	glLinkProgram(m_program);

	check_shader_error(m_program, "LINK");

	glDeleteShader(vertex);
	glDeleteShader(pixel);
}

Shader::~Shader()
{
}

void Shader::enable()
{
	GL_CALL(glUseProgram(m_program));
}

void Shader::disable()
{
	GL_CALL(glUseProgram(0));
}

void Shader::check_shader_error(GLuint target, std::string type)
{
	int success = 0;

	char info_log[1024];

	if (type == "COMPILE")
	{
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(target, 1024, NULL, info_log);
			std::cout << "Error: Shader compile error\n" << info_log << std::endl;
		}
	}
	else if (type == "LINK")
	{
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(target, 1024, NULL, info_log);
			std::cout << "Error: Shader link error - program\n" << info_log << std::endl;
		}
	}
	else
	{
		std::cout << "error: parameter type invalid"<<std::endl;
	}
}
