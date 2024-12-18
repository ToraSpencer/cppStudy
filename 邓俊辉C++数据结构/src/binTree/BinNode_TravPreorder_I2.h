#pragma once

// 从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST> //元素类型、操作器
static void visitAlongVine ( BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>>& S ) 
{
   while ( x ) {
      visit ( x->data ); //访问当前节点
      S.push ( x->rc ); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
      x = x->lc;  //沿左分支深入一层
   }
}

template <typename T, typename VST> //元素类型、操作器
void travPre_I2 ( BinNodePosi<T> x, VST& visit ) { //二叉树先序遍历算法（迭代版#2）
   Stack<BinNodePosi<T>> S; //辅助栈
   while ( true ) {
      visitAlongVine ( x, visit, S ); //从当前节点出发，逐批访问
      if ( S.empty() ) break; //直到栈空
      x = S.pop(); //弹出下一批的起点
   }
}