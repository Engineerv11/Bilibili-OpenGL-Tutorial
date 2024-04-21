#include <string>
#include <iostream>
#include <cassert>
#include <glad/glad.h>

#include "errorcheck.h"


void error_check()
{
	GLenum error_code = glGetError();

	if (error_code != GL_NO_ERROR)
	{
		switch (error_code)
		{
		case GL_INVALID_VALUE:
		{
			std::cout << "GL_INVALID_VALUE " << error_code << std::endl;

			break;
		}
		case GL_INVALID_ENUM:
		{
			std::cout << "GL_INVALID_ENUM " << error_code << std::endl;

			break;
		}
		case GL_INVALID_OPERATION:
		{
			std::cout << "GL_INVALID_OPERATION " << error_code << std::endl;

			break;
		}
		case GL_OUT_OF_MEMORY:
		{
			std::cout << "GL_OUT_OF_MEMORY " << error_code << std::endl;

			break;
		}
		default:
		{
			std::cout << "UNKNOWN " << error_code << std::endl;

			break;
		}
		}

		// 根据传入的bool值决定程序是否停止，
		// 值为true程序继续运行，值为false程序中断
		assert(false);
	}
}

