#pragma once

//ͨ��zag��ת��������BST����x����������ͨ·
template <typename T> void stretchByZag ( BinNodePosi<T> & x ) {
   /*DSA*/   int c = 0; //��¼��ת����
   BinNodePosi<T> p = x; while ( p->rc ) p = p->rc; //���ڵ㣬�����������յĸ�
   while ( x->lc ) x = x->lc; //ת����ʼ�����ͨ·��ĩ��
   for ( ; x != p; x = x->parent ) { //��x�������ѿգ�������һ��
      while ( x->rc ) //���򣬷�����
         /*DSA*/{
         x->zag(); //��xΪ����zag��ת
         /*DSA*/c++;
         /*DSA*/}
   } //ֱ���ִ������ĸ�
   /*DSA*/printf ( "\nsize = %d, height = %d, #zag = %d\n\n", x->size(), x->height, c );
}
