#pragma once

#include <typeinfo>

/******************************************************************************************
 * 列表、向量等结构内的节点中，可以存放基本类型或构造类型
 * 按照本书约定，出于效率的考虑，对于后一情况通常只保存对象的指针
 * 因此，在主体结构析构之前，需要首先释放这些成员对象所占的空间
 * 此处，借助C++中偏特化技术区分上述两种情况，并做对应处理
 ******************************************************************************************/

template <typename T> struct Cleaner 
{
   static void clean ( T x ) 
   { 

#ifdef _DEBUG
      static int n = 0;
      if ( 7 > strlen ( typeid ( T ).name() ) ) { //复杂类型一概忽略，只输出基本类型
         printf ( "\t<%s>[%d]=", typeid ( T ).name(), ++n );
         print ( x );
         printf ( " purged\n" );
      }
#endif
   }
};

template <typename T> struct Cleaner<T*>
{
   static void clean ( T* x ) 
   {
      if ( x ) { delete x; } //如果其中包含指针，递归释放
#ifdef _DEBUG
      static int n = 0;
      printf ( "\t<%s>[%d] released\n", typeid ( T* ).name(), ++n );
#endif
   }
};

template <typename T> void release ( T x ) { Cleaner<T>::clean ( x ); }