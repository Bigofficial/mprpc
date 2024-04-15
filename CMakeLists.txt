#设置cmake最低版本，项目名称
cmake_minimum_required(VERSION 3.0)

project(mprpc)

#生成debug版本可以gdb调试
set(CMAKE_BUILD_TYPE "Debug")

#设置可文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#头文件路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/example)

#库文件搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)
#子搜索
add_subdirectory(src)
add_subdirectory(example)