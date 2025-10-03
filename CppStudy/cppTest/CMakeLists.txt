cmake_minimum_required(VERSION 3.12)
 

# 0. blah blah blah
project(cppTest VERSION 1.0)                     # 设定项目名称，版本是1.0
set(CMAKE_CXX_STANDARD 14)                          # 指定项目的C++标准：
set(CMAKE_CXX_STANDARD_REQUIRED True)               # 强制要求标准生效；

message(STATUS "PROJECT_NAME == ${PROJECT_NAME}")   # STATUS表示非重要消息

#       CMAKE_CONFIGURATION_TYPES——配置版本；默认情形下为Debug;Release;MinSizeRel;RelWithDebInfo
message(STATUS "CMAKE_CONFIGURATION_TYPES == ${CMAKE_CONFIGURATION_TYPES}")


# 1. 导入源代码文件：
#       include_directories()——指定源代码的头文件所在目录；
include_directories(${PROJECT_SOURCE_DIR}/../)
include_directories(C:/gitRepositories/TTTML/Auxiliary)       


#       aux_source_directory()——查找某路径下所有源文件：
aux_source_directory(${PROJECT_SOURCE_DIR} SRC_FILES)    # aux_source_directory(路径，存储源文件列表的变量)，PROJECT_SOURCE_DIR——此CMakeLists.txt所在目录；
aux_source_directory(C:/gitRepositories/TTTML/Auxiliary SRC_FILES_AUXILIARY)  
  

# 5. 预处理器
#       add_definitions(-DXXX)——预处理器中添加宏XXX
add_definitions(-D_CRT_SECURE_NO_WARNINGS)  

 
# 6. 设定输出内容：
#       6.1 设定输出的可执行文件名称为"cppTest"; 对应的源代码列表是SRC_FILES中存储的值；
add_executable(cppTest ${SRC_FILES} ${SRC_FILES_AUXILIARY}) 