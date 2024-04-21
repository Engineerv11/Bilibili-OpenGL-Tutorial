#需求的最低cmake版本
cmake_minimum_required(VERSION 3.12)

#此工程的名称
project(OpenGL_Lecture)

#此工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

#往项目中加入一个全局的预编译宏(格式: -D + DEBUG)
add_definitions(-DDEBUG)


include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include
)

link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib
)

add_subdirectory(wrapper)
add_subdirectory(application)

#此工程所有cpp文件编译链接生成exe
add_executable(OpenGL_App "main.cpp" "glad.c")

target_link_libraries(OpenGL_App glfw3.lib wrapper app)