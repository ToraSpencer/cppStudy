#pragma once

template <typename T>		 //将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
ListNodePosi<T> ListNode<T>::insertAsSucc ( T const& e ) 
{
   ListNodePosi<T> x = new ListNode ( e, this, succ );		//创建新节点
   succ->pred = x; succ = x;			//设置逆向链接
   return x;			//返回新节点的位置
}