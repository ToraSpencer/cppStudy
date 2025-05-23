#pragma once

#include <iostream>
using namespace std;

/******************************************************************************************
 * 将binTree各方法的实现部分，简洁地引入binTree.h
 * 效果等同于将这些实现直接汇入binTree.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
 ******************************************************************************************/
#include "BinTree_updateHeight.h"
#include "BinTree_insert.h"
#include "BinTree_attach.h"
#include "BinTree_remove.h"
#include "BinTree_secede.h"
