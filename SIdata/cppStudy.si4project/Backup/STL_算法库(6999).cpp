#include <algorithm>
#include<functional>
#include <numeric>
#include <vector>
#include <deque>

#include <iostream>
#include <string>
#include <typeinfo>

 
#include <cstdio>


#include "STL_�㷨��.h"

 

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159









// C++��׼�⡪���㷨�� 
/*
        <algorithm>
                        һ���ģ�庯��
        <numeric>
                        �����������Ͻ��м���ѧ�����ģ�庯��
        <functional>
                        ����һЩ��ģ�壬����������������

*/



// <algorithm>�е����к���
/*
    1. ֻ���㷨
            (C++11) all_of                  ���ν���Ƿ�Է�Χ������Ԫ��Ϊ true
            (C++11) any_of                  ���ν���Ƿ�Է�Χ����һԪ��Ϊ true
            (C++11) none_of                 ���ν���Ƿ�Է�Χ����Ԫ��Ϊ true

            for_each                        Ӧ�ú�������Χ�е�Ԫ��
            (C++17) for_each_n              Ӧ��һ�������������е�ǰ n ��Ԫ��

            count                           ��������ָ���б��׼��Ԫ����
            count_if                        ��������ָ���б��׼��Ԫ����

            mismatch                        Ѱ��������Χ���ֲ�ͬ���׸�λ��

            find                            Ѱ���׸������ض��б��׼��Ԫ��
            find_if                         Ѱ���׸������ض��б��׼��Ԫ��
            (C++11)find_if_not              Ѱ���׸������ض��б��׼��Ԫ��

            find_end                        ���ض���Χ��Ѱ�������ֵ�Ԫ������
            find_first_of                   ����Ԫ�ؼ����е�����Ԫ��
            adjacent_find                   �����׶����ڵ���ͬ�����������ν�ʵģ�Ԫ��
            search                          ����һ��Ԫ�ط�Χ
            search_n                        �ڷ�Χ������һ������ĳ��Ԫ�ص���������

     2. �޸��������㷨
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
            (C++17 ǰ) random_shuffle
            (C++11) shuffle
            (C++17) sample
            unique
            unique_copy

    3. �����㷨
            (C++11) is_partitioned
            partition
            (C++11) partition_copy
            stable_partition
            (C++11) partition_point

    4. �����㷨
        (C++11) is_sorted
        is_sorted_until
        sort
        partial_sort
        partial_sort_copy
        stable_sort
        nth_element

    5. ����������������Χ�ϵģ�
        lower_bound
        upper_bound
        binary_search
        equal_range

    6. ����������Χ�ϲ������㷨
        merge
        inplace_merge

    7. ���ϲ����㷨��������Χ�ϵģ�
        includes
        set_difference
        set_intersection
        set_symmetric_difference
        set_union

    8. ���㷨
        is_heap
        (C++11) is_heap_until
        make_heap
        push_heap
        pop_heap
        sort_heap

    9. ��С/������
        max
        max_element
        min
        min_element
        (C++11) minmax
        (C++11) minmax_element
        (C++17) clamp

    10. �Ƚ��㷨
        equal
        lexicographical_compare
        (C++20) lexicographical_compare_three_way

    11. �����㷨
        (C++11) is_permutation
        next_permutation
        prev_permutation
*/



//  ģ�庯����find
/*. BC------------------------------------------------------------------------
  ģ�庯����find

  ������
            �������в���Ԫ�ء�
            ���õ����ذ汾�У����ҵ�����Ԫ�أ��򷵻����������


  ����1��
            (C++20 ǰ)
            template<class InputIt, class T >
            InputIt find( InputIt first,                                  �����е�һ��������
                                InputIt last,                                   �����еڶ���������
                                const T& value);                           �����ҵ�Ԫ��ֵ
              ����ֵ��ָ�����Ԫ�صĵ����������Ҳ������������Ϊ�ա�
                                  ע�������Ϊ�ղ�������==NULL����Щ�����������ܽ�NULL��ֵ����������
                                  Ҫ�뽫��������ֵΪ�գ����Խ��丳ֵΪend();


  ����2��
           (C++20 ��)
           template<class InputIt, class T >
           constexpr InputIt find(    InputIt first,                  �����е�һ��������
                                                   InputIt last,                  �����еڶ���������
                                                   const T& value);           �����ҵ�Ԫ��ֵ
             ����ֵ��

  ����3��...



*. EC------------------------------------------------------------------------
*/




//  ģ�庯����accumulate
/*. BC------------------------------------------------------------------------
  ģ�庯����accumulate

  ������
          �������ֵ�������и�����Χ������Ԫ�صĺ͡�             
             

  ����1��
          (C++20 ǰ) template< class InputIt, class T >
          T accumulate(   InputIt first,                  ȷ�������з�Χ�ĵ�һ��������
                                      InputIt last,                 ȷ�������з�Χ�ĵڶ���������
                                      T init );                        ����Ԫ��
          ����ֵ�� T   ����Ԫ��init�������и�����Χ����Ԫ�صĺ͡�
          ע�⣺C++20�𣬷���ֵ��Ϊconstexpr
         
  ����2��
        (C++20 ǰ) template< class InputIt, class T, class BinaryOperation >
        T accumulate( InputIt first,                                  ȷ�������з�Χ�ĵ�һ��������
                                  InputIt last,                                ȷ�������з�Χ�ĵڶ���������
                                  T init,                                         ����Ԫ��
                                  BinaryOperation op );               
          ����ֵ��
          ע�⣺C++20�𣬷���ֵ��Ϊconstexpr


*. EC------------------------------------------------------------------------
*/



//  ģ�庯����equal
/*. BC------------------------------------------------------------------------
  ģ�庯����equal

  ������
          ����Ƚ������и�����Χ�ڵ�Ԫ�أ�ȫ����ȷ���true�����򷵻�false            
            
  ����1��
            (C++20 ǰ) template< class InputIt1, class InputIt2 >
            bool equal(   InputIt1 first1,                            ����1����ʼ������  
                                  InputIt1 last1,                             ����1����ֹ������
                                  InputIt2 first2 );                          ����2����ʼ������
              ����ֵ��bool�������бȽϵ�Ԫ��ȫ����ȷ���true�����򷵻�false
              ע�⣺C++20�𣬷���ֵ��Ϊconstexpr
     

  ����2��...
           



*. EC------------------------------------------------------------------------
*/



//  ģ�庯����for_each�����������������е�Ԫ��
/*. BC------------------------------------------------------------------------
    ������

    ����1(C++20 ǰ)��
        template< class InputIt, class UnaryFunction >
        UnaryFunction for_each( InputIt first, 
                                InputIt last, 
                                UnaryFunction f);

    ����1(C++20 ��)��
        template< class InputIt, class UnaryFunction >
        constexpr UnaryFunction for_each(   InputIt first, 
                                            InputIt last, 
                                            UnaryFunction f );

    ����2��
        template< class ExecutionPolicy, class ForwardIt, class UnaryFunction2 >
        void for_each( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryFunction2 f );
*. EC------------------------------------------------------------------------
*/



virtualModule* STL_algorithm_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_algorithm_module;
	return p_moduleIns;
}

 
 



// test0��algorithm��һЩ���õ�ֻ���㷨����find(), accumulate(), equal(), for_each(), max_element()
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
    std::cout << "test0��algorithm��һЩ���õ�ֻ���㷨" << std::endl;



    // find()���������в���Ԫ�ء�
    pi = std::find(std::begin(iarr), std::end(iarr), 5);                                        // ���ز���Ԫ�صĵ�������
  
    if (pi)         // ��û�ҵ����Ԫ�أ����ص�ָ����NULL
    {
        std::cout << "\tthe number 5 is present in the int array iarr."<< std::endl;
    }
    else 
    {
        std::cout << "\tthe number 5 is not present in the int array iarr" << std::endl;
    }

    iti = find(begin(vi), end(vi), 99);
    if (iti != vi.end())      // vec.end()��ʾvec���һ��Ԫ�غ�һ��λ�ã�������Ϊ�ǿ�λ�á�
    {
        std::cout << "\tthe number -4 is present in the int vector vi." << std::endl;
    }
    else
    {
        std::cout << "\tthe number -4 is not present in the int vector vi." << std::endl;
    }
    std::cout << std::endl;


    // accumulate��������Ԫ�����
    sum = accumulate(vi.cbegin(),vi.cend(),0);    // �����б�������ʾ������ϵ�����
    std::cout << sum << std::endl;
    sum = std::accumulate(std::begin(iarr), std::end(iarr), 0);			// ������Ҳ���ã���ֻ��STL������
    std::cout << sum << std::endl;
    std::cout << std::endl;


    // equal�����Ƚ������е�Ԫ��
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


    // for_each�������������е�Ԫ��:
    std::cout << "for_each�������������е�Ԫ��:" << std::endl;
 

    std::cout << "���ݺ���������" << std::endl;
 

    std::cout << "���ݺ����ӱ�����" << std::endl;
 
    std::cout << std::endl;
 

	// max_element(), min_element()�������������е���ֵԪ�صĵ�������ָ�롣
	iti = std::max_element(vi.begin(), vi.end());
	pi = std::min_element(std::begin(iarr), std::end(iarr));
	std::cout << *iti << std::endl;
	std::cout << *pi << std::endl;
	
   
}




// test1: algorithm�г��õķ�ֻ���㷨����random_shuffle()
void STL_algorithm_module::test1(void)
{
    std::cout << "\n\n\n\n" << std::endl;
    std::cout << "test1: algorithm�г��õķ�ֻ���㷨" << std::endl;

    // random_shuffle(iterBegin, iterEnd)����������һ��Ԫ�������������
    //      ������STL��������
	std::vector<int> arri1 = {1,2,3,4,5,6,7,8,9,10};
	std::random_shuffle(arri1.begin(), arri1.end());
    for (std::vector<int>::iterator iter = arri1.begin(); iter != arri1.end(); iter++)
    {
        std::cout << "\t" << *iter;
    }
    std::cout << std::endl;




    //      ����������
    int arri2[] = { 1,2,3,4,5,6,7,8,9,10 };
	std::random_shuffle(std::begin(arri2), std::end(arri2));
    for (int num : arri2)
    {
        std::cout << "\t" << num;
    }
    std::cout << std::endl;

 



}



// test2: �㷨Ӧ�þ���
void STL_algorithm_module::test2()
{
    // 
    std::cout << "\n\n\n\n" << std::endl;
    std::cout << "test2: �㷨Ӧ�þ���" << std::endl;

    // ȥ��һ����߷֣�һ����ͷ֣�ȡƽ����Ϊ���÷֣�
    std::deque<float> df1 = {};

}


void STL_algorithm_module::test3(){}


void STL_algorithm_module::test4() {}


void STL_algorithm_module::test5() {}


void STL_algorithm_module::test6() {}