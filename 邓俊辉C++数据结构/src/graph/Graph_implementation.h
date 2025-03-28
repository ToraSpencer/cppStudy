#pragma once

/******************************************************************************************
 * 将Graph各方法的实现部分，简洁地引入Graph.h
 * 效果等同于将这些实现直接汇入Graph.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
 ******************************************************************************************/
#include "_share/release.h"
#include "_share/util.h"

#include "Graph_bfs.h"
#include "Graph_bfs_PU.h"
#include "Graph_dfs.h"
#include "Graph_dfs_PU.h"
#include "Graph_tsort.h"
#include "Graph_bcc.h"
#include "Graph_prim.h"
#include "Graph_dijkstra.h"
#include "Graph_pfs.h"
#include "Graph_prim_PU.h"
#include "Graph_dijkstra_PU.h"
