#pragma once

template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove ( BinNodePosi<T> x )
 { //assert: xΪ�������еĺϷ�λ��
   FromParentTo ( *x ) = NULL; //�ж����Ը��ڵ��ָ��
   updateHeightAbove ( x->parent ); //�������ȸ߶�
   int n = removeAt ( x ); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}


template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt ( BinNodePosi<T> x ) 
{ //assert: xΪ�������еĺϷ�λ��
   if ( !x ) 
      return 0; //�ݹ��������
   int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc ); //�ݹ��ͷ���������
   release ( x->data ); release ( x ); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} //release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ����������