#pragma once

#if defined( DSA_REDBLACK )
#define stature(p) ((p) ? (p)->height : 0) //������ڵ�ĺڸ߶ȣ�NULL�����ⲿ�ڵ㣬��Ӧ��0��
#else
#define stature(p) ((p) ? (p)->height : -1) //����BST�нڵ�ĸ߶ȣ�NUll������������Ӧ��-1��
#endif

typedef enum { RB_RED, RB_BLACK} RBColor;       //�ڵ���ɫ

template <typename T> struct BinNode;

template <typename T> using BinNodePosi = BinNode<T>*; //�ڵ�λ��


// BinNode�ࡪ��BT�ڵ���
template <typename T>
struct BinNode
{  
   T data; //��ֵ
   BinNodePosi<T> parent, lc, rc; //���ڵ㼰���Һ���
   int height; //�߶ȣ�ͨ�ã�
   int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
   RBColor color; //��ɫ���������
 
   BinNode() :
      parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { }
   BinNode ( T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
             int h = 0, int l = 1, RBColor c = RB_RED ) :
      data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { }
 

   int size();                              //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
   BinNodePosi<T> insertAsLC ( T const & ); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
   BinNodePosi<T> insertAsRC ( T const & ); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
   BinNodePosi<T> succ();           //ȡ��ǰ�ڵ��ֱ�Ӻ��
   template <typename VST> void travLevel ( VST& ); //������α���
   template <typename VST> void travPre ( VST& ); //�����������
   template <typename VST> void travIn ( VST& ); //�����������
   template <typename VST> void travPost ( VST& ); //�����������

    // �Ƚ������е�����������һ���������в��䣩
   bool operator< ( BinNode const& bn ) { return data < bn.data; } //С��
   bool operator== ( BinNode const& bn ) { return data == bn.data; } //����
   
   BinNodePosi<T> zig(); //˳ʱ����ת
   BinNodePosi<T> zag(); //��ʱ����ת
   BinNodePosi<T> balance(); //��ȫƽ�⻯
   BinNodePosi<T> imitate( const BinNodePosi<T> );
};


#include "BinNode_implementation.h"