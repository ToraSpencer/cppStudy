#pragma once

/*DSA*/template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
/*DSA*/BinNodePosi<T> BinTree<T>::attachAsLC ( BinNodePosi<T> x, BinTree<T>* &S ) { //x->lc == NULL
/*DSA*/   if ( x->lc = S->_root ) x->lc->parent = x; //����
/*DSA*/   _size += S->_size; updateHeightAbove ( x ); //����ȫ����ģ��x�������ȵĸ߶�
/*DSA*/   S->_root = NULL; S->_size = 0; release ( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
/*DSA*/}
/*DSA*/

template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi<T> BinTree<T>::attachAsRC ( BinNodePosi<T> x, BinTree<T>* &S ) 
{ //x->rc == NULL
   if ( x->rc = S->_root ) 
      x->rc->parent = x; //����
   _size += S->_size; updateHeightAbove ( x ); //����ȫ����ģ��x�������ȵĸ߶�
   S->_root = NULL; S->_size = 0; release ( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
} //attachAsLC()��ȫ�Գƣ��ڴ�ʡ�ԣ�release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ����������
