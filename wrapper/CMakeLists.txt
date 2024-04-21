#递归，将此文件夹下的所有cpp文件放到wrapper中
file(GLOB_RECURSE WRAPPER ./*.cpp)

#将wrapper中所有cpp编译为wrapper库，lib文件
add_library(wrapper ${WRAPPER})