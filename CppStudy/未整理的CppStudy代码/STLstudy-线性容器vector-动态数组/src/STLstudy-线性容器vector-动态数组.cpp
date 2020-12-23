#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中
using namespace std;


/* vector:
 * 		本质是动态数组：
 * 				元素在内存中连续存储；
 * 				当以开辟内存被填满时，若需要添加元素，则重新分配内存，容量扩张为原来的两倍。
 * 		特点：
 * 				尾插，尾删速度很快，其他位置可能比较慢。
 * 				支持随机访问。
 */

// 遍历打印vector元素的函数
template <typename T>
void dispVector(vector<T> v)
{
	vector<int>::const_iterator it1,it2;
	it1 = v.cbegin();
	it2 = v.cend();
	while(it1!=it2)
	{
		cout << *it1 << "   ";
		it1++;
	}
	cout << endl;
}

//test1():vector与其他线性容器相比特有的特点：
void test1()
{
	cout << "test1():vector与其他线性容器相比特有的特点：" << endl << endl;
	vector<int>vi;
	vector<int>::iterator iter_i;
	vector<int>::const_iterator citer_i;

	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);
	vi.push_back(6);

	//vector可以使用下标v[i]直接访问元素：
	cout << "vector可以使用下标v[i]直接访问元素：" << endl;
	for(int i  = 0; i<=vi.size()-1; i++)
	{cout << vi[i] << "  ";}
	cout << endl;
}

//test2():构造函数、初始化方法。
void test2()
{
	cout << "test2():向量构造函数、初始化方法" << endl << endl;

	// vector<_Tp>() 声明/无参构造：
	cout << "vector<_Tp>() 声明/无参构造：" << endl;
	vector<int> vi1;				//构造一个空向量。
	cout << "is vi1 empty?  " << vi1.empty() << endl << endl;

	// vector<_Tp>(int size) 构造包含size个0元素的vector
	cout << "vector<_Tp>(int size) 构造包含size个0元素的vector" << endl;
	vector<int> vi2(3);				//构造一个设定容量为3的向量。
	dispVector(vi2);
	cout << endl;
	cout << "the capacity of vi2 is : " << vi2.capacity() << endl;
	vi2.push_back(1);
	vi2.push_back(2);
	vi2.push_back(3);
	vi2.push_back(4);
	dispVector(vi2);
	cout << "now the actual size of vi2 is : " << vi2.size() << endl;
	//实际存储的元素数量是可以超出容器的capacity的
	cout << endl << endl;


	// vector<_Tp>(int size, _Tp val)：构造包含n个值为val元素的vector
	cout << "vector<_Tp>(int size, _Tp val)：构造包含n个值为val元素的vector" << endl;
	vector<int> vi3(3,10);					//构造一个设定容量为3，初值全为10的向量。
	vector<int> vi4 = vector<int>(8,14);	//上下两种实例化对象的语句是等效的。
	dispVector(vi3);
	dispVector(vi4);
	cout << endl;

	// 输入两个数组元素的指针，将范围内的元素放入vector:
	cout << "输入两个数组元素的指针，将范围内的元素放入vector:" << endl;
	int arr[] = {1,2,3,4,5,6,7,8,9};
	vector<int> vi5(arr,arr+9);
	dispVector(vi5);

	// 输入两个迭代器，将范围内的元素放入vector；
	cout << "输入两个迭代器，将范围内的元素放入vector；" << endl;
	vector<int>::iterator it1 = vi5.begin();
	vector<int>::iterator it2 = vi5.end();
	it1++;
	it2--;
	vector<int> vi6(it1,it2);
	dispVector(vi6);
	cout << endl;



}

// test3():vector访问、操作元素的成员方法。
void test3()
{
	cout << "test3():vector访问、操作单个元素的成员方法。" << endl << endl;

	// push_back():从末尾添加元素。
	vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);

	// pop_back():删除末尾的元素。
	cout << "pop_back():删除末尾的元素。" << endl;
	cout << "vi.pop_back()之前，输出vi:" << endl;
	dispVector(vi);
	vi.pop_back();
	cout << "vi.pop_back()之后，输出vi:" << endl;
	dispVector(vi);
	cout << endl;

	// T front():返回第一个元素的引用
	cout << "T front():返回第一个元素的引用：" << endl;
	cout << "vi.front() = " << vi.front() << endl;
	cout << endl;

	// T back():返回最后一个元素的引用：
	cout << "T back():返回最后一个元素的引用：" << endl;
	cout << "vi.back() = " << vi.back() << endl;
	cout << endl;

	// at(i): 返回元素的引用；这种方法比直接用下标访问安全，i越界时会抛出异常；
	cout << "at(i): 返回元素的引用；这种方法比直接用下标访问安全，i越界时会抛出异常；" << endl;
	cout << "vi.at(1) = " << vi.at(1) << endl;
	cout << "引用也可以使用自加自减运算符：++vi.at(1) = " << ++vi.at(1) << endl;
	cout << endl;



	// 插入元素insert();
    //		iterator insert(const_iterator position, const T& x);					插入单个元素
    //		iterator insert(const_iterator position, size_type n, const T& x);		插入多个相同元素
    //		template <class InputIterator>											从别的容器中选取一系列元素插入到本容器中的某位置。
    //    		iterator insert (const_iterator position, InputIterator first,
    // 		                    InputIterator last);  注意first和last必须是别的容器元素的迭代器，元素类型必须匹配。
    //		iterator insert(const_iterator position, initializer_list<T>);
	cout << "插入元素insert()" << endl;
	cout << "v.insert(v.begin(),88):插入单个元素" << endl;
	vector<int> v(3,0);
	dispVector(v);
	v.insert(v.begin(),88);
	dispVector(v);

	cout << "v.insert(iter,3,77):插入多个相同元素" << endl;
	vector<int>::iterator iter = v.begin();
	iter++;
	v.insert(iter,3,77);
	dispVector(v);

	cout << "v.insert(iter,it1,it2)：从别的容器中选取一系列元素插入到本容器中：" << endl;
	vector<int>::iterator it1,it2;
	it1 = vi.begin();
	it2 = vi.end();
	it1+=2;
	iter = v.begin()+3;
	v.insert(iter,it1,it2);
	dispVector(v);
	cout << endl;

}

//test4():vector的迭代器
void test4()
{
	cout << "test4():vector的迭代器" << endl << endl;

	vector<int>vi;
	vector<int>::iterator iter_i;
	vector<int>::const_iterator citer_i;

	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);
	vi.push_back(6);

	// 使用const_iterator来遍历vector中所有元素。
	cout << "use const_iterator to traverse all the items on the vector container:" << endl;
	for(citer_i = vi.begin(); citer_i != vi.end(); citer_i++)
	{cout << *citer_i << endl;}							//const_iterator只能访问元素，不可以修改元素。
	cout << endl;


	// 使用iterator来遍历vector中所有元素。
	// !!!遍历结束的flag → iter == v.end();
	cout << "use iterator to traverse all the items on the vector container:" << endl;
	for(iter_i = vi.begin(); iter_i != vi.end(); iter_i++)
	{cout << *iter_i << endl;}
	cout << endl;

	// 使用iterator来修改vector中的元素。
	cout << "use iterator to change the vector's item's value: " << endl;
	iter_i = vi.begin();								//迭代器指向第一个元素。
	*iter_i = -1;
	cout << "vi[0] == " << *iter_i << endl;
	iter_i++;
	*iter_i = -2;
	cout << "vi[1] == " << *iter_i << endl;
	iter_i += 1;
	*iter_i = -3;
	cout << "vi[2] == " << *iter_i << endl;
	cout << endl;

}

// test5():vector的其他成员方法。
void test5()
{
	//clear()：清空vector
	//swap()：两个vector对象之间的元素交换。

	vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);

	//empty()：返回bool值表示向量是否为空。
	cout << "empty()：返回bool值表示向量是否为空.   vi.empty() = " << vi.empty() << endl;
	cout << endl;

	//size():返回vector现有元素数。
	cout << "size():返回vector现有元素数。  vi.size() = " << vi.size() << endl;
	cout << endl;

	//capacity():返回vector当前容量，当vector超容时，容量会自动扩张为原来的两倍。容量对应于开辟的内存空间。
	cout << "capacity():返回vector当前容量，当vector超容时，容量会自动扩张为原来的两倍。容量对应于开辟的内存空间。" << endl;
	cout << "vi.capacity() = " << vi.capacity() << endl;
	cout << endl;

	//reserve():设定vector的容量即capacity
	cout << "" << endl;
	vi.reserve(8);
	cout << "vi.reserve(8)设定vector的容量即capacity; vi.capacity() = " << vi.capacity() << endl;

	//max_size():返回STL规定的vector最大能容纳的元素数。
	cout << "max_size():返回STL规定的vector最大能容纳的元素数。  vi.max_size() =  " << vi.max_size() << endl;
	cout << endl;
}

//test6()：获取容器的属性：
void test6()
{
	vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);

	cout<<"vi.size() = "<< vi.size()<< endl;					// 元素个数
	cout << "vi.empty() = "<< vi.empty()<< endl;				// 是否为空
	cout <<"vi.capacity() = " <<vi.capacity() <<endl;			// 容量

}


int main()
{
	//test1();
	//test2();
	test3();
	//test4();
	//test5();
	//test6();

	return 0;
}
