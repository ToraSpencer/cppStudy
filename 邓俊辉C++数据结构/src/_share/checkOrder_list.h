#pragma once

#include "list/list.h"

template <typename T> void checkOrder ( List<T> & L )
{ 
    //判断列表是否整体有序
   int nInv = 0;                 //逆序计数器
   L.traverse ( CheckOrder<T> ( nInv, L.first()->data ) ); //进行遍历

   if ( 0 < nInv )
      printf ( "Unsorted with %d adjacent inversion(s)\n", nInv );
   else
      printf ( "Sorted\n" );
}