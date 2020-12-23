cmake_minimum_required(VERSION 2.8)
project(CppStudy)

# 检查c++编译器标志，设置c++11支持变量
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# 使用变量设置编译标志
if(COMPILER_SUPPORTS_CXX11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_executable(CppStudy
        main.cpp
        dataType_内置类型.cpp
        dataType_函数指针.cpp
        dataType_指针、智能指针、内存泄漏问题.cpp
        dataType_数组.cpp
        dataType_枚举、共用体、结构体.cpp
        dataType_对、元祖.cpp
        dataType_引用.cpp
        dataType_c风格字符串、string.cpp
        OOP_函数对象.cpp
        OOP_类、对象.cpp
        OOP_类模板.cpp
        OOP_多态、虚函数、抽象类.cpp
        practice_面试题.cpp
        set_funcs.cpp
        stdlib_IO库.cpp
        stdlib_数值库.cpp
        stdlib_工具库.cpp
        stdlib_线程支持库.cpp
        stdlib_正则表达式.cpp
        stdlib_类型支持库.cpp
        STL_线性容器.cpp
        STL_list双向链表.cpp
        STL_set键集合.cpp
        STL_map键值对集合.cpp
        STL_容器适配器.cpp
        STL_算法库.cpp
        STL_iterator迭代器.cpp
        syntax_关键字.cpp
        syntax_重载运算符.cpp
        syntax_表达式.cpp
        syntax_基本语句_新增语句.cpp
        syntax_类型转换.cpp
        syntax_几个特殊运算符.cpp
        function_内联函数.cpp
        function_基本知识.cpp
        function_函数模板.cpp
        function_可变参数函数.cpp
        example.h
        exception_基本异常处理.cpp
        exception_标准异常.cpp
        UP_预处理指令.cpp
        UP_内存管理.cpp
	 UP_断言.cpp
        )