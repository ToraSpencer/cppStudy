#include <algorithm>
#include<functional>
#include <numeric>
#include <vector>
#include <deque>

#include <iostream>
#include <string>
#include <typeinfo>

 
#include <cstdio>


#include "STL_算法库.h"

 

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159









// C++标准库——算法库 
/*
        <algorithm>
                        一大堆模板函数
        <numeric>
                        包含在序列上进行简单数学运算的模板函数
        <functional>
                        包含一些类模板，用以声明函数对象。

*/



// <algorithm>中的所有函数
/*
    1. 只读算法
            (C++11) all_of                  检查谓词是否对范围中所有元素为 true
            (C++11) any_of                  检查谓词是否对范围中任一元素为 true
            (C++11) none_of                 检查谓词是否对范围中无元素为 true

            for_each                        应用函数到范围中的元素
            (C++17) for_each_n              应用一个函数对象到序列的前 n 个元素

            count                           返回满足指定判别标准的元素数
            count_if                        返回满足指定判别标准的元素数

            mismatch                        寻找两个范围出现不同的首个位置

            find                            寻找首个满足特定判别标准的元素
            find_if                         寻找首个满足特定判别标准的元素
            (C++11)find_if_not              寻找首个满足特定判别标准的元素

            find_end                        在特定范围中寻找最后出现的元素序列
            find_first_of                   搜索元素集合中的任意元素
            adjacent_find                   查找首对相邻的相同（或满足给定谓词的）元素
            search                          搜索一个元素范围
            search_n                        在范围中搜索一定量的某个元素的连续副本

     2. 修改容器的算法
            copy
            (C++11) copy_if
            (C++11) copy_n
            copy_backward
            (C++11) move
            (C++11) move_backward
            fill
            fill_n
            transform
            generate
            generate_n
            remove
            remove_if
            remove_copy
            remove_copy_if
            replace
            replace_if
            replace_copy
            replace_copy_if
            swap
            swap_ranges
            iter_swap
            reverse
            reverse_copy
            rotate
            rotate_copy
            shift_left
            (C++20) shift_right
            (C++17 前) random_shuffle
            (C++11) shuffle
            (C++17) sample
            unique
            unique_copy

    3. 划分算法
            (C++11) is_partitioned
            partition
            (C++11) partition_copy
            stable_partition
            (C++11) partition_point

    4. 排序算法
        (C++11) is_sorted
        is_sorted_until
        sort
        partial_sort
        partial_sort_copy
        stable_sort
        nth_element

    5. 二分搜索（已排序范围上的）
        lower_bound
        upper_bound
        binary_search
        equal_range

    6. 其他已排序范围上操作的算法
        merge
        inplace_merge

    7. 集合操作算法（已排序范围上的）
        includes
        set_difference
        set_intersection
        set_symmetric_difference
        set_union

    8. 堆算法
        is_heap
        (C++11) is_heap_until
        make_heap
        push_heap
        pop_heap
        sort_heap

    9. 最小/最大操作
        max
        max_element
        min
        min_element
        (C++11) minmax
        (C++11) minmax_element
        (C++17) clamp

    10. 比较算法
        equal
        lexicographical_compare
        (C++20) lexicographical_compare_three_way

    11. 排列算法
        (C++11) is_permutation
        next_permutation
        prev_permutation
*/



//  模板函数：find
/*. BC------------------------------------------------------------------------
  模板函数：find

  描述：
            在容器中查找元素。
            常用的重载版本中，若找到给定元素，则返回其迭代器。


  重载1：
            (C++20 前)
            template<class InputIt, class T >
            InputIt find( InputIt first,                                  容器中第一个迭代器
                                InputIt last,                                   容器中第二个迭代器
                                const T& value);                           待查找的元素值
              返回值：指向查找元素的迭代器。若找不到，则迭代器为空。
                                  注意迭代器为空不代表其==NULL，有些编译器不接受将NULL赋值给迭代器。
                                  要想将迭代器赋值为空，可以将其赋值为end();


  重载2：
           (C++20 起)
           template<class InputIt, class T >
           constexpr InputIt find(    InputIt first,                  容器中第一个迭代器
                                                   InputIt last,                  容器中第二个迭代器
                                                   const T& value);           待查找的元素值
             返回值：

  重载3：...



*. EC------------------------------------------------------------------------
*/




//  模板函数：accumulate
/*. BC------------------------------------------------------------------------
  模板函数：accumulate

  描述：
          计算给定值和容器中给定范围内所有元素的和。             
             

  重载1：
          (C++20 前) template< class InputIt, class T >
          T accumulate(   InputIt first,                  确定容器中范围的第一个迭代器
                                      InputIt last,                 确定容器中范围的第二个迭代器
                                      T init );                        给定元素
          返回值： T   给定元素init和容器中给定范围所有元素的和。
          注意：C++20起，返回值改为constexpr
         
  重载2：
        (C++20 前) template< class InputIt, class T, class BinaryOperation >
        T accumulate( InputIt first,                                  确定容器中范围的第一个迭代器
                                  InputIt last,                                确定容器中范围的第二个迭代器
                                  T init,                                         给定元素
                                  BinaryOperation op );               
          返回值：
          注意：C++20起，返回值改为constexpr


*. EC------------------------------------------------------------------------
*/



//  模板函数：equal
/*. BC------------------------------------------------------------------------
  模板函数：equal

  描述：
          逐个比较容器中给定范围内的元素，全部相等返回true，否则返回false            
            
  重载1：
            (C++20 前) template< class InputIt1, class InputIt2 >
            bool equal(   InputIt1 first1,                            容器1的起始迭代器  
                                  InputIt1 last1,                             容器1的终止迭代器
                                  InputIt2 first2 );                          容器2的起始迭代器
              返回值：bool——进行比较的元素全部相等返回true，否则返回false
              注意：C++20起，返回值改为constexpr
     

  重载2：...
           



*. EC------------------------------------------------------------------------
*/



//  模板函数：for_each————遍历容器中的元素
/*. BC------------------------------------------------------------------------
    描述：

    重载1(C++20 前)：
        template< class InputIt, class UnaryFunction >
        UnaryFunction for_each( InputIt first, 
                                InputIt last, 
                                UnaryFunction f);

    重载1(C++20 起)：
        template< class InputIt, class UnaryFunction >
        constexpr UnaryFunction for_each(   InputIt first, 
                                            InputIt last, 
                                            UnaryFunction f );

    重载2：
        template< class ExecutionPolicy, class ForwardIt, class UnaryFunction2 >
        void for_each( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryFunction2 f );
*. EC------------------------------------------------------------------------
*/



virtualModule* STL_algorithm_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_algorithm_module;
	return p_moduleIns;
}

 
 



// test0：algorithm中一些常用的只读算法——find(), accumulate(), equal(), for_each(), max_element()
void STL_algorithm_module::test0(void)
{
	std::vector<int> vi = {1,2,5,6,1,3,-1,-9};
	std::vector<std::string> vs = {"dog","cat","panda"};
    int iarr[] = {1,-3,5,4,5,-6,4,-4,6};
    int* pi = NULL;
    int sum;
	std::vector<int>::iterator iti;
    const char* sarr[] = {"dog","cat","duck"};
    bool flag;


    std::cout << "\n\n\n\n" << std::endl;
    std::cout << "test0：algorithm中一些常用的只读算法" << std::endl;



    // find()——容器中查找元素。
    pi = std::find(std::begin(iarr), std::end(iarr), 5);                                        // 返回查找元素的迭代器。
  
    if (pi)         // 若没找到相符元素，返回的指针是NULL
    {
        std::cout << "\tthe number 5 is present in the int array iarr."<< std::endl;
    }
    else 
    {
        std::cout << "\tthe number 5 is not present in the int array iarr" << std::endl;
    }

    iti = find(begin(vi), end(vi), 99);
    if (iti != vi.end())      // vec.end()表示vec最后一个元素后一个位置，可以认为是空位置。
    {
        std::cout << "\tthe number -4 is present in the int vector vi." << std::endl;
    }
    else
    {
        std::cout << "\tthe number -4 is not present in the int vector vi." << std::endl;
    }
    std::cout << std::endl;


    // accumulate——容器元素求和
    sum = accumulate(vi.cbegin(),vi.cend(),0);    // 参数列表第三项表示额外加上的量。
    std::cout << sum << std::endl;
    sum = std::accumulate(std::begin(iarr), std::end(iarr), 0);			// 对数组也可用，不只是STL容器。
    std::cout << sum << std::endl;
    std::cout << std::endl;


    // equal——比较容器中的元素
    flag = equal(vs.begin(),vs.end(), std::begin(sarr));
    if (flag)
    {
        std::cout << "\telements from two containers are the same. " << std::endl;
    }
    else 
    {
        std::cout << "\telements from two containers are not the same." << std::endl;
    }
    std::cout << std::endl;


    // for_each——遍历容器中的元素:
    std::cout << "for_each——遍历容器中的元素:" << std::endl;
 

    std::cout << "传递函数遍历：" << std::endl;
 

    std::cout << "传递函数子遍历：" << std::endl;
 
    std::cout << std::endl;
 

	// max_element(), min_element()——返回容器中的最值元素的迭代器或指针。
	iti = std::max_element(vi.begin(), vi.end());
	pi = std::min_element(std::begin(iarr), std::end(iarr));
	std::cout << *iti << std::endl;
	std::cout << *pi << std::endl;
	
   
}




// test1: algorithm中常用的非只读算法——random_shuffle()
void STL_algorithm_module::test1(void)
{
    std::cout << "\n\n\n\n" << std::endl;
    std::cout << "test1: algorithm中常用的非只读算法" << std::endl;

    // random_shuffle(iterBegin, iterEnd)————将一个元素序列随机打乱
    //      作用于STL线性容器
	std::vector<int> arri1 = {1,2,3,4,5,6,7,8,9,10};
	std::random_shuffle(arri1.begin(), arri1.end());
    for (std::vector<int>::iterator iter = arri1.begin(); iter != arri1.end(); iter++)
    {
        std::cout << "\t" << *iter;
    }
    std::cout << std::endl;




    //      作用于数组
    int arri2[] = { 1,2,3,4,5,6,7,8,9,10 };
	std::random_shuffle(std::begin(arri2), std::end(arri2));
    for (int num : arri2)
    {
        std::cout << "\t" << num;
    }
    std::cout << std::endl;

 



}



// test2: 算法应用举例
void STL_algorithm_module::test2()
{
    // 
    std::cout << "\n\n\n\n" << std::endl;
    std::cout << "test2: 算法应用举例" << std::endl;

    // 去掉一个最高分，一个最低分，取平均作为最后得分：
    std::deque<float> df1 = {};

}


void STL_algorithm_module::test3(){}


void STL_algorithm_module::test4() {}


void STL_algorithm_module::test5() {}


void STL_algorithm_module::test6() {}